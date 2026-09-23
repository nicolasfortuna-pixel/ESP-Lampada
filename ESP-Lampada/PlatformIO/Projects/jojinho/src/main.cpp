////////////////////////////////////////////////////////////////////////
// Bibliotecas
#include <Arduino.h>
#include <WiFi.h>
#include <Firebase_ESP_Client.h>

////////////////////////////////////////////////////////////////////////
// Credenciais do Wi-Fi 
#define WIFI_SSID "pacoca"
#define WIFI_PASSWORD "Versinhos@"

////////////////////////////////////////////////////////////////////////
// Credenciais do FB
#define API_KEY "AIzaSyD_sYsXnnnw82H6qUWLe25z3zoarqL03HQ"
#define DATABASE_URL "https://luze-7340c-default-rtdb.firebaseio.com/"
#define USER_EMAIL "venecos@gmail.com"
#define USER_PASSWORD "123456"
// Configuração FB
FirebaseConfig config;
FirebaseAuth auth;
FirebaseData fbdo;

////////////////////////////////////////////////////////////////////////
// Pino da lâmpada
const int lampPin = 13;

////////////////////////////////////////////////////////////////////////
// Inicialização
void setup()
{
    ////////////////////////////////////////////////////////////////////////
    // Começo
    pinMode(lampPin, OUTPUT);
    pinMode(2, OUTPUT);
    digitalWrite(lampPin, LOW);
    Serial.begin(9600);


    ////////////////////////////////////////////////////////////////////////
    // Wi-Fi
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    Serial.print("Conectando ao Wi-Fi");

    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(300);
    }

    Serial.println();
    Serial.println("Wi-Fi conectado!");


    ////////////////////////////////////////////////////////////////////////
    // Firebase
    config.api_key = API_KEY;
    config.database_url = DATABASE_URL;

    auth.user.email = USER_EMAIL;
    auth.user.password = USER_PASSWORD;

    Firebase.begin(&config, &auth);

    Firebase.reconnectWiFi(true);
}


////////////////////////////////////////////////////////////////////////
// Loop
void loop()
{
    if (Firebase.ready())
    {
        if (Firebase.RTDB.getBool(&fbdo, "lampada/estado"))
        {
            bool estado = fbdo.boolData();

            Serial.print("Estado da lampada: ");

            if (estado)
            {
                Serial.println("LIGADA");
                digitalWrite(2, HIGH);
            }
            else
            {
                Serial.println("DESLIGADA");
                digitalWrite(2, LOW);
            }

            digitalWrite(lampPin, estado ? HIGH : LOW);
        }
        else
        {
            Serial.print("Erro Firebase: ");
            Serial.println(fbdo.errorReason());
        }
    }
    else
    {
        Serial.println("Firebase ainda nao esta pronto!");
    }

    delay(100);
}

//#define ENABLE_USER_AUTH
#define ENABLE_DATABASE

#include <FirebaseClient.h>
#include "ExampleFunctions.h"

#define WIFI_SSID "ADEMAR_2G"
#define WIFI_PASSWORD "99581430"

#define API_KEY "AIzaSyD_sYsXnnnw82H6qUWLe25z3zoarqL03HQ"
#define USER_EMAIL "niculas@gmail.com"
#define USER_PASSWORD "12345678"
#define DATABASE_URL "https://luze-7340c-default-rtdb.firebaseio.com/"

#define RELE_PIN 13

SSL_CLIENT ssl_client;

using AsyncClient = AsyncClientClass;
AsyncClient aClient(ssl_client);

UserAuth user_auth(
  API_KEY,
  USER_EMAIL,
  USER_PASSWORD,
  3000
);

FirebaseApp app;
RealtimeDatabase Database;

AsyncResult databaseResult;

bool firebaseReady = false;
bool ultimoEstado = false;

void setup()
{
  Serial.begin(115200);
  delay(1000);

  pinMode(RELE_PIN, OUTPUT);
  digitalWrite(RELE_PIN, LOW);

  Serial.println();
  Serial.println("================================");
  Serial.println("ESP32 + Firebase");
  Serial.println("================================");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Conectando ao Wi-Fi");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }

  Serial.println();
  Serial.println("Wi-Fi conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Firebase.printf(
    "Firebase Client v%s\n",
    FIREBASE_CLIENT_VERSION
  );

  set_ssl_client_insecure_and_buffer(ssl_client);

  Serial.println("Inicializando Firebase...");

  initializeApp(
    aClient,
    app,
    getAuth(user_auth),
    auth_debug_print,
    "authTask"
  );

  app.getApp<RealtimeDatabase>(Database);

  Database.url(DATABASE_URL);

  Serial.println("Firebase configurado.");
  Serial.println();
}

void loop()
{
  app.loop();

  if (app.ready())
  {
    if (!firebaseReady)
    {
      firebaseReady = true;

      Serial.println("Firebase conectado!");
      Serial.println("Lendo estado da lampada...");
    }

    bool estado = Database.get<bool>(
      aClient,
      "/lampada/estado"
    );

    if (aClient.lastError().code() == 0)
    {
      if (estado != ultimoEstado)
      {
        ultimoEstado = estado;

        Serial.print("Estado recebido: ");

        if (estado)
        {
          Serial.println("LIGADA");
          digitalWrite(RELE_PIN, HIGH);
        }
        else
        {
          Serial.println("DESLIGADA");
          digitalWrite(RELE_PIN, LOW);
        }
      }
    }
    else
    {
      Serial.print("Erro ao ler Firebase: ");
      Serial.print(aClient.lastError().message());
      Serial.print(" | Codigo: ");
      Serial.println(aClient.lastError().code());
    }
  }

  delay(500);
} 

// NICOLAS
// #define ENABLE_USER_AUTH
// #define ENABLE_DATABASE

// #include <FirebaseClient.h>
// #include "ExampleFunctions.h"

// #define WIFI_SSID "ADEMAR_2G"
// #define WIFI_PASSWORD "99581430"

// #define API_KEY "AIzaSyD_sYsXnnnw82H6qUWLe25z3zoarqL03HQ"
// #define USER_EMAIL "niculas@gmail.com"
// #define USER_PASSWORD "12345678"
// #define DATABASE_URL "https://luze-7340c-default-rtdb.firebaseio.com/"

// #define RELE_PIN 13

// SSL_CLIENT ssl_client;

// using AsyncClient = AsyncClientClass;
// AsyncClient aClient(ssl_client);

// UserAuth user_auth(
//   API_KEY,
//   USER_EMAIL,
//   USER_PASSWORD,
//   3000
// );

// FirebaseApp app;
// RealtimeDatabase Database;

// AsyncResult databaseResult;

// bool firebaseReady = false;
// bool ultimoEstado = false;

// void setup()
// {
//   Serial.begin(115200);
//   delay(1000);

//   pinMode(RELE_PIN, OUTPUT);
//   digitalWrite(RELE_PIN, LOW);

//   Serial.println();
//   Serial.println("================================");
//   Serial.println("ESP32 + Firebase");
//   Serial.println("================================");

//   WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

//   Serial.print("Conectando ao Wi-Fi");

//   while (WiFi.status() != WL_CONNECTED)
//   {
//     Serial.print(".");
//     delay(300);
//   }

//   Serial.println();
//   Serial.println("Wi-Fi conectado!");
//   Serial.print("IP: ");
//   Serial.println(WiFi.localIP());

//   Firebase.printf(
//     "Firebase Client v%s\n",
//     FIREBASE_CLIENT_VERSION
//   );

//   set_ssl_client_insecure_and_buffer(ssl_client);

//   Serial.println("Inicializando Firebase...");

//   initializeApp(
//     aClient,
//     app,
//     getAuth(user_auth),
//     auth_debug_print,
//     "authTask"
//   );

//   app.getApp<RealtimeDatabase>(Database);

//   Database.url(DATABASE_URL);

//   Serial.println("Firebase configurado.");
//   Serial.println();
// }

// void loop()
// {
//   app.loop();

//   if (app.ready())
//   {
//     if (!firebaseReady)
//     {
//       firebaseReady = true;

//       Serial.println("Firebase conectado!");
//       Serial.println("Lendo estado da lampada...");
//     }

//     bool estado = Database.get<bool>(
//       aClient,
//       "/lampada/estado"
//     );

//     if (aClient.lastError().code() == 0)
//     {
//       if (estado != ultimoEstado)
//       {
//         ultimoEstado = estado;

//         Serial.print("Estado recebido: ");

//         if (estado)
//         {
//           Serial.println("LIGADA");
//           digitalWrite(RELE_PIN, HIGH);
//         }
//         else
//         {
//           Serial.println("DESLIGADA");
//           digitalWrite(RELE_PIN, LOW);
//         }
//       }
//     }
//     else
//     {
//       Serial.print("Erro ao ler Firebase: ");
//       Serial.print(aClient.lastError().message());
//       Serial.print(" | Codigo: ");
//       Serial.println(aClient.lastError().code());
//     }
//   }

//   delay(500);
// } 