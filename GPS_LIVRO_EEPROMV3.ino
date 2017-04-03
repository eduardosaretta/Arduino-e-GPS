#include <SoftwareSerial.h>

#include <EEPROM.h>

#include <String.h> 

SoftwareSerial gpsSerial(4 , 3); // ARDUINO(RX) -> GPS(TX) , ARDUINO(TX) -> GPS(RX) (not used)
const int sentenceSize = 80; //tamanho do buffer

char sentence[sentenceSize]; //vetor com o tamanho definido

int adress = 0;    // endereço de escrita na memória
String stringOne;
String stringTwo;

char charAux[5];

int one;
byte dgree;
byte primiroLoop = 0;
byte dgreeByte;
int minn; //até 65536
float minuts;
int memoriaFull = 0;
byte hiByte,loByte;
int posicaoInicial;


void setup()
{
  Serial.begin(9600);
  gpsSerial.begin(9600);

     // EEPROM.write(0, 2);
     // EEPROM.write(1, 0);
      //le o primeiro valor
      hiByte = EEPROM.read(0);
      loByte = EEPROM.read(1);
      posicaoInicial  = word(hiByte, loByte);
      Serial.println( hiByte );
      Serial.println( posicaoInicial );
      adress = 2;
      
}

void loop()
{
  static int i = 0;
  if (gpsSerial.available())
  {
    char ch = gpsSerial.read();
    if (ch != '\n' && i < sentenceSize)
    {
      sentence[i] = ch;
      i++;
    }
    else
    {
     sentence[i] = '\0'; //identifica fim de string
     i = 0;
     //Serial.println(sentence);
     gravaMem(); //exibe os dados do GPS
    }
  }
}

void gravaMem() //função
{
  char field[20]; //define um campo
  getField(field, 0);
  if (strcmp(field, "$GPRMC") == 0){
    
    getField(field, 2);
    if ((strcmp(field, "A") == 0) && memoriaFull == 0 ){ //Verifica se for verdadeiro

      if(primiroLoop == 0){ //quando é ressetado e existe uma coleta, o GPS resseta a posição inicial.
        EEPROM.write(0, 0);
        EEPROM.write(1, 0);
        primiroLoop++;
      }
    
      Serial.print("Lat: "); //latitude
      
      getField(field, 3);// GET coordenada LAT
      stringOne = field;

      //Serial.print(stringOne); 
      //stringOne.replace(".",",");
      stringTwo = stringOne.substring(2); 
      stringOne = stringOne.substring(0 , 2); //dgree
     
      // Serial.print(stringTwo); 
       
      getField(field, 4); //get N/S
      if(strcmp(field, "S") == 0){
        stringOne = "-"+stringOne; //transforma para negativo
      }
      
      dgree = stringOne.toInt(); //valor para EEPROM graus

      // grava no primeiro endereco EEPROM o valor de graus 
      EEPROM.write(adress, dgree);//grava valor negativo entre -128 a 127: para calcular colocal (dgree -256)
      adress++;
      minuts = stringTwo.toFloat();
      minuts = (minuts / 60) * 100000; //transforma para coordenada em MM e SS!
      minn = minuts;

      // divide val que é um inteiro de 16 bits em dois bytes
      hiByte = highByte(minn);
      loByte = lowByte(minn);

      // escreve o byte mais significativo de min na EEPROM no endereço selecionado em address
      EEPROM.write(adress, hiByte);
      adress++;
      // escreve o byte menos significativo de min na EEPROM no endereço selecionado em address+1.
      EEPROM.write(adress, loByte);
      adress++;
      
      Serial.print(dgree);
      Serial.print(" ");
      Serial.print(minn);
      
      
      Serial.print(" Long: "); //longitude

      getField(field, 5);  // coordenada LONG
      stringOne = field;

      if(stringOne.charAt(0) == '0'){ //remove o '0' a esquerda
        stringOne = stringOne.substring(1);
      }

      stringTwo = stringOne.substring(2); 
      stringOne = stringOne.substring(0 , 2); //dgree
      
      getField(field, 6);  //get E/W
      if(strcmp(field, "W") == 0){
        stringOne = "-"+stringOne; //passa para negativo
      }

      dgree = stringOne.toInt(); //valor para EEPROM graus
      
      // grava no primeiro endereco EEPROM o valor de graus 
      EEPROM.write(adress, dgree);
      adress++;
      minuts = stringTwo.toFloat();
      minuts = (minuts / 60) * 100000; //transforma para coordenada em MM e SS!
      minn = minuts;

      // divide val que é um inteiro de 16 bits em dois bytes
      hiByte = highByte(minn);
      loByte = lowByte(minn);

      // escreve o byte mais significativo de min na EEPROM no endereço selecionado em address
      EEPROM.write(adress, hiByte);
      adress++;
      // escreve o byte menos significativo de min na EEPROM no endereço selecionado em address+1.
      EEPROM.write(adress, loByte);
      adress++;

      hiByte = highByte(adress);
      loByte = lowByte(adress);
      
      EEPROM.write(0, hiByte);//grava o proximo valor inicial
      EEPROM.write(1, loByte);//grava o proximo valor inicial

      Serial.print(dgree);
      Serial.print(" ");
      Serial.println(minn);

      Serial.println(adress);
      
      if(adress > 1002){
        memoriaFull++;
      }

      delay(8000);
     
    }else{
      Serial.print(".");
      delay(5000);
    }
  }
}


void getField(char* buffer, int index){ //funcao percorre sentença
  int sentencePos = 0;
  int fieldPos = 0;
  int commaCount = 0;
  while (sentencePos < sentenceSize)
  {
    if (sentence[sentencePos] == ',')
    {
      commaCount ++;
      sentencePos ++;
    }
    if (commaCount == index)
    {
      buffer[fieldPos] = sentence[sentencePos];
      fieldPos ++;
    }
    sentencePos ++;
  }
  buffer[fieldPos] = '\0';
}
