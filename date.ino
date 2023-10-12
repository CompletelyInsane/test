
typedef struct {
  int distance = 0;
  int strength = 0;
  int ID   = 0;            //雷达 ID

  long int BaudRate = 0;

  boolean LidarFlag = false;
  boolean receiveComplete = false;
  boolean IO = 0;
} TF;
TF Lidar;

void getLidarData( TF* Lidar);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
   // struct TF lidarData;
    //getLidarData(&Lidar);
}

void loop() {
  // put your main code here, to run repeatedly:
  getLidarData(&Lidar);
  Serial.print("长度为: ");
  Serial.println(Lidar.distance);
  Serial.print("长度为: ");
  Serial.println(Lidar.distance);
}

void getLidarData( TF* Lidar)  //串口获取一帧数据，并计算距离，信号强度和记录成功计算的标志。
{ 
  //59 59 03 00 E9 09 68 09 18  一帧数据
  static char i = 0;
  char j = 0;
  int checksum = 0;
  static int rx[9] = {0x59 ,0x59 ,0x2F ,0x00 ,0xC9 ,0x0B ,0x70 ,0x09 ,0x2E};
  // while (Serial.available() > 0) {
  //   rx[i] = Serial.read();
    if (rx[0] != 0x59) {
      i = 0;
    } else if (i == 1 && rx[1] != 0x59) {
      i = 0;
    } else if (i == 8) {
      for (j = 0; j < 8; j++) {
        checksum += rx[j];      //计算校验和
      }
      if (rx[8] == (checksum % 256)) {
        Lidar->distance = rx[2] + rx[3] * 256;  //距离
        Lidar->strength = rx[4] + rx[5] * 256;  //信号强度
        Lidar->receiveComplete = true;          //接收完成
      }
      i = 0;
    } else {
      i++;
    }
    
}





// void getLidarData( TF* Lidar)
// { 
//   //59 59 03 00 E9 09 68 09 18  一帧数据
//   static char i = 0;
//   char j = 0;
//   int checksum = 0;
//   static int rx[9] ;
//   while (Serial.available() > 0) {
//     rx[i] = Serial.read();
//     if (rx[0] != 0x59) {
//       i = 0;
//     } else if (i == 1 && rx[1] != 0x59) {
//       i = 0;
//     } else if (i == 8) {
//       for (j = 0; j < 8; j++) {
//         checksum += rx[j];      //计算校验和
//       }
//       if (rx[8] == (checksum % 256)) {
//         Lidar->distance = rx[2] + rx[3] * 256;  //距离
//         Lidar->strength = rx[4] + rx[5] * 256;  //信号强度
//         Lidar->receiveComplete = true;          //接收完成
//       }
//       i = 0;
//     } else {
//       i++;
//     }
//   }
// }
