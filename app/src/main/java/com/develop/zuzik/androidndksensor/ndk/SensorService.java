package com.develop.zuzik.androidndksensor.ndk;

import android.util.Log;

import com.develop.zuzik.androidndksensor.ndk.sensorEvent.SensorEvent;

/**
 * yaroslavzozulia
 * 2/1/19.
 */
public class SensorService {

    static {
        System.loadLibrary("sensorService");
    }

    public native boolean sensorAvailable(SensorType sensorType);

    public native void startListenSensor(SensorType sensorType,
                                         int periodInMicroseconds,
                                         int listenerId);

    boolean onSensorEvent(SensorEvent sensorEvent,
                          int listenerId) {
        Log.d("aaaa", String.format("Id: %d, Event: %s", listenerId, sensorEvent));
        return true;
    }

    void onSensorError(Exception exception,
                       int listenerId) {
        Log.d("aaaa", String.format("Id: %d, Error: %s,", listenerId, exception));
    }
}
