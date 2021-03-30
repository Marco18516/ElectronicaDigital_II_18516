//-----------------Laboratorio#5-----------------
//------------Electronica Digital II-------------
//-----------------Marco Juárez------------------
//-----------Carné 18516 - Seccion 30 -----------

#include <SPI.h>
#include <SD.h>

int N;  

File root;

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  SPI.setModule(0);

  Serial.println(" ");
  Serial.println("Initializing SD card...");
  pinMode(PA_3, OUTPUT);

  if (!SD.begin(PA_3)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  root = SD.open("/"); //abrir archivos
  printDirectory(root, 0); //funcion que muestra archivos dentro de SD
}

void loop(){
  
     if (Serial.available() > 0) { //Leer valor que se ingresa
     N = Serial.read();//Se lee el valor ingresado
    }
    
      if (N == '1'){ //Si es igual 1 mostrar img1 que sera la imagen de Among Us
         root = SD.open("img1.txt");
        if (root) {    
          // read from the file until there's nothing else in it:
          while (root.available()) {
            Serial.write(root.read());
          }
          // close the file:
          root.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening test.txt");
        }
      }

      if (N == '2'){ //Si es igual 2 mostrar img2 que sera la imagen de rayo
         root = SD.open("img2.txt");
        if (root) {    
          // read from the file until there's nothing else in it:
          while (root.available()) {
            Serial.write(root.read());
          }
          // close the file:
          root.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening test.txt");
        }
      }

      if (N == '3'){ //Si es igual 3 mostrar img3 que sera la imagen de Kirby
         root = SD.open("img3.txt");
        if (root) {    
          // read from the file until there's nothing else in it:
          while (root.available()) {
            Serial.write(root.read());
          }
          // close the file:
          root.close();
        } else {
          // if the file didn't open, print an error:
          Serial.println("error opening test.txt");
        }
      } 
        
    else{}
 }    
        

void printDirectory(File dir, int NTabs) {//funcion que muestra los archivos de la SD 
   while(true) {
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       break;
     }
     for (uint8_t i=0; i<NTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, NTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
  Serial.println("");

}
