package com.client.exampleapp;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.widget.Button;
import android.widget.EditText;
import android.view.View;
import com.example.api.aidl.IExampleService;
import com.example.api.aidl.IExampleListener;
import android.os.ServiceManager;
import android.os.IBinder;
import com.client.exampleapp.ExampleListenerFromApp;

public class ExampleApp extends Activity {
    private static final String TAG = "ExampleApp";
    private Button btn_register, btn_unregister, btn_read, btn_write;
    private EditText ev_text;
    private ExampleListenerFromApp mExampleListener;
    private IExampleService mExampleService;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        ev_text = (EditText)findViewById(R.id.editText);
        btn_register = (Button)findViewById(R.id.button1);
        btn_unregister = (Button)findViewById(R.id.button2);
        btn_read = (Button)findViewById(R.id.button3);
        btn_write = (Button)findViewById(R.id.button4);

        btn_register.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d(TAG, "RegisterListener button is clicked");
                registerListener();
            }
        });
        btn_unregister.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d(TAG, "UnregisterListener button is clicked");
                unregisterListener();
            }
        });
        btn_read.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d(TAG, "Read button is clicked");
                readDeviceFile();
            }
        });
        btn_write.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Log.d(TAG, "Write button is clicked");
                writeDeviceFile();
            }
        });

        init();
    }

    @Override
    protected void onStart() {
        super.onStart();
    }

    private void init() {
        final String instance = "com.example.api.aidl.IExampleService/default";
        IBinder binder = ServiceManager.getService(instance);
        if (binder == null)
        {
            Log.d(TAG, "Binder is null");
            return;
        }
        Log.d(TAG, "Get Binder is successfully");

        mExampleService = IExampleService.Stub.asInterface(binder);
        if (mExampleService == null)
        {
            Log.d(TAG, "mExampleService is null");
            return;
        }
        Log.d(TAG, "mExampleService is got successfully");

        mExampleListener = new ExampleListenerFromApp(new ExampleListenerFromActivity());
        if (mExampleListener == null) 
        {
            Log.d(TAG, "mExampleListener is null");
            return;
        }
        Log.d(TAG, "mExampleListener is got successfully");
    }

    private void registerListener()
    {
        if (mExampleService == null)
        {
            Log.d(TAG, "mExampleService is null, can't call RegisterListener()");
            return;
        }
        if (mExampleListener == null)
        {
            Log.d(TAG, "mExampleListener is null, can't call RegisterListener()");
            return;
        }
        try {
            mExampleService.registerListener(mExampleListener);
            Log.d(TAG, "Call method registerListener successfully");
        } catch (android.os.RemoteException e) {
            Log.e(TAG, "CallR method registerListener failed", e);
        }
    }

    private void unregisterListener()
    {
        if (mExampleService == null)
        {
            Log.d(TAG, "mExampleService is null, can't call unregisterListener()");
            return;
        }
        if (mExampleListener == null)
        {
            Log.d(TAG, "mExampleListener is null, can't call unregisterListener()");
            return;
        }
        try {
            mExampleService.unregisterListener(mExampleListener);
            Log.d(TAG, "Call method unregisterListener successfully");
        } catch (android.os.RemoteException e) {
            Log.e(TAG, "Call method unregisterListener failed", e);
        }
    }

    private void readDeviceFile()
    {
        if (mExampleService == null)
        {
            Log.d(TAG, "mExampleService is null, can't call readDeviceFile()");
            return;
        }
        
        try {
            mExampleService.readDeviceFile();
            Log.d(TAG, "Call method readDeviceFile successfully");
        } catch (android.os.RemoteException e) {
            Log.e(TAG, "Call method readDeviceFile failed", e);
        }
    }

    private void writeDeviceFile() 
    {
        if (mExampleService == null)
        {
            Log.d(TAG, "mExampleService is null, can't call writeDeviceFile()");
            return;
        }
        String text = ev_text.getText().toString();
        try {
            mExampleService.writeDeviceFile(text);
            Log.d(TAG, "Call method writeDeviceFile successfully");
        } catch (android.os.RemoteException e) {
            Log.e(TAG, "Call method writeDeviceFile failed", e);
        }
    }

    public class ExampleListenerFromActivity {
        public void updateEditText(String text) {
            Log.d(TAG, "Update text = " + text);
            ev_text.setText(text);
        }
    }
}
