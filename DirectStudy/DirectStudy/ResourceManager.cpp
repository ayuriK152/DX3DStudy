#include "pch.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device) : _device(device) {

}

void ResourceManager::Init() {
	CreateDefaultTexture();
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}

void ResourceManager::CreateDefaultTexture() {
	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"Kokona");
		texture->Create(L"sennam1.png");
		Add(texture->GetName(), texture);
	}
}

void ResourceManager::CreateDefaultMesh() {

}

void ResourceManager::CreateDefaultShader() {

}

void ResourceManager::CreateDefaultMaterial() {

}

void ResourceManager::CreateDefaultAnimation() {

}
