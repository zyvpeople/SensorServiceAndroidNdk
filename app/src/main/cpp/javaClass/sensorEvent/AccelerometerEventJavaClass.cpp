#include "AccelerometerEventJavaClass.h"

#define CONSTRUCTOR_METHOD_NAME "<init>"

#define ENTITY_CLASS "com/develop/zuzik/androidndksensor/ndk/sensorEvent/AccelerometerEvent"
#define CONSTRUCTOR_METHOD_SIGNATURE "()V"
#define X_FIELD_NAME "x"
#define X_FIELD_SIGNATURE "F"
#define Y_FIELD_NAME "y"
#define Y_FIELD_SIGNATURE "F"
#define Z_FIELD_NAME "z"
#define Z_FIELD_SIGNATURE "F"

AccelerometerEventJavaClass::AccelerometerEventJavaClass(JNIEnv *env) {
    this->entityClass = env->FindClass(ENTITY_CLASS);
    this->constructorMethodId = env->GetMethodID(this->entityClass,
                                                 CONSTRUCTOR_METHOD_NAME,
                                                 CONSTRUCTOR_METHOD_SIGNATURE);
    this->xFieldId = env->GetFieldID(this->entityClass,
                                     X_FIELD_NAME,
                                     X_FIELD_SIGNATURE);
    this->yFieldId = env->GetFieldID(this->entityClass,
                                     Y_FIELD_NAME,
                                     Y_FIELD_SIGNATURE);
    this->zFieldId = env->GetFieldID(this->entityClass,
                                     Z_FIELD_NAME,
                                     Z_FIELD_SIGNATURE);
}

jobject AccelerometerEventJavaClass::constructor(JNIEnv *env) {
    return env->NewObject(this->entityClass,
                          this->constructorMethodId);
}

void AccelerometerEventJavaClass::update(JNIEnv *env,
                                         jobject accelerometerEvent,
                                         float x,
                                         float y,
                                         float z) {
    env->SetFloatField(accelerometerEvent, this->xFieldId, x);
    env->SetFloatField(accelerometerEvent, this->yFieldId, y);
    env->SetFloatField(accelerometerEvent, this->zFieldId, z);
}
