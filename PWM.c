#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define PWM_MOTOR 22

#define WRAP_PERIOD 20000
#define PWM_DIVISOR 125.0

void init();

int main()
{
    stdio_init_all();
    init();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
        
    }
}

void init (){
    //inicializa os pinos

    gpio_set_function(PWM_MOTOR, GPIO_FUNC_PWM); //habilitar o pino GPIO como PWM

    uint sliceMotor = pwm_gpio_to_slice_num(PWM_MOTOR); //obter o canal PWM da GPIO

    pwm_set_clkdiv(sliceMotor, PWM_DIVISOR); //define o divisor de clock do PWM

    pwm_set_wrap(sliceMotor, WRAP_PERIOD); //definir o valor de wrap

    pwm_set_gpio_level(PWM_MOTOR, 100); //definir o ciclo de trabalho (duty cycle) do pwm

    pwm_set_enabled(sliceMotor, true); //habilita o pwm no slice correspondente

}