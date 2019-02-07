#include <jni.h>

class MagneticFieldEventJavaClass {
private:
    jclass entityClass;
    jmethodID constructorMethodId;
    jfieldID xFieldId;
    jfieldID yFieldId;
    jfieldID zFieldId;
public:
    MagneticFieldEventJavaClass(JNIEnv *env);

    jobject constructor(JNIEnv *env);

    void update(JNIEnv *env,
                jobject accelerometerEvent,
                float x,
                float y,
                float z);
};