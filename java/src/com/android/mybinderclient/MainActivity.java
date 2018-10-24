package com.android.mybinderclient;

import android.app.Activity;
import android.app.ActivityManager;
import android.os.Bundle;
import android.os.IBinder;
import android.os.ServiceManager;
import android.os.RemoteException;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;
import java.io.IOException;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;


public class MainActivity extends Activity implements OnClickListener {
    private final static String TAG = "MainActivity";
    private Button mTestButton;
    private TextView mInfoText;

    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.main_activity);

        mTestButton = (Button)findViewById(R.id.test_button);
        mTestButton.setOnClickListener(this);

        mInfoText = (TextView)findViewById(R.id.info_text);
    }

    public void onClick(View view) {
        switch (view.getId()) {
            case R.id.test_button: {
                IBinder binder = ServiceManager.getService("com.android.mybinderclient.IMyService");
                if (binder == null) {
                    Log.d(TAG, "Failed to get the MyService binder object");
                    break;
                }

                IMyService service = IMyService.Stub.asInterface(binder);
                if (binder == null) {
                    Log.d(TAG, "Failed to get the MyService service");
                    break;
                }

                try {
                    //int v1 = service.getInt();
                    //mInfoText.setText(v1);

                    service.sendInt(2);

                    String str2 = service.getString();
                    Log.d(TAG, "******** str2:" + str2);
                    mInfoText.setText(str2);
                } catch (RemoteException e) {
                    Log.e(TAG, "error in onClick", e);
                }

                break;
            }
        }
    }
}
