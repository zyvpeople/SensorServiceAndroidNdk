#include <jni.h>
#include "../javaClass/sensorEvent/AccelerometerEventJavaClass.h"
#include "SensorStrategy.h"

class AccelerometerStrategy : public SensorStrategy {
private:
    AccelerometerEventJavaClass *javaClass;
public:
    AccelerometerStrategy(JNIEnv *env);

    ~AccelerometerStrategy();

    jobject createSensorEvent(JNIEnv *env) override;

    void updateSensorEvent(JNIEnv *env, jobject sensorEvent, ASensorEvent *aSensorEvent) override;
};