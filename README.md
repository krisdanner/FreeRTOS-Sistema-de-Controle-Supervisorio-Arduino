(English)
## A supervisory control and data acquisition system with FreeRTOS for Arduino UNO R3

The system is running with 3 tasks simultaneously, but at the limit of the SRAM memory,
using a total of 718 bytes, the total size of which is only 2 KB, and the system makes
more than 1 KB for various tasks, and FreeRTOS itself consumes some of the memory as well.
memory as well.
The tasks implemented were as follows:

1. Reading a potentiometer that controls a servo motor, reading the position of the servo motor;
2. Reading the temperature and humidity of the environment using the DHT11 sensor.
3. Display of readings on a 16x2 LCD display with I2C module.

Note: It is necessary to manage the memory properly, as it is limited.
When serial communication is used, the number of words in the task increases.
It is advisable to use FreeRTOS on the Arduino UNO R3 only for 2 tasks, and a maximum of 3 tasks.
simple.

(Português)
## Um sistema de controle supervisório e aquisição de dados com FreeRTOS para Arduino UNO R3

O sistema está funcionando com 3 tarefas simultaneamente, mas no limite da memória SRAM, 
utilizando um total de 718 bytes, sendo que o tamanho total é apenas 2 KB, e o sistema faz
uso de mais de 1 KB para tarefas diversas, e o próprio FreeRTOS consome uma parte da
memória também.
A tarefas implementadas foram as seguintes:

1. Leitura de um potenciômetro que controla um servo motor, leitura da posição do servo motor;
2. Leitura da temperatura e umidade do ambiente através do sensor DHT11.
3. Exibição das leituras em um display LCD 16x2 com módulo I2C.

Obs: É necessário fazer o gerenciamento adequado da memória, tendo em vista que a mesma é 
limitada, quando usada a comunicação serial a quantidade de palavras na tarefa aumenta.
Aconselhável usar o FreeRTOS no Arduino UNO R3 apenas para 2 tarefas, e no máximo 3 tarefas
simples.


Circuito:
![Imagem do WhatsApp de 2024-12-29 à(s) 21 19 00_269fa832](https://github.com/user-attachments/assets/bb5187a5-b973-4827-bf9b-b1eb6ee33042)
