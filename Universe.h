#pragma once

#include <SFML/Graphics.hpp>
#include <math.h>
#include "Body.h"
#include <vector>

static float gravityStrength = 300;
static float density = 0.3;


using namespace std;

class Universe {
	vector<Body> bodies;
	sf::RenderWindow* window;
	float t;
	float dt;

public:




	Universe(sf::RenderWindow* _window) {
		window = _window;
		t = 0.0;
		dt = 0.01;
	}

	void addBody(Body* b) {
		bodies.push_back(*b);
	}

	void update() {
		for (int i = 0; i < bodies.size(); i++) {
			if (bodies[i].isActive())
				bodies[i].update(bodies, t, dt);
		}
		t += dt;
	}

	void render(sf::Vector2f camera_offset, float zoom_modifier) {
		// draw all lines first
		for (Body b : bodies) {
			b.draw_lines(window, camera_offset, zoom_modifier);
		}
		// draw bodies
		for (Body b : bodies) {
			b.render(window, camera_offset, zoom_modifier);
		}
	}

	void clear() {
		t = 0;
		bodies.clear();
	}

	float getTime() {
		return t;
	}

	void setDeltaTime(float _dt) {
		dt = _dt;
	}
};
