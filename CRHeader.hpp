#include <SFML/Graphics.hpp>


class Base
{
	std::string m_name;
	float m_speedX, m_speedY;
public:

	const std::string name() const
	{
		return m_name;
	}

	const float speedX() const
	{
		return m_speedX;
	}

	const float speedY() const
	{
		return m_speedY;
	}

	void bounceX() 
	{
		m_speedX *= -1.0f;
	}

	void bounceY()
	{
		m_speedY *= -1.0f;
	}
};


class Circle : public sf::CircleShape
{
	std::string m_name;
	float m_speedX, m_speedY;
public:
	Circle(const std::string& name, float& speedX, float& speedY)
		: m_name(name)
		, m_speedX(speedX)
		, m_speedY(speedY)
	{
	}

	const std::string name() const
	{
		return m_name;
	}

	const float speedX() const
	{
		return m_speedX;
	}

	const float speedY() const
	{
		return m_speedY;
	}

	void bounceX()
	{
		m_speedX *= -1.0f;
	}

	void bounceY()
	{
		m_speedY *= -1.0f;
	}
};

class Rectangle : public sf::RectangleShape
{
	std::string m_name;
	float m_speedX, m_speedY;
public:
	Rectangle(const std::string& name, float& speedX, float& speedY)
		: m_name(name)
		, m_speedX(speedX)
		, m_speedY(speedY)
	{
	}

	const std::string name() const
	{
		return m_name;
	}

	const float speedX() const
	{
		return m_speedX;
	}

	const float speedY() const
	{
		return m_speedY;
	}

	void bounceX()
	{
		m_speedX *= -1.0f;
	}

	void bounceY()
	{
		m_speedY *= -1.0f;
	}
};