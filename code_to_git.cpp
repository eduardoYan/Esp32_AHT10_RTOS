#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHT10.h>
#include <HTTPClient.h>

// Credenciais Wifi
const char* ssid = "Your_Wifi";
const char* password = "your_Wifi_Password";

// ThingSpeak API Key
const String apiKey = "ThingSpeak_Token_Key";

// Bot Telegram
const String botToken = "Telegram_Bot_Token";
const String chatID = "00000000";

// Instância do sensor AHT10
Adafruit_AHT10 aht;

// Variáveis globais para dados do sensor
float temperature = 0.0;
float humidity = 0.0;

// Handle para a task de processamento
TaskHandle_t processingTaskHandle;

// Função para ler dados do sensor

void readSensorData() {
  sensors_event_t humidityEvent, tempEvent;
  aht.getEvent(&humidityEvent, &tempEvent);

  temperature = tempEvent.temperature;
  humidity = humidityEvent.relative_humidity;

}

// Função para enviar dados ao ThingSpeak
void sendDataToThingSpeak() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "http://api.thingspeak.com/update?api_key=" + apiKey;
    url += "&field1=" + String(temperature);  // Temperatura
    url += "&field2=" + String(humidity);    // Umidade

    http.begin(url);
    int httpCode = http.GET(); // Envia GET request
    http.end(); // Libera recursos

    if (httpCode > 0) {
      Serial.println("Dados enviados ao ThingSpeak com sucesso.");
    } else {
      Serial.println("Falha ao enviar dados ao ThingSpeak.");
    }
  } else {
    Serial.println("WiFi não conectado.");
  }
}

// Função para enviar mensagens ao Telegram
void sendTelegramMessage(String message) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatID + "&text=" + message;

    http.begin(url);
    int httpCode = http.GET(); // Envia GET request
    http.end(); // Libera recursos

    if (httpCode > 0) {
      Serial.println("Mensagem enviada ao Telegram com sucesso.");
    } else {image.png
      Serial.println("Falha ao enviar mensagem ao Telegram.");
    }
  } else {
    Serial.println("WiFi não conectado.");
  }
}

// Task que processa os dados e realiza envio
void processDataTask(void* parameter) {
  for (;;) {
    // Aguarda notificação de nova leitura do sensor
    ulTaskNotifyTake(pdTRUE, portMAX_DELAY);


    // Envia dados ao ThingSpeak
    sendDataToThingSpeak();

    // Condição para enviar alerta ao Telegram
    if (temperature > 25) {
      sendTelegramMessage("Alerta: Temperatura alta! (" + String(temperature) + " °C)");
    }
  }
}

// Interrupção acionada pelo timer
void IRAM_ATTR onTimerInterrupt(TimerHandle_t xTimer) {
  readSensorData(); // Apenas coleta os dados
  xTaskNotifyGive(processingTaskHandle); // Notifica a task para processar os dados
}

void setup() {
  Serial.begin(115200);
  delay(3000);
  Wire.begin();
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("\nConectado ao WiFi!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());
  if (!aht.begin()) {
    Serial.println("AHT10 não encontrado. Verifique as conexões.");
  }
  Serial.println("Sensor AHT10 inicializado com sucesso.");
  // Cria a task de processamento de dados
  xTaskCreatePinnedToCore(processDataTask, "ProcessData", 4096, NULL, 1, &processingTaskHandle, 1);

  // Configura o timer para acionar a interrupção a cada 600000 ms
  TimerHandle_t timer = xTimerCreate("Timer", pdMS_TO_TICKS(6000), pdTRUE, NULL, onTimerInterrupt);
  if (timer != NULL) {
    xTimerStart(timer, 0); // Inicia o timer
    Serial.println("Timer iniciado.");
  } else {
    Serial.println("Falha ao criar o timer.");
  }
  vTaskDelete(NULL);
}

void loop() {
  // Nada a fazer aqui, as tasks e interrupções cuidam de tudo
}
