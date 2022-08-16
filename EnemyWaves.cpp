#include "EnemyWaves.h"
EnemyWaves::EnemyWaves(Updater* u, Render* r, Camera* c, Shape* s)
{
	updater = u;
	render = r;
	camera = c;
	shape = s;
	updaterCountItems = updater->GetSize();
	renderCountItems = render->GetSize();
	Start();
}
void EnemyWaves::Restart()
{
	for (auto it = enemies.begin(); it != enemies.end(); ++it)
	{
		(*it).MustDeletedR();
		(*it).MustDeletedU();
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	DeleteEnemies();
	Start();
}
void EnemyWaves::Start()
{
	countEnemies = 1;
	countWaves = 0;
	addEnemies = false;
	timerWorking = true;
	startTime = std::chrono::steady_clock::now();
}
void EnemyWaves::AddEnemies(int number)
{
	for (int i = enemies.size(); number > 0; i++, number--)
	{
		Vector3D position = { rand() % 200, rand() % 200, 0 };
		enemies.push_back(Enemy(true, 4, position, i + 1, 0, 10, 3.5, 100, 20, shape, camera));
		updater->Add(&enemies[i]);
		render->Add(&enemies[i], Position::world);
	}
	if (enemies.size() == countEnemies)
	{
		addEnemies = false;
	}
}
void EnemyWaves::DeleteEnemies()
{
	if (updaterCountItems == updater->GetSize() && renderCountItems == render->GetSize() && enemies.size())
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		countWaves++;
		countEnemies += 8;
		if (countEnemies > 100)
			countEnemies = 100;
		enemies.erase(enemies.begin(), enemies.end());
		timerWorking = true;
		startTime = std::chrono::steady_clock::now();
	}
}
void EnemyWaves::NewWave()
{
	if (addEnemies && startTime + deltaTime * enemies.size() / 10 < std::chrono::steady_clock::now())
	{
		int number = countEnemies - enemies.size();
		if (number > 10)
			number = 10;
		AddEnemies(number);
	}
}
void EnemyWaves::HUpdate()
{
	DeleteEnemies();
	if (timerWorking && startTime + timer < std::chrono::steady_clock::now())
	{
		addEnemies = true;
		timerWorking = false;
		startTime = std::chrono::steady_clock::now();
	}
	else if (timerWorking)
	{
		camera->SetWavesTimer(std::chrono::duration_cast<std::chrono::seconds>(startTime + timer - std::chrono::steady_clock::now()).count());
	}
	else
	{
		camera->SetWavesTimer(-1);
	}
	NewWave();
}
void EnemyWaves::StopHUpdate()
{
	canHardUpdate = false;
	for (auto i = enemies.begin(); i != enemies.end(); ++i)
	{
		(*i).StopRender();
	}
}
void EnemyWaves::ContinueHUpdate()
{
	canHardUpdate = true;
	for (auto i = enemies.begin(); i != enemies.end(); ++i)
	{
		(*i).ContinueRender();
	}
}
Enemy& EnemyWaves::GetEnemy(int i)
{
	return enemies[i - 1];
}
int EnemyWaves::GetSize()
{
	return enemies.size();
}