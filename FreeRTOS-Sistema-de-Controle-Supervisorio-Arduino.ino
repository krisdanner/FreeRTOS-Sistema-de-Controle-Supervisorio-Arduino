/*
#===========================================#
# FreeRTOS Sistema de Controle Suprvisório  #
#===========================================#
# Autor: Christian Danner Ramos de Carvalho #
# Universidade Federal do Maranhão          #
# 29/12/2024                                #
#===========================================#
*/

#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Arduino_FreeRTOS.h>

// Configurações do display LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Endereço I2C do LCD

// Configurações do sensor DHT
#define DHTPIN 4  // Pino do sensor DHT
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Pino potenciômetro
#define potPin A0

// Variáveis globais compartilhadas
volatile int pos;
volatile int val;
volatile float temp;
volatile float umid;

void setup() {

  // Inicializa o monitor serial
  //Serial.begin(9600);

  lcd.init();
  lcd.backlight();

  // Definição das Tarefas
  xTaskCreate(tarefaPotServo, "tarefaPotServo", 128, NULL, 5, NULL);  // 1 - prioridade mín, 5 - prioridade máx // palavra = 1 byte // máx de palavras na memória = 1000
  xTaskCreate(tarefaTempUmi, "tarefaTempUmi", 450, NULL, 4, NULL);
  xTaskCreate(exibirLCD, "exibirLCD", 140, NULL, 3, NULL);

  // Cria a tarefa de monitoramento
  //xTaskCreate(TaskMonitor, "Monitor", 128, NULL, 4, NULL);
}

void loop() {
 
}


void tarefaPotServo() {

  Servo meuServo;  // Cria um objeto Servo para controlar o servo motor
  //int pos;          // Variável para armazenar a posição do servo motor
  //int val;          // Variável para armazenar o valor lido do potenciômetro

  meuServo.attach(6);  // Associa o servo motor ao pino digital 6 do Arduino
  meuServo.write(0);   // Define a posição inicial do servo motor para 0 graus

  while (1) {
    val = analogRead(potPin);         // Lê o valor do potenciômetro (0 a 1023)
    val = constrain(val, 0, 1023);    // Garante que o valor fique entre 0 e 1023
    pos = map(val, 0, 1023, 0, 180);  // Mapeia o valor do potenciômetro para a faixa de 0 a 180 graus
    meuServo.write(pos);              // Define a posição do servo motor

    //Serial.print("Pot: ");
    //Serial.print(val);
    //Serial.print(" / Pos: ");
    //Serial.println(pos);

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void tarefaTempUmi() {
  dht.begin();

  while (1) {

    temp = dht.readTemperature();
    umid = dht.readHumidity();

    if (isnan(temp) || isnan(umid)) {
      //Serial.println(F("Failed to read from DHT sensor!"));  //Por padrão, strings literais são armazenadas na RAM, mas usando F(), a string é mantida na memória de programa (flash), que geralmente é mais abundante que a RAM no Arduino.
      return;
    }
    
    //Serial.print("Umidade: ");
    //Serial.print(hum);
    //Serial.print(" / Temperatura: ");
    //Serial.print(temp);
    //Serial.println("°C");
    
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}


// Tarefa de monitoramento (exibição no LCD)
void exibirLCD(void *pvParameters) {
  for (;;) {
    // Exibir valores do potenciômetro e servo
    lcd.setCursor(0, 0);
    lcd.print("Pot:");
    lcd.print("    ");
    lcd.setCursor(4, 0);
    lcd.print(val);
    lcd.setCursor(8, 0);
    lcd.print(" Pos:");
    lcd.print("   ");
    lcd.setCursor(13, 0);
    lcd.print(pos);

    // Exibir valores do temperatura e humidade
    lcd.setCursor(0, 1);
    lcd.print("Tem:");
    lcd.print("    ");
    lcd.setCursor(4, 1);
    lcd.print(temp);
    lcd.setCursor(8, 1);
    lcd.print(" Umi:");
    lcd.print("   ");
    lcd.setCursor(13, 1);
    lcd.print(umid);

    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

/*
void TaskMonitor(void *pvParameters) {
  for (;;) {
    // Obtém o High Water Mark da tarefa "TaskExample"
    UBaseType_t highWaterMark = uxTaskGetStackHighWaterMark(NULL);

    // Calcula a memória utilizada (em palavras da pilha)
    Serial.print("Espaço mínimo livre na pilha: ");
    Serial.print(highWaterMark);
    Serial.println(" palavras");

    // Aguarda 2 segundos antes de monitorar novamente
    vTaskDelay(pdMS_TO_TICKS(2000));
  }
}*/