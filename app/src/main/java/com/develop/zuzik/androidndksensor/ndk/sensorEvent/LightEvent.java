package com.develop.zuzik.androidndksensor.ndk.sensorEvent;

/**
 * yaroslavzozulia
 * 2/7/19.
 */
public class LightEvent implements SensorEvent {
    public float illumination;

    @Override
    public String toString() {
        return "LightEvent{" +
                "illumination=" + illumination +
                '}';
    }
}
