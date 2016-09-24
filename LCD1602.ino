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
  
  // ??????
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
  // 1 ???????????
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
    //????
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
  LcdCommandWrite(0x28);// ???4-bit???2????5x7????
  delay(10);
  // ?????? ???????????
  LcdCommandWrite(0x06);
  delay(10);
  // ???????????
  LcdCommandWrite(0x01);
  delay(10);
  // ???? ??????????????
  LcdCommandWrite(0x0e);
  delay(10);
}

void loop (void) {
  LcdCommandWrite(0x01);  // ???????????  
  delay(10);
  LCDWriteString(1, 1, str1);
  delay(10);
  LCDWriteString(2, 4, str2);
  delay(1000);
  LcdCommandWrite(0x01);  // ???????????  
  delay(10);
  LCDWriteString(1, 1, str3);
  delay(1000);
  
  LcdCommandWrite(0x02); //??????????????????????????
  delay(10);
  LcdCommandWrite(0x80+5); //???????????????
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