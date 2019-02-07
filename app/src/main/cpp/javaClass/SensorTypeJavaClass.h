#include <jni.h>

class SensorTypeJavaClass {
private:
    jclass entityClass;
    jmethodID nameMethodId;
public:
    SensorTypeJavaClass(JNIEnv *env);

    const char *name(JNIEnv *env,
                     jobject object);
};
