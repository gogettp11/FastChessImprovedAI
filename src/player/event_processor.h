#include <SFML/Graphics.hpp>

class Event_Processor {
private:
  sf::Event event;

public:
  void handleEvents();

private:
  void movePiece();
  void closeWindow();
  void debugPrint();
};