## Robotnik -> Equipe de robótica da UTFPR - Pato Branco
## Descrição do projeto:
Em resumo trata-se de um Braço robótico de 4 Eixos impresso em 3D controlado remotamente por um Controle de PS2 que consiste basicamente de 2 Módulos, conforme a imagem abaixo:

![description](https://media.giphy.com/media/iF7Q4W4Bpecq1VxmoA/giphy.gif)

Os códigos comentados e todo o material necessário para criação e/ou continuação desde projeto estão contidos nesse repositório na pasta **Code**.

A seguir você encontrará a descrição do funcionamento, referências, demonstração e dicas para aprimorar o projeto atual.

### Module 1:
 A função do **Arduino** neste módulo é de receber e interpretar os dados ao pressionar/mover algum de seus botões/analógico do **Controle de PS2** e armazenar os dados em uma struct contendo o estado de cada botão e enviar para o **Module 2** via **Wireless RF** com o **NRF24L01**.
 
 **Hardware:**
 - 01x NRF24L01
 - 01x Arduino Uno
 - 01x Controle PS2 (qualquer)
 
 O **Controle PS2** utilizado foi um controle sem fio, contudo, as conexões permanecem as mesmas da imagem abaixo.
 
 ![](http://microcontrolado.com/wp-content/uploads/2013/02/pinagem-conector-playstation.png)
 
 Para mais informações sobre o **Module 1**, recomendo os materiais:
 * [Como funciona os pinos do Controle PS2]( http://microcontrolado.com/controle-playstation-no-pic-2/)
 * [Como funciona o NRF24L01]( https://lastminuteengineers.com/nrf24l01-arduino-wireless-communication/)
 * [Documentação da Lib para o NRF24L01]( https://maniacbug.github.io/RF24/classRF24.html#aeb9920e7a95699748b003c4a839b0814)
 

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
 
O projeto original, utilizado como base para montagem e adaptação em um braço robótico de 4 eixos que pode ser encontrado abaixo em **Montagem do Braço**, deste vários arquivos **STL** que compoêm o braço precisaram ser modificadas, pois o projeto original conta com uma **Bomba de Sucção**, que foi substituída por uma **Garra** e utilizada como referência o material abaixo **Garra adaptada**.

Todas as alterações nos arquivos **STL** foram realizadas utilizando o software **Autocad 2012 Student Version** e estão contidos neste repositório na pasta **3D Files**.

Todas as substituições de peças do projeto original podem ser comparadas acessando o arquivo **orçamento**.

 Para mais informações sobre o **Module 2**, recomendo os materiais:
 * [Documentação Lib Display LCD]( https://www.arduino.cc/en/Reference/LiquidCrystal)
 * [Montagem do Braço](https://www.youtube.com/watch?v=dlAjBVg1W2E&t=)
 * [Garra adaptada]( http://www.eezyrobots.it/eba_mk2.html#)
 

 
### Demonstração/Resultado:
Teste realizado antes de integrar com o montagem do braço impresso.

 ![demonstration1](https://media.giphy.com/media/JTsvwLzcdkDZwfN1cp/giphy.gif)
 
 
### Integrantes: Victor Alberti Costa e Murilo Santos Alves
