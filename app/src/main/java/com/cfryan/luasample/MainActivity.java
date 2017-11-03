package com.cfryan.luasample;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private LuaState luaState;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initLua();

        TextView tv = (TextView) findViewById(R.id.sample_text);
        String helloString = luaState.stringFromJNI();
        tv.setText(helloString);

        luaState.doFile("");

        findViewById(R.id.sample_btn).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                luaState.openLibs();
                luaState.doLuaScriptString("function calculate(a,n) return a^n end");
                luaState.getGlobal("calculate");
                luaState.pushInteger(2);
                luaState.pushInteger(10);
                luaState.call(2, 1);

                int result = luaState.toNumberResult(-1);
                Toast.makeText(MainActivity.this, "result is " + result, Toast.LENGTH_LONG).show();

                luaState.closeLua();
            }
        });
    }

    private void initLua() {
        luaState = new LuaState();
    }

}
