#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#include <SFML/Graphics.hpp>

namespace thegame {

namespace {
class ObjectManager;
}

class Object : sf::Drawable {
  friend class ObjectManager;

public:
  Object(uint64_t objid)
      : id(objid), position(sf::Vector2f(400, 400)),
        velocity(sf::Vector2f(0, 0)) {}
  ~Object() {}

  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const = 0;

  virtual void handleKeyInput(sf::Event &keyEvent) = 0;

  virtual void update(double dt) = 0;

  void setPosition(sf::Vector2f p) { position = p; }
  void setVelocity(sf::Vector2f v) { velocity = v; }
  sf::Vector2f getPosition() const { return position; }
  sf::Vector2f getVelocity() const { return velocity; }

  virtual sf::Shape *getShape() const { return nullptr; };

  uint64_t getID() { return id; }

private:
  uint64_t id;
  sf::Vector2f position;
  sf::Vector2f velocity;
};

} // namespace thegame

#endif
