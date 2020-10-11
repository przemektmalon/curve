#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include <cmath>

#include <iostream>

#define PI 3.14159265358979323846462338347

namespace thegame {

class Player : public Object {
  friend thegame::ObjectManager;

public:
  Player(uint64_t id) : Object(id) {
    shape.setRadius(30.f);
    shape.setPointCount(32);
    shape.setPosition(200, 100);
    shape.setFillColor(sf::Color::Blue);
  }
  ~Player() {}

  void setColour(sf::Color c) {
    colour = c;
    shape.setFillColor(c);
  }

  void handleKeyInput(sf::Event &event) {
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Key::Left) {
        rotation = -0.5f;
      } else if (event.key.code == sf::Keyboard::Key::Right) {
        rotation = 0.5f;
      }
    } else if (event.type == sf::Event::KeyReleased) {
      rotation = 0.f;
    }

    if (rotation > PI)
      rotation -= 2 * PI;
    else if (rotation < -PI)
      rotation += 2 * PI;
  }

  void update(double dt) {
    sf::Vector2f cp = getPosition();
    sf::Vector2f v;
    v.x = std::cos(rotation) * dt;
    v.y = std::sin(rotation) * dt;
    auto mag = std::sqrt((v.x * v.x) + (v.y * v.y));
    v.x /= mag;
    v.y /= mag;
    setVelocity(v);
    // setPosition(sf::Vector2f(cp.x + (v.x * dt), cp.y + (v.y * dt)));
  }

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override {
    // states.transform.translate(getPosition());
    target.draw(shape, states);
    std::cout << "pos: " << getPosition().x << " : " << getPosition().y << "\n";
  }

  sf::Shape *getShape() const { return &shape; }

private:
  sf::Color colour;
  sf::CircleShape shape;

  float speed = 20.f;
  float rotation = 0.f;
};

} // namespace thegame

#endif
