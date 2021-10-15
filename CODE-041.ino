//Cơ Điện Tử VTM
#include <PS2X_lib.h>
//https://www.youtube.com/channel/UCpzhReI3a9MZaFaS-nw4wDw?view_as=subscriber
// Các bạn đăng kí kênh ủng hộ mình để mình có động lực cho những video tiếp theo nha.
// Nếu code không chạy các bạn liên hệ với mình để nhận hỗ trợ nha. thankyou :0)
/////////////////////////////////
#define PS2_DAT 13 // data     //
#define PS2_CMD 50 //command   //
#define PS2_SEL 51 // attention//
#define PS2_CLK 12 //clock     //  
/////////////////////////////////


//#define pressures   true
#define pressures false
//#define rumble      true
#define rumble false
int dem_L3;
#include <VirtualWire.h> // khai báo thư viện VirtualWire
byte msg[VW_MAX_MESSAGE_LEN];// biến lưu dữ liệu nhận được
byte msgLen = VW_MAX_MESSAGE_LEN;
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 16, 2);// uno Sda scl: a4, a5// mega2560: 21, 22
PS2X ps2x; // tạo PS2 điều khiển lớp
int error = 0;
byte type = 0;
byte vibrate = 0;
//Biến cho analog
int tempLY;
int tempLX;
int tempRY;
int tempRX;

void setup()
{
  Serial.begin(57600);
  lcd.begin();//Initializing display
  lcd.backlight();//To Power ON the back light
  //lcd.backlight();// To Power OFF the back light
  //delay(300);
  error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  if (error == 0) {
    Serial.print("Đã tìm thấy bộ điều khiển ");
    Serial.print("pressures = ");
    if (pressures)
      Serial.println("true ");
    else
      Serial.println("false");
    Serial.print("rumble = ");
    if (rumble)
      Serial.println("true)");
    else
      Serial.println("false");
    Serial.println("Hãy thử tất cả các nút;");
    Serial.println("giữ L1 hoặc R1 sẽ in ra các giá trị analog.");
  }
  else if (error == 1)
    Serial.println("Không kết nối đc, thử lại...");

  else if (error == 2)
    Serial.println("Bộ điều khiển tìm thấy nhưng không chấp nhận lệnh");

  else if (error == 3)
    Serial.println("Bộ điều khiển từ chối để vào chế độ Pressures ");

  //  Serial.print(ps2x.Analog(1), HEX);
  type = ps2x.readType();
  switch (type) {
    case 0:
      Serial.print("Tay điều khiển không phù hợp ");
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("--Disconnected--");
      lcd.setCursor(0, 1);
      lcd.print("Please try again");
      break;
    case 1:
      Serial.print("Đã tìm thấy DualShock ");
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(" Try your best!");
      break;
    case 2:
      Serial.print("Đã tìm thấy GuitarHero ");
      break;
    case 3:
      Serial.print("Không dây của Sony DualShock điều khiển tìm thấy ");
      break;
  }
}

void loop()
{
  //Cho về 0 xét lại
  tempLY = 0;
  tempLX = 0;
  tempRY = 0;
  tempRX = 0;
  if (error == 1)
    return;

  if (type == 2) {
    ps2x.read_gamepad();
  }
  else {


set:
    ps2x.read_gamepad();
    tempLY = ps2x.Analog(PSS_LY);
    tempLX = ps2x.Analog(PSS_LX);
    tempRX = ps2x.Analog(PSS_RX);
    tempRY = ps2x.Analog(PSS_RY);

    lcd.setCursor(0, 0);
    lcd.print("  Connected :0)");
    lcd.setCursor(0, 1);
    lcd.print("                ");

    ////////////////////////////////////////////////////////////////////////////////
    while (tempRY < 127)
    {

      int change = map(tempRY, 127, 0, 0, 255);
      Serial.print("RY  ");
      Serial.println(change);
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("    VTM :0)");
      lcd.setCursor(0, 1);
      lcd.print(change);
      lcd.print("     RY");
      ps2x.read_gamepad();
      tempRY = ps2x.Analog(PSS_RY);
      if (tempRY >= 127)
      {
        break;
        goto set;
      }
    }

    /////////////////////////////////////////////////////////////////////
    while (tempRY > 127)
    {
      int change = map(tempRY, 127, 255, 0, 255);
      Serial.print("RY -");
      Serial.println(change);
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(change);
      lcd.print("     RY");
      ps2x.read_gamepad();
      tempRY = ps2x.Analog(PSS_RY);
      if (tempRY <= 127)
      {
        break;
        goto set;
      }
    }

    //////////////////////////////////////////////////////////////////////
    while (tempLY < 127)
    {
      int change = map(tempLY, 127, 0, 0, 255);
      Serial.print("LY  ");
      Serial.println(change);
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(change);
      lcd.print("     LY");
      ps2x.read_gamepad();
      tempLY = ps2x.Analog(PSS_LY);
      if (tempLY >= 127)
      {
        break;
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////////////////////////
    while (tempLY > 127)
    {
      int change = map(tempLY, 127, 255, 0, 255);
      Serial.print("LY -");
      Serial.println(change);
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(change);
      lcd.print("     LY");
      ps2x.read_gamepad();
      tempLY = ps2x.Analog(PSS_LY);
      if (tempRX <= 127)
      {
        break;
        goto set;
      }
    }

    ////////////////////////////////////////////////////////////////////
    while (tempRX > 128)
    {
      int change = map(tempRX, 128, 255, 0, 255);
      Serial.print("RX  ");
      Serial.println(change);
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(change);
      lcd.print("     RX");
      ps2x.read_gamepad();
      tempRX = ps2x.Analog(PSS_RX);
      if (tempRX <= 128)
      {
        break;
        goto set;
      }
    }
    //////////////////////////////////////////////////////////////////////
    while (tempRX < 128)
    {
      int change = map(tempRX, 128, 0, 0, 255);
      Serial.print("RX -");
      Serial.println(change);
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(change);
      lcd.print("     RX");
      ps2x.read_gamepad();
      tempRX = ps2x.Analog(PSS_RX);
      if (tempRX >= 128)
      {
        break;
        goto set;
      }
    }
    while (tempLX > 128)
    {
      int change = map(tempLX, 128, 255, 0, 255);
      Serial.print("LX  ");
      Serial.println(change);
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(change);
      lcd.print("     RX");
      ps2x.read_gamepad();
      tempLX = ps2x.Analog(PSS_LX);
      if (tempLX <= 128)
      {
        break;
        goto set;
      }
    }
    //////////////////////////////////////////////////////////////////////
    while (tempLX < 128)
    {
      int change = map(tempLX, 128, 0, 0, 255);
      Serial.print("LX -");
      Serial.println(change);
      lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print(change);
      lcd.print("     LX");
      ps2x.read_gamepad();
      tempLX = ps2x.Analog(PSS_LX);
      if (tempLX >= 128)
      {
        break;
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_CROSS) == HIGH)
    {
      Serial.println("PAD_CROSS");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_CROSS");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_CROSS) == LOW)
      {
        break;
        goto set;
      }
    }
    ////////////////////////////////////////////////////////////////////

    while (ps2x.Button(PSB_TRIANGLE) == HIGH)
    {
      Serial.println("TRIANGLE");
      //lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("TRIANGLE");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_TRIANGLE) != HIGH)
      {
        break;
        goto set;
      }
    }
    ///////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_PAD_UP) == HIGH)
    {
      Serial.println("PAD_UP");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_UP");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_PAD_UP) == LOW)
      {
        break;
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_PAD_DOWN) == HIGH)
    {
      Serial.println("PAD_DOWN");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_DOWN");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_PAD_DOWN) == LOW)
      {
        break;
        goto set;
      }
    }
    ///////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_SQUARE) == HIGH )
    {
      Serial.println("SQUARE");
      //lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("SQUARE");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_SQUARE) != HIGH)
      {
        break;
        goto set;
      }
    }
    ////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_CIRCLE) == HIGH )
    {
      Serial.println("CIRCLE");
      //lcd.clear();//Clean the screen
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("CIRCLE");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_CIRCLE) != HIGH)
      {
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_PAD_LEFT) == HIGH)
    {
      Serial.println("PAD_LEFT");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_LEFT");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_PAD_LEFT) == LOW)
      {
        break;
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_PAD_RIGHT) == HIGH)
    {
      Serial.println("PAD_RIGHT");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_RIGHT");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_PAD_RIGHT) == LOW)
      {
        break;
        goto set;
      }
    }
    ///////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_R1) == HIGH)
    {
      Serial.println("PSB_R1");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_R1");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_R1) == LOW)
      {
        break;
        goto set;
      }
    }
    /////////////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_R2) == HIGH)
    {
      Serial.println("PSB_R2");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_R2");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_R2) == LOW)
      {
        break;
        goto set;
      }
    }
    ///////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_L3) == HIGH)
    {
      Serial.println("PSB_L3");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_L3");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_L3) == LOW)
      {
        break;
        goto set;
      }
    }
    ///////////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_L1) == HIGH)
    {
      Serial.println("PSB_L1");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_L1        ");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_L1) != HIGH)
      {
        break;
        goto set;
      }
    }
    ////////////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_L2) == HIGH)
    {
      Serial.println("PSB_L2");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PAD_L2");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_L2) == LOW)
      {
        break;
        goto set;
      }
    }
    //////////////////////////////////////////////////////////
    while (ps2x.Button(PSB_R3) == HIGH)
    {
      Serial.println("PSB_R3");
      lcd.setCursor(0, 0);
      lcd.print("  Connected :0)");
      lcd.setCursor(0, 1);
      lcd.print("PSB_R3");
      ps2x.read_gamepad();
      if (ps2x.Button(PSB_R3) != HIGH)
      {
        break;
        goto set;
      }
    }
  }
}
