#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Player.hpp"

using namespace thegame;

thegame::ObjectManager Game::objectManager;

int main(int argc, char *argv[]) {

  sf::Window window(sf::VideoMode(1280, 720), "Game");

  sf::RenderWindow renWindow;
  renWindow.create(window.getSystemHandle());

  sf::RenderTexture renTex;
  renTex.create(window.getSize().x, window.getSize().y);

  sf::RectangleShape targetDrawRect;
  targetDrawRect.setTexture(&renTex.getTexture(), true);

  sf::Clock clock;
  clock.restart();

  Player *p = new Player(0);

  Game::objectManager.addObject(p);

  p->setPosition(sf::Vector2f(400, 200));
  p->setColour(sf::Color::Red);
  p->setVelocity(sf::Vector2f(0, 0));

  while (window.isOpen()) {

    sf::Event event;
    while (window.pollEvent(event)) {
      for (auto &obj : Game::objectManager.getObjects()) {
        obj.second->handleKeyInput(event);
      }
      if (event.type == sf::Event::Closed)
        window.close();
    }

    renWindow.clear(sf::Color::Black);

    Game::objectManager.drawAll(renTex, sf::RenderStates::Default);

    sf::CircleShape c;
    c.setFillColor(sf::Color::Red);
    c.setPointCount(32);
    c.setPosition(200, 200);
    c.setRadius(50);

    targetDrawRect.setTexture(&renTex.getTexture(), true);

    for (auto &obj : Game::objectManager.getObjects()) {
      auto tempptr = obj.second;
      renWindow.draw(c);
      renTex.draw(c, sf::Vector2f(300, 300));
      renTex.draw(*reinterpret_cast<thegame::Player *>(tempptr),
                  sf::RenderStates::Default);
      // renWindow.draw(;
      // window.draw(&obj.(*second)->getShape());
    }

    // renWindow.draw(targetDrawRect, sf::RenderStates::Default);
    // renWindow.draw(c);

    // Game::objectManager.updateAll(clock.getElapsedTime());
    Game::objectManager.updateAll(sf::Time::Zero);

    renWindow.display();
    clock.restart();
  }

  return 0;
}