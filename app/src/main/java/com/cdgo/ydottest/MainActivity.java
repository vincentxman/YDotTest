package com.cdgo.ydottest;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import com.cdgo.libydot.Pen;
import com.cdgo.tools.Img;

public class MainActivity extends AppCompatActivity implements Pen.OnTouchListener {

    static private Pen _pen=new Pen();

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
        Log.i("LibYdot",String.format("MainActivity:onTouch(%b)",bTouch));
    }

    @Override
    public void onRecognized(long id) {
        Log.i("LibYdot",String.format("MainActivity:onRecognized(%d)",id));
    }

    public void onTest(View view) {
        //step 1:
        _pen.decode(Img.getBmpRaw(this,"/res/raw/img10001.bmp"));
    }
}
