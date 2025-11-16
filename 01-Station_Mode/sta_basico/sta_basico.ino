/*
-----------------------------------------------------------------------------
 ::   Projeto: ESP8266: Modos de Configuração Wireless (Wi-Fi).
 ::   Arquivo: sta_com_webclient.ino
 :: Descrição: Conecta o ESP8266 a uma rede Wireless (Wi-Fi) existente em modo cliente (Modo Station) e
               imprime o endereço IP no Monitor Serial.
 ::     Autor: Álacy Serrão - www.alacyserrao.com
 ::   Criação: 16/11/2025
 ::    Versão: 1.0.0
 -----------------------------------------------------------------------------
 */

// A biblioteca ESP8266WiFi fornece uma ampla coleção de métodos (funções) e propriedades em C++ para 
// configurar e operar um módulo ESP8266
#include <ESP8266WiFi.h>

// Defina as credenciais da sua rede Wireless (Wi-Fi)
const char* ssid = "Nome de sua rede";
const char* password = "Chave de sua rede";

void setup() {
  
  Serial.begin(115200);
  delay(10);
  
  Serial.println();
  Serial.print("Conectando-se a rede: ");
  Serial.println(ssid);

  // Define o modo do Wireless (Wi-Fi) como Station (Cliente)
  
  WiFi.mode(WiFiMode_t::WIFI_STA); 
  
  // Inicia a conexão
  WiFi.begin(ssid, password);

  // Loop de espera até que a conexão seja estabelecida
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Rede Wireless (Wi-Fi) conectado com sucesso!");
  Serial.print("Endereço IP: ");
  // Imprime o IP que o roteador atribuiu ao ESP8266
  Serial.println(WiFi.localIP()); 
}

void loop() {
  // O modo Station está ativo e conectado.
  // Código para envio de dados, p. ex., via HTTP/MQTT, serão implmentados aqui.
}
