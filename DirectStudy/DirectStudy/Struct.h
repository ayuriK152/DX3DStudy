#pragma once

struct Vertex {
	Vec3 position;
	// Color color;
	Vec2 uv;
};

struct CameraData {
	Matrix matView = Matrix::Identity;
	Matrix matProjection = Matrix::Identity;
};

struct TransformData {
	Matrix matWorld = Matrix::Identity;
};