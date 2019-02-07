#include <jni.h>

class LightEventJavaClass {
private:
    jclass entityClass;
    jmethodID constructorMethodId;
    jfieldID illuminationFieldId;
public:
    LightEventJavaClass(JNIEnv *env);

    jobject constructor(JNIEnv *env);

    void update(JNIEnv *env,
                jobject accelerometerEvent,
                float illumination);
};