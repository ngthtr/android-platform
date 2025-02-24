package com.example.api.aidl;

@VintfStability
interface IExampleListener {
    oneway void notifyEvent(in int number);
}