#define BLINKER_PRINT Serial
#define BLINKER_WIFI
#define BLINKER_MIOT_OUTLET
#include <Blinker.h>
int GPIO = 0;
BlinkerButton Button1("btn-1");
BlinkerNumber Number1("num-1");
// /////////////////////只需修改以下三行////////////////////////////////////
char auth[] = "Blinker key";
char ssid[] = "WiFi名称";
char pswd[] = "WiFi密码";
// /////////////////////////////////////////////////////////////////////
BlinkerText Tex1("tex-1");
BlinkerText Tex2("tex-2");
void heartbeat() //心跳包回调函数
{
  Tex1.print("正常");
}

void Button1_callback(const String & state)
{
  BLINKER_LOG("get button state: ", state);
  if (state == "on")
  {
    digitalWrite(GPIO, LOW);
    delay(200);
    digitalWrite(GPIO, HIGH);
    Button1.print("on");
    Tex2.print("开机");
  }
  if (state == "off")
  {
    digitalWrite(GPIO, LOW);
    delay(200);
    digitalWrite(GPIO, HIGH);
    Button1.print("off");
    Tex2.print("关机");
  }
  if (state == "press")
  {
    Tex2.print("强关");
    digitalWrite(GPIO, LOW);
    delay(5000);
    digitalWrite(GPIO, HIGH);
    Button1.print("press");
  }
  if (state == "pressup")
  {
    Button1.print("pressup");
    Tex2.print("关机");
  }
}

void dataRead(const String & data)
{
  BLINKER_LOG("Blinker readString: ", data);
  Blinker.vibrate();
  uint32_t BlinkerTime = millis();
  Blinker.print("millis", BlinkerTime);
}

void setup() {
  Serial.begin(115200);
  BLINKER_DEBUG.stream(BLINKER_PRINT);
  Blinker.begin(auth, ssid, pswd);
  Blinker.attachData(dataRead);
  Blinker.attachHeartbeat(heartbeat);
  Button1.attach(Button1_callback);
  pinMode(GPIO, OUTPUT);
  digitalWrite(GPIO, HIGH);//默认关闭继电器
}

void loop() {
  Blinker.run();
}
