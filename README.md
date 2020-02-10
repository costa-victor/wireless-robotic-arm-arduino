## Robotnik -> Equipe de robótica da UTFPR - Pato Branco
## Descrição do projeto:
O projeto consiste de 2 Módulos, conforme a imagem abaixo:

![description](https://media.giphy.com/media/iF7Q4W4Bpecq1VxmoA/giphy.gif)

### Module 1:
 A função do **Arduino** neste módulo é de receber e interpretar os dados ao pressionar/mover algum de seus botões/analógico do **Controle de PS2** e armazenar os dados em uma struct contendo o estado de cada botão e enviar para o **Module 2** via **Wireless RF**.
 
 **Hardware:**
 - 01x NRF24L01
 - 01x Arduino Uno
 - 01x Controle PS2 (qualquer)
 
 O **Controle PS2** utilizado foi um controle sem fio, contudo as conexões permanecem as mesmas da imagem abaixo.
 
 ![demonstration1](https://media.giphy.com/media/JTsvwLzcdkDZwfN1cp/giphy.gif)
 
### Module 2:
 A função do **Arduino** neste módulo é de receber os dados enviados do **Module 1** e com isso gerar instruções para o jogador através do **Display LCD** e ao mesmo tempo enviar um sinal PWM aos **Servo-motores** para assim mover o **Braço Robótico de 4 eixos impresso em 3D**  como desejar, dentro dos movimentos que os **Servo-motores** permitem e são eles:
 
 - Rotaçao da **Base** em até 180º
 - Erguer/Abaixar o **Braço**
 - Esticar/Contrair o **Antebraço**
 - Fechar/Abrir **Garra** 

Todos os movimentos acima são exibidos no **Display LCD**.
 
 **Hardware:**
 - 01x NRF24L01
 - 01x Arduino Uno
 - 02x Servo-Motor SG90
 - 02x Servo-Motor MG995

Neste projeto foi necessário utilizar um **Servo-Motor MG995** para a movimentação do **Braço** e outro para movimentação do **Antebraço** por conta da necessidade de maior torque para funcionar, enquanto para a **Garra** e a **Base** a utilização do **Servo-Motor SG90** foi suficiente.

### Integrantes: Victor Alberti Costa e Murilo Alves
