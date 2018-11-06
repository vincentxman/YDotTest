package com.cdgo.libydot;

import android.util.Log;

public class PenJni {
    static {
        System.loadLibrary("Ydot-lib");
    }

    public final native String getVersion();

    protected final native void decodeBuf(byte[] img);
    //----------------------------------------------
    //call back from JNI
    //When the pen point close to the coded paper. Not necessarily successful decoding.
    protected void cbTouch(boolean bTouch){
        if(bTouch){
            Log.d(Constants.TAG,"PenJni:cbTouch()");
        }
    }
    protected void cbRecognized(long id){
        Log.d(Constants.TAG,"PenJni:cbRecognized()");
    }
}
