#include <EEPROM.h>    // incluir a biblioteca

// inicia lendo apartir do primeiro byte (endereço 0) da EEPROM
int address = 2;    // endereço de escrita na memória
int value;    // valor lido da EEPROM    
int posicaoFinal;

byte dgree;
byte hiByte, lowByte;


void setup()
{
  Serial.begin(9600);    // inicializa o canal de comunicação serial

  hiByte = EEPROM.read(0); //le o primeiro valor
  lowByte = EEPROM.read(1); //le o segundo valor
  posicaoFinal  = word(hiByte, lowByte); //concatena Bite
  Serial.println( posicaoFinal );
  
  
}

void loop()
{

  if(address <= posicaoFinal){
    

  Serial.print("EEPROM ");
  Serial.print(address);

  //Le LATITUDE
  Serial.print(" LAT ");
  dgree = EEPROM.read(address);
  Serial.print(dgree);
  address++;
  // lê o byte no endereço atual da EEPROM
  hiByte = EEPROM.read(address);
  address++;
  lowByte = EEPROM.read(address);
  address++;
  
  value  = word(hiByte, lowByte); //concatena Bite
  Serial.print(" ");
  Serial.print(value);
  

  
  //Le LONGITUDE
  Serial.print(" LONG ");
  dgree = EEPROM.read(address);
  Serial.print(dgree);
  address++;
  // lê o byte no endereço atual da EEPROM
  hiByte = EEPROM.read(address);
  address++;
  lowByte = EEPROM.read(address);
  address++;
  
  value  = word(hiByte, lowByte); //concatena Bite
  Serial.print(" ");
  Serial.println(value);
    
  }
  delay(100);
}
