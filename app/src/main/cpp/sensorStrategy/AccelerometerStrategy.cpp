#include "AccelerometerStrategy.h"

AccelerometerStrategy::AccelerometerStrategy(JNIEnv *env) {
    this->javaClass = new AccelerometerEventJavaClass(env);
}

AccelerometerStrategy::~AccelerometerStrategy() {
    delete this->javaClass;
}

jobject AccelerometerStrategy::createSensorEvent(JNIEnv *env) {
    return this->javaClass->constructor(env);
}

void AccelerometerStrategy::updateSensorEvent(JNIEnv *env,
                                              jobject sensorEvent,
                                              ASensorEvent *aSensorEvent) {
    this->javaClass->update(env,
                            sensorEvent,
                            aSensorEvent->acceleration.x,
                            aSensorEvent->acceleration.y,
                            aSensorEvent->acceleration.z);
}

