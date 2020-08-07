package org.cocos2dx.cpp;

import android.app.Application;

import io.karte.android.KarteApp;

public class AppApplication extends Application {
  @Override
  public void onCreate() {
    super.onCreate();
    KarteApp.setup(this, "YOUR_APP_KEY");
  }
}
