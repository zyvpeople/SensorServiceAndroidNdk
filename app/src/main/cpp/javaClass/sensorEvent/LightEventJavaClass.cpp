#include "LightEventJavaClass.h"

#define CONSTRUCTOR_METHOD_NAME "<init>"

#define ENTITY_CLASS "com/develop/zuzik/androidndksensor/ndk/sensorEvent/LightEvent"
#define CONSTRUCTOR_METHOD_SIGNATURE "()V"
#define ILLUMINATION_FIELD_NAME "illumination"
#define ILLUMINATION_FIELD_SIGNATURE "F"

LightEventJavaClass::LightEventJavaClass(JNIEnv *env) {
    this->entityClass = env->FindClass(ENTITY_CLASS);
    this->constructorMethodId = env->GetMethodID(this->entityClass,
                                                 CONSTRUCTOR_METHOD_NAME,
                                                 CONSTRUCTOR_METHOD_SIGNATURE);
    this->illuminationFieldId = env->GetFieldID(this->entityClass,
                                                ILLUMINATION_FIELD_NAME,
                                                ILLUMINATION_FIELD_SIGNATURE);
}

jobject LightEventJavaClass::constructor(JNIEnv *env) {
    return env->NewObject(this->entityClass,
                          this->constructorMethodId);
}

void LightEventJavaClass::update(JNIEnv *env,
                                 jobject accelerometerEvent,
                                 float illumination) {
    env->SetFloatField(accelerometerEvent, this->illuminationFieldId, illumination);
}
