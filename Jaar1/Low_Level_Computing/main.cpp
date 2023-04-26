#include <avr/io.h>
#include <util/atomic.h>

uint16_t t1;
int16_t t2;
int16_t t3;
long n = F_CPU; //kloksnelheid

//alle getallen
uint8_t getallen[12]= {
0b00111111, //0
0b00000110, //1
0b01011011, //2
0b01001111, //3
0b01100110, //4
0b01101101, //5
0b01111101, //6
0b00000111, //7
0b01111111, //8
0b01101111, //9
0b10000000, //,
0b00000000 //niets
};

//data versturen
uint8_t transfer(uint8_t getal){
  USIDR = getal;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    for(int i = 0; i<16;i++){ //16 = 8 rising edges
      USICR |= (1<<USITC);//clock togglen
    }
  }
  return USIDR;
}

void delay(int sec){
  for (long i = 0; i < (n/7)*sec; i++){ //delay van 1 sec
      asm("nop");//niets doen
  }
}

//de temperatuursensor callibreren
void callibratie(){
  PORTB &= ~(1<<PB4);//pin4 LOW (CSB)
  transfer(0x88);
  uint16_t laagT1 = transfer(0);// bit 0-7 uitlezen
  uint16_t hoogT1 = transfer(0);// bit 8-15 uitlezen
  t1 = (hoogT1<<8) | (laagT1);
  
  int16_t laagT2 = transfer(0);// bit 0-7 uitlezen
  int16_t hoogT2 = transfer(0);// bit 8-15 uitlezen
  t2 = (hoogT2<<8) | (laagT2);

  int16_t laagT3 = transfer(0);// bit 0-7 uitlezen
  int16_t hoogT3 = transfer(0);// bit 8-15 uitlezen
  t3 = (hoogT3<<8) | (laagT3);
  PORTB |= (1 << PB4);//pin4 HIGH
}

//modus instellen
void setMode(){ 
  PORTB &= ~(1<<PB4);//pin4 LOW (CSB)
  transfer(0x74);
  transfer(0b01000011);
  PORTB |= (1 << PB4);//pin4 HIGH
}

//data versturen naar de 7-seg display
void writeDigit(int i){
  PORTB &= ~(1<<PB3);//pin3 LOW
   transfer(getallen[i]);
   PORTB |= (1 << PB3);//pin3 HIGH
}

//de temperatuur uitlezen en doorsturen aan de 7-seg display
void tempset(){
  PORTB &= ~(1 << PB4);//PB4 laag
  transfer(0xFA);
  long MSB = transfer(0);
  long LSB = transfer(0);
  long xLSB = transfer(0);
  long adc_T = (MSB << 12) | (LSB << 4) | (xLSB >> 4);
  PORTB |= (1 << PB4);//pb4 hoog
  long var1 = ((((adc_T >> 3) - ((long)t1 << 1))) * ((long)t2)) >> 11;
  long var2 = (((((adc_T >> 4) - ((long)t1)) * ((adc_T >> 4) - ((long)t1))) >> 12) * ((long)t3)) >> 14;
  float temp = (var1 + var2) / 5120.0;
  writeDigit((int)temp / 10);
  delay(1);
  writeDigit((int)temp % 10);
  delay(1);
  writeDigit(10);//comma
  delay(1);
  writeDigit(((int)(temp * 10)) % 10);
  delay(1);
  writeDigit(((int)(temp * 100)) % 10);
  delay(1);
  writeDigit(11);//niets
  delay(1);
}

//de ATtiny85 instellen
void init(){
  //instellen van de at tiny
  DDRB |= (1<<DDB1); //pin1 als output(Master in Slave out/ DO) (pin14 shiftregister)
  DDRB &= ~(1<<DDB0); //pin0 als input(Master out Slave in/ DI)
  DDRB |= (1<<DDB2); //pin2 als output(SCLK/SCL) (pin11 shiftregister)

  DDRB |= (1<<DDB3); //pin3 als output (slave select/latch voor de shift out) (pin12 shiftregister)
  DDRB |= (1<<DDB4); // pin4 als output

  USICR |= (1<<USIWM0); //three wire mode set
  USICR |= (1<<USICS1); //set clock to eternal
}

int main(){
  init();
  setMode();
  callibratie();
  while(1){
    tempset();
  }
}