#include <jni.h>
#include "../javaClass/sensorEvent/AccelerometerEventJavaClass.h"

#ifndef _SensorStrategy_h_included_
#define _SensorStrategy_h_included_

#include "SensorStrategy.h"

#endif

class AccelerometerStrategy : public SensorStrategy {
private:
    AccelerometerEventJavaClass *javaClass;
public:
    AccelerometerStrategy(JNIEnv *env);

    ~AccelerometerStrategy();

    jobject createSensorEvent(JNIEnv *env) override;

    void updateSensorEvent(JNIEnv *env, jobject sensorEvent, ASensorEvent *aSensorEvent) override;
};