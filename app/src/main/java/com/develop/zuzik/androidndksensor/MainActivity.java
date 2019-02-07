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
        final SensorType sensorType = SensorType.LIGHT;
        final int periodInMicroseconds = 10000;
        final boolean sensorAvailable = sensorService.sensorAvailable(sensorType);
        tv.setText(String.valueOf(sensorAvailable));
        if (sensorAvailable) {
            new Thread(new Runnable() {
                @Override
                public void run() {
                    sensorService.startListenSensor(
                            sensorType,
                            periodInMicroseconds,
                            1);
                }
            }).start();
        }
    }
}
