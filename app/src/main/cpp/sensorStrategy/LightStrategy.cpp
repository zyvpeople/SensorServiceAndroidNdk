#include "LightStrategy.h"

LightStrategy::LightStrategy(JNIEnv *env) {
    this->javaClass = new LightEventJavaClass(env);
}

LightStrategy::~LightStrategy() {
    delete this->javaClass;
}

jobject LightStrategy::createSensorEvent(JNIEnv *env) {
    return this->javaClass->constructor(env);
}

void LightStrategy::updateSensorEvent(JNIEnv *env,
                                      jobject sensorEvent,
                                      ASensorEvent *aSensorEvent) {
    this->javaClass->update(env,
                            sensorEvent,
                            aSensorEvent->light);
}

