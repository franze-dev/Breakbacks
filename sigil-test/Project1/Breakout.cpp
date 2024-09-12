#include "Breakout.h"
#include "Rect.h"

Rect mainRect;

void Play()
{
	mainRect = GetDefaultRect();

	// set up our window and a few resources we need
	slWindow(screenWidth, screenHeight, "BREAKBACKS", 0);
	/*slSetFont(slLoadFont("ttf/white_rabbit.ttf"), 24);
	slSetTextAlign(SL_ALIGN_CENTER);
	int tex = slLoadTexture("png/glow.png");*/

	while (!slShouldClose() && !slGetKey(SL_KEY_ESCAPE))
	{
		// background glow
		//slSetForeColor(0.1, 0.9, 0.2, 0.4);
		//slSprite(tex, 200, 240, 300, 200);

		//// large text and fat line
		//slSetFontSize(24);
		//slText(200, 250, "SIGIL:");
		slSetForeColor(0.8, 0.0, 0.2, 1.0);
		slRectangleFill(mainRect.x, mainRect.y, mainRect.width, mainRect.height);

		// smaller subtext
		/*slSetFontSize(14);
		slText(200, 220, "Sprites, text, sound, input, and more!")*/;
		//slLine(48, 210, 352, 210);

		slRender();
	}
	slClose();
}
