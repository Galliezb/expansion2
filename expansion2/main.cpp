#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#define PATHIMG "../expansion2/img/"

#pragma region globalVariable
/*      ECRAN     */
int globScreenWidth = sf::VideoMode::getDesktopMode().width;
int globScreenHeight = sf::VideoMode::getDesktopMode().height;
bool globToggleFullScreen = false;
bool globToggleVisible = false;
sf::Texture textureVaisseau;
sf::Texture textureBackground;
sf::Sprite background;
sf::Sprite spVaisseau[12];
sf::Clock horloge,horloge2;
/*      ECRAN     */
#pragma endregion globalVariable


int main(){

	bool boucleMenu = true;

	// chargement fichier image
	if (!textureVaisseau.loadFromFile(PATHIMG"vaisseau.png", sf::IntRect(0, 0, 2000, 2000))){
		std::cout << "ERREUR : vaisseau.png not load properly\n";
	} else {
		for ( int i=0; i<12; i++){
			spVaisseau[i].setTexture(textureVaisseau);
			spVaisseau[i].setTextureRect(sf::IntRect(0,500,89,52));
			spVaisseau[i].setPosition(1720,0+i*75);
		}
	}
	if (!textureBackground.loadFromFile(PATHIMG"background01.jpg", sf::IntRect(0, 0, 1920, 1080))){
		std::cout << "ERREUR : vaisseau.png not load properly\n";
	} else {
		for ( int i=0; i<12; i++){
			background.setTexture(textureBackground);
		}
	}

	// gère la fenêtre SFML
	sf::RenderWindow window;
	window.create(sf::VideoMode(1920, 1080), "Test sprite SFML", sf::Style::Default);
	sf::View vue;
	vue = window.getView();
	vue.setSize(3840,2160);
	window.setView(vue);
	window.setVerticalSyncEnabled(true);
	//window.setFramerateLimit(60);

	while(boucleMenu){

		// temps écoulé
		sf::Time frameTime = horloge.restart();
		float tps = frameTime.asSeconds();
		if ( horloge2.getElapsedTime().asSeconds() > 1 ){
			std::cout << 1/tps << std::endl;
			horloge2.restart();
		}

		sf::Event event;
		// boucle d'évènements
		while(window.pollEvent(event)){

			// FERMETURE de la fenetre 
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) ){

				// ferme la fenêtre de jeu
				window.close();
				// stop le jeu
				boucleMenu=false;

			}

			if ( event.type == sf::Keyboard::F ){
				if (globToggleFullScreen){
					window.close();
					window.create(sf::VideoMode(1920, 1080), "Test sprite SFML", sf::Style::Default);
					//window.setVerticalSyncEnabled(true);
					globToggleFullScreen = false;
				} else {
					window.close();
					window.create(sf::VideoMode(1920, 1080), "Test sprite SFML", sf::Style::Fullscreen);
					//window.setVerticalSyncEnabled(true);
					globToggleFullScreen = true;
				}
			}

		}

		for ( int i=0; i<12; i++){
			if ( spVaisseau[i].getPosition().x < 0 ){
				spVaisseau[i].move(sf::Vector2f(1720,0));
			} else {
				spVaisseau[i].move(sf::Vector2f(-120*tps,0));
			}
		}


		// Affichage
		window.clear();
		window.draw(background);
		for ( int i=0; i<12; i++){
			window.draw(spVaisseau[i]);
		}
		window.display();

	}

	return 0;

}