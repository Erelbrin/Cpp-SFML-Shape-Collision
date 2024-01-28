#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "CRHeader.hpp"

// Program will read descriptions of shapes	from a configuration file
// Each shave have a name, position, speed, color and properties unique to the shapes(width and height, or radius)
// Draw the shapes from file to the screen
// Shapes need to bounce from the sides of the screen (reverse the speed on the axis the shape touches to the screen side)
// Each shapes name will be centered inside the shape exactly in the middle given font size
// 
// HINTS::
// 
// Use std::vector<> to store the shapes
// Use std::ifstream to read the config file
// shape.getLocalBounds(); // .top, .left, .width, .height to check for collision and name centering


const int typeCheck(const std::string& name);


int main(int argc, char* arcv[])
{
	std::ifstream config("config.txt");
	std::string objType, font, name;
	int screenW = 0, screenH = 0,fontSize = 12, r, g,b;
	float posX, posY, speedX, speedY, radius, width, height;
	std::vector<int> fontRGB;
	std::vector<Circle> circles;
	std::vector<Rectangle> rectangles;
	sf::Font myFont;


	while (config >> objType)
	{
		const int code = typeCheck(objType);
		
		if (code == -1)
		{
			std::cerr << "Object type unidentified!\n";
			return -1;
		}
		else if (code == 0)
		{
			config >> screenW >> screenH;
		}
		else
		{
			if (code == 1)
			{
				config >> font >> fontSize >> r >> g >> b;
				fontRGB.push_back(r);
				fontRGB.push_back(g);
				fontRGB.push_back(b);

				// attempt to load the font from a file
				if (!myFont.loadFromFile(font))
				{
					// if we can't load the font, print an error to the error console and exit
					std::cerr << "Could not load font\n";
					return -2;
				}


			}
			else if (code == 2)
			{
				config >> name >> posX >> posY >> speedX >> speedY >> r >> g >> b >> radius;
				speedX *= 10;
				speedY *= 10;
				Circle circ(name,speedX, speedY);
				circ.setRadius(radius);
				circ.setFillColor(sf::Color(r, g, b));
				circ.setPosition(posX, posY);
				circles.push_back(circ);
			}
			else
			{
				config >> name >> posX >> posY >> speedX >> speedY >> r >> g >> b >> width >> height;
				speedX *= 10;
				speedY *= 10;
				Rectangle rec(name, speedX, speedY);
				sf::Vector2f vect(width, height);
				rec.setSize(vect);
				rec.setFillColor(sf::Color(r, g, b));
				rec.setPosition(posX, posY);
				rectangles.push_back(rec);
			}
		}
	}

	// create a new window of size w*h pixels
	// top-left of the window is (0,0) and buttom-right is (w,h)
	sf::RenderWindow window(sf::VideoMode(screenW, screenH), "SFML works!");
	window.setFramerateLimit(60);

	while (window.isOpen())
	{
		// event handling
		sf::Event event;
		while (window.pollEvent(event))
		{
			// this event triggers when the window is closed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			// this event triggered when a key is pressed
			/*if (event.type == sf::Event::KeyPressed)
			{
				// print the key that was pressed to the console
				std::cout << "Key pressed with code = " << event.key.code << "\n";

				// example, what happens when x is pressed 
				if (event.key.code == sf::Keyboard::X)
				{
					// reverse the direction of the circle on the screen
					circleMoveSpeed *= -1.0f;
				}
			}*/
		}

		// basic rendering function calls
		window.clear();			// clear the window of anything previously drawn

		for (auto& shape : circles)
		{
			if (shape.getGlobalBounds().left < 0 || shape.getGlobalBounds().left + shape.getLocalBounds().width > screenW)
			{
				shape.bounceX();
			}
			else if (shape.getGlobalBounds().top < 0 || shape.getGlobalBounds().top + shape.getLocalBounds().height  > screenH)
			{
				shape.bounceY();
			}

			window.draw(shape);
			sf::Text text(shape.name(), myFont, fontSize);
			float textPosX = shape.getGlobalBounds().left + shape.getRadius() - (text.getLocalBounds().width / 1.9);
			float textPosY = shape.getGlobalBounds().top + shape.getRadius() - (text.getLocalBounds().height / 1.25);
			text.setPosition(textPosX, textPosY);
			window.draw(text);
			// Move the shape for the next frame
			shape.setPosition(shape.getPosition().x + shape.speedX(), shape.getPosition().y + shape.speedY());
		}

		for (auto& shape : rectangles)
		{
			if (shape.getGlobalBounds().left < 0 || shape.getGlobalBounds().left + shape.getLocalBounds().width > screenW)
			{
				shape.bounceX();
			}
			else if (shape.getGlobalBounds().top < 0 || shape.getGlobalBounds().top + shape.getLocalBounds().height > screenH)
			{
				shape.bounceY();
			}

			window.draw(shape);
			sf::Text text(shape.name(), myFont, fontSize);
			float textPosX = shape.getGlobalBounds().left + (shape.getLocalBounds().width / 2.0) - (text.getLocalBounds().width / 1.9);
			float textPosY = shape.getGlobalBounds().top + (shape.getLocalBounds().height / 2.0) - (text.getLocalBounds().height / 1.25);
			text.setPosition(textPosX, textPosY);
			window.draw(text);
			// Move the shape for the next frame
			shape.setPosition(shape.getPosition().x + shape.speedX(), shape.getPosition().y + shape.speedY());
		}

		window.display();		// call the window display function
	}

	return 0;
}

const int typeCheck(const std::string& name)
{
	if (name == "Window")
	{
		return 0;
	}
	else if (name == "Font")
	{
		return 1;
	}
	else if (name == "Circle")
	{
		return 2;
	}
	else if (name == "Rectangle")
	{
		return 3;
	}
	
	return -1;
}
