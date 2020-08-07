package org.cocos2dx.cpp;

import org.json.JSONArray;
import org.json.JSONObject;

class NativeTestBridge {
  native JSONObject stringToJSONObject(String str);
  native String JSONObjectToString(JSONObject json);
  native String JSONArrayToString(JSONArray json);
  native String copyString(String str);

  static {
    System.loadLibrary("MyGame");
  }
}
