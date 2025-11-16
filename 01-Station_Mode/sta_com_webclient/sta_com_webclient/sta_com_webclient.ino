/*
-----------------------------------------------------------------------------
 ::   Projeto: ESP8266: Modos de Configuração Wireless (Wi-Fi).
 ::   Arquivo: sta_basica.ino
 :: Descrição: Conecta o ESP8266 em Modo Station e realiza uma requisição 
               HTTP GET simples a um servidor web externo.
 ::     Autor: Álacy Serrão - www.alacyserrao.com
 ::   Criação: 16/11/2025
 ::    Versão: 1.0.0
 -----------------------------------------------------------------------------
 */

// A biblioteca ESP8266WiFi fornece uma ampla coleção de métodos (funções) e 
// propriedades em C++ para configurar e operar um módulo ESP8266
#include <ESP8266WiFi.h>
// A biblioteca WiFiClient é usada para conectar, enviar e receber dados de e para 
// servidores.
#include <WiFiClient.h>

// Defina as credenciais da sua rede Wireless (Wi-Fi)
const char* ssid = "Nome de sua rede";
const char* password = "Chave de sua rede"; 
const char* host = "www.alacyserrao.com"; // Servidor de destino

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  Serial.println("\n--- MODO STATION: Cliente HTTP ---");

  // Conexão Wireless (Wi-Fi) modo cliente (Modo Station)
  WiFi.mode(WiFiMode_t::WIFI_STA); 
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n Wireless (Wi-Fi) conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP()); 
}

void loop() {
  // Executa o cliente HTTP a cada 30 segundos
  if (WiFi.status() == WL_CONNECTED) {
    
    Serial.printf("\nConectando-se a %s...", host);
    
    // Tenta conectar ao host na porta 80 (HTTP)
    if (!client.connect(host, 80)) {
      Serial.println("Falha na conexão com o host!");
      return;
    }
    
    // Envia o cabeçalho da requisição HTTP GET
    Serial.println("Enviando requisição GET...");
    client.print(String("GET / HTTP/1.1\r\n") +
                 "Host: " + host + "\r\n" +
                 "Conexão: fechada\r\n\r\n");

    // Aguarda a resposta do servidor
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) { // Timeout de 5 segundos
        Serial.println(">>> Tempo limite dãe resposta esgotado!");
        client.stop();
        return;
      }
    }

    // Lê e imprime a resposta do servidor
    Serial.println("Recebendo resposta:");
    while (client.available()) {
      String linha = client.readStringUntil('\r');
      Serial.print(linha);
    }
    
    // Fecha a conexão
    client.stop();
    Serial.println("\nConexão fechada.");
  }
  
  delay(30000); // Espera 30 segundos antes da próxima requisição
}
