#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "MeshRenderer.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "ResourceManager.h"
#include "RenderManager.h"

unique_ptr<Game> GGame = make_unique<Game>();

Game::Game() {

}

Game::~Game() {

}

void Game::Init(HWND hWnd) {
	_hWnd = hWnd;

	_graphics = make_shared<Graphics>(hWnd);
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

	_input = make_shared<InputManager>();
	_input->Init(_hWnd);
	_time = make_shared<TimeManager>();
	_time->Init();
	_scene = make_shared<SceneManager>(_graphics);
	_scene->Init();
	_resource = make_shared<ResourceManager>(_graphics->GetDevice());
	_resource->Init();
	_render = make_shared<RenderManager>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_render->Init();

	SCENE->LoadScene(L"Test");
}

void Game::Update() {
	INPUT->Update();
	TIME->Update();
	SCENE->Update();
}

void Game::Render() {
	RENDER->Update(_graphics);
}
