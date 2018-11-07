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
    String imagePath="";
    int idx=1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        String s=_pen.getVersion()+"...";
        TextView tv=findViewById(R.id.idText);
        tv.setText(s);

        _pen.setOnTouchListener(this);
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
        //step 1:
        idx=1;
        imagePath=String.format(Locale.US,"/res/raw/a%d.bmp",idx++);
        idx%=10;
        if(idx==0)
            idx=1;

        Log.d(Constants.TAG,imagePath+"........");
        _pen.decode(Img.getBmpRaw(this,imagePath));
    }
}
