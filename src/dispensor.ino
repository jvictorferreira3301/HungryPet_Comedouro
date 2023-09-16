#include <virtuabotixRTC.h>
#include <Servo.h>

virtuabotixRTC myRTC(6, 7, 8);  // Cria um objeto RTC e define os pinos de comunicação.

const int pinoServo = 5;        // Pino digital usado para controlar o servo.

Servo s;                         // Cria um objeto do tipo Servo para controlar o servo.
int pos, r;                      // Variáveis para a posição do servo e controle.

void setup() {
  Serial.begin(9600);           // Inicializa a comunicação serial com uma taxa de 9600 baud.
  s.attach(pinoServo);           // Associa o objeto Servo ao pino digital.
  s.write(80);                   // Define a posição inicial do servo para 80 graus.
}

void loop() {
  myRTC.updateTime();            // Atualiza a hora do RTC.

  // Verifica se é hora de acionar o servo para liberar ração.
  if (myRTC.hours == 17 && myRTC.minutes == 11 && myRTC.seconds == 10) {
    for (r = 0; r <= 3; r++) {
      for (pos = 0; pos < 180; pos++) {
        s.write(pos);             // Move o servo de 0 a 180 graus.
        delay(1);                 // Pequeno atraso entre os movimentos.
      }
      delay(1000);                // Atraso de 1 segundo após cada ciclo de movimento.
      for (pos = 180; pos >= 0; pos--) {
        s.write(pos);             // Move o servo de volta de 180 a 0 graus.
        delay(1);
      }
      s.write(82);                // Retorna o servo à posição inicial.
    }
  }

  // Outras ações e leituras de RTC podem ser adicionadas aqui.

  myRTC.updateTime();
  Serial.print("Data : ");
  imprime_dia_da_semana(myRTC.dayofweek);
  Serial.print(", ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print("Hora : ");
  if (myRTC.hours < 10) {
    Serial.print("0");
  }
  Serial.print(myRTC.hours);
  Serial.print(":");
  if (myRTC.minutes < 10) {
    Serial.print("0");
  }
  Serial.print(myRTC.minutes);
  Serial.print(":");
  if (myRTC.seconds < 10) {
    Serial.print("0");
  }
  Serial.println(myRTC.seconds);
  delay(1000);
}

void imprime_dia_da_semana(int dia) {
  switch (dia) {
    case 1:
      Serial.print("Domingo");
      break;
    case 2:
      Serial.print("Segunda");
      break;
    case 3:
      Serial.print("Terça");
      break;
    case 4:
      Serial.print("Quarta");
      break;
    case 5:
      Serial.print("Quinta");
      break;
    case 6:
      Serial.print("Sexta");
      break;
    case 7:
      Serial.print("Sábado");
      break;
  }
}
