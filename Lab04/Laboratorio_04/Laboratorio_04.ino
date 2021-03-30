//---------------Laboratorio #4-----------------
//-----------Marco Juárez - 18516---------------
//----------Electronica digital II -------------

//Variables botones
const byte button_SW1 = PA_2;
const byte button_SW2 = 17;
const byte button = 31;
//Variables para semaforo
const int rojo = RED_LED;
const int amarillo = BLUE_LED;
const int verde = GREEN_LED;
//Estado de los botones
int buttonState_1 = 0;
int buttonState_2 = 0;
int buttonState_3 = 0;
//Contadores
int cont2=0;
int cont1=0;
//Salida de leds J1
const int LEDA = PB_0;
const int LEDB = PB_1;
const int LEDC = PB_2;
const int LEDD = PB_3;
const int LEDE = PB_4;
const int LEDF = PB_5;
const int LEDG = PB_6;
const int LEDH = PB_7;
//Salida de leds J2
const int LED1 = PE_0;
const int LED2 = PE_1;
const int LED3 = PE_2;
const int LED4 = PE_3;
const int LED5 = PE_4;
const int LED6 = PE_5;
const int LED7 = PD_1;
const int LED8 = PD_2;

const int win1 = RED_LED;
const int win2 = GREEN_LED;



void setup() {
  //Se configura los botones como pullups
  pinMode(button_SW1, INPUT_PULLUP);
  pinMode(button_SW2, INPUT_PULLUP);
  pinMode(button, INPUT_PULLUP);
  //Se configura como salida el puerto para las leds
  pinMode(rojo, OUTPUT);
  pinMode(amarillo, OUTPUT);
  pinMode(verde, OUTPUT);

   pinMode(LEDA, OUTPUT);
   pinMode(LEDB, OUTPUT);
   pinMode(LEDC, OUTPUT);
   pinMode(LEDD, OUTPUT);
   pinMode(LEDE, OUTPUT);
   pinMode(LEDF, OUTPUT);
   pinMode(LEDG, OUTPUT);
   pinMode(LEDH, OUTPUT);

   pinMode(LED1, OUTPUT);
   pinMode(LED2, OUTPUT);
   pinMode(LED3, OUTPUT);
   pinMode(LED4, OUTPUT);
   pinMode(LED5, OUTPUT);
   pinMode(LED6, OUTPUT);
   pinMode(LED7, OUTPUT);
   pinMode(LED8, OUTPUT);

}

void loop() {
  //Se lee el estado
  buttonState_1 = digitalRead(button_SW1);
  buttonState_2 = digitalRead(button_SW2);
  buttonState_3 = digitalRead(button);
  //Si el boton esta presionado empieza el semaforo
  if (buttonState_3 == 0) {        
    digitalWrite(rojo,1);
    delay(1000);
    digitalWrite(rojo,0);
       
    digitalWrite(amarillo,1);
    delay(1000);
    digitalWrite(amarillo,0);  
           
    digitalWrite(verde,1);
    delay(1000);
    digitalWrite(verde,0);

  } 
  else {
    delay(100); 
  }
  
  
        
   if (buttonState_2 == 1){
    delay(100);
   }
   if (buttonState_2 == 0){
    cont2++;
    switch(cont2){
      case 1:
      digitalWrite(LEDA,HIGH);
      digitalWrite(LEDB,LOW);
      digitalWrite(LEDC,LOW);
      digitalWrite(LEDD,LOW);
      digitalWrite(LEDE,LOW);
      digitalWrite(LEDF,LOW);
      digitalWrite(LEDG,LOW);
      digitalWrite(LEDH,LOW);
      delay(100);
      break;

      case 2:
      digitalWrite(LEDA,HIGH);
      digitalWrite(LEDB,HIGH);
      digitalWrite(LEDC,LOW);
      digitalWrite(LEDD,LOW);
      digitalWrite(LEDE,LOW);
      digitalWrite(LEDF,LOW);
      digitalWrite(LEDG,LOW);
      digitalWrite(LEDH,LOW);
      delay(100);
      break;
      case 3:
      digitalWrite(LEDA,HIGH);
      digitalWrite(LEDB,HIGH);
      digitalWrite(LEDC,HIGH);
      digitalWrite(LEDD,LOW);
      digitalWrite(LEDE,LOW);
      digitalWrite(LEDF,LOW);
      digitalWrite(LEDG,LOW);
      digitalWrite(LEDH,LOW);
      delay(100);
      break;
      case 4:
      digitalWrite(LEDA,HIGH);
      digitalWrite(LEDB,HIGH);
      digitalWrite(LEDC,HIGH);
      digitalWrite(LEDD,HIGH);
      digitalWrite(LEDE,LOW);
      digitalWrite(LEDF,LOW);
      digitalWrite(LEDG,LOW);
      digitalWrite(LEDH,LOW);
      delay(100);
      break;
      case 5:
      digitalWrite(LEDA,HIGH);
      digitalWrite(LEDB,HIGH);
      digitalWrite(LEDC,HIGH);
      digitalWrite(LEDD,HIGH);
      digitalWrite(LEDE,HIGH);
      digitalWrite(LEDF,LOW);
      digitalWrite(LEDG,LOW);
      digitalWrite(LEDH,LOW);
      delay(100);
      break;
      case 6:
      digitalWrite(LEDA,HIGH);
      digitalWrite(LEDB,HIGH);
      digitalWrite(LEDC,HIGH);
      digitalWrite(LEDD,HIGH);
      digitalWrite(LEDE,HIGH);
      digitalWrite(LEDF,HIGH);
      digitalWrite(LEDG,LOW);
      digitalWrite(LEDH,LOW);
      delay(100);
      break;
      case 7:
      digitalWrite(LEDA,HIGH);
      digitalWrite(LEDB,HIGH);
      digitalWrite(LEDC,HIGH);
      digitalWrite(LEDD,HIGH);
      digitalWrite(LEDE,HIGH);
      digitalWrite(LEDF,HIGH);
      digitalWrite(LEDG,HIGH);
      digitalWrite(LEDH,LOW);
      delay(100);
      break;
 
      case 8:
      digitalWrite(LEDA,HIGH);
      digitalWrite(LEDB,HIGH);
      digitalWrite(LEDC,HIGH);
      digitalWrite(LEDD,HIGH);
      digitalWrite(LEDE,HIGH);
      digitalWrite(LEDF,HIGH);
      digitalWrite(LEDG,HIGH);
      digitalWrite(LEDH,HIGH);
      delay(100);
      break;

      default:
      digitalWrite(LEDA,LOW);
      digitalWrite(LEDB,LOW);
      digitalWrite(LEDC,LOW);
      digitalWrite(LEDD,LOW);
      digitalWrite(LEDE,LOW);
      digitalWrite(LEDF,LOW);
      digitalWrite(LEDG,LOW);
      digitalWrite(LEDH,LOW);
      delay(100);
      }
          
   }
    //Contador 2
   if (buttonState_1 == 1){
    delay(100);
   }
   if (buttonState_1 == 0){
    cont1++;
    switch(cont1){
      case 1:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
      digitalWrite(LED6,LOW);
      digitalWrite(LED7,LOW);
      digitalWrite(LED8,LOW);
      delay(100);
      break;

      case 2:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
      digitalWrite(LED6,LOW);
      digitalWrite(LED7,LOW);
      digitalWrite(LED8,LOW);
      delay(100);
      break;
      case 3:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
      digitalWrite(LED6,LOW);
      digitalWrite(LED7,LOW);
      digitalWrite(LED8,LOW);
      delay(100);
      break;
      case 4:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,HIGH);
      digitalWrite(LED5,LOW);
      digitalWrite(LED6,LOW);
      digitalWrite(LED7,LOW);
      digitalWrite(LED8,LOW);
      delay(100);
      break;
      case 5:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,HIGH);
      digitalWrite(LED5,HIGH);
      digitalWrite(LED6,LOW);
      digitalWrite(LED7,LOW);
      digitalWrite(LED8,LOW);
      delay(100);
      break;
      case 6:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,HIGH);
      digitalWrite(LED5,HIGH);
      digitalWrite(LED6,HIGH);
      digitalWrite(LED7,LOW);
      digitalWrite(LED8,LOW);
      delay(100);
      break;
      case 7:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,HIGH);
      digitalWrite(LED5,HIGH);
      digitalWrite(LED6,HIGH);
      digitalWrite(LED7,HIGH);
      digitalWrite(LED8,LOW);
      delay(100);
      break;
      case 8:
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,HIGH);
      digitalWrite(LED4,HIGH);
      digitalWrite(LED5,HIGH);
      digitalWrite(LED6,HIGH);
      digitalWrite(LED7,HIGH);
      digitalWrite(LED8,HIGH);
      delay(100);
      break;

      default:
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
      digitalWrite(LED4,LOW);
      digitalWrite(LED5,LOW);
      digitalWrite(LED6,LOW);
      digitalWrite(LED7,LOW);
      digitalWrite(LED8,LOW);
      delay(100);
      }
          
   }

   if (cont1 == 9){
    digitalWrite(win1,HIGH);
    }

   if (cont2 == 9){
    digitalWrite(win2,HIGH);
    }
}
