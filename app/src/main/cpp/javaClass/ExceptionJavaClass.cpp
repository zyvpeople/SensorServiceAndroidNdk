#include "ExceptionJavaClass.h"

#define CONSTRUCTOR_METHOD_NAME "<init>"

#define EXCEPTION_CLASS "java/lang/Exception"
#define EXCEPTION_CONSTRUCTOR_METHOD_SIGNATURE "(Ljava/lang/String;)V"

ExceptionJavaClass::ExceptionJavaClass(JNIEnv *env) {
    this->entityClass = env->FindClass(EXCEPTION_CLASS);
    this->constructorMethodId = env->GetMethodID(this->entityClass,
                                                 CONSTRUCTOR_METHOD_NAME,
                                                 EXCEPTION_CONSTRUCTOR_METHOD_SIGNATURE);
}

jobject ExceptionJavaClass::constructor(JNIEnv *env,
                                        const char *message) {
    return env->NewObject(this->entityClass,
                          this->constructorMethodId,
                          env->NewStringUTF(message));
}