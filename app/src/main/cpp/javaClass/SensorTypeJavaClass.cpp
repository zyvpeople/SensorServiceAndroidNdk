#include "SensorTypeJavaClass.h"

#define ENTITY_CLASS "com/develop/zuzik/androidndksensor/ndk/SensorType"
#define NAME_METHOD_NAME "name"
#define NAME_METHOD_SIGNATURE "()Ljava/lang/String;"

SensorTypeJavaClass::SensorTypeJavaClass(JNIEnv *env) {
    this->entityClass = env->FindClass(ENTITY_CLASS);
    this->nameMethodId = env->GetMethodID(this->entityClass,
                                          NAME_METHOD_NAME,
                                          NAME_METHOD_SIGNATURE);
}

const char *SensorTypeJavaClass::name(JNIEnv *env,
                                      jobject object) {
    jstring value = (jstring) env->CallObjectMethod(object,
                                                    nameMethodId);
    return env->GetStringUTFChars(value, 0);
}