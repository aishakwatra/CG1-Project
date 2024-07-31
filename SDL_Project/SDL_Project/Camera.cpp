#include "Camera.h"

Camera::Camera(void): center(Point(0.0f, 0.0f)), right(Vector(1.0f, 0.0f)), up(Vector(0.0f, 1.0f)), width(2.0f), height(2.0f) {}

Camera::Camera(const Point& C, const Vector& up, float W, float H): center(C), up(up), width(W), height(H) {
	
	right = Vector(up.y, up.x);

}

Point Camera::Center(void) const {
	return center;
}

Vector Camera::Right(void) const{
	return right;
}

Vector Camera::Up(void) const {
	return up;
}

float Camera::Width(void) const {
	return width;
}

float Camera::Height(void) const {
	return height;
}

Camera& Camera::MoveRight(float x) {

	center = center + (x * right);

	return *this;

}

Camera& Camera::MoveUp(float y) {

	center = center + (y * up);

	return *this;
}

Camera& Camera::Rotate(float t) {


	Affine rotateMatrix = Rot(-t);
	
	right = Vector(rotateMatrix * right);
	up = Vector(rotateMatrix * up);

	return *this;

}



Camera& Camera::Zoom(float f) {

	width *= f;
	height *= f;

	return *this;

}


Affine WorldToCamera(const Camera& cam) {


	Affine result, m1, m2;

	m1 = Affine(cam.Right(), cam.Up(), Point(0.0f, 0.0f));

	//translation matrix
	m2.row[0][2] = -cam.Center().x;
	m2.row[1][2] = -cam.Center().y;

	result = m1 * m2;

	return result;

}

Affine CameraToWorld(const Camera& cam) {

	return Inverse(WorldToCamera(cam));

}

Affine CameraToNDC(const Camera& cam) {

	return Scale(2 / cam.Width(), (2 / cam.Height()));

}

Affine NDCToCamera(const Camera& cam) {


	return Inverse(CameraToNDC(cam));

}