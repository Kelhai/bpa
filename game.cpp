#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"

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

	GameLevel one = GameLevel();
	one.load("K:/Programming/c/bpa/bpa/src/one.lvl", this->width, this->height / 2);

	this->levels.push_back(one);
	this->level = 0;
}

void Game::update(float dt) {

}

void Game::processInput(float dt) {

}

void Game::render() {
	if (this->state == ACTIVE) {
		renderer->drawSprite(ResourceManager::getTexture("background"),
			glm::vec2(0.0f, 0.0f), glm::vec2(this->width, this->height), 0.0f);
		this->levels[this->level].draw(*renderer);
	}
}
