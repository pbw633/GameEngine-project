#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
class UIComponent {
public:
    virtual ~UIComponent() = default;

    //virtual void draw(sf::RenderTarget& window) = 0;
	// ------------------ Variables ------------------
	void initVariables(sf::IntRect frame);
	void initTexture(std::string textureFileName);
	void initSprite();
	// ------------------ Initialization ------------------

	// ------------------ Setters ------------------	
	void setSpritePosition(float x, float y);
	void setSpritePosition(sf::Vector2f position);
	void setSpriteScale(float scaleX, float scaleY);
	void setSpriteScale(sf::Vector2f scale);
	void setSpriteScale(float scale);


	// ------------------ Getters ------------------
	float getSpriteWidth();
	float getSpriteHeight();

	// ------------------ Adders -------------------	

	// ------------------ Actions ------------------


    void drawSprite(sf::RenderTarget& window);
	void resizeSprite(float scaleX, float scaleY);
	void resizeSprite(sf::Vector2f scale);

private:
	sf::Texture texture;   
	sf::Sprite sprite;
	sf::IntRect currentFrame; // The rectangle of the picture

};