# Arduino-e-GPS
Arduino UNO + GPS; Programa que grava as informações de latitude e longitude na memoria EEPROM do Arduino Uno (1K ATmega328p)

Arduino UNO + GPS; Program that records the latitude and longitude information in the Arduino Uno's EEPROM memory (1K ATmega328p)

## Go to Wiki

# Welcome to the Arduino-and-GPS wiki!

![Módulo GPS](http://www.msseletronica.com/imagens/974_529.jpg)

## Especificações:
* Modelo: GY-GPS6MV2; 
* Tensão de alimentação: 3 V ~ 5 V; 
* Comunicação serial Tx Rx.
* Velocidade padrão: 9600 bauds; 
* Frequência de atualização de navegação: 1 Hz; 
* Possui bateria de backup; 
* Possui LED para indicar o sinal;
* Precisão de 2,5 metros ([Datasheet](https://www.u-blox.com/sites/default/files/products/documents/NEO-6_DataSheet_(GPS.G6-HW-09005).pdf));


## O módulo possui uma pré-configuração de transmissão de dados no formato NMEA:
	**NMEA** (Associação Nacional de Eletrônicos Marinhos), este, sentenças com as seguintes abreviaturas: GPGGA, GPGLL, GPGSA, GPGSV, _**GPRMC**_, GPVTG, GPTXT.

A mensagem utilizada neste projeto é: GPRMC


## Descrição das sentenças da mensagem:

**$GPRMC,045725.00,A,3002.48968,S,05113.26679,W,0.088,0,021116,,,D*7E** 	
* **GPRMC**        Tipo da sentença 	
* **045725.00** 	Horário 04 h 57 min 25 s 	
* **A** 		Dado Válido 'A' / Dado Inválido 'D' 	
* **3002.48968** 	Latitude, -30 graus 02.48 min 	
* **S** 		'N' Norte (positivo) / 'S' Sul (negativo) 	
* **5113.26679** 	Longitude, -51 graus 13.26 min 	
* **W** 		'E' Leste (positivo) / 'W' Oeste (negativo) 	
* **0.088** 		Velocidade 	
* **0** 		Curso 	
* **021116** 		Data 02/11/2016 	
* **D** 		'A' = Autônomo, 'D' = DGPS, 'E' = DR. 'D' Sem estação 	
* ***7E** 		Soma de verificação, usado para verificar erro de transmissão 	


## Para transformar os dados no formato do GoogleMaps: é aplicada a conversão:

1. Formato em decimal: 		dddd.dddd (decimal) 		
1. Valor em decimal: 		3002.48968 	
1. Formato em GMS: 		gg ° mm" ss' ms 	(graus, minutos, segundos)
1. Valor em GMS: 		30 02,48968 	
1. Equação de conversão: 	gg + (mm,ssms / 60) 	
1. Calculo de conversão: 	30 + (02,48968 / 60) 	
1. Resultado10: 		-30 ° 04" 14' 9 
