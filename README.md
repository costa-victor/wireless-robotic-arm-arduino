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
 
 O **Controle PS2** utilizado foi um controle sem fio, contudo, as conexões permanecem as mesmas da imagem abaixo.
 
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
 - 01x Fonte ATX (simples)

 Neste projeto foi necessário utilizar um **Servo-Motor MG995** para a movimentação do **Braço** e outro para movimentação do **Antebraço** por conta da necessidade de maior torque dos motores para funcionar, enquanto para a **Garra** e a **Base** a utilização do **Servo-Motor SG90** foi suficiente.
 Para alimentação do **Module 2**  foi utilizado uma **Fonte ATX**, pois é permitido executar os 4 movimentos simultaneamente e a utilização de um regulador linear como o **LM7805** não é suficiente para a alimentação de todo o **Module 2**, pois durante a execução de movimentos combinados a corrente necessária foi superior à **2,5 A** e portanto caso desejar uma solução mais elegante que a utilização de uma **Fonte ATX**, sugiro utilizar um **Conversor DC/DC (Step Down) LM2596** ou similar.

### Integrantes: Victor Alberti Costa e Murilo Alves
