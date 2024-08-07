#include "pch.h"
#include "Game.h"
#include "Camera.h"
#include "MeshRenderer.h"

Game::Game() {

}

Game::~Game() {

}

void Game::Init(HWND hWnd) {
	_hWnd = hWnd;

	_graphics = make_shared<Graphics>(hWnd);
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

	_tempObj = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_tempObj->GetOrAddTransform();
		_tempObj->AddComponent(make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext()));
	}
	_camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_camera->GetOrAddTransform();
		_camera->AddComponent(make_shared<Camera>());
	}
}

void Game::Update() {
	_tempObj->Update();


	_camera->Update();
}

void Game::Render() {
	_graphics->RenderBegin();

	// TEMP
	_tempObj->GetMeshRenderer()->Render(_pipeline);

	_graphics->RenderEnd();
}
