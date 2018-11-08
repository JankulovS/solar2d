#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Universe.h"


using namespace std;
int g_id = 0;
const int STAR_MASS = 9999;
const int RED_DWARF_MASS = 999;
const int PLANET_MASS = 99;
const int LESSER_OBJECT_MASS = 9;

// unused
Body::Body() {
	id = g_id++;
	draw = 0;
	pos = sf::Vector2f((float)(rand() % 800), (float)(rand() % 600));
	vel = sf::Vector2f(0.0, 0.0);
	mass = 5;
	radius = (float)(rand() % 25 + 10);
	color = sf::Color::Red;

}




Body::Body(float x, float y, float vx, float vy, float _mass)
{
	active = true;
	id = g_id++;
	draw = 0;
	pos = sf::Vector2f(x, y);
	vel = sf::Vector2f(vx, vy);
	texture = new sf::Texture();
	texture_glow = new sf::Texture();
	spr = new sf::Sprite();
	spr_glow = new sf::Sprite();

	texture->setSmooth(true);


	mass = _mass;
	radius = calculateRadius(_mass);



	spr->setOrigin(radius, radius);

	// change sprite and color depending on mass
	if (mass > STAR_MASS) {
		color = sf::Color::Yellow;
		texture->loadFromFile("data/star.png");
		texture_glow->loadFromFile("data/star_glow.png");
		spr->setTexture(*texture);
		spr_glow->setTexture(*texture_glow);
	}
	else if (mass > RED_DWARF_MASS) {
		color = sf::Color::Red;
		texture->loadFromFile("data/star.png");
		texture_glow->loadFromFile("data/star_glow.png");
		spr->setTexture(*texture);
		spr_glow->setTexture(*texture_glow);
	}
	else if (mass > PLANET_MASS) {
		color = sf::Color::Color(170, 100, 0, 255);
		texture->loadFromFile("data/planet.png");
		spr->setTexture(*texture);
	}
	else if (mass > LESSER_OBJECT_MASS) {
		color = sf::Color::Color(128, 128, 128, 255);
		texture->loadFromFile("data/moon.png");
		spr->setTexture(*texture);
	}
	else {
		color = sf::Color::Color(92, 92, 92, 255);
		texture->loadFromFile("data/asteroid.png");
		spr->setTexture(*texture);
	}

}

float Body::calculateRadius(float _mass)
{
	return cbrt(3 * _mass / (density * 4 * 3.14159));
}

void Body::updateVisuals()
{
	radius = calculateRadius(mass);

	spr->setOrigin(radius, radius);

	// change sprite and color depending on mass
	if (mass > STAR_MASS) {
		color = sf::Color::Yellow;
		texture->loadFromFile("data/star.png");
		texture_glow->loadFromFile("data/star_glow.png");
		spr->setTexture(*texture);
		spr_glow->setTexture(*texture_glow);
	}
	else if (mass > RED_DWARF_MASS) {
		color = sf::Color::Red;
		texture->loadFromFile("data/star.png");
		texture_glow->loadFromFile("data/star_glow.png");
		spr->setTexture(*texture);
		spr_glow->setTexture(*texture_glow);
	}
	else if (mass > PLANET_MASS) {
		color = sf::Color::Color(170, 100, 0, 255);
		texture->loadFromFile("data/planet.png");
		spr->setTexture(*texture);
	}
	else if (mass > LESSER_OBJECT_MASS) {
		color = sf::Color::Color(128, 128, 128, 255);
		texture->loadFromFile("data/moon.png");
		spr->setTexture(*texture);
	}
	else {
		color = sf::Color::Color(92, 92, 92, 255);
		texture->loadFromFile("data/asteroid.png");
		spr->setTexture(*texture);
	}
}

void Body::render(sf::RenderWindow *window, sf::Vector2f camera_offset, float zoom_modifier) {
	if (active == false) {
		return;
	}
	spr->setColor(color);
	spr->setPosition((pos * zoom_modifier + (5.0f - zoom_modifier) * camera_offset));
	spr->setScale(sf::Vector2f(radius/35 * zoom_modifier, radius/35 * zoom_modifier));
	spr->setOrigin(radius + 20, radius + 20);

	window->draw(*spr);

	if (mass > 999) {
		spr_glow->setColor(color);
		spr_glow->setPosition((pos * zoom_modifier + (5.0f - zoom_modifier) * camera_offset));
		spr_glow->setScale(sf::Vector2f(radius / 35 * zoom_modifier, radius / 35 * zoom_modifier));
		spr_glow->setOrigin(radius + 52, radius + 52);

		window->draw(*spr_glow);
	}


}

void Body::draw_lines(sf::RenderWindow *window, sf::Vector2f camera_offset, float zoom_modifier) {
	sf::VertexArray line;

	if (active == false) {
		return;
	}

	int alpha = 255;
	for (int i = 0; i < prev_points.size(); i++) {
		if (i > 80)
			alpha = (int)(alpha * 0.9);
		line.append(sf::Vertex((prev_points[i] * zoom_modifier + (5.0f - zoom_modifier) * camera_offset), sf::Color(color.r, color.g, color.b, alpha)));
	}
	line.setPrimitiveType(sf::PrimitiveType::LineStrip);
	window->draw(line);
}

void Body::update(vector<Body> &bodies, float t, float dt) {

	if (active == false)
		return;

	// store previous point every 5 updates (used for drawing orbital lines)
	if (prev_points.size() < 100) {
		for (int i = 0; i < 100; i++)
			prev_points.push_back(pos);
	}
	else if (draw == 0){
		prev_points.emplace(prev_points.begin(), pos);
		prev_points.pop_back();
	}
	
	draw++;
	if (draw > 5)
		draw = 0;

	// rk4


	Derivative a = initialDerivative(pos, vel, bodies, t);
	Derivative b = nextDerivative(pos, vel, a, bodies, t, dt*0.5);
	Derivative c = nextDerivative(pos, vel, b, bodies, t, dt*0.5);
	Derivative d = nextDerivative(pos, vel, c, bodies, t, dt);
	float dxdt = 1.0 / 6.0 * (a.getVel().x + 2.0*(b.getVel().x + c.getVel().x) + d.getVel().x);
	float dydt = 1.0 / 6.0 * (a.getVel().y + 2.0*(b.getVel().y + c.getVel().y) + d.getVel().y);
	float dvxdt = 1.0 / 6.0 * (a.getAcc().x + 2.0*(b.getAcc().x + c.getAcc().x) + d.getAcc().x);
	float dvydt = 1.0 / 6.0 * (a.getAcc().y + 2.0*(b.getAcc().y + c.getAcc().y) + d.getAcc().y);
	pos.x += dxdt*dt;
	pos.y += dydt*dt;
	vel.x += dvxdt*dt;
	vel.y += dvydt*dt;

}

sf::Vector2f Body::acceleration(sf::Vector2f _pos, vector<Body> &bodies) {
	sf::Vector2f acc(0.0, 0.0);
	for (int i = 0; i < bodies.size(); i++) {
		if (bodies[i].getId() == id || bodies[i].isActive() == false || active == false) {
			continue;  // ignore ourselves and merged bodies
		}
		sf::Vector2f d = bodies[i].getPos() - _pos;
		float distsq = d.x*d.x + d.y*d.y;		// distance squared
		float dist = sqrt(distsq);				// distance


		// check for collisions, calculate new velocity and mass if a collision is detected
		if (dist < radius + bodies[i].getRadius()) {
			//cout << "Two bodies combined!" << endl;
			sf::Vector2f newVel(0.0, 0.0);
			if (mass < bodies[i].getMass()) {
				newVel = (vel * mass + bodies[i].getVel() * bodies[i].getMass()) / (mass + bodies[i].getMass());
				bodies[i].setVel(newVel);
				bodies[i].addMass(mass);
				bodies[i].updateVisuals();
				active = false;
			}
			else {
				newVel = (vel * mass + bodies[i].getVel() * bodies[i].getMass()) / (mass + bodies[i].getMass());
				vel = newVel;
				mass += bodies[i].getMass();
				updateVisuals();
				bodies[i].setIsActive(false);
			}
			
		}

		
		// newton's law of gravity	F = G * (m1 * m2) / d^2
		float force = gravityStrength * mass * bodies[i].getMass() / distsq;

		// accumulate acceleration
		// both bodies feel the same force but accelerate acording to their mass --- a = F / m
		acc = acc + sf::Vector2f(force * d.x / dist / mass, force * d.y / dist / mass);
	}
	return acc;
}

Derivative Body::initialDerivative(sf::Vector2f _pos, sf::Vector2f _vel, vector<Body> &bodies, float t) {
	sf::Vector2f acc = acceleration(_pos, bodies);
	return Derivative(_vel, acc);
}


Derivative Body::nextDerivative(sf::Vector2f _initialPos, sf::Vector2f _initialVel, Derivative derivative, vector<Body> &bodies, float t, float dt) {
	sf::Vector2f pos(0.0, 0.0);
	sf::Vector2f vel(0.0, 0.0);

	pos.x = _initialPos.x + derivative.getVel().x * dt;
	pos.y = _initialPos.y + derivative.getVel().y * dt;

	vel.x = _initialVel.x + derivative.getAcc().x * dt;
	vel.y = _initialVel.y + derivative.getAcc().y * dt;

	sf::Vector2f acc = acceleration(pos, bodies);
	return Derivative(vel, acc);
}

