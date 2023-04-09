/*
接线说明:无

程序说明:使用闪存文件系统(SPIFFS)来对esp32s3的闪存中的文件进行内容的添加

注意事项:无

函数示例:无

作者:灵首

时间:2023_3_11

*/
#include <Arduino.h>
#include <SPIFFS.h>
#include <FS.h>

String file_name = "/lingsou/notes.txt";    //被读取的文件的地址及文件名


/*
# brief 启动SPIFFS
# param 无
# retval 无
*/
void SPIFFS_start_init(){
  if(SPIFFS.begin()){
    Serial.print("\nSPIFFS Start!!!");
  }
  else{
    Serial.print("\nSPIFFS Failed to start!!!");
  }
}


/*
# brief 检查在指定位置是否有对应的文件
# param 无
# retval 无
*/
void SPIFFS_document_scan(void){
  if(SPIFFS.exists(file_name)){
    Serial.print("\nSPIFFS document exists!!!\n");
  }
  else{
    Serial.print("\nSPIFFS document don't exists!!!\n");
  }

}


void setup() {

  Serial.begin(9600);
  Serial.print("...");

  SPIFFS_start_init();

  //检查是否有对应的文件,若有则在对应的文件后添加相关内容,如无,则串口打印错误提示
  if(SPIFFS.exists(file_name)){
    Serial.print("\n");
    Serial.print(file_name);
    Serial.print("\nSPIFFS document exists!!!\n");
    File dataFile = SPIFFS.open(file_name,"a"); //建立File对象用于对SPIFFS存在的文件进行内容上的添加
    dataFile.println("\nhello IOT world!!"); //添加的具体内容
    dataFile.close();
  }
  else{
    Serial.print(file_name);
    Serial.print("NOT FOUND");
  }

  Serial.print("\nFinshed appending data from SPIFFS");

  SPIFFS_document_scan();
  //打开指定的文件进行读操作并通过串口输出读取的文件内容
  File dataFile = SPIFFS.open(file_name,"r"); //建立File对象用于从SPIFFS中读取文件
  for (int i = 0; i < dataFile.size(); i++)
  {
    Serial.print((char)dataFile.read());    //不加(char) 会输出ASCII码
  }

  Serial.print("\n");
  Serial.print("\nFinshed reading data from SPIFFS");
}


void loop() {

}