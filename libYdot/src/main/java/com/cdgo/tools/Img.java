package com.cdgo.tools;

import android.content.ContextWrapper;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;

public class Img extends Dir {
    //Bitmap bmp1=Img.getBmpSD("img10002.bmp");
    static public Bitmap getBmpSD(String pathName){
        String filePath=sd_dir()+"/"+pathName;
        return BitmapFactory.decodeFile(filePath, null);
    }

    //Bitmap bmp2=getBmpRes(this,R.drawable.ic_launcher);
    static public Bitmap getBmpRes(ContextWrapper context, int resId){
        return BitmapFactory.decodeResource(context.getResources(), resId);
    }

    //Bitmap bmp3=getBmpRaw(this,"/res/raw/img10001.bmp");
    static public Bitmap getBmpRaw(Object obj,String pathName){
        return BitmapFactory.decodeStream(obj.getClass().getResourceAsStream(pathName));
    }
}
