package com.cdgo.libydot;

import android.graphics.Bitmap;

import com.cdgo.tools.Img;

public class Pen extends PenJni {

    final private boolean bUseTread = true;//使用线程发送

    public interface OnTouchListener {
        void onTouch(boolean bTouch);

        void onRecognized(long id);
    }

    public enum Type {
        TOUCH, RECOGNIZED
    }

    protected class DoThread implements Runnable {
        private Type m_type;
        private long m_id;
        private boolean m_bTouch;
        private OnTouchListener _touchListener = null;

        public DoThread(Type type, long id, boolean bTouch, OnTouchListener listener) {
            m_type = type;
            m_id = id;
            m_bTouch = bTouch;
            _touchListener = listener;
        }

        public void run() {
            if (_touchListener == null)
                return;
            if (m_type == Type.TOUCH) {
                _touchListener.onTouch(m_bTouch);
            } else if (m_type == Type.RECOGNIZED) {
                _touchListener.onRecognized(m_id);
            }
        }
    }

    private OnTouchListener _touchListener = null;

    public void setOnTouchListener(OnTouchListener touchListener) {
        _touchListener = touchListener;
    }

    //-------------------------------------------------------------
    //只读一个码
    public void decode(byte[] data) {
        decodeBuf(data, false);
    }

    //点读, 连续解同样的码时只返回一次.
    public void decodeLoop(byte[] data) {
        decodeBuf(data, true);
    }

    public byte[] getImgRawData(Object obj, String pathName) {
        Bitmap bmp = Img.getBmpRaw(obj, pathName);
        if (bmp == null)
            return null;
        return captureImg(bmp);
    }

    //call back
    @Override
    protected void cbTouch(boolean bTouch) {

        if (bUseTread) {
            DoThread doT = new DoThread(Type.TOUCH, 0, bTouch, _touchListener);
            Thread thread = new Thread(doT);
            thread.start();
        } else {
            _touchListener.onTouch(bTouch);
        }

    }

    @Override
    protected void cbRecognized(long id) {
        if (bUseTread) {
            DoThread doT = new DoThread(Type.RECOGNIZED, id, false, _touchListener);
            Thread thread = new Thread(doT);
            thread.start();
        } else {
            _touchListener.onRecognized(id);
        }
    }

    //private
    private byte[] captureImg(Bitmap bmp) {
        int cx = bmp.getWidth();
        int cy = bmp.getHeight();
        byte[] data = new byte[cx * cy];

        for (int y = 0; y < cy; y++) {
            for (int x = 0; x < cx; x++) {
                int clr = bmp.getPixel(x, y);
                byte R = ((byte) ((clr >> 16) & 0xFF));
                byte G = ((byte) ((clr >> 8) & 0xFF));
                byte B = ((byte) ((clr) & 0xFF));
                data[y * cx + x] = (byte) (R * 0.299 + G * 0.587 + B * 0.114);
            }
        }
        return data;
    }
}
