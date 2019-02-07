#include "SensorServiceJavaClass.h"

#define ENTITY_CLASS "com/develop/zuzik/androidndksensor/ndk/SensorService"
#define ON_SENSOR_EVENT_METHOD_NAME "onSensorEvent"
#define ON_SENSOR_EVENT_METHOD_SIGNATURE "(Lcom/develop/zuzik/androidndksensor/ndk/sensorEvent/SensorEvent;I)Z"
#define ON_SENSOR_ERROR_METHOD_NAME "onSensorError"
#define ON_SENSOR_ERROR_METHOD_SIGNATURE "(Ljava/lang/Exception;I)V"

SensorServiceJavaClass::SensorServiceJavaClass(JNIEnv *env) {
    this->entityClass = env->FindClass(ENTITY_CLASS);
    this->onSensorEventMethodId = env->GetMethodID(this->entityClass,
                                                   ON_SENSOR_EVENT_METHOD_NAME,
                                                   ON_SENSOR_EVENT_METHOD_SIGNATURE);
    this->onSensorErrorMethodId = env->GetMethodID(this->entityClass,
                                                   ON_SENSOR_ERROR_METHOD_NAME,
                                                   ON_SENSOR_ERROR_METHOD_SIGNATURE);
}

bool SensorServiceJavaClass::onSensorEvent(JNIEnv *env,
                                           jobject sensorService,
                                           jobject sensorEvent,
                                           jint listenerId) {
    return env->CallBooleanMethod(sensorService,
                                  this->onSensorEventMethodId,
                                  sensorEvent,
                                  listenerId);
}

void SensorServiceJavaClass::onSensorError(JNIEnv *env,
                                           jobject sensorService,
                                           jobject exception,
                                           jint listenerId) {
    env->CallVoidMethod(sensorService,
                        this->onSensorErrorMethodId,
                        exception,
                        listenerId);
}