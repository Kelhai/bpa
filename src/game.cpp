#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include "../glfw/include/GLFW/glfw3.h"

SpriteRenderer* renderer;

Game::Game(unsigned int width, unsigned int height) 
		: state(ACTIVE), keys(), width(width), height(height), level(0) {

}

Game::~Game() {
	delete renderer;
}

void Game::init() {
	ResourceManager::loadShader("K:/Programming/c/bpa/bpa/src/vertex.vs", "K:/Programming/c/bpa/bpa/src/fragment.fs", nullptr, "sprite");
	
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->width), static_cast<float>(this->height), 0.0f, -1.0f, 1.0f);
	
	ResourceManager::getShader("sprite").use().setInteger("image", 0);
	ResourceManager::getShader("sprite").setMatrix4("projection", projection);

	renderer = new SpriteRenderer(ResourceManager::getShader("sprite"));

	ResourceManager::loadTexture("K:/Programming/c/bpa/bpa/pizza.png", true, "pizza");
	ResourceManager::loadTexture("K:/Programming/c/bpa/bpa/rob.png", true, "rob");
	ResourceManager::loadTexture("K:/Programming/c/bpa/bpa/background.png", true, "background");
	ResourceManager::loadTexture("K:/Programming/c/bpa/bpa/sigma.png", true, "sigma");
	
	GameLevel one = GameLevel();
	one.load("K:/Programming/c/bpa/bpa/src/one.lvl", this->width, this->height);

	this->levels.push_back(one);
	this->level = 0;

	characters.push_back(Character(400, 300, ResourceManager::getTexture("sigma")));
}

void Game::update(float dt) {

}

void Game::processInput(float dt) {
	if (keys[GLFW_KEY_UP]) {
		if (characters.size() > 0) {
			characters[0].y -= 1;
		}
	}
	if (keys[GLFW_KEY_DOWN]) {
		if (characters.size() > 0) {
			characters[0].y += 1;
		}
	}
	if (keys[GLFW_KEY_LEFT]) {
		if (characters.size() > 0) {
			characters[0].x -= 1;
		}
	}
	if (keys[GLFW_KEY_RIGHT]) {
		if (characters.size() > 0) {
			characters[0].x += 1;
		}
	}
}

void Game::render() {
	if (this->state == ACTIVE) {
		renderer->drawSprite(ResourceManager::getTexture("background"), glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
		this->levels[this->level].draw(*renderer);
		// draw all characters
		for (Character& character : characters) {
			character.draw(*renderer, this->levels[level].unitWidth, this->levels[level].unitHeight);
		}
	} else if (this->state == MENU) {

	}
}
