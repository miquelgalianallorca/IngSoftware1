#include "stdafx.h"
#include "Utils.h"
#include "World.h"

#include "Bullet.h"
#include "Enemy.h"
#include "Mushroom.h"
#include "Player.h"
#include "MeteoManager.h"

World::World() {
	enemySpawnTime    = 20;
	mushroomSpawnTime = 20;
	enemyTimer        = 0;
	mushroomTimer     = 0;
	player            = nullptr;
	meteoManager      = nullptr;
}

World::~World() {
	delete player;
	delete meteoManager;
}

void World::Init() {
	player       = new Player();
	meteoManager = new MeteoManager();
	meteoManager->Init(5);
}

void World::Update() {
	meteoManager->Update();
	// Bullet logic
	for (auto itB = bullets.begin(); itB != bullets.end();) {
		bool eraseBullet = false;
		itB->Update();
		// Destroy bullet out of bounds
		if (OutOfBounds(itB->GetPos())) eraseBullet = true;
		else {
			// Collision bullet/enemy
			for (auto itE = enemies.begin(); itE != enemies.end();) {
				bool eraseEnemy = false;
				if (Distance(itB->GetPos(), itE->GetPos()) <= 1) {
					eraseEnemy = true;
					eraseBullet = true;
					player->AddPoints(pointsEnemyKill);
				}
				if (eraseEnemy) itE = enemies.erase(itE);
				else            itE++;
			}
			// Collision bullet/mushroom
			for (auto itM = mushrooms.begin(); itM != mushrooms.end();) {
				bool eraseMushroom = false;
				if (Distance(itB->GetPos(), itM->GetPos()) < 1) {
					eraseBullet = true;
					eraseMushroom = true;
				}
				if (eraseMushroom) itM = mushrooms.erase(itM);
				else               itM++;
			}
		}

		if (eraseBullet) itB = bullets.erase(itB);
		else             itB++;
	}

	// Enemy logic
	if (enemyTimer > enemySpawnTime) {
		//Spawn enemy
		Enemy e;
		e.Init(lineSize);
		enemies.push_back(e);
		enemyTimer = 0;
	}
	else enemyTimer++;
	for (auto it = enemies.begin(); it != enemies.end();) {
		bool remove = false;
		it->Update();
		//Destroy enemy out of bounds
		if (OutOfBounds(it->GetPos())) remove = true;
		else {
			//Collision enemy/player
			if (Distance(player->GetPos(), it->GetPos()) <= 1) {
				remove = true;
				player->Damage();
			}
		}
		if (remove) it = enemies.erase(it);
		else        it++;
	}

	// Mushroom logic
	if (mushroomTimer > mushroomSpawnTime) {
		//Spawn mushroom
		Mushroom m;
		m.Init(lineSize);
		mushrooms.push_back(m);
		mushroomTimer = 0;
	}
	else mushroomTimer++;
	for (auto itM = mushrooms.begin(); itM != mushrooms.end();) {
		bool eraseMushroom = false;
		//Collision mushroom/player
		if (Distance(player->GetPos(), itM->GetPos()) < 1) {
			eraseMushroom = true;
			player->AddPoints(pointsMushroom);
		}
		if (eraseMushroom) itM = mushrooms.erase(itM);
		else               itM++;
	}
}

void World::MovePlayer(Direction _dir) {
	player->Move(_dir);
}

void World::AddBullet(Direction _dir) {
	Bullet b;
	if (_dir == Direction::Left) b.SetLeftBullet (player->GetPos() - 1);
	else                         b.SetRightBullet(player->GetPos() + 1);
	bullets.push_back(b);
}

void World::Draw() {
	//Draw sky
	MoveConsoleCursor(0, 11);
	for (int i = 0; i < lineSize; i++) {
		char draw = meteoManager->GetGraphicAt(i, 1);
		printf("%c", draw);
	}
	//Draw ground
	MoveConsoleCursor(0, 12);
	for (int i = 0; i < lineSize; i++) {
		// Weather effects
		char draw = meteoManager->GetGraphicAt(i, 0);
		// Draw character
		if (i == player->GetPos()) draw = player->GetGraphic();
		// Draw bullets
		for (auto it = bullets.begin(); it != bullets.end(); it++) {
			if (it->GetPos() == i) draw = it->GetGraphic();
		}
		// Draw enemies
		for (auto it = enemies.begin(); it != enemies.end(); it++) {
			if (it->GetPos() == i) draw = it->GetGraphic();
		}
		// Draw mushrooms
		for (auto it = mushrooms.begin(); it != mushrooms.end(); it++) {
			if (it->GetPos() == i) draw = it->GetGraphic();
		}
		printf("%c", draw);
	}
	printf(" LIVES: %i    POINTS: %03i", player->GetLives(), player->GetPoints());
}