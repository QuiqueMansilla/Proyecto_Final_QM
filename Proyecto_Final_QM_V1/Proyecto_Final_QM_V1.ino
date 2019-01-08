//Autor Quique Mansilla
//Escuela Tecnica N° 2 Obispo Colombres
//Control de Nivel de Cisterna Automatico que muestra estado y datos en LCD usando un sensor ultrasonico 
//Se mide el nivel y se expone en %, en variable "Nivel", el valor de dicha variable se usa para la evaluacion de las condiciones logicas
//Se usa en este proyecto un LCD Winstar WH1602A

#include <LiquidCrystal.h>

const int EchoPin = 11;
const int TriggerPin = 12;
const int BombaPin = 13;//Pin de salida para encender bomba
const int Maximo = 100; //nivel maximo 100% cisterna llena
const int Minimo = 90; //nivel minimo 90%, bajando de ese nivel se vuelve a llenar la cisterna
//int Nivel = 0; //Se declara la variable "Nivel",que se usará de aqui en adelante. Condicion inical, tanque vacio
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //Configuracion del LCD: parametros (RS, EN, D4, D5, D6, D7) 

void setup() {
  pinMode(BombaPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  
  lcd.begin(16, 2); // Configura el lcd con los siguientes parametros (Columnas, Filas) LCD de 16 columnas x 2 filas
  
  apagarBomba(BombaPin); //Apaga la Bomba cuando inicia

  lcd.println("   Iniciando");
  lcd.print(" Control Nivel");
  delay(2000);
  lcd.clear();
  
  //Ejecuta la condicion inicial: El sistema, cuando inicia, mide el nivel y si este es menor que el Minimo establecido encenderá la bomba hasta llenar cisterna,
  //luego ingresa en modo trabajo normal, caso contrario asegura apagando la bomba y pasa directamente a modo de trabajo normal
      
  lcd.println("  Nivel Inical");
  float Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
  long int Nivel = nivel(Distancia); //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
  imprimeLCDValor(Nivel); //Muestra en display LCD el valor del Nivel en %
  delay(1000);
  
  //Si Nivel es menor que el minimo establecido mantiene el proceso de llenado de bomba mientras en nivel sea menor que el maximo establecido
  if (Nivel < Minimo){
    while (Nivel < Maximo) {
      encenderBomba(BombaPin); //Enciende la bomba para llenar la cisterna
      lcd.clear();
      lcd.println("Llenando Tanque");
      Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
      Nivel = nivel(Distancia); //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
      imprimeLCDValor(Nivel); //Muestro en display LCD el valor del nivel (%)
    }
  }
   
  apagarBomba(BombaPin);
  lcd.clear();
  lcd.println(" Cisterna llena");
  delay(1000);  
}  

//Inicial lazo infinito, secuencial ingresando en el modo normal de trabajo
void loop() {
  lcd.println("  Modo normal");
  lcd.print("   de trabajo");
  delay(1000);
  float Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
  long int Nivel = nivel(Distancia); //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
  imprimeLCDValor(Nivel); //Muestro display LCD el valor del nivel (%)
  delay(1000);
  
  //Si el nivel es mayor que el Minimo establecido mantiene la Bomba apagada mientras el nivel sea mayor que el minimo establecido
  if (Nivel > Minimo){
    do {
      Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
      Nivel = nivel(Distancia);  //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
      apagarBomba(BombaPin);
      lcd.println(" Bomba Apagada");
      imprimeLCDValor(Nivel); //Muestro en display LCD el valor del nivel (%)
      delay(1000);
    } while (Nivel > Minimo);
    lcd.clear();
  }
  
  //Actualiza el valor de la medicion de nivel en %
  Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
  Nivel = nivel(Distancia);  //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
   
  // Si el nivel esta por debajo del minimo establecido enciente la bomba hasta que alcamce el maximo (Tanque lleno)
  if (Nivel < Minimo) {
    lcd.println(" Reponer Nivel ");
    delay(1000);
    lcd.clear();
    do {
    encenderBomba(BombaPin);
    lcd.println("Bomba Encendida");
    Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
    Nivel = nivel(Distancia);  //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
    imprimeLCDValor(Nivel); //Muestro en display LCD el valor del nivel (%)
    delay(1000);
    } while (Nivel < Maximo);
    lcd.clear();
  }
}
