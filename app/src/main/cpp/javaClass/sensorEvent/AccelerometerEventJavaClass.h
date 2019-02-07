#include <jni.h>

class AccelerometerEventJavaClass {
private:
    jclass entityClass;
    jmethodID constructorMethodId;
    jfieldID xFieldId;
    jfieldID yFieldId;
    jfieldID zFieldId;
public:
    AccelerometerEventJavaClass(JNIEnv *env);

    jobject constructor(JNIEnv *env);

    void update(JNIEnv *env,
                jobject accelerometerEvent,
                float x,
                float y,
                float z);
};