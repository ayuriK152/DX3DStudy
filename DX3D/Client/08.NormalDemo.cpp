#include "pch.h"
#include "08.NormalDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "CameraScript.h"
#include "Texture.h"

void NormalDemo::Init()
{
	_shader = make_shared<Shader>(L"07.Normal.fx");

	//_texture = RESOURCES->Load<Texture>(L"mari", L"..\\Resources\\Textures\\mari.png");_texture = RESOURCES->Load<Texture>(L"mari", L"..\\Resources\\Textures\\mari.png");
	_texture = RESOURCES->Load<Texture>(L"koyuki", L"..\\Resources\\Textures\\koyuki.png");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetLocalPosition(Vec3(0.f, 0.f, -3.f));

	_light = make_shared<GameObject>();
	_light->GetOrAddTransform();
	_light->GetTransform()->SetRotation(Vec3(60.f, 45.f, 0.f));

	_geometry = make_shared<Geometry<VertexTextureNormalData>>();
	GeometryHelper::CreateSphere(_geometry);
	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());
}

void NormalDemo::Update()
{
	_camera->Update();
	Vec3 _lightRot = _light->GetTransform()->GetLocalRotation();
	_light->GetTransform()->SetRotation(Vec3(60.f, _lightRot.y + 5.f * TIME->GetDeltaTime(), 0.f));
}

void NormalDemo::Render()
{
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());
	Vec3 _lightVec = _light->GetTransform()->GetLook();
	_shader->GetVector("LightDir")->SetFloatVector((float*)&_lightVec);

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	// _shader->Draw(0, 1, _vertexBuffer->GetCount());
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}
