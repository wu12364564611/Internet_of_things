#include <PubSubClient.h>
#include<ESP8266WiFi.h>

/*环境数据*/
String SGP30_date_co2;
String SGP30_date_tvoc;
String BH1750_date_light;
String DHT11_date_humi;
String DHT11_date_temp;
String All_date;

const char* ssid = "MI";      // 连接WiFi名（此处使用taichi-maker为示例）
                                            // 请将您需要连接的WiFi名填入引号中
const char* password = "wwwwwwww";          // 连接WiFi密码（此处使用12345678为示例）
                                            // 请将您需要连接的WiFi密码填入引号中

//定义一个MQTT客户端对象
WiFiClient client;
PubSubClient MqttClient(client);

//MQTT服务器地址
const char *MqttServer = "bemfa.com";

const int subQoS = 1;     // 客户端订阅主题时使用的QoS级别（截止2020-10-07，仅支持QoS = 1，不支持QoS = 2）
const bool cleanSession = false; // 清除会话（如QoS>0必须要设为false）

const char* willTopic = "willTopic"; // 遗嘱主题名称
const char* willMsg = "willMsg";     // 遗嘱主题信息
const int willQos = 0;               // 遗嘱QoS
const int willRetain = false;        // 遗嘱保留

void setup() {
  /*开启与STM32通信的串口*/
  Serial.begin(9600);
  /*开启打印信息的串口*/
  //Serial1.begin(9600);
  /*开始连接wifi*/
  WiFi.begin(ssid, password);                  // 启动网络连接
  //Serial1.print("Connecting to ");              // 串口监视器输出网络连接信息
 // Serial1.print(ssid); Serial1.println(" ...");  // 告知用户NodeMCU正在尝试WiFi连接
  
  int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
  while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
    delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
    //Serial1.print(i++); Serial1.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
  }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。
                                               // 这个读秒是通过变量i每隔一秒自加1来实现的。
                                               
//  Serial1.println("");                          // WiFi连接成功后
//  Serial1.println("Connection established!");   // NodeMCU将通过串口监视器输出"连接成功"信息。
//  Serial1.print("IP address:    ");             // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
//  Serial1.println(WiFi.localIP());              // WiFi.localIP()函数来实现的。该函数的返回值即NodeMCU的IP地址。

  //对MqttClient设置要连接的服务器和端口
  MqttClient.setServer(MqttServer,9501);

  //设置收到订阅主题信息的处理函数
   MqttClient.setCallback(receiveCallback);
  
  //开始连接服务器
  connectMQTTServer();
  
}

void loop() {
  //Serial1.println("ok");
  // put your main code here, to run repeatedly:
  if (MqttClient.connected()) { // 如果开发板成功连接服务器
    // 保持心跳
    MqttClient.loop();
  } else {                  // 如果开发板未能成功连接服务器
    connectMQTTServer();    // 则尝试连接服务器
  }
   if (Serial.available())
  {  
    // 当串口接收到信息后
    //Serial1.println("Serial Data Available...");
    // 通过串口监视器通知用户//读取到包头位置
    Serial.readStringUntil('\t');
    All_date=Serial.readStringUntil('\n');
    pubMQTTmsg("AllDate",All_date);

//    //分离每个数据
//    //读取第一个SGP30_date_co2
//    SGP30_date_co2=Serial.readStringUntil('A');
//    //读取第二个SGP30_date_tvoc
//    SGP30_date_tvoc=Serial.readStringUntil('B');
//    //读取第三个数据BH1750_date_light
//    BH1750_date_light=Serial.readStringUntil('C');
//    //读取第四个数据DHT11_date_humi
//    DHT11_date_humi=Serial.readStringUntil('D');
//    //读取第五个数据DHT11_date_temp
//    DHT11_date_temp=Serial.readStringUntil('\n');
    
  }
}

void connectMQTTServer()
{
  
  // 根据ESP8266的MAC地址生成客户端ID（避免与其它ESP8266的客户端ID重名）
  String clientId = "93f964eab29b40768bd5c2ceba469f0e";
  // 连接MQTT服务器
  if (MqttClient.connect(clientId.c_str(), NULL, NULL, willTopic, willQos, willRetain, willMsg, cleanSession)) { 
//    Serial1.println("MQTT Server Connected.");
//    Serial1.println("Server Address: ");
//    Serial1.println(MqttServer);
//    Serial1.println("ClientId:");
//    Serial1.println(clientId);
    // 订阅指定主题
    subscribeTopic(); 
  } else {
//    Serial1.print("MQTT Server Connect Failed. Client State:");
//    Serial1.println(MqttClient.state());
    delay(3000);
  }   
  
}

void subscribeTopic()
{
  String topicString = "led-control" + WiFi.macAddress();
  char subTopic[topicString.length() + 1];  
  strcpy(subTopic, topicString.c_str());
  
  if(MqttClient.subscribe(subTopic,subQoS)){
//    Serial1.println("Subscrib Topic:");
//    Serial1.println(subTopic);
  } else {
//    Serial1.print("Subscribe Fail...");
  }  
  
}

// 收到信息后的回调函数（函数参数为固定格式）
void receiveCallback(char* topic, byte* payload, unsigned int length) {
  //输出收到的主题是什么
//  Serial1.print("Message Received [");
//  Serial1.print(topic);
//  Serial1.print("] ");
  //输出主题的内容
  for (int i = 0; i < length; i++) {
//    Serial1.print((char)payload[i]);
  }
  //输出主题的字节数
//  Serial1.println("");
//  Serial1.print("Message Length(Bytes) ");
//  Serial1.println(length);
 
  if ((char)payload[0] == '1') {     // 如果收到的信息以“1”为开始
   
  } else {                           
    
  }
}

//发布主题
void pubMQTTmsg(String topic,String sta){
  
  String topicString = topic;
  char publishTopic[topicString.length() + 1];  
  strcpy(publishTopic, topicString.c_str());
 
  // 定时向服务器主题发布当前D3引脚状态
  String messageString = sta;
  char publishMsg[messageString.length() + 1];   
  strcpy(publishMsg, messageString.c_str());
  
  // 实现ESP8266向主题发布信息
  if(MqttClient.publish(publishTopic, publishMsg)){
//    Serial1.println("Publish Topic:");Serial1.println(publishTopic);
//    Serial1.println("Publish message:");Serial1.println(publishMsg);    
  } else {
//    Serial1.println("Message Publish Failed."); 
  }
}
