package com.develop.zuzik.androidndksensor.ndk;

import com.develop.zuzik.androidndksensor.ndk.sensorEvent.SensorEvent;

import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ConcurrentMap;

/**
 * yaroslavzozulia
 * 2/1/19.
 */
public class SensorService {

    static {
        System.loadLibrary("sensorService");
    }

    private final ConcurrentMap<Integer, SensorServiceListener> listeners = new ConcurrentHashMap<>();

    public void startListenSensor(final SensorType sensorType,
                                  final int periodInMicroseconds,
                                  SensorServiceListener sensorServiceListener) {
        final int key = sensorServiceListener.hashCode();
        listeners.put(key, sensorServiceListener);
        new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    startListenSensor(sensorType, periodInMicroseconds, key);
                } catch (Exception e) {
                    onSensorError(e, key);
                }
            }
        }).start();
    }

    public void stopListenSensor(SensorServiceListener sensorServiceListener) {
        listeners.remove(sensorServiceListener.hashCode());
    }

    //region native

    public native boolean sensorAvailable(SensorType sensorType);

    native void startListenSensor(SensorType sensorType,
                                  int periodInMicroseconds,
                                  int listenerId);

    //endregion

    //region native callback

    boolean onSensorEvent(SensorEvent sensorEvent,
                          int listenerId) {
        SensorServiceListener sensorServiceListener = listeners.get(listenerId);
        if (sensorServiceListener != null) {
            sensorServiceListener.onSensorEvent(sensorEvent);
            return true;
        }
        return false;
    }

    void onSensorError(Exception exception,
                       int listenerId) {
        SensorServiceListener sensorServiceListener = listeners.remove(listenerId);
        if (sensorServiceListener != null) {
            sensorServiceListener.onSensorError(exception);
        }
    }

    //endregion
}
