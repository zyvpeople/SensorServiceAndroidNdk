#include <jni.h>
#include "../javaClass/sensorEvent/LightEventJavaClass.h"
#include "SensorStrategy.h"

class LightStrategy : public SensorStrategy {
private:
    LightEventJavaClass *javaClass;
public:
    LightStrategy(JNIEnv *env);

    ~LightStrategy();

    jobject createSensorEvent(JNIEnv *env) override;

    void updateSensorEvent(JNIEnv *env, jobject sensorEvent, ASensorEvent *aSensorEvent) override;
};