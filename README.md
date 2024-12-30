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
