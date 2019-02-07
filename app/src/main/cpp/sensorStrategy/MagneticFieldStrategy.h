#include <jni.h>
#include "../javaClass/sensorEvent/MagneticFieldEventJavaClass.h"
#include "SensorStrategy.h"

class MagneticFieldStrategy : public SensorStrategy {
private:
    MagneticFieldEventJavaClass *javaClass;
public:
    MagneticFieldStrategy(JNIEnv *env);

    ~MagneticFieldStrategy();

    jobject createSensorEvent(JNIEnv *env) override;

    void updateSensorEvent(JNIEnv *env, jobject sensorEvent, ASensorEvent *aSensorEvent) override;
};