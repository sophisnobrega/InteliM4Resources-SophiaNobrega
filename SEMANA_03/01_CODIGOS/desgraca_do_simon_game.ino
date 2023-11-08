#include <Arduino.h>

const int pinosLED[] = {2, 4, 16, 17};
const int pinosBotao[] = {14, 27, 26, 25};
const int pinoBotaoReset = 12;
const int pinoBuzzer = 34;

int sequencia[20];
int sequenciaJogador[20];
int comprimentoSequencia = 0;
int turnoJogador = false;
int pontuacao = 0;
bool jogadorCometeuErro = false;
bool jogadorVenceu = false;

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(pinosLED[i], OUTPUT);
    pinMode(pinosBotao[i], INPUT_PULLUP);
  }
  pinMode(pinoBotaoReset, INPUT_PULLUP);
  pinMode(pinoBuzzer, OUTPUT);

  randomSeed(analogRead(0));

  while (digitalRead(pinoBotaoReset) == HIGH) {
  }
}

void reiniciarJogo() {
  if (digitalRead(pinoBotaoReset) == LOW) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(pinosLED[i], LOW);
    }
    comprimentoSequencia = 0;
    turnoJogador = false;
    pontuacao = 0;
    jogadorCometeuErro = false;
    sequenciaJogador[0] = -1;
  }
}

void loop() {
  if (digitalRead(pinoBotaoReset) == LOW) {
    delay(50);
    if (digitalRead(pinoBotaoReset) == LOW) {
      reiniciarJogo();
      while (digitalRead(pinoBotaoReset) == LOW) {
      }
      delay(50);
    }
  }

  if (!turnoJogador) {
    adicionarCorAleatoriaASequencia();
    mostrarSequencia();
    turnoJogador = true;
  }

  for (int i = 0; i < comprimentoSequencia; i++) {
    int botaoPressionado = aguardarPressionarBotao();
    if (botaoPressionado == sequencia[i]) {
      tocarTons(500, 200);
      delay(300);
    } else {
      turnoJogador = false;
      jogadorCometeuErro = true;
      tocarTonsErro();
      pontuacao = 0;
      comprimentoSequencia = 0;
      sequenciaJogador[0] = -1;
      todosLEDsLigados();
      break;
    }

    if (i == comprimentoSequencia - 1) {
      pontuacao++;
      delay(500);
      turnoJogador = false;
      jogadorCometeuErro = false;
    }
  }
}

void adicionarCorAleatoriaASequencia() {
  int numeroAleatorio = random(0, 4);
  sequencia[comprimentoSequencia] = pinosLED[numeroAleatorio];
  comprimentoSequencia++;
}

void mostrarSequencia() {
  for (int i = 0; i < comprimentoSequencia; i++) {
    digitalWrite(sequencia[i], HIGH);
    tocarTons(500, 200);
    delay(500);
    digitalWrite(sequencia[i], LOW);
    delay(200);
  }
}

int aguardarPressionarBotao() {
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(pinosBotao[i]) == LOW) {
        while (digitalRead(pinosBotao[i]) == LOW) {
        }
        return pinosLED[i];
      }
    }
  }
}

void tocarTons(int frequencia, int duracao) {
  tone(pinoBuzzer, frequencia, duracao);
  delay(duracao);
  noTone(pinoBuzzer);
}

void tocarTonsErro() {
  if (jogadorCometeuErro) {
    tone(pinoBuzzer, 200, 500);
    delay(500);
    noTone(pinoBuzzer);
  }
}

void todosLEDsLigados() {
  if (jogadorCometeuErro) {
    for (int i = 0; i < 4; i++) {
      digitalWrite(pinosLED[i], HIGH);
    }
    delay(1000);
    for (int i = 0; i < 4; i++) {
      digitalWrite(pinosLED[i], LOW);
    }
  }
}

void vencedor() {
  if (!jogadorCometeuErro && comprimentoSequencia == 20) {
    jogadorVenceu = true;
  }

  if (jogadorVenceu) {
    for (int contador = 0; contador < 3; contador++) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(pinosLED[i], HIGH);
      }
      delay(500);
      for (int i = 0; i < 4; i++) {
        digitalWrite(pinosLED[i], LOW);
      }
      delay(500);
    }
  }
}
