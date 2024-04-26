/* main.c - Application main entry point */

#include <zephyr/types.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>
#include <zephyr/sys/printk.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/kernel.h>

#include <zephyr/bluetooth/bluetooth.h>
#include <zephyr/bluetooth/hci.h>
#include <zephyr/bluetooth/conn.h>
#include <zephyr/bluetooth/uuid.h>
#include <zephyr/bluetooth/gatt.h>
#include <zephyr/bluetooth/services/bas.h>
#include <zephyr/bluetooth/services/hrs.h>

#include "../inc/display.h"
#include "../inc/spi.h"
#include "../inc/r_enc.h"
#include "../inc/bluetooth.h" //TODO: TEST THAT BLUETOOTH WORKS ON DONGLE W/ MOVING BT CODE TO SEP. FILE
#include "../inc/bme.h"
#include "../inc/temp.h"
#include "../inc/hr.h"

const struct device* gpio0_dev = DEVICE_DT_GET(DT_NODELABEL(gpio0));
const struct device* gpio1_dev = DEVICE_DT_GET(DT_NODELABEL(gpio1));
const struct device* i2c0_dev = DEVICE_DT_GET(DT_NODELABEL(i2c0));
const struct device *spi1_dev = DEVICE_DT_GET(DT_NODELABEL(spi1));

int main(void)
{
	uint16_t color = 0xFFFF; // Black color

	main_display_init(spi1_dev, gpio0_dev, color);

	int err;
	err = bt_enable(NULL);
	if (err) {
		printk("Bluetooth init failed (err %d)\n", err);
		return 0;
	}

	bt_ready();
	bt_conn_auth_cb_register(&auth_cb_display);
	init_enc();
	BME688_Init();
	init_hr();

	/* Implement notification. At the moment there is no suitable way
	 * of starting delayed work so we do it here
	 */
	while (1) {
		k_sleep(K_SECONDS(1));
		check_enc_btn();

		/* Heartrate measurements simulation */
		hrs_notify();

		/* Battery level simulation */
		bas_notify();

		//weather sensor
		BME688_Take_Measurement();
		int humidity = (int)BME688_Get_Humidity();
		// char gas_str[30];
		// sprintf(gas_str, "%f", gas);
		printk("humidity: %d\n", humidity);

		/* Update the display */
		// color = main_display_update_test(spi1_dev, gpio0_dev, color);
		
		float final_temp = get_body_temp();
		int temp_int = (int)final_temp;
		int temp_frac = (int)((final_temp-temp_int)*100);
		printf("Body Temperature: %d.%d F\n", temp_int, temp_frac);

		float heart_rate = read_hr();
		float SpO2 = read_blood_ox();

		int HR_whole = (int)heart_rate;
		int HR_frac = (int)((heart_rate - HR_whole)*10);

		int SpO2_whole = (int)SpO2;
		int SpO2_frac = (int)((SpO2 - SpO2_whole)*10);
		
		printf("Heart rate: %d.%d BPM\n", HR_whole, HR_frac);
		printf("Blood oxygen saturation: %d.%d%%\n\n", SpO2_whole, SpO2_frac);
	}
	return 0;
}
