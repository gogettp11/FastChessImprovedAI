#include "event_processor.h"
#include "../board.h"
#include "../common/config.h"
#include "../core/black_.h"
#include "../core/white_.h"
#include "../queue.h"

void Event_Processor::closeWindow() {
  if (this->event.type == sf::Event::Closed)
    window.close();
}

void Event_Processor::movePiece() {
  if (this->event.type == sf::Event::MouseButtonPressed) {
    sf::Vector2i position = sf::Mouse::getPosition(window);
    if (position.x >= 1 && position.x <= X_RES - 1 && position.y >= 1 &&
        position.y <= Y_RES - 1) {
      std::vector<int> pos = board.get_coords(position.x, position.y);
      board.selected_row = pos[1];
      board.selected_col = pos[0];
      if (white::blocks[board.selected_row][board.selected_col]) {
        board.clicked_piece = white::get_piece(pos[1], pos[0]);
        board.clicked_coords = {pos[1], pos[0]};
        white::last_clicked_piece = white::get_piece(pos[1], pos[0]);
        if (board.clicked_piece != "") {
          queue.enqueue(pos[1], pos[0]);
          board.play();
        }
      }
#ifndef IS_BLACK_AI
      else if (black::blocks[board.selected_row][board.selected_col]) {
        board.clicked_piece = black::get_piece(pos[1], pos[0]);
        board.clicked_coords = {pos[1], pos[0]};
        black::last_clicked_piece = black::get_piece(pos[1], pos[0]);
        if (board.clicked_piece != "") {
          queue.enqueue(pos[1], pos[0]);
          board.play();
        }
      }
#endif
    }
  }
  if (this->event.type == sf::Event::MouseButtonReleased) {
    board.clicked_piece = "";
    white::reset_sprite_pos();
    black::reset_sprite_pos();
    sf::Vector2i position = sf::Mouse::getPosition(window);
    if (position.x >= 1 && position.x <= X_RES - 1 && position.y >= 1 &&
        position.y <= Y_RES - 1) {
      std::vector<int> pos = board.get_coords(position.x, position.y);
      board.selected_row = pos[1];
      board.selected_col = pos[0];
      queue.enqueue(pos[1], pos[0]);
      board.play();
    }
  }
}

void Event_Processor::debugPrint() {
  if (this->event.type == sf::Event::KeyPressed) {
    switch (this->event.key.code) {
    case sf::Keyboard::B:
      black::print_blocks();
      break;
    case sf::Keyboard::W:
      white::print_blocks();
      break;
    case sf::Keyboard::Z:
      board.pop();
      break;
    case sf::Keyboard::U:
      board.print_undo();
      break;
    }
  }
}

void Event_Processor::handleEvents() {
  while (window.pollEvent(this->event)) {
    this->closeWindow();
    this->debugPrint();
    this->movePiece();
  }
}