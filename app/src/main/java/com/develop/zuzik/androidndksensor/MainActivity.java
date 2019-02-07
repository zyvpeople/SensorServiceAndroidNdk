package com.develop.zuzik.androidndksensor;

import android.os.Bundle;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.widget.TextView;

import com.develop.zuzik.androidndksensor.ndk.SensorService;
import com.develop.zuzik.androidndksensor.ndk.SensorServiceListener;
import com.develop.zuzik.androidndksensor.ndk.SensorType;
import com.develop.zuzik.androidndksensor.ndk.sensorEvent.SensorEvent;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.text);

        final SensorService sensorService = new SensorService();
        final int periodInMicroseconds = 100000;

        tv.setText(String.format(
                "Light sensor available: %b\nAccelerometer sensor available: %b",
                sensorService.sensorAvailable(SensorType.LIGHT),
                sensorService.sensorAvailable(SensorType.ACCELEROMETER)));

        sensorService.startListenSensor(SensorType.LIGHT, periodInMicroseconds, lightSensorServiceListener);
        sensorService.startListenSensor(SensorType.ACCELEROMETER, periodInMicroseconds, accelerometerSensorServiceListener);

        new Handler().postDelayed(
                new Runnable() {
                    @Override
                    public void run() {
                        sensorService.stopListenSensor(lightSensorServiceListener);
                    }
                },
                10000);
        new Handler().postDelayed(
                new Runnable() {
                    @Override
                    public void run() {
                        sensorService.stopListenSensor(accelerometerSensorServiceListener);
                    }
                },
                5000);
    }

    final SensorServiceListener lightSensorServiceListener = new SensorServiceListener() {
        @Override
        public void onSensorEvent(SensorEvent sensorEvent) {
            Log.d("Sensor", String.format("LightEvent: %s", sensorEvent));
        }

        @Override
        public void onSensorError(Throwable throwable) {
            Log.d("Sensor", String.format("Throwable: %s,", throwable));
        }
    };

    final SensorServiceListener accelerometerSensorServiceListener = new SensorServiceListener() {
        @Override
        public void onSensorEvent(SensorEvent sensorEvent) {
            Log.d("Sensor", String.format("AccelerometerEvent: %s", sensorEvent));
        }

        @Override
        public void onSensorError(Throwable throwable) {
            Log.d("Sensor", String.format("Throwable: %s,", throwable));
        }
    };
}
