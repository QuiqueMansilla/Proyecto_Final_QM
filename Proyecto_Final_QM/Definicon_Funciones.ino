//ARCHIVO DE DEFINICION DE FUNCIONES

// Se define la funcion "ping" para medir la distancia usando las caracteristicas del sensor ultrasonico. El valor de la distancia indica el nivel(cm)
float ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;
  
  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);
  
  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos
  
  distanceCm = duration * 10 / 292/ 2;   //convertimos a distancia, en cm

  return distanceCm;
}

//Se define la funcion "nivel" que calcula el nivel de agua en %, suponemos una profundidad de 15 cm + distancia ubicacion del sensor (8 cm)
long int nivel(int Distancia){
  const int Vacio = 23; //Distancia maxima, cuando el bidon está vacio
  long int Porciento;
  Porciento = (-(100*(Distancia - Vacio)))/15;  //Calcula el nivel de agua en % Ecuacion de una recta Y  = Nivel(%); x = Distancia(cm)
                                                //x = 8 cm -> Y = 100% (valde lleno); x = 23 cm -> y = 0% (valde vacio)
  return Porciento;                                      
  }

//Definicion de funcion "impreimeValor" que muestra en monitor serial valor de "Distancia"
void imprimeValor(float Distancia) {
  Serial.print("Distancia: ");
  Serial.print(Distancia);
  Serial.println(" cm");
  return;
  }
  
//Definicion de funcion "imprimeValor1" que muestra en monitor serial valor de "Nivel" en %
void imprimeValor1(long int Nivel) {
  Serial.print("Nivel: ");
  Serial.print(Nivel);
  Serial.println(" %");
  return;
  }

//Se define la funcion "encenderBomba"
void encenderBomba(int BombaPin){
  digitalWrite(BombaPin, HIGH); // Enciende la bomba para que se llene la cisterna
  Serial.println("Bomba Encendida");
  }
  
//Se define la funcion "apagarBomba"
void apagarBomba(int BombaPin){
  digitalWrite(BombaPin, LOW); //Apaga la bomba
  Serial.println("Bomba Apagada");
  }  
