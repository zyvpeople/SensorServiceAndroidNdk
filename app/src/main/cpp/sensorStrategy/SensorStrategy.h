#include <jni.h>
#include <android/sensor.h>

class SensorStrategy {
public:
    virtual jobject createSensorEvent(JNIEnv *env) = 0;

    virtual void updateSensorEvent(JNIEnv *env,
                                   jobject sensorEvent,
                                   ASensorEvent *aSensorEvent) = 0;
};