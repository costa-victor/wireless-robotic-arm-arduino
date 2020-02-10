#include <PS2X_lib.h>
#include <SPI.h>
#include <RF24.h>
#include <printf.h>

RF24 myRadio (9, 10); // CE, CS
PS2X ps2x; // Criação de uma instancia de controle PS2

int error = 0;
byte type = 0;
byte vibrate = 0;

byte addresses[][6] = {"0"};

struct package
{
  int id=1;
  int LY;
  int LX;  
  int RY;
  int RX;
  int up;
  int down;
  int left;
  int right;
    int L1;
  int L2;
  int R1;
  int R2;
    int start;  
  int x;
  int square;   // Envia até aqui
  int triangle;
  int circle;


};


typedef struct package Package;
Package data;

void setup() { 
  // Address: 0
  // Channel: 115
  // Data Rate: 250 Kbit
  
  // Inicialização da comunicação serial
  Serial.begin(57600);
  delay(1000);
  
  // Configuraçao do modulo RF
  myRadio.begin();  
  myRadio.setChannel(115);  // Modulo suporta 128 canais diferentes, definimos o canal do pipe que queremos usar para a comunicação
  myRadio.setPALevel(RF24_PA_MAX);    // seta o valor maximo de poder para o alcance do modulo
  myRadio.setDataRate( RF24_250KBPS ) ;   //  data rate da transmissão -- menor datarate possível pra atender melhor o longo alcance
  myRadio.openWritingPipe( addresses[0]); // abrindo o pipe para comunicaação

   // Configuração do controle PS2
   // GamePad(clock, command, attention, data, Pressures?, Rumble?)
   error = ps2x.config_gamepad(8,6,5,7, false, false);  

    // Confirmação de sucesso ou falha
   if(error == 0){
     Serial.println("Found Controller, configured successful");
     Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
     Serial.println("holding L1 or R1 will print out the analog stick values.");
     Serial.println("Go to www.billporter.info for updates and to report bugs.");
   }
   else if(error == 1)
     Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   else if(error == 2)
     Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
   else if(error == 3)
     Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
   
   // Tipo de controle suportado
   type = ps2x.readType(); 
   switch(type) {
       case 0:
        Serial.println("Unknown Controller type");
       break;
       case 1:
        Serial.println("DualShock Controller Found");
       break;
       case 2:
         Serial.println("GuitarHero Controller Found");
       break;
   }
   delay(1000);
}

void loop() {
  // Lê as informações do controle o controle  
  ps2x.read_gamepad(false, vibrate);

  // Armazenando os dados de cada botão lido em variaveis da estrutura para ser enviados
  data.LX = ps2x.Analog(PSS_LX);
  data.LY = ps2x.Analog(PSS_LY);
  data.RX = ps2x.Analog(PSS_RX);
  data.RY = ps2x.Analog(PSS_RY);

  data.up = ps2x.Button(PSB_PAD_UP);
  data.down = ps2x.Button(PSB_PAD_DOWN);
  data.left = ps2x.Button(PSB_PAD_LEFT);
  data.right = ps2x.Button(PSB_PAD_RIGHT);

  data.x = ps2x.Button(PSB_CROSS);
  data.square = ps2x.Button(PSB_SQUARE);
  data.triangle = ps2x.Button(PSB_TRIANGLE);
  data.circle = ps2x.Button(PSB_CIRCLE);
  data.start = ps2x.Button(PSB_START);
  data.L1 = ps2x.Button(PSB_L1);
  data.L2 = ps2x.Button(PSB_L2);
  data.R1 = ps2x.Button(PSB_R1);
  data.R2 = ps2x.Button(PSB_R2);
  
  // Trasmissao dos dados
  myRadio.write(&data, sizeof(data)); 
  
  // Verificação no monitor serial
  Serial.print("\nPackage Transmitter: ");
  Serial.print(data.id);
  Serial.print("\n");
  Serial.println(data.LX, DEC);
  Serial.print(",");
  Serial.println(data.LY, DEC);
  Serial.print(",");
  Serial.println(data.RX, DEC);
  Serial.print(",");
  Serial.println(data.RY, DEC);
  Serial.print("X: ");
  Serial.print(data.x);
  Serial.println("");
  
  Serial.print("Square: ");
  Serial.print(data.square);
  Serial.println("");
  
  Serial.print("Triangle: ");
  Serial.print(data.triangle);
  Serial.println("");
  
  Serial.print("Circle: ");
  Serial.print(data.circle);
  Serial.println("");
  
  Serial.print("Start: ");
  Serial.print(data.start);
  Serial.println("");

  Serial.print("up: ");
  Serial.print(data.up);
  Serial.println("");

    Serial.print("down: ");
  Serial.print(data.down);
  Serial.println("");

    Serial.print("left: ");
  Serial.print(data.left);
  Serial.println("");

    Serial.print("right: ");
  Serial.print(data.right);
  Serial.println("");

  Serial.print("L1: ");
  Serial.print(data.L1);
  Serial.println("");

  Serial.print("R1: ");
  Serial.print(data.R1);
  Serial.println("");

  Serial.print("L2: ");
  Serial.print(data.L2);
  Serial.println("");

  
  Serial.print("R2: ");
  Serial.print(data.R2);
  Serial.println("");
  
  data.id = data.id + 1;
  
  delay(50);
}
