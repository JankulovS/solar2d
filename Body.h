#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

// containr class representing velocity and acceleration of a body, used by rk4
class Derivative {

	sf::Vector2f vel;
	sf::Vector2f acc;



public:

	Derivative(sf::Vector2f _vel, sf::Vector2f _acc) {
		vel = _vel;
		acc = _acc;
	}

	sf::Vector2f getVel() {
		return vel;
	}

	sf::Vector2f getAcc() {
		return acc;
	}

};

// planetary body or a sun (a planet with very high mass)
class Body {
	vector<sf::Vector2f> prev_points;
	int draw;
	sf::Vector2f pos;
	sf::Vector2f vel;
	float mass;
	float radius;
	int id;
	sf::Color color;
	sf::Sprite *spr;
	sf::Sprite *spr_glow;
	sf::Texture *texture;
	sf::Texture *texture_glow;
	bool active;

public:

	Body();
	Body(float x, float y, float vx, float vy, float _mass);

	float calculateRadius(float _mass);

	const sf::Vector2f getPos() {
		return pos;
	}

	int getId() {
		return id;
	}

	const sf::Vector2f getVel() {
		return vel;
	}

	float getRadius() {
		return radius;
	}

	void setRadius(float _r) {
		radius = _r;
	}

	float getMass() {
		return mass;
	}

	void setIsActive(bool _a) {
		active = _a;
	}

	bool isActive() {
		return active;
	}

	void addMass(float _mass) {
		mass += _mass;
	}

	void addVel(sf::Vector2f _vel) {
		vel += _vel;
	}

	void setVel(sf::Vector2f _vel) {
		vel = _vel;
	}

	void updateVisuals();

	void render(sf::RenderWindow *window, sf::Vector2f camera_offset, float zoom_modifier);
	void draw_lines(sf::RenderWindow *window, sf::Vector2f camera_offset, float zoom_modifier);
	void update(vector<Body> &bodies, float t, float dt);
	sf::Vector2f acceleration(sf::Vector2f _pos, vector<Body> &bodies);
	Derivative initialDerivative(sf::Vector2f _pos, sf::Vector2f _vel, vector<Body> &bodies, float t);
	Derivative nextDerivative(sf::Vector2f _initialPos, sf::Vector2f _initialVel, Derivative derivative, vector<Body> &bodies, float t, float dt);
};

