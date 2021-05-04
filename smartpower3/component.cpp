#include "component.h"

Component::Component(TFT_eSPI *tft, uint16_t width, uint16_t height, uint8_t font)
{
	this->tft = tft;
	img = new TFT_eSprite(tft);
	this->width = width;
	this->height = height;
	this->font = font;
}

Component::~Component(void)
{
	img->deleteSprite();
	delete img;
	img = NULL;
}

void Component::init(uint16_t fg_color, uint16_t bg_color, uint8_t size, uint8_t align)
{
	img->setColorDepth(8);
	img->fillSprite(TFT_BLACK);
	img->createSprite(width, height);
	img->setTextColor(fg_color, bg_color);
	img->setTextSize(size);
	img->setTextDatum(align);
}

void Component::setCoordinate(uint16_t x, uint16_t y)
{
	this->x = x;
	this->y = y;
}

void Component::drawOutLines(void)
{
	for (int i = 0; i < 3; i++) {
		tft->drawRect(x-(i+2), y-(i+2), width+(4+i*2), height+(4 +2*i), TFT_YELLOW);
	}
}

void Component::clearOutLines(void)
{
	for (int i = 0; i < 3; i++) {
		tft->drawRect(x-(i+2), y-(i+2), width+(4+i*2), height+(4 +2*i), TFT_BLACK);
	}
}

void Component::draw(float val, uint16_t x, uint16_t y)
{
	img->drawString(String(val, 2), width, 0, font);
	img->pushSprite(x, y);
	delay(WAIT);
}

void Component::draw(float val)
{
	img->drawString(String(val, 2), width, 0, font);
	img->pushSprite(x, y);
	delay(WAIT);
}

void Component::draw(String s)
{
	img->drawString(s, 0, 0, font);
	img->pushSprite(x, y);
	delay(WAIT);
}

void Component::draw(String s, uint16_t x, uint16_t y)
{
	img->drawString(s, 0, 0, font);
	img->pushSprite(x, y);
	delay(WAIT);
}

void Component::activate(void)
{
	activated = true;
}
