package com.develop.zuzik.androidndksensor.ndk.sensorEvent;

/**
 * yaroslavzozulia
 * 2/6/19.
 */
public class AccelerometerEvent implements SensorEvent {
    public float x;
    public float y;
    public float z;

    @Override
    public String toString() {
        return "AccelerometerEvent{" +
                "x=" + x +
                ", y=" + y +
                ", z=" + z +
                '}';
    }
}
