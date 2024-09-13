#include "SceneManager.h"

static SceneManager::Scene currentScene = SceneManager::Gameplay;

void SceneManager::SetCurrentScene(Scene scene)
{
	currentScene = scene;
}

SceneManager::Scene SceneManager::GetCurrentScene()
{
	return currentScene;
}