#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define PWM_MOTOR 22

#define WRAP_PERIOD 20000
#define PWM_DIVISOR 125.0
#define MOTOR_STEP 5

uint initMotorPWM();
void wrapHandler();
void initMove();

int main()
{
    uint slicenum = initMotorPWM();
    stdio_init_all();
    initMove();
    printf("Interrupção Ativada: ");
    pwm_set_irq_enabled(slicenum, true);

    while (true)
    {
        
    }
}

uint initMotorPWM()
{
    // inicializa o pwm do ServoMotor

    gpio_set_function(PWM_MOTOR, GPIO_FUNC_PWM);        // habilitar o pino GPIO como PWM
    uint sliceMotor = pwm_gpio_to_slice_num(PWM_MOTOR); // obter o canal PWM da GPIO

    pwm_clear_irq(sliceMotor);                            // Reseta a flag de interrupção para o slice do motor
    irq_set_exclusive_handler(PWM_IRQ_WRAP, wrapHandler); // interrupção quando o contador do slice atinge o wrap
    irq_set_enabled(PWM_IRQ_WRAP, true);                  // Habilitar ou desabilitar uma interrupção específica

    pwm_set_clkdiv(sliceMotor, PWM_DIVISOR); // define o divisor de clock do PWM
    pwm_set_wrap(sliceMotor, WRAP_PERIOD);   // definir o valor de wrap
    pwm_set_gpio_level(PWM_MOTOR, 100);      // definir o ciclo de trabalho (duty cycle) do pwm
    pwm_set_enabled(sliceMotor, true);       // habilita o pwm no slice correspondente

    return (sliceMotor);
}
void wrapHandler()
{
    static int Position = 500;                       // 180°
    static bool rise = true;                         // flag mudar o sentido do movimento
    pwm_clear_irq(pwm_gpio_to_slice_num(PWM_MOTOR)); // resetar o flag de interrupção

    if (rise)
    {
        Position += MOTOR_STEP; // Roda no sentido horário
        if (Position > 2400)
        {                    // caso a Position seja maior que 2470
            Position = 2400; // iguala Position a 2470
            sleep_ms(10);
            rise = false;    // muda o flag rise para trocar o sentido do movimento
        }
    }
    else
    {
        Position -= MOTOR_STEP; // Roda no sentido anti-horário
        if (Position < 500)
        {                   // caso a Position seja menor que 500
            Position = 500; // iguala Position a 500
            sleep_ms(10);
            rise = true;    // muda o flag rise para trocar o sentido do movimento
        }
    }
    pwm_set_gpio_level(PWM_MOTOR, Position); // define o ciclo ativo (Ton) de forma quadrática, para acentuar a variação de luminosidade.
}
void initMove(){
    pwm_set_gpio_level(PWM_MOTOR, 2400);
    sleep_ms(5000);
    pwm_set_gpio_level(PWM_MOTOR, 1470);
    sleep_ms(5000);
    pwm_set_gpio_level(PWM_MOTOR, 500);
    sleep_ms(5000);
}