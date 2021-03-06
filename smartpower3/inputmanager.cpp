#include "inputmanager.h"

ESP32Encoder encoder;

Button::Button(uint8_t pin) : PIN(pin)
{
	pinMode(pin, INPUT_PULLUP);
}

void Button::isr_pol(void) {
	if (pressed == 0) {
		if (digitalRead(PIN) == 0) {
			debounceTimer = millis();
			pressed = 1;
		}
	} else if (digitalRead(PIN) == 1) {
		if (pressed == 2)
			pressed = 0;
	}
}

uint8_t Button::checkPressed(void) {
	if (pressed == 1) {
		if (millis() - debounceTimer >= DEBOUNCE_TIME) {
			if (digitalRead(PIN) == 1) {
				pressed = 2;
				return 1;
			}
			if (millis() - debounceTimer >= 3000) {
				pressed = 2;
				return 2;
			}
		}
	}
	return 0;
}

void initEncoder(void *dial)
{
	ESP32Encoder::useInternalWeakPullResistors = UP;
	encoder.attachHalfQuad(33, 32);
	encoder.setCount(0);
	encoder.setFilter(500);
	xTaskCreate(countEncoder, "encoderTask", 1500, dial, 1, NULL);
}

void countEncoder(void *dial)
{
	struct dial_t *tmp = (struct dial_t *)dial;
	int8_t cnt;
	for (;;) {
		cnt = encoder.getCount();
		if (cnt > 5) {
			encoder.setCount(0);
			tmp->cnt += 1;
			tmp->direct = 1;
			tmp->step = 10;
		} else if (cnt < -5) {
			encoder.setCount(0);
			tmp->cnt -= 1;
			tmp->direct = -1;
			tmp->step = 10;
		} else if (cnt > 1) {
			encoder.setCount(0);
			tmp->cnt += 1;
			tmp->direct = 1;
			tmp->step = 1;
		} else if (cnt < -1) {
			encoder.setCount(0);
			tmp->cnt -= 1;
			tmp->direct = -1;
			tmp->step = 1;
		}
		vTaskDelay(100);
	}
}

