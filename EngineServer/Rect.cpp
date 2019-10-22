#include "Rect.h"

Rect::Rect()
{
	_x = 0;
	_y = 0;
	_width = 0;
	_height = 0;
}

Rect::Rect(float x, float y, float width, float height)
{
	_x = x;
	_y = y;
	_width = width;
	_height = height;
}
