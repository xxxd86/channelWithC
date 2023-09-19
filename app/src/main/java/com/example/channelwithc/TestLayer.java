package com.example.channelwithc;


import android.content.res.AssetManager;
import android.util.Log;

public class TestLayer {

    public String setAssetManager(AssetManager assetManager) {
        Log.v("ENTER","ENTTER");

         return SetAssetManager(assetManager);
    }

    //////////////////////////Native///////////////////////////////////////////
    private native static  String SetAssetManager(AssetManager assetManager);

}