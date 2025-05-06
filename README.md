# Estação de Monitoramento Ambiental e Fisiológico com ESP32

Este projeto consiste no desenvolvimento de uma estação de monitoramento ambiental e fisiológico utilizando o microcontrolador **ESP32**, sensores **AHT10** (temperatura/umidade) e **MAX30100** (oximetria/frequência cardíaca), com integração ao **ThingSpeak** e **Telegram** para coleta e visualização dos dados. O sistema foi desenvolvido com foco em **sistemas embarcados** e **IoT** utilizando o **FreeRTOS** para gerenciamento de tarefas em tempo real.

## Funcionalidades

- **Monitoramento ambiental**: Coleta de dados de temperatura e umidade através do sensor **AHT10**.
- **Monitoramento fisiológico**: Teste de oximetria e frequência cardíaca com o sensor **MAX30100** (não funcional no projeto devido a problemas de comunicação via I2C).
- **Comunicação em tempo real**: Envio dos dados coletados para a plataforma **ThingSpeak** e notificação via **Telegram**.
- **Gestão de tarefas**: Utilização do **FreeRTOS** para gerenciamento de tarefas em múltiplas threads com controle de prioridades.
- **Reconexão automática**: Implementação de reconexão automática à rede Wi-Fi em caso de falhas de conexão.
- **Segurança e estabilidade**: Implementação de rotinas de **watchdog** e tratamento de falhas de sensores.

## Estrutura do Projeto

- **ESP32**: Microcontrolador principal.
- **AHT10**: Sensor para medir temperatura e umidade.
- **MAX30100**: Sensor para medir oxigenação sanguínea e frequência cardíaca (não integrado ao sistema devido a falhas de comunicação).
- **ThingSpeak**: Plataforma de IoT para visualização dos dados.
- **Telegram Bot**: Envio de dados em tempo real para o Telegram.

## Como Usar

### Requisitos

- **Hardware**:
  - Placa **ESP32**.
  - Sensores **AHT10** e **MAX30100**.
  - Acesso à rede Wi-Fi.

- **Software**:
  - IDE de desenvolvimento **Arduino** ou **PlatformIO**.
  - Biblioteca **Wire** para comunicação I2C.

- **Configuração**:
  - Clone o repositório:
   git clone https://github.com/eduardoYan/Esp32_AHT10_RTOS.git

  - Abra o código na sua IDE preferida e configure a rede Wi-Fi e o canal do ThingSpeak.

  - Instale as bibliotecas necessárias:
    Wire: Para comunicação I2C.
    ThingSpeak: Para comunicação com a plataforma.

  - Carregue o código no seu ESP32
    
  - O sistema começará a coletar dados de temperatura e umidade, enviando-os para o ThingSpeak e notificando no Telegram.


