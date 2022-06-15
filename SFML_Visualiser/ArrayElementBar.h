#pragma once
#include <SFML\Graphics.hpp>
class ArrayElementBar
{
public:
	ArrayElementBar();
	ArrayElementBar(int value, const sf::Vector2f& position);
	~ArrayElementBar();
	const sf::Vector2f& get_position() const;
	const sf::Vector2f& get_size() const;
	void set_size(const sf::Vector2f& size);
	void set_position(const sf::Vector2f& position);
	int get_value();
	void set_value(int n);
private:
	sf::Vector2f position;
	sf::Vector2f size;
	int represent_value{ 0 };
};

