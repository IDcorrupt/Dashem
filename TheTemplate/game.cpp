#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	void Game::DrawI(int x, int y)
	{
		screen->Line(100 + x, 50 + y, 200 + x, 50 + y, 0xffffff);
		screen->Line(150 + x, 50 + y, 150 + x, 300 + y, 0xffffff);
		screen->Line(100 + x, 300 + y, 200 + x, 300 + y, 0xffffff);
	}
	void Game::DrawFatI(int width, int moveoffset) {
		for (int i = 0; i < width; i++)
		{
			DrawI(i+moveoffset, i);
		}
	}


	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		for (int i = 0; i < 16; i++)
		{
			theSprite.SetFrame(i);
			theSprite.Draw(screen, i * 50, 0);
		}
	}
	
};