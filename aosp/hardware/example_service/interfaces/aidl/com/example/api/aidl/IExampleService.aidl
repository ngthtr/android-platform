package com.example.api.aidl;
import com.example.api.aidl.IExampleListener;

@VintfStability
interface IExampleService {
    oneway void registerListener(in IExampleListener listener);
    oneway void unregisterListener(in IExampleListener listener);
    oneway void readDeviceFile();
    oneway void writeDeviceFile(in String data);
}
