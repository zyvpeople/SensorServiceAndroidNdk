#include <jni.h>

class SensorServiceJavaClass {
private:
    jclass entityClass;
    jmethodID onSensorEventMethodId;
    jmethodID onSensorErrorMethodId;
public:
    SensorServiceJavaClass(JNIEnv *env);

    bool onSensorEvent(JNIEnv *env,
                       jobject sensorService,
                       jobject sensorEvent,
                       jint listenerId);

    void onSensorError(JNIEnv *env,
                       jobject sensorService,
                       jobject exception,
                       jint listenerId);

};