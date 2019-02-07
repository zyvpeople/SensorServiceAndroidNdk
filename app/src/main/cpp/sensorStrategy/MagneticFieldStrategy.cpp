#include "MagneticFieldStrategy.h"

MagneticFieldStrategy::MagneticFieldStrategy(JNIEnv *env) {
    this->javaClass = new MagneticFieldEventJavaClass(env);
}

MagneticFieldStrategy::~MagneticFieldStrategy() {
    delete this->javaClass;
}

jobject MagneticFieldStrategy::createSensorEvent(JNIEnv *env) {
    return this->javaClass->constructor(env);
}

void MagneticFieldStrategy::updateSensorEvent(JNIEnv *env,
                                              jobject sensorEvent,
                                              ASensorEvent *aSensorEvent) {
    this->javaClass->update(env,
                            sensorEvent,
                            aSensorEvent->magnetic.x,
                            aSensorEvent->magnetic.y,
                            aSensorEvent->magnetic.z);
}

