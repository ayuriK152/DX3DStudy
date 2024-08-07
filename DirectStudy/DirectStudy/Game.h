#pragma once

#include "GameObject.h"

class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hWnd);
	void Update();
	void Render();

private:
	HWND _hWnd;

	shared_ptr<Graphics> _graphics;
	shared_ptr<Pipeline> _pipeline;

	shared_ptr<GameObject> _tempObj;
	shared_ptr<GameObject> _camera;
};
