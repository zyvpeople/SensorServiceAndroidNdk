#include <jni.h>

class ExceptionJavaClass {
private:
    jclass entityClass;
    jmethodID constructorMethodId;
public:
    ExceptionJavaClass(JNIEnv *env);

    jobject constructor(JNIEnv *env,
                        const char *message);
};