package com.cdgo.tools;

import android.os.Environment;

public class Dir {
    static public String sd_dir(){
        return Environment.getExternalStorageDirectory().toString();
    }
}
