# ServoMotor_PWM
O algoritmo implementa o controle de um servomotor através do microcontrolador RP2040 em linguagem C, Utilizando o Ambiente de desenvolvimento PICO SDK. o funcionamento é demonstrado através do simulador online WOKWI.

## Funcionalidades

- Executa uma rotina inicial onde o ServoMotor Parte da posição de 180°.
- Após 5 segundos em 180° se move para 90°.
- Após 5 segundos em 90° se move para 0°.
- Por fim após 5 segundos em 0° se move de 0° a 180° e vice-versa de maneira suave repetidamente.
## Hardware Necessário

- 1 Raspberry Pi Pico W (rp2040).
- 1 ServoMotor
- Fios de conexão.

## Pinagem

- Servo Motor: Pino 22

## Configuração do Ambiente

Antes de começar, certifique-se de que você tenha o ambiente de desenvolvimento do **Raspberry Pi Pico** configurado corretamente. Siga as instruções do [Raspberry Pi Pico SDK](https://www.raspberrypi.org/documentation/rp2040/getting-started/) para configurar o SDK e as ferramentas de compilação. Para visualição do projeto no simulador também é importante configurar o simuldor WOKWI no VS code, conforme as instruções no link [WOKWI para VS code](https://docs.wokwi.com/pt-BR/vscode/getting-started).

## Compilação e Upload

1. Compile o código usando o ambiente de desenvolvimento configurado.
2. Após a compilação, faça o upload do código para o seu **Raspberry Pi Pico**.

## Tecnologias Utilizadas

- **C/C++**
- **Raspberry Pi Pico SDK**
- **Simulador Online WOKWI**

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir um problema ou enviar um pull request.
