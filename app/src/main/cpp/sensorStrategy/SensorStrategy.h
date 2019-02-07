#include <jni.h>
#include <android/sensor.h>

#ifndef _SensorStrategy_h_included_
#define _SensorStrategy_h_included_

class SensorStrategy {
public:
    virtual jobject createSensorEvent(JNIEnv *env) = 0;

    virtual void updateSensorEvent(JNIEnv *env,
                                   jobject sensorEvent,
                                   ASensorEvent *aSensorEvent) = 0;
};

#endif
