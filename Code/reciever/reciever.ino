/* Projeto de oficina de integração --- Curso Engenharia de computação --- 7º Período
 * Autor: Victor Alberti Costa, Murilo Alves
 * Email: victorengcomp15@gmail.com
 * 
 * MÓDULO RECIEVER
 * 
 * Código referente ao módulo receptor de sinal proveniente do módulo RF do transmissor
 * e movimentação de 4 servomotores e um display LCD.
 * 
 * INSTRUÇÕES DE USO:
 *   Aberte START para começar
 *   Informe-se pelo display e divirta-se :)
 * 
 *    Movimentação BASE:
 *      ->  Seta para esquerda gera movimento no sentido Anti-horário
 *      ->  Seta para direita gera movimento no sentido Horário
 *      
 *    Movimentação BRAÇO:
 *      ->  Seta para cima gera movimento para frente
 *      ->  Seta para baixo gera movimento para trás
 *      
 *    Movimentação ANTEBRAÇO:
 *      ->  Analógico Direito pressionado para cima gera movimento para frente
 *      ->  Analógico Direito pressionado para baixo gera movimento para trás
 *      
 *    Movimentação GARRA:
 *      ->  Segurar R1 fecha a garra
 *      ->  Soltar R1 abre a garra
 */

#include <SPI.h>  
#include <RF24.h>
#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 5, 4, 3, 2); // lcd(rs, en, d4, d5, d6, d7) 
Servo base, braco, garra, antebraco;
RF24 myRadio (9, 10); // CE, CS

// variaveis utilizadas para controle do ang. dos servomotores
int posBase = 90;
int posBraco = 90;
int posAntebraco = 90;

// Estrutura dos dados que estão sendo enviados do transmissor - idem no transmissor
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
  int square;   // Consegue receber até aqui
  int triangle;
  int circle;
};

typedef struct package Package;
Package data;

// Definição do pipe de comunição do módulo RF
byte addresses[][6] = {"0"}; 

byte smiley[8] = {
  0b00000,
  0b00000,
  0b01010,
  0b00000,
  0b00000,
  0b10001,
  0b01110,
  0b00000
};


void setup() {
  // Incialização do display LCD
  lcd.begin(16, 2);
  lcd.createChar(1, smiley);
  lcd.clear();  
  
  // Mensagem inicial
  lcd.print("Pressione START");
  lcd.setCursor(0, 1);
  lcd.print("para comecar");

  // Inicialização dos servomotores
  base.attach(A5);
  braco.attach(A4);
  garra.attach(A0);
  antebraco.attach(A3);

  // Inicialização do monitor serial
  Serial.begin(57600);

  // Movimentação dos motores para testes
  delay(1000);
  base.write(90);
  braco.write(90);
  antebraco.write(90);
  garra.write(0);

  // Configuração do módulo RF
  // Documentação da biblioteca: https://maniacbug.github.io/RF24/classRF24.html#aeb9920e7a95699748b003c4a839b0814
  myRadio.begin(); 
  myRadio.setChannel(115);  // Canais de 0 - 127
  myRadio.setPALevel(RF24_PA_MAX);  // Power Level Amplifier - Máximo
  myRadio.openReadingPipe(1, addresses[0]);  // Numero identificador do pipe e seu endereço
  myRadio.setDataRate( RF24_250KBPS );  // Taxa de transmissão

  // Começa a ouvir o pipe
  myRadio.startListening(); 

  // Enquanto não ler o dado corresponde ao start, continua ouvindo
  do{
     if(myRadio.available()){
      while (myRadio.available()){
         myRadio.read( &data, sizeof(data) );
      }
    }  
  }while(!data.start);

  // Motivacional
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Divirta-se ");
  lcd.write((byte)1);
}


void loop() {
  // Sempre que recebe um dado, lê e armazena na struct data
  if ( myRadio.available()) 
  {    
    while (myRadio.available())
    {
      myRadio.read( &data, sizeof(data) );
    }

  // Inicio da verificação dos dados para tomar ações

  // Caso seja pressionado botões que contradizem o movimento, informa o usuário
  if((data.left == 1 && data.right == 1) || (data.up == 1 && data.down == 1)){
        lcd.clear();      
        lcd.setCursor(4, 0);
        lcd.print("Movimento");      
        lcd.setCursor(5, 1);
        lcd.print("Invalido");
    }
    else{
          // Lógica para a base
          // Conectado: Pin A5

          // Se pressionado Seta Esquerda
          if(data.left == 1){
            if(data.right || data.up || data.down){
              lcd.clear();      
              lcd.setCursor(4, 0);
              lcd.print("Movimento");      
              lcd.setCursor(5, 1);
              lcd.print("Diagonal");               
            }
            else{
              lcd.clear();      
              lcd.setCursor(0, 0);
              lcd.print("Movendo BASE...");      
              lcd.setCursor(2, 1);
              lcd.print("Horario");
            }            
            // Para dar movimento mais fluido e restringir o movimento para não forçar a estrutura
            if(posBase >= 10){  
              posBase = posBase - 5; 
              base.write(posBase);
            }
            else{
              lcd.clear();      
              lcd.setCursor(0, 0);
              lcd.print("Cuidado");      
              lcd.setCursor(2, 1);
              lcd.print("Limite !!");              
            }
          }
          
          // Se pressionado Seta Direita
          else if(data.right == 1){ 
            if(data.left || data.up || data.down){
              lcd.clear();      
              lcd.setCursor(4, 0);
              lcd.print("Movimento");      
              lcd.setCursor(5, 1);
              lcd.print("Diagonal");               
            }
            else{             
              lcd.clear();      
              lcd.setCursor(0, 0);
              lcd.print("Movendo BASE...");      
              lcd.setCursor(2, 1);
              lcd.print("Anti-horario");
            }                    
            if(posBase <= 160){
              posBase = posBase + 5;
              base.write(posBase);
            }
            else{
              lcd.clear();      
              lcd.setCursor(0, 0);
              lcd.print("Cuidado");      
              lcd.setCursor(2, 1);
              lcd.print("Limite !!");              
            }
          }
      
          // Lógica para o braço
          // Conectado: Pin A4
          
          // Se pressionado a Seta Para cima
          if(data.up == 1){
            if(data.right || data.left || data.down){
              lcd.clear();      
              lcd.setCursor(4, 0);
              lcd.print("Movimento");      
              lcd.setCursor(5, 1);
              lcd.print("Diagonal");               
            }
            else{             
              lcd.clear();      
              lcd.setCursor(0, 0);
              lcd.print("Movendo BRACO...");      
              lcd.setCursor(2, 1);
              lcd.print("Frente");
            }
            
            // Para dar movimento mais fluido e restringir o movimento para não forçar a estrutura
            if(posBraco >= 10){
              posBraco = posBraco - 5;
              braco.write(posBraco);    
            }
            else{
              lcd.clear();      
              lcd.setCursor(0, 0);
              lcd.print("Cuidado");      
              lcd.setCursor(2, 1);
              lcd.print("Limite !!");              
            }
          }

          // Se pressionado a Seta Para Baixo
          else if(data.down){
            if(data.right || data.up || data.left){
              lcd.clear();      
              lcd.setCursor(4, 0);
              lcd.print("Movimento");      
              lcd.setCursor(5, 1);
              lcd.print("Diagonal");               
            }
            else{
            lcd.clear();      
            lcd.setCursor(0, 0);
            lcd.print("Movendo BRACO...");      
            lcd.setCursor(2, 1);
            lcd.print("Atras");
            }

            // Reduzindo velocidade do braço
            if(posBraco <= 170){
              posBraco = posBraco + 5;
              braco.write(posBraco);
                
            }
            else{
              lcd.clear();      
              lcd.setCursor(0, 0);
              lcd.print("Cuidado");      
              lcd.setCursor(2, 1);
              lcd.print("Limite !!");              
            }            
          }

          // Como os motores utilizados são fracos eles não conseguem manter o braço imóvel, então quando
          // nada é pressionado o motor tenta manter o braço imóvel
          else if(!data.up && !data.down){
            posBraco = 90;
            braco.write(posBraco);
          }

         
          // Lógica para o Antebraço
          // Conectado: Pin A3
          
          // Se pressionado o analógico direito   
          if(data.RY < 127){
            lcd.clear();      
            lcd.setCursor(0, 0);
            lcd.print("Mov. ANTEBRACO");      
            lcd.setCursor(2, 1);
            lcd.print("Para cima");

            // Valores do PWM ajustados empiricamente
            // Parte onde necessita de maior torque dos motores, portanto o movimento mais suave
            // não dava bons resultados
            antebraco.write(0);
          }
          else if(data.RY > 127){
            lcd.clear();      
            lcd.setCursor(0, 0);
            lcd.print("Mov. ANTEBRACO");      
            lcd.setCursor(2, 1);
            lcd.print("Para baixo");

            antebraco.write(180);
          }
          // Como os motores utilizados são fracos eles não conseguem manter o braço imóvel, então quando
          // nada é pressionado o motor tenta manter o braço imóvel
          else if(data.RY == 127){
            antebraco.write(90);
          }

      
          // Lógica para a garra  -- microservo
          // Conectado: Pin A0
          
          // Se R2 estiver pressionado
          if(data.R2){
            lcd.setCursor(0, 0);
            lcd.clear();
            lcd.print("Ativando GARRA");

            garra.write(120);
          }
          else{
            garra.write(0);      
          }

          // Se nada estiver pressionado
          if(!data.left && !data.right && !data.up & !data.down && !data.R2 && data.RY == 127)
            lcd.clear();
      }            
  }

  // Para verificação no monitor serial
  Serial.print("\nPackage Receptor: ");
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

}
