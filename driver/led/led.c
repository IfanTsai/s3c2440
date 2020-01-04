#include <linux/init.h>
#include <linux/module.h>
#include <linux/leds.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <asm/arch/regs-gpio.h>
#include <asm/io.h>

struct s3c2440_led_dev {
    struct led_classdev led_cdev;
    unsigned int gpio;
};

static void s3c2400_led_set(struct led_classdev *led_cdev,
			    enum led_brightness value)
{
	struct s3c2440_led_dev *led = container_of(led_cdev, struct s3c2440_led_dev, led_cdev);
	unsigned int gpio = led->gpio;

    s3c2410_gpio_setpin(gpio, value);
}

int s3c2440_led_probe(struct platform_device *pdev)
{
    int ret;
    unsigned int gpio;
    struct resource *resource;
    struct s3c2440_led_dev *led;

    printk(KERN_INFO "led probe\n");

    led = kzalloc(sizeof(*led), GFP_KERNEL);
    if (IS_ERR(led)) {
        printk(KERN_ERR "%s:%d kzalloc struct s3c2440_led_dev fail !\n", __func__, __LINE__);
        return -EINVAL;
    }
    platform_set_drvdata(pdev, led);
    
    resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (IS_ERR(resource)) {
        printk(KERN_ERR "%s:%d platform_get_resource fail !\n", __func__, __LINE__);
        return -EINVAL;
    }
    
    gpio = resource->start;
    s3c2410_gpio_cfgpin(gpio, S3C2410_GPIO_OUTPUT);
 
    led->gpio = gpio;
    led->led_cdev.name = pdev->name;
    led->led_cdev.brightness_set = s3c2400_led_set;

    ret = led_classdev_register(&pdev->dev, &led->led_cdev);
    if (ret < 0) {
        kfree(led);
        return ret;
    }

    return 0;
}

int s3c2440_led_remove(struct platform_device *pdev)
{
    struct s3c2440_led_dev *led = platform_get_drvdata(pdev);

    led_classdev_unregister(&led->led_cdev);
    kfree(led);

    return 0;
}

static struct platform_driver s3c2440_led_driver = {
	.probe		= s3c2440_led_probe,
	.remove		= s3c2440_led_remove,
	.driver		= {
		.name		= "s3c2440_led",
		.owner		= THIS_MODULE,
	},
};

static int __init s3c2440_led_init(void)
{
    return platform_driver_register(&s3c2440_led_driver);
}

static void __exit s3c2440_led_exit(void)
{
    platform_driver_unregister(&s3c2440_led_driver);
}

module_init(s3c2440_led_init);
module_exit(s3c2440_led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ifan Tsai <i@caiyifan.cn>");
MODULE_DESCRIPTION("led driver for s3c2440");