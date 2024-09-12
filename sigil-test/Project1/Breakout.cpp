#include "Breakout.h"
#include "Rect.h"
#include "KeyManager.h"

static Rect mainRect;

namespace Breakout
{
	void Init();
	void Update();
	void Draw();
}

void Play()
{
	Breakout::Init();

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		Breakout::Update();
		Breakout::Draw();

		slRender();
	}
	slClose();
}

void Breakout::Init()
{
	slWindow(screenWidth, screenHeight, "BREAKBACKS", 0);

	mainRect = RectSpace::GetDefaultRect();
}

void Breakout::Update()
{
	RectSpace::MoveRect(mainRect);
}

void Breakout::Draw()
{
	RectSpace::DrawRect(mainRect);
}

