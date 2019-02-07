package com.develop.zuzik.androidndksensor;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.widget.TextView;

import com.develop.zuzik.androidndksensor.ndk.SensorService;
import com.develop.zuzik.androidndksensor.ndk.SensorType;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = (TextView) findViewById(R.id.sample_text);

        final SensorService sensorService = new SensorService();
        boolean sensorAvailable = sensorService.sensorAvailable(SensorType.MAGNETIC_FIELD);
        tv.setText(String.valueOf(sensorAvailable));
        if (sensorAvailable) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    sensorService.startListenSensor(
                            SensorType.MAGNETIC_FIELD,
                            10000,
                            1);
                }
            }).start();
        }
//
//        SensorManager service = (SensorManager) getSystemService(SENSOR_SERVICE);
//        service.registerListener(
//                new SensorEventListener() {
//                    @Override
//                    public void onSensorChanged(SensorEvent event) {
//                        float[] v = event.values;
//                        Log.d("aaaa", String.format("%f %f %f", v[0], v[1], v[2]));
//                    }
//
//                    @Override
//                    public void onAccuracyChanged(android.hardware.Sensor sensor, int accuracy) {
//
//                    }
//                },
//                service.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD),
//                SensorManager.SENSOR_DELAY_NORMAL);
    }
}
