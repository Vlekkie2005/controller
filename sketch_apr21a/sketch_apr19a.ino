#include "tusb.h"

// Button GPIO pins
const uint8_t BUTTON_A_PIN = 25;
const uint8_t BUTTON_B_PIN = 23;
const uint8_t BUTTON_X_PIN = 26;
const uint8_t BUTTON_Y_PIN = 24;

// Joystick GPIO pins
const uint8_t JOYSTICK_X_PIN = 27;
const uint8_t JOYSTICK_Y_PIN = 28;

// Gamepad report structure
HID_GamepadReport_Data_t gamepad_report;

// Function to initialize GPIO
void initGPIO()
{
    // Set button pins as inputs with pull-ups
    gpio_init(BUTTON_A_PIN);
    gpio_set_dir(BUTTON_A_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_A_PIN);

    gpio_init(BUTTON_B_PIN);
    gpio_set_dir(BUTTON_B_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_B_PIN);

    gpio_init(BUTTON_X_PIN);
    gpio_set_dir(BUTTON_X_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_X_PIN);

    gpio_init(BUTTON_Y_PIN);
    gpio_set_dir(BUTTON_Y_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_Y_PIN);

    // Set joystick pins as analog inputs
    adc_init();
    adc_gpio_init(JOYSTICK_X_PIN);
    adc_gpio_init(JOYSTICK_Y_PIN);
}

// Function to update the gamepad report
void updateGamepadReport()
{
    // Read button states
    gamepad_report.buttons = 0;

    if (!gpio_get(BUTTON_A_PIN))
        gamepad_report.buttons |= GAMEPAD_BUTTON_A;

    if (!gpio_get(BUTTON_B_PIN))
        gamepad_report.buttons |= GAMEPAD_BUTTON_B;

    if (!gpio_get(BUTTON_X_PIN))
        gamepad_report.buttons |= GAMEPAD_BUTTON_X;

    if (!gpio_get(BUTTON_Y_PIN))
        gamepad_report.buttons |= GAMEPAD_BUTTON_Y;

    // Read joystick positions
    gamepad_report.axis_x = adc_read_blocking(JOYSTICK_X_PIN);
    gamepad_report.axis_y = adc_read_blocking(JOYSTICK_Y_PIN);
}

int main()
{
    tusb_init();

    initGPIO();

    while (1)
    {
        // Poll USB
        tud_task();

        // Update gamepad report
        updateGamepadReport();

        // Send the gamepad report
        tud_hid_gamepad_report(&gamepad_report);
    }

    return 0;
}
