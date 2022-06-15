#include "ArrayElementBar.h"



ArrayElementBar::ArrayElementBar()
{
}

ArrayElementBar::ArrayElementBar(int value, const sf::Vector2f & position)
{
	this->represent_value = value;
	this->position = position;
}


ArrayElementBar::~ArrayElementBar()
{
}

const sf::Vector2f & ArrayElementBar::get_position() const
{
	return this->position;
}

const sf::Vector2f & ArrayElementBar::get_size() const
{
	return this->size;
}

void ArrayElementBar::set_size(const sf::Vector2f & size)
{
	this->size = size;
}

void ArrayElementBar::set_position(const sf::Vector2f & position)
{
	this->position = position;
}

int ArrayElementBar::get_value()
{
	return this->represent_value;
}

void ArrayElementBar::set_value(int n)
{
	this->represent_value = n;
}
