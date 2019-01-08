//Autor Quique Mansilla
//Escuela Tecnica N° 2 Obispo Colombres
//Control de Nivel de Cisterna Automatico que muestra estado y datos en LCD usando un sensor ultrasonico 
//Se mide el nivel y se expone en %, en variable "Nivel", el valor de dicha variable se usa para la evaluacion de las condiciones logicas

const int EchoPin = 11;
const int TriggerPin = 12;
const int BombaPin = 13;//Pin de salida para encender bomba
const int Maximo = 100; //nivel maximo 100% cisterna llena
const int Minimo = 90; //nivel minimo 90%, bajando de ese nivel se vuelve a llenar la cisterna
//int Nivel = 0; //Se declara la variable "Nivel",que se usará de aqui en adelante. Condicion inical, tanque vacio 

void setup() {
  Serial.begin(9600);
  pinMode(BombaPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  apagarBomba(BombaPin); //Apaga la Bomba cuando inicia
  
  //Ejecuta la condicion inicial: El sistema, cuando inicia, mide el nivel y si este es menor que el Minimo establecido encenderá la bomba hasta llenar cisterna,
  //luego ingresa en modo trabajo normal, caso contrario asegura apagando la bomba y pasa directamente a modo de trabajo normal
      
  float Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
  imprimeValor(Distancia); //Muestro en Monitor serial el valor de la distancia (cm)
  long int Nivel = nivel(Distancia); //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
  imprimeValor1(Nivel); //Muestro en Monitor serial el valor del nivel (%)
  delay(1000);

  //Si Nivel es menor que el minimo establecido mantiene el proceso de llenado de bomba mientras en nivel sea menor que el maximo establecido
  if (Nivel < Minimo){
    while (Nivel < Maximo) {
      encenderBomba(BombaPin); //Enciende la bomba para llenar la cisterna
      Serial.println("Iniciando llenado de cisiterna");
      Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
      imprimeValor(Distancia); //Muestro en Monitor serial el valor de la distancia (cm)
      Nivel = nivel(Distancia); //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
      imprimeValor1(Nivel); //Muestro en Monitor serial el valor del nivel (%)
    }
  }
   
  apagarBomba(BombaPin);
  Serial.println("Cisterna llena");
  delay(1000);  
}  

//Inicial lazo infinito, secuencial ingresando en el modo normal de trabajo
void loop() {
  Serial.println("Iniciando modo normal de trabajo");
  float Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
  imprimeValor(Distancia); //Muestro en Monitor serial el valor de la distancia (cm)
  long int Nivel = nivel(Distancia);  //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
  imprimeValor1(Nivel); //Muestro en Monitor serial el valor del nivel (%)
  delay(1000);
  
  //Si el nivel es mayor que el Minimo establecido mantiene la Bomba apagada mientras el nivel sea mayor que el minimo establecido
  if (Nivel > Minimo){
    do {
      Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
      imprimeValor(Distancia); //Muestro en Monitor serial el valor de la distancia (cm)
      Nivel = nivel(Distancia);  //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
      imprimeValor1(Nivel); //Muestro en Monitor serial el valor del nivel (%)
      apagarBomba(BombaPin);
      delay(1000);
    } while (Nivel > Minimo);                             
  }
  
  Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
  imprimeValor(Distancia); //Muestro en Monitor serial el valor de la distancia (cm)
  Nivel = nivel(Distancia);  //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
  imprimeValor1(Nivel); //Muestro en Monitor serial el valor del nivel (%)
  delay(1000);
    
  // Si el nivel esta por debajo del minimo establecido enciente la bomba hasta que alcamce el maximo (llena)
  if (Nivel < Minimo) {
    do {
    Serial.println("Reponer nivel de cisterna");
    Distancia = ping(TriggerPin, EchoPin); //Se llama a la funcion "ping" definida al final y guardo el valor que devuelve dicha funcion en variable Distancia
    imprimeValor(Distancia); //Muestro en Monitor serial el valor de la distancia (cm)
    Nivel = nivel(Distancia);  //Se llama a la funcion "nivel" definida al final y guardo el valor que devuelva esta funcion en variable "Nivel"
    imprimeValor1(Nivel); //Muestro en Monitor serial el valor del nivel (%)
    encenderBomba(BombaPin);
    delay(1000);
    } while (Nivel < Maximo);
  }
}
