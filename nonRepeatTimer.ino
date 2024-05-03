#include "esp32-hal-timer.h"

hw_timer_t * timer1 = NULL;
volatile bool isr = false;

void ARDUINO_ISR_ATTR onTimer1() {
  isr = true;
  /*
  É uma boa prática evitar chamadas como Serial.println() dentro de uma ISR (Interrupt Service Routine) no ESP32, pois elas podem causar instabilidade devido à execução de operações não seguras para interrupção ou que demandam muito tempo.
  No seu código revisado, você usou a abordagem correta ao definir uma flag volatile chamada isr na ISR e manipular qualquer comunicação serial ou lógica mais complexa no loop principal. Essa é a maneira recomendada de lidar com interrupções, especialmente em plataformas sensíveis ao tempo como o ESP32. Isso evita problemas com watchdog timers e garante que a ISR seja o mais rápida e leve possível.
  Além disso, você utilizou timerWrite(timer1, 0) e timerAlarmEnable(timer1) para reiniciar o timer a partir do loop principal, o que é uma excelente maneira de controlar quando o timer deve começar a contar novamente, evitando manipulações desnecessárias na ISR.
*/
}

void setup() {
  Serial.begin(115200);
  timer1 = timerBegin(0, 80, true);
  timerAttachInterrupt(timer1, &onTimer1, true);
  // Configura o Timer 1 para o primeiro disparo
  timerAlarmWrite(timer1, 5000000, false);
  timerAlarmEnable(timer1);
  // setupTimer1();
}

void loop() {
  // Suponha que, baseado em alguma condição, você quer reiniciar o Timer 1 para um novo disparo único
  // Aqui, usamos uma entrada Serial simples para o exemplo
  if (Serial.available() > 0) {
    char c = Serial.read();
    if (c == 'r') { // Se o caractere 'r' for recebido, reinicie o timer
      timerWrite(timer1, 0);
      timerAlarmEnable(timer1);
      Serial.println("Timer 1 reiniciado para um novo disparo único.");
    }
  }
  if (isr) {
    isr=false;
    Serial.println("Timer 1 foi disparado");
  }
}
