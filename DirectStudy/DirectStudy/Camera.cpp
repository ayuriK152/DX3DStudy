#include "pch.h"
#include "Camera.h"

Matrix Camera::S_MatView = Matrix::Identity;
Matrix Camera::S_MatProjection = Matrix::Identity;

Camera::Camera() : Super(ComponentType::Camera) {

}

Camera::~Camera() {

}

void Camera::Update() {
	UpdateMatrix();
}

void Camera::UpdateMatrix() {
	S_MatView = GetTransform()->GetWorldMatrix().Invert();

	if (_type == ProjectionType::Perspective) {
		S_MatProjection = ::XMMatrixPerspectiveFovLH(XM_PI / 4.0f, 800.0f / 600.0f, 1.0f, 100.0f);
	}
	else {
		S_MatProjection = ::XMMatrixOrthographicLH(8.0f, 6.0f, 0.0f, 1.0f);
	}
}
