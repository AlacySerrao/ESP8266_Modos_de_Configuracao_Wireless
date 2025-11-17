/*
 * --------------------------------------------------------------------------
 * PROJETO: ESP8266: Modos de Configuração Wireless (Wi-Fi)
 * ARQUIVO: ap_basico.ino
 * * DESCRIÇÃO: Cria um roteador simples (Access Point) e verifica a conexão 
 * de outros dispositivos.
 * * AUTOR: Álacy Serrão - www.alacyserrao.com
 * DATA DE CRIAÇÃO: 16/11/2025
 * VERSÃO: 1.0.0
 * --------------------------------------------------------------------------
 */
// Biblioteca obrigatória para configurar o módulo ESP8266 (Wi-Fi).
#include <ESP8266WiFi.h>


// --- Configurações do ACCESS POINT ---
const char *ssid_ap = "ESP8266_AP";
const char *password_ap = "senha12345"; 

void setup() {
  Serial.begin(115200);
  delay(10);
 
  Serial.println("\n--- MODO AP: Access Point Básico ---");

  // Inicia o modo Soft AP (Ponto de Acesso)
  WiFi.softAP(ssid_ap, password_ap);
  
  Serial.print("Ponto de Acesso criado. \nSSID: ");
  Serial.println(ssid_ap);
  Serial.print("IP do AP: ");
  Serial.println(WiFi.softAPIP());
  Serial.print("Senha: ");
  Serial.println(password_ap);
}

void loop() {
  // Mostra o número de clientes conectados
  int n = WiFi.softAPgetStationNum();
  if (n > 0) {
    Serial.print("Clientes conectados: ");
    Serial.println(n);
  }
  delay(5000);
}
