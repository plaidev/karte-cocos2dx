package org.cocos2dx.cpp;

import android.support.test.rule.ActivityTestRule;
import android.support.test.runner.AndroidJUnit4;

import org.cocos2dx.lib.Cocos2dxHelper;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Rule;
import org.junit.Test;
import org.junit.experimental.runners.Enclosed;
import org.junit.runner.RunWith;

import java.util.Arrays;

class BaseTest {
  NativeTestBridge testBridge;
  @Rule
  public ActivityTestRule<AppActivity> rule = new ActivityTestRule<>(AppActivity.class);

  @Before
  public void setup() {
    testBridge = new NativeTestBridge();
    Cocos2dxHelper.init(rule.getActivity());
  }
}

/**
 * Instrumented test, which will execute on an Android device.
 * <p>
 * See [testing documentation](http://d.android.com/tools/testing).
 */
@RunWith(Enclosed.class)
public class NativeTest {

  @RunWith(AndroidJUnit4.class)
  public static class stringToJSONObject extends BaseTest {
    @Test
    public void 有効なjson文字列からJSONObjectへの変換() throws JSONException {
      String json1 = "{\"string\": \"abc\", \"number\": 123, \"double\": 123.45, \"isNull\": null }";
      JSONObject dict1 = testBridge.stringToJSONObject(json1);

      Assert.assertEquals("abc", dict1.get("string"));
      Assert.assertEquals(123, dict1.getInt("number"));
      Assert.assertEquals(123.45, dict1.getDouble("double"), 0.01);
      Assert.assertTrue(dict1.isNull("isNull"));
      Assert.assertTrue(dict1.isNull("unknown-key"));
    }

    @Test
    public void 無効なjson文字列からJSONObjectへの変換() {
      String json2 = "{ string }";
      JSONObject dict2 = testBridge.stringToJSONObject(json2);
      Assert.assertNull("invalid json string should return nil", dict2);
    }
  }

  @RunWith(Enclosed.class)
  public static class JSONObjectToString {

    @RunWith(AndroidJUnit4.class)
    public static class JSONObjectから文字列JSONへの変換成功時 extends BaseTest {
      @Test
      public void _1() throws JSONException {
        JSONObject dict1 = new JSONObject("{\"string\":\"abc\",\"number\":123,\"double\":123.45,\"isNull\":null}");
        String expected = "{\"string\":\"abc\",\"number\":123,\"double\":123.45,\"isNull\":null}";
        String actual = testBridge.JSONObjectToString(dict1);

        Assert.assertEquals(expected, actual);
      }

      @Test
      public void _2() throws JSONException {
        JSONObject dict1 = new JSONObject("{\"hoge\":\"fuga\"}");
        String expected = "{\"hoge\":\"fuga\"}";
        String actual = testBridge.JSONObjectToString(dict1);

        Assert.assertEquals(expected, actual);
      }

    }

    @RunWith(AndroidJUnit4.class)
    public static class JSONObjectから文字列JSONへの変換失敗時にnullptrが返ること extends BaseTest {
      @Test
      public void 引数がnull() {
        Assert.assertNull(testBridge.JSONObjectToString(null));
      }
    }
  }

  @RunWith(Enclosed.class)
  public static class JSONArrayToString {
    @RunWith(AndroidJUnit4.class)
    public static class JSONArrayから文字列JSONへの変換成功時 extends BaseTest {
      @Test
      public void _1() {
        JSONArray param = new JSONArray(Arrays.asList("string", "abc", "number"));
        String expected = "[\"string\",\"abc\",\"number\"]";
        String actual = testBridge.JSONArrayToString(param);

        Assert.assertEquals(expected, actual);
      }

      @Test
      public void _2() throws JSONException {
        JSONArray param = new JSONArray(Arrays.asList(new JSONObject("{\"string\":\"abc\",\"number\":123,\"double\":123.45,\"isNull\":null}")));
        String expected = "[{\"string\":\"abc\",\"number\":123,\"double\":123.45,\"isNull\":null}]";
        String actual = testBridge.JSONArrayToString(param);

        Assert.assertEquals(expected, actual);
      }
    }

    @RunWith(AndroidJUnit4.class)
    public static class JSONArrayから文字列JSONへの変換失敗時にnullptrが返ること extends BaseTest {
      @Test
      public void 引数がnull() {
        Assert.assertNull(testBridge.JSONArrayToString(null));
      }
    }
  }

  @RunWith(AndroidJUnit4.class)
  public static class copyString extends BaseTest {
    @Test
    public void CのASCII文字列がコピーできること() {
      String expected = "abc";
      String actual = testBridge.copyString(expected);

      Assert.assertEquals(expected, actual);
    }

    @Test
    public void nullpointerを渡すとnullpointerが返ること() {
      Assert.assertNull(testBridge.copyString(null));
    }

    @Test
    public void マルチバイト文字列が渡された時に正しくコピーできること() {
      String expected = "家族の絵文字👪";
      String actual = testBridge.copyString(expected);

      Assert.assertEquals(expected, actual);
    }
  }
}