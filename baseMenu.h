#pragma once
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class baseMenu{
    sf::IntRect currentFrame;

    sf::Texture texture;
    sf::Sprite sprite;

	sf::RectangleShape menuBackground;
public:
    baseMenu() {};
    baseMenu( int menuWidth, int menuHeight) {
		this->menuBackground.setSize(sf::Vector2f(menuWidth, menuHeight));
    }
	// ----------------- Initialization -----------------
	void initTexture(std::string fileName);
	void initSprite();
	// ----------------- Setters -----------------
    void setBackgroundColor(sf::Color color);
    void setMenuBorderColor(sf::Color color);
	void setMenuSprite(sf::Texture& texture);
    void setSize(float width, float height);
    void setPosition(float x, float y);


    virtual void open() {}
    virtual void close() {}
};

