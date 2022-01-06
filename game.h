#ifndef GAME_H_
#define GAME_H_

#include <vector>
#include "game_level.h"

enum GameState {
	ACTIVE, MENU, WIN
};

class Game {
	public:
		GameState state;
		std::vector<GameLevel> levels;
		unsigned int level;
		bool keys[1024];
		unsigned int width, height;

		Game(unsigned int width, unsigned int height);
		~Game();

		void init();

		void processInput(float dt);
		void update(float dt);
		void render();
};

#endif
