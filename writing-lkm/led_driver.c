#include <linux/gpio.h> // for the GPIO functions
#include <linux/init.h>
#include <linux/interrupt.h> // for the IRQ code
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Loris");
MODULE_DESCRIPTION("A simple driver for the LED");
MODULE_VERSION("0.1");

#define GPIO_LED_PIN 60    /* P9_12 (GPIO 60) */
#define GPIO_BUTTON_PIN 46 /* P8_16 (GPIO 46) */

static bool gpio_led_value = false; /* led value (true==on / false==off) */
static int irq_number;              /* irq number is set at runtime by fn gpio_init */

static irq_handler_t gpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs);

static int __init gpio_init(void)
{
    int rc = 0;
    printk(KERN_INFO "LED_DRIVER: Initializing led\n");
    if (!gpio_is_valid(GPIO_LED_PIN))
    {
        printk(KERN_ERR "LED_DRIVER: Invalid gpio pin %d\n", GPIO_LED_PIN);
        return -ENODEV;
    }
    gpio_request(GPIO_LED_PIN, "sysfs");
    gpio_direction_output(GPIO_LED_PIN, gpio_led_value);
    gpio_set_value(GPIO_LED_PIN, gpio_led_value);
    gpio_export(GPIO_LED_PIN, false);

    printk(KERN_INFO "LED_DRIVER: Initializing button\n");
    if (!gpio_is_valid(GPIO_BUTTON_PIN))
    {
        printk(KERN_ERR "LED_DRIVER: Invalid gpio pin %d\n", GPIO_BUTTON_PIN);
        return -ENODEV;
    }
    gpio_request(GPIO_BUTTON_PIN, "sysfs");
    gpio_direction_input(GPIO_BUTTON_PIN);
    gpio_set_debounce(GPIO_BUTTON_PIN, 200);
    gpio_export(GPIO_BUTTON_PIN, false);

    irq_number = gpio_to_irq(GPIO_BUTTON_PIN);
    rc = request_irq(irq_number, (irq_handler_t)gpio_irq_handler, IRQF_TRIGGER_RISING,
                     "led_driver_irq_handler", /* used in /proc/interrupts */
                     NULL);
    printk(KERN_INFO "LED_DRIVER: GPIO %d (input - rising edge) mapped to IRQ %d\n", GPIO_BUTTON_PIN, irq_number);
    printk(KERN_INFO "LED_DRIVER: Module loaded successfully!\n");
    return rc;
}

static void __exit gpio_exit(void)
{
    gpio_unexport(GPIO_LED_PIN);
    gpio_unexport(GPIO_BUTTON_PIN);
    free_irq(irq_number, NULL);
    gpio_free(GPIO_LED_PIN);
    gpio_free(GPIO_BUTTON_PIN);
    printk(KERN_INFO "LED_DRIVER: Module unloaded successfully!\n");
}

static irq_handler_t gpio_irq_handler(unsigned int irq, void *dev_id, struct pt_regs *regs)
{
    gpio_led_value = !gpio_led_value;
    gpio_set_value(GPIO_LED_PIN, gpio_led_value);
    printk(KERN_INFO "LED_DRIVER: Interrupt! LED is %s\n", gpio_get_value(GPIO_LED_PIN) ? "on" : "off");
    return (irq_handler_t)IRQ_HANDLED;
}

module_init(gpio_init);
module_exit(gpio_exit);
