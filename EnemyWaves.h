#pragma once
#include <deque>
#include <ctime>
#include <chrono>
#include "Enemy.h"
#include "Update.h"
#include "Render.h"
#include "Camera.h"
#include "Shape.h"
#include "HardUpdate.h"

class EnemyWaves : public HUpdateItem
{
	int countEnemies;
	int countWaves;
	bool addEnemies;
	bool timerWorking;
	int updaterCountItems;
	int renderCountItems;
	Updater* updater;
	Render* render;
	Camera* camera;
	Shape* shape;
	std::chrono::steady_clock::time_point startTime;
	std::chrono::milliseconds timer = std::chrono::milliseconds(10000);
	std::chrono::milliseconds deltaTime = std::chrono::milliseconds(1000);
	std::deque<Enemy> enemies;

public:
	EnemyWaves(Updater* u, Render* r, Camera* c, Shape* s);
	void Restart();
	void Start();
	void AddEnemies(int number);
	void DeleteEnemies();
	void NewWave();
	void HUpdate() override;
	void StopHUpdate() override;
	void ContinueHUpdate();
	Enemy& GetEnemy(int i);
	int GetSize();
};