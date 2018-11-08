#include <SFML/Graphics.hpp>
#include <iostream>
#include "Universe.h"
#include "Body.h"

using namespace std;

int main() {

	cout << "Initializing ..." << endl;

	sf::RenderWindow *window;
	Universe *universe;


	sf::Vector2f camera_offset(0.0, 0.0);
	float zoom_modifier = 1;
	float _dt = 0.01;
	bool pause = false;

	sf::Font font;
	font.loadFromFile("data/arial.ttf");
	sf::Text tipsMove("Arrow keys for camera movement", font, 15);
	sf::Text tipsZoom("+ / - for changing zoom level", font, 15);
	sf::Text tipsTime("Page Up / Page Down for changing time step (dt)", font, 15);
	sf::Text tipsPause("SPACE for pausing simulation", font, 15);
	sf::Text tipsAdd("Click and hold to add currently selected body type (direction and velocity are represented by the line)", font, 15);
	sf::Text tipsChange("Numbers 1 to 4 for changing body mass (from lower to higher)", font, 15);

	tipsMove.setColor(sf::Color::White);
	tipsZoom.setColor(sf::Color::White);
	tipsTime.setColor(sf::Color::White);
	tipsPause.setColor(sf::Color::White);
	tipsAdd.setColor(sf::Color::White);
	tipsChange.setColor(sf::Color::White);

	tipsMove.setPosition(15.0, 515.0);
	tipsZoom.setPosition(15.0, 535.0);
	tipsTime.setPosition(15.0, 555.0);
	tipsPause.setPosition(15.0, 495.0);
	tipsAdd.setPosition(15.0, 575.0);
	tipsChange.setPosition(15.0, 475.0);

	sf::Text statsZoom;
	statsZoom.setPosition(15, 5);
	statsZoom.setFont(font);
	statsZoom.setColor(sf::Color::White);
	statsZoom.setCharacterSize(15);
	statsZoom.setString("Camera zoom : " + to_string((int)round(zoom_modifier * 100)) + "%");

	sf::Text statsSize;
	statsSize.setPosition(15, 65);
	statsSize.setFont(font);
	statsSize.setColor(sf::Color::White);
	statsSize.setCharacterSize(15);
	statsSize.setString("Selected body mass : 50");

	sf::Text statsTime;
	statsTime.setPosition(15, 25);
	statsTime.setFont(font);
	statsTime.setColor(sf::Color::White);
	statsTime.setCharacterSize(15);

	sf::Text statsDeltaTime;
	statsDeltaTime.setPosition(15, 45);
	statsDeltaTime.setFont(font);
	statsDeltaTime.setColor(sf::Color::White);
	statsDeltaTime.setCharacterSize(15);
	statsDeltaTime.setString("Time step : " + to_string(_dt));

	// mouse points for adding planets

	sf::Vector2f mouseStart;
	sf::Vector2f mouseEnd;
	bool drawIntensity = false;
	sf::VertexArray intensityLine;
	intensityLine.setPrimitiveType(sf::PrimitiveType::LineStrip);


	// debug
	sf::Text debug("mouse x = " + to_string(sf::Mouse::getPosition().x) + " mouse y = " +to_string(sf::Mouse::getPosition().y) + " camera x = " + to_string(camera_offset.x) + " camera y = " + to_string(camera_offset.y), font, 15);
	debug.setPosition(15.0, 495.0);	
	debug.setFont(font);
	debug.setColor(sf::Color::White);
	debug.setCharacterSize(15);


	int choice = -1;
	bool chosen = false;
	int planetType = 1;
	bool adding = false;
	sf::Texture *texture;
	texture = new sf::Texture();
	sf::Sprite *spr;
	spr = new sf::Sprite();
	sf::Vector2f pos;

	while (true) {


		while (!chosen) {
			cout << "1 - Binary star system" << endl;
			cout << "2 - Solar system with one planet and his moon" << endl;
			cout << "3 - Two planets' orbital inteference" << endl;
			cout << "4 - Chaotic solar system with 4 planets" << endl;
			cout << "5 - Sandbox solar system with only one star in the center" << endl;
			cout << " >> ";
			cin >> choice;
			switch (choice) {
			case 1:

				window = new sf::RenderWindow(sf::VideoMode(800, 600), "Solar2D");
				window->setFramerateLimit(60);
				universe = new Universe(window);
				universe->clear();
				chosen = true;

				// starting camera parameters
				zoom_modifier = 0.5;
				statsZoom.setString("Camera zoom : " + to_string((int)round(zoom_modifier * 100)) + "%");
				camera_offset = sf::Vector2f(45, 15);
				universe->addBody(new Body(300, 300, 0, 0, 13000));		// star in the center
				universe->addBody(new Body(300, 100, 100, 0, 3000));	// brown dwarf
				universe->addBody(new Body(700, 200, 20, 140, 30));		// lesser body
				break;

			case 2:

				window = new sf::RenderWindow(sf::VideoMode(800, 600), "Solar2D");
				window->setFramerateLimit(60);
				universe = new Universe(window);
				universe->clear();
				chosen = true;

				// starting camera parameters
				zoom_modifier = 0.3;
				statsZoom.setString("Camera zoom : " + to_string((int)round(zoom_modifier * 100)) + "%");
				camera_offset = sf::Vector2f(-20, -15);
				universe->addBody(new Body(1600, 1200, 0, 0, 19000));	// star in the center
				universe->addBody(new Body(1600, 650, 115, 0, 100));	// planet
				universe->addBody(new Body(1623, 673, 144, -10, 0.3));	// planet's moon
				break;

			case 3:
				window = new sf::RenderWindow(sf::VideoMode(800, 600), "Solar2D");
				window->setFramerateLimit(60);
				universe = new Universe(window);
				universe->clear();
				chosen = true;

				universe->addBody(new Body(400, 300, 0, 0, 15000));		// star in the center
				universe->addBody(new Body(400, 50, 70, -20, 9));		// smaller planet
				universe->addBody(new Body(400, 500, -150, 0, 120));	// bigger planet


				break;

			case 4:
				chosen = true;
				window = new sf::RenderWindow(sf::VideoMode(800, 600), "Solar2D");
				window->setFramerateLimit(60);
				universe = new Universe(window);
				universe->clear();

				// starting camera parameters
				zoom_modifier = 0.7;
				statsZoom.setString("Camera zoom : " + to_string((int)round(zoom_modifier * 100)) + "%");
				camera_offset = sf::Vector2f(25, 15);

				universe->addBody(new Body(400, 300, 0, 0, 19000));		// star in the center
				universe->addBody(new Body(200, 100, 120, -75, 110));	// planet
				universe->addBody(new Body(300, 125, 155, -30, 70));	// lesser body
				universe->addBody(new Body(100, 500, 5, -80, 25));		// lesser body
				universe->addBody(new Body(300, 250, 220, -100, 105));	// planet dwarf
				break;

			case 5:
				chosen = true;
				window = new sf::RenderWindow(sf::VideoMode(800, 600), "Solar2D");
				window->setFramerateLimit(60);
				universe = new Universe(window);
				universe->clear();

				universe->addBody(new Body(400, 300, 0, 0, 10000));		// star in the center

				break;

			default:
				cout << "Wrong input!" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}

		}



		// main loop
		while (window->isOpen()) {
			sf::Event event;
			while (window->pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window->close();
					chosen = false;
					choice = -1;
					cout << "\nSimulation canceled.\n" << endl;
				}

				if (event.type == sf::Event::KeyPressed) {

					// camera movement
					if (event.key.code == sf::Keyboard::Left) {
						camera_offset = camera_offset + sf::Vector2f(3.0 * (2.5f - zoom_modifier), 0.0);
					}
					if (event.key.code == sf::Keyboard::Right) {
						camera_offset = camera_offset + sf::Vector2f(-3.0 * (2.5f - zoom_modifier), 0.0);
					}
					if (event.key.code == sf::Keyboard::Up) {
						camera_offset = camera_offset + sf::Vector2f(0.0, 3.0 *(2.5f - zoom_modifier));
					}
					if (event.key.code == sf::Keyboard::Down) {
						camera_offset = camera_offset + sf::Vector2f(0.0, -3.0 * (2.5f - zoom_modifier));
					}

					// zoom
					if (event.key.code == sf::Keyboard::Add) {
						zoom_modifier += 0.1;
						if (zoom_modifier > 2.0)
							zoom_modifier = 2.0;
						statsZoom.setString("Camera zoom : " + to_string((int)round(zoom_modifier * 100)) + "%");
					}
					if (event.key.code == sf::Keyboard::Subtract) {
						zoom_modifier -= 0.1;
						if (zoom_modifier < 0.1)
							zoom_modifier = 0.1;
						statsZoom.setString("Camera zoom : " + to_string((int)round(zoom_modifier * 100)) + "%");
					}

					// time step
					if (event.key.code == sf::Keyboard::PageUp) {
						_dt *= 1.1;
						if (_dt > 0.1)
							_dt = 0.1;
						statsDeltaTime.setString("Time step : " + to_string(_dt));
						universe->setDeltaTime(_dt);
					}
					if (event.key.code == sf::Keyboard::PageDown) {
						_dt *= 0.9;
						if (_dt < 0.001)
							_dt = 0.001;
						statsDeltaTime.setString("Time step : " + to_string(_dt));
						universe->setDeltaTime(_dt);
					}

					// pause
					if (event.key.code == sf::Keyboard::Space) {
						if (!pause)
							pause = true;
						else pause = false;
					}

					// adding planets
					if (event.key.code == sf::Keyboard::Num1) {
						planetType = 1;
						statsSize.setString("Selected body mass : 50");
					}

					if (event.key.code == sf::Keyboard::Num2) {
						planetType = 2;
						statsSize.setString("Selected body mass : 100");
					}

					if (event.key.code == sf::Keyboard::Num3) {
						planetType = 3;
						statsSize.setString("Selected body mass : 5000");
					}

					if (event.key.code == sf::Keyboard::Num4) {
						planetType = 4;
						statsSize.setString("Selected body mass : 10000");
					}

				}

				if (event.type == sf::Event::MouseButtonPressed) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						mouseStart = sf::Vector2f(sf::Mouse::getPosition(*window));

						drawIntensity = true;
					}
				}

				if (event.type == sf::Event::MouseButtonReleased) {
					if (event.mouseButton.button == sf::Mouse::Left) {
						mouseEnd = sf::Vector2f(sf::Mouse::getPosition(*window));

						drawIntensity = false;
						adding = true;
					}
				}
			}

			statsTime.setString("Time passed : " + to_string(universe->getTime()) + " time units");


			if (adding == true) {
				switch (planetType) {
				case 1:
					adding = false;
					pos = (-(5.0f - zoom_modifier) * camera_offset + mouseStart) / zoom_modifier;
					universe->addBody(new Body(pos.x, pos.y, (mouseEnd - mouseStart).x, (mouseEnd - mouseStart).y, 50));
					break;

				case 2:
					adding = false;
					pos = (-(5.0f - zoom_modifier) * camera_offset + mouseStart) / zoom_modifier;
					universe->addBody(new Body(pos.x, pos.y, (mouseEnd - mouseStart).x, (mouseEnd - mouseStart).y, 100));
					break;

				case 3:
					adding = false;
					pos = (-(5.0f - zoom_modifier) * camera_offset + mouseStart) / zoom_modifier;
					universe->addBody(new Body(pos.x, pos.y, (mouseEnd - mouseStart).x, (mouseEnd - mouseStart).y, 5000));
					break;

				case 4:
					adding = false;
					pos = (-(5.0f - zoom_modifier) * camera_offset + mouseStart) / zoom_modifier;
					universe->addBody(new Body(pos.x, pos.y, (mouseEnd - mouseStart).x, (mouseEnd - mouseStart).y, 10000));
					break;
				}
			}






			window->clear(sf::Color::Black);
			if (!pause)
				universe->update();
			universe->render(camera_offset, zoom_modifier);
			window->draw(tipsMove);
			window->draw(tipsZoom);
			window->draw(tipsTime);
			window->draw(tipsPause);
			window->draw(tipsChange);
			window->draw(tipsAdd);
			window->draw(statsZoom);
			window->draw(statsTime);
			window->draw(statsDeltaTime);
			window->draw(statsSize);

			intensityLine.clear();
			mouseEnd = sf::Vector2f(sf::Mouse::getPosition(*window));
			intensityLine.append(mouseStart);
			intensityLine.append(mouseEnd);
			if (drawIntensity == true)
				window->draw(intensityLine);

			


			window->display();
		}
	}
	return 0;


}