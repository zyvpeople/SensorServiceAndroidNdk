#include <jni.h>
#include "javaClass/SensorServiceJavaClass.h"
#include "javaClass/SensorTypeJavaClass.h"
#include "javaClass/ExceptionJavaClass.h"
#include "sensorStrategy/AccelerometerStrategy.h"
#include "sensorStrategy/MagneticFieldStrategy.h"
#include "sensorStrategy/LightStrategy.h"
#include <string>
#include <android/sensor.h>
#include <unistd.h>

extern "C" {

//region private

int sensorTypeNameToASensorTypeOrInvalid(const char *sensorTypeName) {
    if (strcmp(sensorTypeName, "ACCELEROMETER") == 0) {
        return ASENSOR_TYPE_ACCELEROMETER;
    } else if (strcmp(sensorTypeName, "MAGNETIC_FIELD") == 0) {
        return ASENSOR_TYPE_MAGNETIC_FIELD;
    } else if (strcmp(sensorTypeName, "LIGHT") == 0) {
        return ASENSOR_TYPE_LIGHT;
    } else {
        return ASENSOR_TYPE_INVALID;
    }
}

int sensorTypeToASensorTypeOrInvalid(JNIEnv *env,
                                     jobject sensorType) {
    SensorTypeJavaClass sensorTypeJavaClass(env);
    const char *name = sensorTypeJavaClass.name(env,
                                                sensorType);
    return sensorTypeNameToASensorTypeOrInvalid(name);
}

SensorStrategy *createSensorStrategyOrNull(JNIEnv *env,
                                           int aSensorType) {
    switch (aSensorType) {
        case ASENSOR_TYPE_ACCELEROMETER: {
            return new AccelerometerStrategy(env);
        }
        case ASENSOR_TYPE_MAGNETIC_FIELD: {
            return new MagneticFieldStrategy(env);
        }
        case ASENSOR_TYPE_LIGHT: {
            return new LightStrategy(env);
        }
        default:
            return NULL;
    }
}

//endregion

//region public

JNIEXPORT
jboolean JNICALL
Java_com_develop_zuzik_androidndksensor_ndk_SensorService_sensorAvailable(JNIEnv *env,
                                                                          jobject,
                                                                          jobject sensorType) {
    int aSensorType = sensorTypeToASensorTypeOrInvalid(env,
                                                       sensorType);
    if (aSensorType == ASENSOR_TYPE_INVALID) {
        return JNI_FALSE;
    }
    ASensorManager *sensorManager = ASensorManager_getInstance();
    const ASensor *sensor = ASensorManager_getDefaultSensor(sensorManager,
                                                            aSensorType);
    if (sensor == NULL) {
        return JNI_FALSE;
    }
    return JNI_TRUE;
}

JNIEXPORT void JNICALL
Java_com_develop_zuzik_androidndksensor_ndk_SensorService_startListenSensor(JNIEnv *env,
                                                                            jobject instance,
                                                                            jobject sensorType,
                                                                            jint periodInMicroseconds,
                                                                            jint listenerId) {
    JavaVM *jvm = NULL;
    env->GetJavaVM(&jvm);
    jvm->AttachCurrentThread(&env, NULL);
    SensorServiceJavaClass sensorServiceJavaClass(env);
    ExceptionJavaClass exceptionJavaClass(env);
    int aSensorType = sensorTypeToASensorTypeOrInvalid(env,
                                                       sensorType);
    if (aSensorType == ASENSOR_TYPE_INVALID) {
        jobject exception = exceptionJavaClass.constructor(env,
                                                           "Sensor type is not found");
        sensorServiceJavaClass.onSensorError(env,
                                             instance,
                                             exception,
                                             listenerId);
        return;
    }
    SensorStrategy *sensorStrategy = createSensorStrategyOrNull(env,
                                                                aSensorType);
    if (sensorStrategy == NULL) {
        jobject exception = exceptionJavaClass.constructor(env,
                                                           "Sensor strategy is not created");
        sensorServiceJavaClass.onSensorError(env,
                                             instance,
                                             exception,
                                             listenerId);
        return;
    }
    ASensorManager *sensorManager = ASensorManager_getInstance();
    const ASensor *aSensor = ASensorManager_getDefaultSensor(sensorManager,
                                                             aSensorType);
    if (aSensor == NULL) {
        jobject exception = exceptionJavaClass.constructor(env,
                                                           "Sensor is not found");
        sensorServiceJavaClass.onSensorError(env,
                                             instance,
                                             exception,
                                             listenerId);
        delete sensorStrategy;
        return;
    }
    ASensorEventQueue *queue = ASensorManager_createEventQueue(
            sensorManager,
            ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS),
            1,
            NULL,
            NULL);
    if (queue == NULL) {
        jobject exception = exceptionJavaClass.constructor(env,
                                                           "Sensor event queue is not created");
        sensorServiceJavaClass.onSensorError(env,
                                             instance,
                                             exception,
                                             listenerId);
        delete sensorStrategy;
        return;
    }

    int enableSensorStatus = ASensorEventQueue_enableSensor(queue, aSensor);
    if (enableSensorStatus != 0) {
        jobject exception = exceptionJavaClass.constructor(env,
                                                           "Sensor is not enabled");
        sensorServiceJavaClass.onSensorError(env,
                                             instance,
                                             exception,
                                             listenerId);
        ASensorManager_destroyEventQueue(sensorManager,
                                         queue);
        delete sensorStrategy;
        return;
    }
    ASensorEventQueue_setEventRate(queue,
                                   aSensor,
                                   periodInMicroseconds);
    bool listenSensor = true;
    jobject event = sensorStrategy->createSensorEvent(env);
    while (listenSensor) {
        ALooper_pollAll(0,
                        NULL,
                        NULL,
                        NULL);
        ASensorEvent aSensorEvent;
        ssize_t numberOrEvents = ASensorEventQueue_getEvents(queue,
                                                             &aSensorEvent,
                                                             1);
        if (numberOrEvents < 0) {
            usleep(periodInMicroseconds);
            continue;
        }
        sensorStrategy->updateSensorEvent(env,
                                          event,
                                          &aSensorEvent);
        listenSensor = sensorServiceJavaClass.onSensorEvent(env,
                                                            instance,
                                                            event,
                                                            listenerId);
        usleep(periodInMicroseconds);
    }
    ASensorEventQueue_disableSensor(queue,
                                    aSensor);
    ASensorManager_destroyEventQueue(sensorManager,
                                     queue);
    delete sensorStrategy;
}

//endregion

}