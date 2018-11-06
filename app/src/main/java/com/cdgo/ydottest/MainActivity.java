package com.cdgo.ydottest;

import android.content.Intent;
import android.net.Uri;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import com.cdgo.libydot.PenJni;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        // ATTENTION: This was auto-generated to handle app links.
//        Intent appLinkIntent = getIntent();
//        String appLinkAction = appLinkIntent.getAction();
//        Uri appLinkData = appLinkIntent.getData();

        PenJni pj=new PenJni();
        String s=pj.stringFromJNI()+"...";
        TextView tv=findViewById(R.id.idText);
        tv.setText(s);

    }
}
