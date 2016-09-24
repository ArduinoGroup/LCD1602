int LCD1602_RS = 12;
int LCD1602_RW = 11;
int LCD1602_EN = 10;
int DB[] = { 6, 7, 8, 9 };

char str1[]="HELLO WORLD";
char str2[]="nag24.org";
char str3[]="I am NaG24";
char str4[]="4-bit interface";

void LcdCommandWrite(int command) {
  int i,temp;

  // 定义所有引脚
  temp = command & 0xf0;
  for (i=DB[0]; i <= LCD1602_RS; i++) {
     digitalWrite(i,temp & 0x80);
     temp <<= 1;
  }

  digitalWrite(LCD1602_RS, LOW);
  delayMicroseconds(1);
  digitalWrite(LCD1602_RW, LOW);
  delayMicroseconds(1);

  digitalWrite(LCD1602_EN, LOW);
  delayMicroseconds(1);
  digitalWrite(LCD1602_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite(LCD1602_EN, LOW);
  delayMicroseconds(1);

  temp=(command & 0x0f) << 4;
  for (i=DB[0]; i <= LCD1602_RS; i++) {
     digitalWrite(i,temp & 0x80);
     temp <<= 1;
  }

  digitalWrite(LCD1602_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite(LCD1602_EN, LOW);
}

void LcdDataWrite(int dat) {
  int i=0,temp;
  digitalWrite( LCD1602_RS,HIGH);
  digitalWrite( LCD1602_RW,LOW);
  digitalWrite( LCD1602_EN,LOW);

  temp=dat & 0xf0;
  for (i=DB[0]; i <= 9; i++) {
     digitalWrite(i,temp & 0x80);
     temp <<= 1;
  }

  digitalWrite(LCD1602_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite( LCD1602_EN,LOW);

  temp=(dat & 0x0f)<<4;
  for (i=DB[0]; i <= 9; i++) {
     digitalWrite(i,temp & 0x80);
     temp <<= 1;
  }

  digitalWrite(LCD1602_EN, HIGH);
  delayMicroseconds(1);
  digitalWrite(LCD1602_EN, LOW);
}

void LcdSetXY( int y, int x ) {
  int address;
  // 1 为第一行，其他为第二行
  if (y == 1) address = 0x80 + x - 1;
  else address = 0xC0 + x - 1;
  LcdCommandWrite(address);
}

void LcdWriteChar(int y, int x, int dat) {
  LcdSetXY(y, x);
  LcdDataWrite(dat);
}

void LCDWriteString(int y, int x, char *s) {
    LcdSetXY(y, x);
    //写字符串
    while (*s) {
      LcdDataWrite(*s);
      s ++;
    }
}

void setup (void) {
  int i = 6;
  for (i; i <= 12; i++) {
     pinMode(i, OUTPUT);
  }
  delay(1);
  LcdCommandWrite(0x28);// 设置为4-bit接口，2行显示，5x7文字大小
  delay(10);
  // 输入方式设定 自动增量，没有显示移位
  LcdCommandWrite(0x06);
  delay(10);
  // 屏幕清空，光标位置归零
  LcdCommandWrite(0x01);
  delay(10);
  // 显示设置 开启显示屏，光标显示，无闪烁
  LcdCommandWrite(0x0e);
  delay(10);
}

void loop (void) {
  LcdCommandWrite(0x01);  // 屏幕清空，光标位置归零
  delay(10);
  LCDWriteString(1, 1, str1);
  delay(10);
  LCDWriteString(2, 4, str2);
  delay(1000);
  LcdCommandWrite(0x01);  // 屏幕清空，光标位置归零
  delay(10);
  LCDWriteString(1, 1, str3);
  delay(1000);

  LcdCommandWrite(0x02); //设置模式为新文字替换老文字，无新文字的地方显示不变。
  delay(10);
  LcdCommandWrite(0x80+5); //定义光标位置为第一行第六个位置
  delay(10);
  LcdDataWrite('t');
  LcdDataWrite('h');
  LcdDataWrite('e');
  LcdDataWrite(' ');
  LcdDataWrite('a');
  LcdDataWrite('d');
  LcdDataWrite('m');
  LcdDataWrite('i');
  LcdDataWrite('n');
  delay(1000);
}
