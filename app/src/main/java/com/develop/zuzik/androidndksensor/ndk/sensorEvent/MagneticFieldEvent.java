package com.develop.zuzik.androidndksensor.ndk.sensorEvent;

/**
 * yaroslavzozulia
 * 2/7/19.
 */
public class MagneticFieldEvent implements SensorEvent {
    public float x;
    public float y;
    public float z;

    @Override
    public String toString() {
        return "MagneticFieldEvent{" +
                "x=" + x +
                ", y=" + y +
                ", z=" + z +
                '}';
    }
}
