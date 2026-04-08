#include <iostream>
#include "Game.h"
//#include <SFML/Graphics.hpp>

int main() {
	//std::cout << "dette er en test" << "\n";
	//system("pause");
	//sf::RenderWindow window(sf::VideoMode(640, 480), "my first game", sf::Style::Titlebar | sf::Style::Close);
	//sf::Event ev;

	//Init game engine
	Game game;

	//Game loop
	while (game.running()){ // the void draw
		//event polling
		
		//Update
		game.update();

		//Render
		//window.clear(); // remove old frame
		game.render();
		//Draw your game

		//window.display(); //display new frame


	}

	//end application
	return 0;
}