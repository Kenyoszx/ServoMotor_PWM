#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/irq.h"
#include "hardware/pwm.h" //biblioteca para controlar o hardware de PWM

#define PWM_MOTOR 22

#define WRAP_PERIOD 20000
#define PWM_DIVISOR 125.0
#define MOTOR_STEP 5

void init();
void wrapHandler();

int main()
{
    stdio_init_all();
    init();

    while (true)
    {
        pwm_set_gpio_level(PWM_MOTOR, 2400);
        sleep_ms(5000);
        pwm_set_gpio_level(PWM_MOTOR, 1470);
        sleep_ms(5000);
        pwm_set_gpio_level(PWM_MOTOR, 500);
        sleep_ms(5000);
    }
}

void init()
{
    // inicializa os pinos

    gpio_set_function(PWM_MOTOR, GPIO_FUNC_PWM);        // habilitar o pino GPIO como PWM
    uint sliceMotor = pwm_gpio_to_slice_num(PWM_MOTOR); // obter o canal PWM da GPIO

    pwm_clear_irq(sliceMotor);                            // Reseta a flag de interrupção para o slice do motor
    irq_set_exclusive_handler(PWM_IRQ_WRAP, wrapHandler); //interrupção quando o contador do slice atinge o wrap
    irq_set_enabled(PWM_IRQ_WRAP, true);                  // Habilitar ou desabilitar uma interrupção específica

    pwm_set_clkdiv(sliceMotor, PWM_DIVISOR); // define o divisor de clock do PWM
    pwm_set_wrap(sliceMotor, WRAP_PERIOD);   // definir o valor de wrap
    pwm_set_gpio_level(PWM_MOTOR, 100);      // definir o ciclo de trabalho (duty cycle) do pwm
    pwm_set_enabled(sliceMotor, true);       // habilita o pwm no slice correspondente
}
void wrapHandler()
{
    static int fade = 0;                             // nível de iluminação
    static bool rise = true;                         // flag para elevar ou reduzir a iluminação
    pwm_clear_irq(pwm_gpio_to_slice_num(PWM_MOTOR)); // resetar o flag de interrupção

    if (rise)
    {           // caso a iluminação seja elevada
        fade++; // aumenta o nível de brilho
        if (fade > 255)
        {                 // caso o fade seja maior que 255
            fade = 255;   // iguala fade a 255
            rise = false; // muda o flag rise para redução do nível de iluminação
        }
    }
    else
    {           // caso a iluminação seja reduzida
        fade--; // reduz o nível de brilho
        if (fade < 0)
        {                // Icaso o fade seja menor que 0
            fade = 0;    // iguala fade a 0
            rise = true; // muda o flag rise para elevação no nível de iluminação
        }
    }

    pwm_set_gpio_level(PWM_MOTOR, fade * fade); // define o ciclo ativo (Ton) de forma quadrática, para acentuar a variação de luminosidade.
}