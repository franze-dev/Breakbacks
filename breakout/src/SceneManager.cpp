#include "SceneManager.h"

static SceneManager::Scene currentScene = SceneManager::Menu;

void SceneManager::SetCurrentScene(Scene scene)
{
	currentScene = scene;
}

SceneManager::Scene SceneManager::GetCurrentScene()
{
	return currentScene;
}