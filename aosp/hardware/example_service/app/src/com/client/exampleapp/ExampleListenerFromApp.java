package com.client.exampleapp;

import android.os.Parcel;
import android.os.Parcelable;
import com.example.api.aidl.IExampleListener;
import android.util.Log;
import com.client.exampleapp.ExampleApp;

class ExampleListenerFromApp extends IExampleListener.Stub {
    private static final String TAG = "ExampleListenerFromApp";
    private ExampleApp.ExampleListenerFromActivity mListener;
    public ExampleListenerFromApp(ExampleApp.ExampleListenerFromActivity listener) {
        mListener = listener;
    }
    @Override
    public void notifyEvent(int number)
    {
        Log.d(TAG, "notifyEvent is called with number = " + number);
        if (mListener != null)
        {
            mListener.updateEditText(Integer.toString(number));
        }
    }
    @Override
    public int getInterfaceVersion()
    {
        return 0;
    };
    @Override
    public String getInterfaceHash()
    {
        return "";
    };
}