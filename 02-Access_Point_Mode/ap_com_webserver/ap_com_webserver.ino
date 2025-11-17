/*
 * --------------------------------------------------------------------------
 * PROJETO: ESP8266: Modos de Configuração Wireless (Wi-Fi)
 * ARQUIVO: ap_com_webserver.ino
 * * DESCRIÇÃO: Configura o ESP8266 como Access Point e hospeda um servidor 
 * web simples. Acessar em http://192.168.4.1/.
 * * AUTOR: Álacy Serrão - www.alacyserrao.com
 * DATA DE CRIAÇÃO: 16/11/2025
 * VERSÃO: 1.0.0
 * --------------------------------------------------------------------------
 */
// Biblioteca obrigatória para configurar o módulo ESP8266 (Wi-Fi).
#include <ESP8266WiFi.h>
// Biblioteca necessária para criar um servidor web e responder a requisições HTTP.
#include <ESP8266WebServer.h>


const char *ssid_ap = "ESP_WEB_SERVER";
const char *password_ap = "web12345";

// Cria o objeto servidor web na porta 80 (porta padrão para HTTP).
ESP8266WebServer server(80);

// -----------------------------------------------------------------------------
// Função: handleRoot()
// Descrição: Lida com as requisições HTTP feitas à URL raiz ("/") do servidor.
// Ela constrói e envia a página HTML de resposta ao cliente.
// -----------------------------------------------------------------------------
void handleRoot() {
  String html = "<html><body><h1>Servidor Web Ativo (Modo AP)</h1>";
  html += "<p>Acesse http://192.168.4.1/</p></body></html>";
  html += "<a href=\"https:\\alacyserrao.com\">By :: Alacy Serrão </a>";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  
  // Configura e inicia o Ponto de Acesso (Access Point).
  WiFi.softAP(ssid_ap, password_ap);
  
  Serial.println("\n--- MODO AP: Web Server ---");
  Serial.print("IP do AP: ");
  Serial.println(WiFi.softAPIP());

  // Define a rota: Quando o cliente acessar a URL raiz ("/")
  // a função 'handleRoot' será chamada para responder.
  server.on("/", handleRoot);
  // Inicia o servidor, tornando-o capaz de ouvir requisições na porta 80.
  server.begin(); 
  
  Serial.println("Servidor HTTP iniciado.");
}

void loop() {
  
  // O servidor precisa checar constantemente se há requisições HTTP
  // esperando para serem processadas.
  server.handleClient();
}
