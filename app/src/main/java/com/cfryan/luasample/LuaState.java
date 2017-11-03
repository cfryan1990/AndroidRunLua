package com.cfryan.luasample;

/**
 * lua处理
 *
 * @author chenfeng
 * @since 2017-11-03 16:13
 */

public class LuaState {
    /**
     * 最好为C point单独建立一个数据结构
     */
    private long luaState;

    static {
        System.loadLibrary("luajava");
    }

    public LuaState() {
        this.luaState = _newState();
    }

    public void openLibs() {
        _openLibs(luaState);
    }

    public void doLuaScriptString(String text) {
        _doString(luaState, text);
    }

    public void getGlobal(String name) {
        _getGlobal(luaState, name);
    }

    public void pushInteger(int integer) {
        _pushInteger(luaState, integer);
    }

    public void call(int args, int results) {
        _call(luaState, args, results);
    }

    public int toNumberResult(int idx) {
        return _toNumber(luaState, idx);
    }

    public void closeLua() {
        _close(luaState);
    }

    public native long _newState();

    public native void _openLibs(long j);

    public native void _doString(long j, String s);

    public native void _getGlobal(long j, String name);

    public native void _pushInteger(long j, int i);

    public native void _call(long j, int i, int k);

    public native int _toNumber(long j, int i);

    public native void _close(long j);


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();

    public native void doFile(String path);
}
