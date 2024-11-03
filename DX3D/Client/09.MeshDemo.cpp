#include "pch.h"
#include "09.MeshDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "CameraScript.h"
#include "Texture.h"
#include "MeshRenderer.h"

void MeshDemo::Init()
{
	//_texture = RESOURCES->Load<Texture>(L"mari", L"..\\Resources\\Textures\\mari.png");
	//_texture = RESOURCES->Load<Texture>(L"koyuki", L"..\\Resources\\Textures\\koyuki.png");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -3.f));

	_light = make_shared<GameObject>();
	_light->GetOrAddTransform();
	_light->GetTransform()->SetRotation(Vec3(60.f, 45.f, 0.f));

	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		auto shader = make_shared<Shader>(L"07.Normal.fx");
		_obj->GetMeshRenderer()->SetShader(shader);
	}
	{
		RESOURCES->Init();
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"koyuki", L"..\\Resources\\Textures\\koyuki.png");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}
}

void MeshDemo::Update()
{
	_camera->Update();
	_obj->Update();
}

void MeshDemo::Render()
{
}
