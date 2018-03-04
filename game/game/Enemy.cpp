#include "Enemy.h"
#include <thread>
Enemy::Enemy(int num,sf::Texture gtex,sf::Texture stex, sf::Texture bullet,sf::SoundBuffer guns, sf::Vector2f initialPosition, int hp, int dmgValue,int t,sf::Vector2f d,sf::Vector2u wb) {

	
	damageMin = dmgValue;
	level = 1;
//	speed = 3.5f;
	damageMax = 20;
	currentLevel = 0;
	speed = 2.5f;
//	imgPath = path;
//	bulletPath = bullet;
	playerNr = num;
	bulletTexture = bullet;
	spaceTexture = stex;
	groundTex = gtex;
	direction = d;
	maxhp = hp;
	type = t;
	initialPos = initialPosition;
	gunBuffer = guns;
	windowBounds = wb;
	loadFiles();

}
int Enemy::initialize() {
	if (currentLevel ==1) sprite.setTexture(spaceTexture);
	else sprite.setTexture(groundTex);
//	sprite.setPosition(initialPos);
	sprite.setPosition((rand() % windowBounds.x)+ 1240 , (rand() % windowBounds.y )+ sprite.getGlobalBounds().height);
	return 0;
}
float Enemy::vectorLength(sf::Vector2f v) {
	return sqrt(pow(v.x, 2) + pow(v.y, 2));
}
sf::Vector2f Enemy::normalize(sf::Vector2f v, float length) {
	return v / length;
}

int Enemy::loadFiles() {

	return 0;

}
int Enemy::takeDamage(int damage) {
	this->hp -= damage;
	if (this->hp <= 0) {
		this->hp = 0;
	}
	return 0;
}

void Enemy::movement(sf::Vector2f playerPos) {
	sf::Vector2f fudir;
	if (this->currentLevel == 1) {
		if (type==1) this->sprite.move(direction * speed);
		else {
			direction.x = playerPos.x - this->sprite.getPosition().x;
			direction.y = playerPos.y - this->sprite.getPosition().y;

			fudir = normalize(direction, vectorLength(direction));
			this->sprite.setRotation(atan2(fudir.y, fudir.x) * 180 / 3.141592 + 180);
			this->sprite.move(fudir.x * 3.f * speed, fudir.y * 3.f * speed);

		}
	}
}
void Enemy::update(sf::Vector2f playerPos) {
	this->movement(playerPos);
}
void Enemy::draw(sf::RenderTarget * target) {
	target->draw(this->sprite);
}


