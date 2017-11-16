#pragma once

class Bullet;
class Enemy;
class Mushroom;
class Player;
class MeteoManager;

class World {
public:
	World();
	~World();
	void Init();
	void Update();
	void Draw();

	void MovePlayer(Direction _dir);
	void AddBullet(Direction _dir);

private:
	// Entities
	std::vector<Bullet>   bullets;
	std::vector<Enemy>    enemies;
	std::vector<Mushroom> mushrooms;
	
	Player       * player;
	MeteoManager * meteoManager;

	unsigned int enemySpawnTime;
	unsigned int mushroomSpawnTime;
	unsigned int enemyTimer;
	unsigned int mushroomTimer;
	
	const unsigned int pointsEnemyKill = 5;
	const unsigned int pointsMushroom  = 10;
};