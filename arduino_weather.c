#include <LiquidCrystal_I2C.h>
#define PINO_TRIGGER 10  
#define PINO_ECHO    9 

LiquidCrystal_I2C lcd_lumi(0x20,16,2);
LiquidCrystal_I2C lcd_temp(0x21,16,2);
LiquidCrystal_I2C lcd_prox(0x22,16,2);
int porta_LDR = A0;
int porta_temp = A1;
int polegadas = 0;
int centimetros = 0;

long readUltrasonicDistance(){
  
  digitalWrite(PINO_TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(PINO_TRIGGER, HIGH);
  delayMicroseconds(10);  
  digitalWrite(PINO_TRIGGER, LOW);
  
  return pulseIn(PINO_ECHO, HIGH);
  
}

void setup() {
    
  lcd_lumi.init();
  lcd_lumi.backlight();
  lcd_lumi.clear();
  
  lcd_temp.init();
  lcd_temp.backlight();
  lcd_temp.clear();
  
  lcd_prox.init();
  lcd_prox.backlight();
  lcd_prox.clear();
  
  pinMode(PINO_TRIGGER, OUTPUT);
  pinMode(PINO_ECHO, INPUT); 
  
}

void loop() {
  // Luminosidade
  int valor_LDR = analogRead(porta_LDR);
  int luminosidade = map(valor_LDR,0,679,0,100);
    
  lcd_lumi.setCursor(0,0);
  lcd_lumi.print("LDR: ");
  lcd_lumi.print(valor_LDR);
  lcd_lumi.setCursor(0,1);
  lcd_lumi.print("Lum: ");
  lcd_lumi.print(luminosidade);
  lcd_lumi.print("%");
  
  
  // Temperatura
  int temp_c = (( 5.0 * analogRead(porta_temp) / 1024 ) - 0.5) * 100 ; 
  int temp_f = (temp_c * 9) / 5 + 32; 
  
  lcd_temp.setCursor(0,0);
  lcd_temp.print("Temp C: ");
  lcd_temp.print(temp_c,DEC);
  lcd_temp.print("C");
  lcd_temp.setCursor(0,1);
  lcd_temp.print("Temp F: ");
  lcd_temp.print(temp_f,DEC);
  lcd_temp.print("F");
  
  
  // Proximidade
  centimetros = 0.01723 * readUltrasonicDistance();
  polegadas = (centimetros / 2.54);
    
  lcd_prox.setCursor(0,0);
  lcd_prox.print("Pol.: ");
  lcd_prox.print(polegadas);
  lcd_prox.setCursor(0,1);
  lcd_prox.print("Cent.: ");
  lcd_prox.print(centimetros);
  
  
  delay(1000);

  lcd_lumi.clear();
  lcd_temp.clear(); 
  lcd_prox.clear();     
}