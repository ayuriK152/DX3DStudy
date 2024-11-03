#pragma once
#include "IExecute.h"
#include "Geometry.h"

class GameObject;

class MeshDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;

private:
	shared_ptr<GameObject> _obj;

	// Camera
	shared_ptr<GameObject> _camera;

	shared_ptr<GameObject> _light;
};