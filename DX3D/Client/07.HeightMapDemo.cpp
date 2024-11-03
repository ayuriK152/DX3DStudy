#include "pch.h"
#include "07.HeightMapDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include "CameraScript.h"
#include "Texture.h"

void HeightMapDemo::Init()
{
	_shader = make_shared<Shader>(L"06.Terrain.fx");

	//_texture = RESOURCES->Load<Texture>(L"mari", L"..\\Resources\\Textures\\mari.png");_texture = RESOURCES->Load<Texture>(L"mari", L"..\\Resources\\Textures\\mari.png");
	_texture = RESOURCES->Load<Texture>(L"mari", L"..\\Resources\\Textures\\mari.png"); _texture = RESOURCES->Load<Texture>(L"terrain", L"..\\Resources\\Textures\\Terrain\\grass.jpg");
	_heightMap = RESOURCES->Load<Texture>(L"height", L"..\\Resources\\Textures\\Terrain\\height.png");

	const int32 width = _heightMap->GetSize().x;
	const int32 height = _heightMap->GetSize().y;

	const DirectX::ScratchImage& info = _heightMap->GetInfo();
	uint8* pixelBuffer = info.GetPixels();

	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateGrid(_geometry, width, height);

	{
		vector<VertexTextureData>& v = const_cast<vector<VertexTextureData>&>(_geometry->GetVertices());
		
		for (int32 z = 0; z < height; z++)
		{
			for (int32 x = 0; x < width; x++)
			{
				int32 idx = width * z + x;

				uint8 height = pixelBuffer[idx] / 255.f * 25.f;
				v[idx].position.y = height;
			}
		}
	}

	_vertexBuffer = make_shared<VertexBuffer>();
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>();
	_indexBuffer->Create(_geometry->GetIndices());

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetLocalPosition(Vec3(0.f, 10.f, -5.f));
	_camera->GetTransform()->SetLocalRotation(Vec3(-25.f, 0.f, 0.f));
}

void HeightMapDemo::Update()
{
	_camera->Update();
}

void HeightMapDemo::Render()
{
	_shader->GetMatrix("World")->SetMatrix((float*)&_world);
	_shader->GetMatrix("View")->SetMatrix((float*)&Camera::S_MatView);
	_shader->GetMatrix("Projection")->SetMatrix((float*)&Camera::S_MatProjection);
	_shader->GetSRV("Texture0")->SetResource(_texture->GetComPtr().Get());

	uint32 stride = _vertexBuffer->GetStride();
	uint32 offset = _vertexBuffer->GetOffset();

	DC->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
	DC->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);

	// _shader->Draw(0, 1, _vertexBuffer->GetCount());
	_shader->DrawIndexed(0, 0, _indexBuffer->GetCount(), 0, 0);
}