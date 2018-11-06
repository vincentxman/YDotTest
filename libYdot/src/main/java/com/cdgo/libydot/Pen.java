package com.cdgo.libydot;

import android.graphics.Bitmap;

public class Pen extends PenJni {
    public interface OnTouchListener {
        void onTouch(boolean bTouch);
        void onRecognized(long id);
    }
    private OnTouchListener _touchListener=null;
    public void setOnTouchListener(OnTouchListener touchListener){
        _touchListener=touchListener;
    }
    //-------------------------------------------------------------
    public void decode(Bitmap bmp){
        if(bmp==null)
            return;

        byte[] data=captureImg(bmp);
        decodeBuf(data);
    }

    //call back
    @Override
    protected void cbTouch(boolean bTouch){
        if(_touchListener!=null)
            _touchListener.onTouch(bTouch);
    }

    @Override
    protected void cbRecognized(long id){
        if(_touchListener!=null)
            _touchListener.onRecognized(id);
    }

    //private
    private byte[] captureImg(Bitmap bmp){
        int cx=bmp.getWidth();
        int cy=bmp.getHeight();
        byte[] data=new byte[cx*cy];

        for(int y=0;y<cy;y++){
            for(int x=0;x<cx;x++){
                int clr=bmp.getPixel(x,y);
                byte R=((byte)((clr>>16	)&0xFF));
                byte G=((byte)((clr>>8	)&0xFF));
                byte B=((byte)((clr		)&0xFF));
                data[y*cx+x]=(byte)(R*0.299 + G*0.587 + B*0.114);
            }
        }
        return data;
    }
}
