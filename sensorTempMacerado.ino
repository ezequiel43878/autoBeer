/// NOTA - SISTEMA EN SECCIONES A: AGUA PARA MACERAR (74°) - B - MACERANDO (67°) - C RECIRCULADO : 78°

#include <OneWire.h>                
#include <DallasTemperature.h>
#include <LiquidCrystal.h>
#include <Keypad.h>

// DECLARO PINES CON I/O
#define LED     A4
#define ALERTA  A2

OneWire ourWire(A5);                //Se establece el pin 2  como bus OneWire
DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

LiquidCrystal lcd(8, 9, 10, 11, 12, 13); //Crear el objeto LCD con los números correspondientes (rs, en, d4, d5, d6, d7)


// Teclado
const byte rowsCount = 4;
const byte columsCount = 4;
 
char keys[rowsCount][columsCount] = {
   { '1','2','3', 'A' },
   { '4','5','6', 'B' },
   { '7','8','9', 'C' },
   { '*','0','#', 'D' }
};

float temp = 0;
int tempPreMacerado = 74;
int tempMacerado = 23;
int tempPostMacerado = 78;

bool preMacerado = false;
bool macerado = false;
bool postMacerado = false;

const byte rowPins[rowsCount] = { 0, A3, 2, 3 };
const byte columnPins[columsCount] = { 4, 5, 6, 7 }; 
Keypad keypad = Keypad(makeKeymap(keys), rowPins, columnPins, rowsCount, columsCount);

void setup() {
  
  pinMode(LED,OUTPUT);
  pinMode(ALERTA,OUTPUT);
  
  lcd.begin(16, 2);  //Didemsion del display
  
}

void aguaPreMacerado();  // Ingresa con la tecla A
void aguaMacerado();     // Ingresa con la tecla B
void aguaPostMacerado();  // Ingresa con la tecla C
 
void loop() {

  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  temp= sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

  lcd.setCursor(0, 1);   // Ubicamos el cursor en la primera posición(columna:0) de la segunda línea(fila:1)
  lcd.print("T:");
  lcd.print(temp);
  lcd.print(" C");

  char key = keypad.getKey();

  switch(key){
    case 'A' : preMacerado = true;
               macerado = false;
               postMacerado = false;
               break;
    case 'B' : macerado = true;
               preMacerado = false;
               postMacerado = false;
               break;
    case 'C' : postMacerado = true;
               macerado = false;
               preMacerado = false;
               break;
           
    }

  aguaPreMacerado();
  aguaMacerado();
  aguaPostMacerado();

}

void aguaPreMacerado(){
   if(preMacerado){
       lcd.setCursor(0, 0);
       lcd.display();
       lcd.print("A:preMac ");
       lcd.print(tempPreMacerado);
       lcd.print("    ");
       if (temp <= tempPreMacerado){
          digitalWrite(LED, LOW);
        }
       else
          digitalWrite(LED, HIGH); 
    }           
  }

void aguaMacerado(){
   if(macerado){
       lcd.setCursor(0, 0);
       lcd.display();
       lcd.print("B:Mac+-2 ");
       lcd.print(tempMacerado);
       lcd.print("    ");
       if (temp <= tempMacerado-2 || temp >= tempMacerado+2){
          digitalWrite(LED, HIGH);
        }
       else
          digitalWrite(LED, LOW); 
    }           
  }

void aguaPostMacerado(){
   if(postMacerado){
       lcd.setCursor(0, 0);
       lcd.display();
       lcd.print("C:postMac ");
       lcd.print(tempPostMacerado);
       lcd.print("    ");
       if (temp <= tempPostMacerado){
          digitalWrite(LED, LOW);
        }
       else
          digitalWrite(LED, HIGH); 
    }           
  }
