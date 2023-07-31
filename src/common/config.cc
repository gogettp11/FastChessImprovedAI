#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>

#include "../board.h"
#include "../core/black/bishop.h"
#include "../core/black/king.h"
#include "../core/black/knight.h"
#include "../core/black/pawn.h"
#include "../core/black/queen.h"
#include "../core/black/rook.h"
#include "../core/white/bishop.h"
#include "../core/white/king.h"
#include "../core/white/knight.h"
#include "../core/white/pawn.h"
#include "../core/white/queen.h"
#include "../core/white/rook.h"
#include "../media/sound.h"
#include "../media/text.h"
#include "../player/event_processor.h"
#include "../queue.h"
#include "config.h"

#ifdef DEBUGAI
std::ofstream log("debug.log");
#endif
struct undo_stack undo = {{}, {}, {}, {}, {}, {}, {}};
sf::RenderWindow window(sf::VideoMode(X_RES, Y_RES), "FastChess");

// Global game objects
Game_Board board;
Click_Queue queue;
Game_Sound sound;
Game_Text text;
Event_Processor event_processor;

namespace black {
Bishop_Piece bishop;
Knight_Piece knight;
Pawn_Piece pawn;
Rook_Piece rook;
King_Piece king;
Queen_Piece queen;
} // namespace black

namespace white {
Bishop_Piece bishop;
Knight_Piece knight;
Pawn_Piece pawn;
Rook_Piece rook;
King_Piece king;
Queen_Piece queen;
} // namespace white
