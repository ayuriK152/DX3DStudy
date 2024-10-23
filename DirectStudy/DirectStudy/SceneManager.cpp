#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Camera.h"
#include "Transform.h"
#include "MeshRenderer.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Mesh.h"
#include "Animator.h"

SceneManager::SceneManager(shared_ptr<Graphics> graphics) : _graphics(graphics) {
	
}

void SceneManager::Init() {
	if (_activeScene == nullptr)
		return;

	_activeScene->Awake();
	_activeScene->Start();
}

void SceneManager::Update() {
	if (_activeScene == nullptr)
		return;

	_activeScene->Update();
	_activeScene->LateUpdate();

	_activeScene->FixedUpdate();
}

void SceneManager::LoadScene(wstring sceneName) {


	_activeScene = LoadTestScene();
	Init();
}

std::shared_ptr<Scene> SceneManager::LoadTestScene() {
	shared_ptr<Scene> scene = make_shared<Scene>();

	// TODO

	shared_ptr<GameObject> camera = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		camera->GetOrAddTransform();
		camera->AddComponent(make_shared<Camera>());
		scene->AddGameObject(camera);
	}

	{
		shared_ptr<GameObject> tempObj = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		{
			tempObj->GetOrAddTransform();

			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			tempObj->AddComponent(meshRenderer);

			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);

			auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);

		}
		{
			auto animator = make_shared<Animator>();
			tempObj->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(tempObj);
	}

	{
		shared_ptr<GameObject> tempObj = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
		tempObj->GetOrAddTransform()->SetPosition(Vec3{ 1.0f, 1.0f, 1.0f });
		{
			tempObj->GetOrAddTransform();

			auto meshRenderer = make_shared<MeshRenderer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
			tempObj->AddComponent(meshRenderer);

			auto material = RESOURCES->Get<Material>(L"Default");
			meshRenderer->SetMaterial(material);

			auto mesh = RESOURCES->Get<Mesh>(L"Rectangle");
			meshRenderer->SetMesh(mesh);

		}
		{
			auto animator = make_shared<Animator>();
			tempObj->AddComponent(animator);
			auto anim = RESOURCES->Get<Animation>(L"SnakeAnim");
			animator->SetAnimation(anim);
		}
		scene->AddGameObject(tempObj);
	}

	return scene;
}
