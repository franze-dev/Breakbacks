#include "SceneManager.h"

namespace SceneManager
{
	static Scene currentScene = SceneManager::Menu;

	void SetCurrentScene(Scene scene)
	{
		currentScene = scene;
	}

	Scene GetCurrentScene()
	{
		return currentScene;
	}
}

