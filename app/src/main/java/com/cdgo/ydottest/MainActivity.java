package com.cdgo.ydottest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

import com.cdgo.libydot.Constants;
import com.cdgo.libydot.Pen;
import com.cdgo.tools.Img;

import java.util.Locale;

public class MainActivity extends AppCompatActivity implements Pen.OnTouchListener {

    static private Pen _pen=new Pen();
    private String imagePath="/res/raw/a1.bmp";
    byte buf[]=null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Log.i(Constants.TAG, "onCreate()**********");
        setContentView(R.layout.activity_main);

        String s=_pen.getVersion()+"...";
        TextView tv=findViewById(R.id.idText);
        tv.setText(s);

        _pen.setOnTouchListener(this);

       buf= _pen.getImgRawData(this,imagePath);
    }

    @Override
    public void onTouch(boolean bTouch) {
        //Log.i(Constants.TAG,String.format(".%b",bTouch));
        //if(bTouch) //当点到纸面时蓝灯闪一下
         //   blueLightBlink();
    }

    @Override
    public void onRecognized(long id) {
        String msg=String.format(Locale.US,"image: %s ------> id: %d",imagePath,id);
        Log.i(Constants.TAG,msg);
        //点击辨识到码是 id
    }

    public void onTest(View view) {
        _pen.decode(buf);
    }
    //------------------------------------------

    private static final int STACK_TRACE_INDEX = 3;
    private static final String SUFFIX = ".java";
    @Override
    protected void onStart() {
        super.onStart();

        Log.i(Constants.TAG, "onStart()**********");
    }

    @Override
    protected void onResume() {
        super.onResume();

        Log.i(Constants.TAG, "onResume()**********");
    }
    //-----------------------------

    @Override
    protected void onPause() {
        super.onPause();
        Log.i(Constants.TAG, "onPause()**********");
    }

    @Override
    protected void onStop() {
        super.onStop();
        Log.i(Constants.TAG, "onStop()**********");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        Log.i(Constants.TAG, "onRestart()**********");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        Log.i(Constants.TAG, "onDestroy()**********");
    }

}
