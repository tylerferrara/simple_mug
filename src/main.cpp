#include <stdio.h>
#include <time.h>
#include "pico/stdlib.h"

constexpr uint ONBOARD_LED = 25;
constexpr uint LED_PIN_RED = 2;
constexpr uint LED_PIN_GREEN = 13;
constexpr uint LED_PIN_BLUE = 20;
constexpr uint BTN_PIN = 16;
constexpr uint HEATER_PIN = 15;
constexpr uint ALIVE_INTERVAL_SEC = 2;

/****** Program State ******/
bool btn_down = false;
bool heater_active = false;
time_t alive = time(0);
bool alive_led_on = false;

void setup_leds() {
  gpio_init(ONBOARD_LED);
  gpio_init(LED_PIN_RED);
  gpio_init(LED_PIN_GREEN);
  gpio_init(LED_PIN_BLUE);

  gpio_set_dir(ONBOARD_LED, GPIO_OUT);
  gpio_set_dir(LED_PIN_RED, GPIO_OUT);
  gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
  gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);

  gpio_put(LED_PIN_RED, 0);
  gpio_put(LED_PIN_GREEN, 0);
  gpio_put(LED_PIN_BLUE, 0);
}

void setup_btns() {
  gpio_init(BTN_PIN);
  gpio_set_dir(BTN_PIN, GPIO_IN);
  gpio_pull_up(BTN_PIN);
}

void setup_heater() {
  gpio_init(HEATER_PIN);
  gpio_set_dir(HEATER_PIN, GPIO_OUT);
  gpio_put(HEATER_PIN, 0);
}

void setup_gpio() {
  stdio_init_all();
  sleep_ms(2000);
  setup_heater();
  setup_btns();
  setup_leds();
}

void handle_onboard_led() {
  if (difftime(time(0), alive) >= ALIVE_INTERVAL_SEC) {
    alive_led_on = !alive_led_on;
    gpio_put(ONBOARD_LED, alive_led_on);
    alive = time(0);
  }
}

int main() {
  setup_gpio();
  printf("Starting Mug firmware...\n");

  while (true) {
    if (gpio_get(BTN_PIN)) {
      if (!btn_down) {
        heater_active = !heater_active;
        gpio_put(ONBOARD_LED, heater_active ? 1 : 0);
        gpio_put(HEATER_PIN, heater_active ? 1 : 0);
      }
      btn_down = true;
    } else if (btn_down) {
      btn_down = false;
    }
  }
}

