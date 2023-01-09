/*

 * Macro Definitions

 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SPEC_TRG         A0

#define SPEC_ST          A1

#define SPEC_CLK         A2

#define SPEC_VIDEO       A3

#define WHITE_LED        A4

#define LASER_404        A5

#define PLAYPAUSE        8

//--------------------------------------------------------------------------------------------
// Máquina de Estados:
#define ESTADO_OCIOSO false           //define que representa o estado ocioso
#define ESTADO_LEITURA true   //define que representa o estado no qual a leitura ocorre
//variáveis globais:
volatile bool ControleMaquinaEstado = false;//ESTADO_OCIOSO; //variável responsável por armazenar o estado atual da máquina de estados
//prototypes:
void ExecutaMaquinaDeEstados(void);  //função que contém o switch/case com a máquina de estados
// função de execução da máquina de estados via switch/case

#define SPEC_CHANNELS    288 // New Spec Channel

uint16_t data[SPEC_CHANNELS];


#define AVERAGE00    750 //H2O 

#define AVERAGE01    747 //Clorofila

#define AVERAGE11     444 //Contaminante



long int avrg = 0;

int conta = 1;



void setup(){
  

  //Set desired pins to OUTPUT

  pinMode(SPEC_CLK, OUTPUT);

  pinMode(SPEC_ST, OUTPUT);

  pinMode(WHITE_LED, OUTPUT);

  pinMode(LASER_404, OUTPUT);

  pinMode(PLAYPAUSE, OUTPUT);



  //digitalWrite(WHITE_LED, HIGH); // Set WHITE_LED High

  //digitalWrite(LASER_404, HIGH); // Set LASER_404 High

  digitalWrite(SPEC_CLK, HIGH); // Set SPEC_CLK High

  digitalWrite(SPEC_ST, LOW); // Set SPEC_ST Low

  digitalWrite(PLAYPAUSE, LOW); // Set PLAYPAUSE Low



  Serial.begin(115200); // Baud Rate set to 115200

  

}



/*

 * This functions reads spectrometer data from SPEC_VIDEO

 * Look at the Timing Chart in the Datasheet for more info

 */

void readSpectrometer(){



  int delayTime = 5; // delay time

  int cont = 1;



  // Start clock cycle and set start pulse to signal start

  digitalWrite(SPEC_CLK, LOW);

  delayMicroseconds(delayTime);

  digitalWrite(SPEC_CLK, HIGH);

  delayMicroseconds(delayTime);

  digitalWrite(SPEC_CLK, LOW);

  digitalWrite(SPEC_ST, HIGH);

  delayMicroseconds(delayTime);



  //Sample for a period of time

  for(int i = 0; i < 15; i++){



      digitalWrite(SPEC_CLK, HIGH);

      delayMicroseconds(delayTime);

      digitalWrite(SPEC_CLK, LOW);

      delayMicroseconds(delayTime); 

 

  }



  //Set SPEC_ST to low

  digitalWrite(SPEC_ST, LOW);



  //Sample for a period of time

  for(int i = 0; i < 85; i++){



      digitalWrite(SPEC_CLK, HIGH);

      delayMicroseconds(delayTime);

      digitalWrite(SPEC_CLK, LOW);

      delayMicroseconds(delayTime); 

      

  }



  //One more clock pulse before the actual read

  digitalWrite(SPEC_CLK, HIGH);

  delayMicroseconds(delayTime);

  digitalWrite(SPEC_CLK, LOW);

  delayMicroseconds(delayTime);



  //Read from SPEC_VIDEO
//int pix;
//float az = 3.071188765*pow(10,2);
//float b1 = 2.710355256*pow(10,0);
//float b2 = -1.368366888*pow(10,-3);
//float b3 = -5.161080308*pow(10,-6);
//float b4 = -1.645262382*pow(10,-9);
//float b5 = 2.137989782*pow(10,-11);

  for(int i = 0; i < SPEC_CHANNELS; i++){
//pix = analogRead(SPEC_VIDEO);


      data[i] = analogRead(SPEC_VIDEO);
      //data[i] = az + b1*pix + b2*pow(pix,2) + b3*pow(pix,3) + b4*pow(pix,4) + b5*pow(pix,5);

      

      avrg = avrg + data[i];

      cont++;

      

      digitalWrite(SPEC_CLK, HIGH);

      delayMicroseconds(delayTime);

      digitalWrite(SPEC_CLK, LOW);

      delayMicroseconds(delayTime);

        

  }

  avrg = avrg/cont;
  


  //Set SPEC_ST to high

  digitalWrite(SPEC_ST, HIGH);



  //Sample for a small amount of time

  for(int i = 0; i < 7; i++){

    

      digitalWrite(SPEC_CLK, HIGH);

      delayMicroseconds(delayTime);

      digitalWrite(SPEC_CLK, LOW);

      delayMicroseconds(delayTime);

    

  }



  digitalWrite(SPEC_CLK, HIGH);

  delayMicroseconds(delayTime);

  

}



/*

 * The function below prints out data to the terminal or 

 * processing plot

 */

void printData(){

  

  for (int i = 0; i < SPEC_CHANNELS; ++i){

    

    Serial.println(data[i]);

    //Serial.print('\n');

    

  }

  //Serial.print(avrg);

  //Serial.print('\n');

}



/*

 * The function below caculates data average

 */

void calcMedia(){

  int avrg = 0;  
  int cont = 1;
  

  int delayTime = 6500;

  for (int i = 0; i <= SPEC_CHANNELS; i++){

    avrg = (avrg + data[i])/cont;

    cont++;

  }



//  if(avrg > AVERAGE00 && conta % 11 == 0){//(avrg > AVERAGE00 && avrg < AVERAGE01){
//
//    digitalWrite(PLAYPAUSE, HIGH); // Set PLAYPAUSE High
//
//    delay(delayTime/10);
//
//    digitalWrite(PLAYPAUSE, LOW); // Set PLAYPAUSE Low
//
//    delay(delayTime);
//
//    digitalWrite(PLAYPAUSE, HIGH); // Set PLAYPAUSE High
//
//    delay(delayTime/10);
//
//    digitalWrite(PLAYPAUSE, LOW); // Set PLAYPAUSE Low
//
//
//    //Serial.print("teste 2");//uva verde
//    delay(delayTime);
//
//  }
//
//  else if(avrg < AVERAGE00 && conta % 11 == 0){//Serial.print("teste 1");}//("teste 1");
//    }//"uva bordeaux"
//
//  //delay(delayTime);
//
//  conta++;
//
}


void ExecutaMaquinaDeEstados()
{
  volatile char matlabData;
matlabData = Serial.read();
  //bool TeclaLida; // faz leitura da tecla pressionada
 // fflush(stdin); // limpa o buffer do teclado
char advance = 'a';
char returni = 'r';
  // executa a máquina de estados
switch(ControleMaquinaEstado)
  {
    case false: //ESTADO_OCIOSO:
    {
      if(matlabData == advance) // somente muda de estado se for digitada a letra 'a'
         ControleMaquinaEstado = true;//ESTADO_LEITURA;
          break;
    }
    case true: //ESTADO_LEITURA:
    {
       //Serial.flush();
       //fflush(stdin);
      //char matlabData2;
      //matlabData2 = Serial.read();
     while(matlabData != returni) 
      {
       readSpectrometer();
       printData();
            delay(500);
       if( Serial.read() == returni)
          matlabData = returni;
      }
        ControleMaquinaEstado = false; //ESTADO_OCIOSO;
           break;
    }
  }
}


void loop(){

  int delayTime = 500;
 // Serial.println(ControleMaquinaEstado);
 
  // Máquina de estados:

ExecutaMaquinaDeEstados();

 
  // Serial.flush();
  // fflush(stdin); // limpa o buffer do teclado
 
  
  //readSpectrometer();

  //printData();

 // calcMedia();

  delay(delayTime); 

   

}
