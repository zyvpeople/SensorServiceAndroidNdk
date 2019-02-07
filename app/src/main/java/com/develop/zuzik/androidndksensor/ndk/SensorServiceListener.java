package com.develop.zuzik.androidndksensor.ndk;

import com.develop.zuzik.androidndksensor.ndk.sensorEvent.SensorEvent;

/**
 * yaroslavzozulia
 * 2/7/19.
 */
public interface SensorServiceListener {

    void onSensorEvent(SensorEvent sensorEvent);

    void onSensorError(Throwable throwable);
}
