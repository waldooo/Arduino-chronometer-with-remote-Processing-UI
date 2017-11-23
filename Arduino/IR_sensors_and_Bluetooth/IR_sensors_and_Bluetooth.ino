
unsigned long tempo_inicial = 0;
unsigned long tempo_final = 0;


void setup() {
  pinMode (2, INPUT);
  pinMode (3, INPUT);
  attachInterrupt (digitalPinToInterrupt(2), sensor_partida, RISING);
  attachInterrupt (digitalPinToInterrupt(3), sensor_chegada, RISING);

  //LOW to trigger the interrupt whenever the pin is low,
  //CHANGE to trigger the interrupt whenever the pin changes value
  //RISING to trigger when the pin goes from low to high,
  //FALLING for when the pin goes from high to low.

  Serial.begin (9600);
}

void loop() {

  //conferir se os sensores estão funcionando:
  //Serial.println(digitalRead(2));
  //Serial.println(digitalRead(3));
  //delay(1000);

  //imprimir o tempo na porta serial:
  if (tempo_final != 0)
  {
    Serial.print("tempo total: ");
    
    // como o tempo é contado em microsegundos, é necesário
    // dividir por 1000000 para ter o valor em segundos
    float total = (tempo_final - tempo_inicial);
    total /= 1000000;
    Serial.print(total);
    Serial.println(" segundos");

    // reinicia os valores para uma nova contagem
    tempo_inicial = 0;
    tempo_final = 0;

    delay(1000); // previne que o tempo de chegada seja disparado novamente
  }

}

void sensor_partida()
{
  if (tempo_inicial == 0 && tempo_final == 0)
  {
    tempo_inicial = micros();
  }
}

void sensor_chegada()
{
  if (tempo_inicial != 0 && tempo_final == 0)
  {
    tempo_final = micros();
  }
}
