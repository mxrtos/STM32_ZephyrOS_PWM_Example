#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>

#define NUM_STEPS 100U
#define SLEEP_DELTA_MSEC 20U

static uint32_t pulse_width_nsec = 0U;
static uint32_t pulse_width_delta_nsec = 0U;
static uint32_t steps_taken = 0U;
static bool increasing_intensity = true;

static const struct pwm_dt_spec fading_led = PWM_DT_SPEC_GET(DT_NODELABEL(fading_led));

void led_delta_timer_handler(struct k_timer *timer_info)
{
    int ret;
    if (increasing_intensity) {
        if (steps_taken < NUM_STEPS) {
            ret = pwm_set_pulse_dt(&fading_led, pulse_width_nsec);
            steps_taken++;
            pulse_width_nsec += pulse_width_delta_nsec;
        } else {
            increasing_intensity = false;
            steps_taken--;
            pulse_width_nsec -= pulse_width_delta_nsec;
        }
    } else {
        if (steps_taken > 0) {
            ret = pwm_set_pulse_dt(&fading_led, pulse_width_nsec);
            steps_taken--;
            pulse_width_nsec -= pulse_width_delta_nsec;
        } else {
            increasing_intensity = true;
            steps_taken++;
            pulse_width_nsec += pulse_width_delta_nsec;
        }
    }
}

K_TIMER_DEFINE(led_delta_timer, led_delta_timer_handler, NULL);


void main(void)
{
    if (!device_is_ready(fading_led.dev)) {
        printk("Error: PWM device %s is not ready\n", fading_led.dev->name);
        return;
    }

    // int ret;
    // while (1) {
    //     ret = pwm_set_pulse_dt(&fading_led, 0);
    //     k_sleep(K_SECONDS(1));
    //     ret = pwm_set_pulse_dt(&fading_led, 5000);
    //     k_sleep(K_SECONDS(1));
    //     ret = pwm_set_pulse_dt(&fading_led, 10000);
    //     k_sleep(K_SECONDS(1));
    //     ret = pwm_set_pulse_dt(&fading_led, 5000);
    //     k_sleep(K_SECONDS(1));
    // }
    pulse_width_delta_nsec = fading_led.period / NUM_STEPS;

    k_timer_start(&led_delta_timer, K_MSEC(SLEEP_DELTA_MSEC), K_MSEC(SLEEP_DELTA_MSEC) ); 
}