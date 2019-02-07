#include <jni.h>
#include "javaClass/SensorServiceJavaClass.h"
#include "javaClass/SensorTypeJavaClass.h"
#include "javaClass/ExceptionJavaClass.h"
#include "sensorStrategy/AccelerometerStrategy.h"
#include <string>
#include <android/sensor.h>
#include <unistd.h>

extern "C" {

//region private

int sensorTypeNameToASensorTypeOrInvalid(const char *sensorTypeName) {
    //TODO:
    if (strcmp(sensorTypeName, "ACCELEROMETER") == 0) {
        return ASENSOR_TYPE_ACCELEROMETER;
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
    //TODO:
    switch (aSensorType) {
        case ASENSOR_TYPE_ACCELEROMETER: {
            return new AccelerometerStrategy(env);
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
        jvm->DetachCurrentThread();
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
        jvm->DetachCurrentThread();
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
        jvm->DetachCurrentThread();
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
        jvm->DetachCurrentThread();
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
        jvm->DetachCurrentThread();
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
    jvm->DetachCurrentThread();
}

//endregion

}

//TODO: delete

//void example(JNIEnv *env) {
//    JavaVM *g_jvm = NULL;
//    env->GetJavaVM(&g_jvm);
//    if(g_jvm->AttachCurrentThread(&env, NULL)) {
//        __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!", "Failed to AttachCurrentThread\n");
//        return;
//    }
//
//    const int kLooperId = 1;
//    ASensorManager *sensor_manager =
//            ASensorManager_getInstance();
//    if (!sensor_manager) {
//        __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!", "Failed to get a sensor manager\n");
//        return;
//    }
//    ASensorList sensor_list;
//    int sensor_count = ASensorManager_getSensorList(sensor_manager, &sensor_list);
//    __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!", "Found sensors\n");
//    for (int i = 0; i < sensor_count; i++) {
//        __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!", "Found\n");
//    }
//    ASensorEventQueue *queue = ASensorManager_createEventQueue(
//            sensor_manager,
//            ALooper_prepare(ALOOPER_PREPARE_ALLOW_NON_CALLBACKS),
//            kLooperId,
//            NULL /* no callback */,
//            NULL /* no data */);
//    if (!queue) {
//        __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!",
//                            "Failed to create a sensor event queue\n");
//        return;
//    }
//
//    const int kNumSamples = 100000;
//    const int kNumEvents = 1;
//    const int kTimeoutMilliSecs = 100;
//
//    const ASensor *sensor = ASensorManager_getDefaultSensor(sensor_manager,
//                                                            ASENSOR_TYPE_ACCELEROMETER);
//    if (sensor && !ASensorEventQueue_enableSensor(queue, sensor)) {
//        for (int i = 0; i < kNumSamples; i++) {
//
//            ALooper_pollAll(0,
//                            NULL /* no output file descriptor */,
//                            NULL /* no output event */,
//                            NULL /* no output data */);
//            ASensorEvent data;
//            if (ASensorEventQueue_getEvents(queue, &data, kNumEvents)) {
//                __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!",
//                                    "Acceleration: x = %f, y = %f, z = %f\n",
//                                    data.acceleration.x, data.acceleration.y, data.acceleration.z);
//            }
//            usleep(kTimeoutMilliSecs * 1000);
//        }
//        int ret = ASensorEventQueue_disableSensor(queue, sensor);
//        if (ret) {
//            __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!", "Failed to disable: \n");
//        }
//    } else {
//        __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!", "No found or failed to enable it\n");
//    }
//
//    int ret = ASensorManager_destroyEventQueue(sensor_manager, queue);
//    if (ret) {
//        __android_log_print(ANDROID_LOG_VERBOSE, "aaaa!!!!", "Failed to destroy event queue: \n");
//        return;
//    }
//
//    g_jvm->DetachCurrentThread();
//}