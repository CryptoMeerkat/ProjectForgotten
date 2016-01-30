#include "Camera.h"

Camera::Camera() {
	yaw = 0.0f;
	pitch = 0.0f;
	roll = 0.0f;
	position = glm::vec3(0, 0, 0);
	speed = 1.0f;
}

Camera::Camera(float pitch, float yaw, float roll, float speed, glm::vec3 position) {
	this->pitch = pitch;
	this->yaw = yaw;
	this->roll = 0.0f;
	this->position = position;
	this->speed = speed;
}

Camera::~Camera() {
}

void Camera::UpdateCamera(float msec) {

	float secondsPassed = msec / 1000.0f;
	msec /= (1000 / speed);

	//pitch -= (Window::GetMouse()->GetRelativePosition().y);
	//yaw -= (Window::GetMouse()->GetRelativePosition().x);

	//pitch = min(pitch, 90.0f);
	//pitch = max(pitch, -90.0f);

	//if (yaw < 0) {
	//	yaw += 360.0f;
	//}

	//if (yaw > 360.0f) {
	//	yaw -= 360.0f;
	//}

	//if (roll < 0) {
	//	roll += 360.0f;
	//}

	//if (roll > 360.0f) {
	//	roll -= 360.0f;
	//}

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_E)) {
	//	//roll--;
	//}

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_Q)) {
	//	//roll++;
	//}

	//Quaternion qcam = Quaternion::EulerAnglesToQuaternion(pitch, yaw, roll);
	//Vector3 oldPosition = position;

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_W)) {
	//	position += qcam.ToMatrix() * Vector3(0.0f, 0.0f, -1.0f) * msec;
	//}

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_S)) {
	//	position -= qcam.ToMatrix() * Vector3(0.0f, 0.0f, -1.0f) * msec;
	//}

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_A)) {
	//	position += qcam.ToMatrix() * Vector3(-1.0f, 0.0f, 0.0f) * msec;
	//}

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_D)) {
	//	position -= qcam.ToMatrix() * Vector3(-1.0f, 0.0f, 0.0f) * msec;
	//}

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_SHIFT)) {
	//	position += qcam.ToMatrix() * Vector3(0.0f, 1.0f, 0.0f) * msec;
	//}

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_SPACE)) {
	//	position -= qcam.ToMatrix() * Vector3(0.0f, 1.0f, 0.0f) * msec;
	//}

	//// the delta position is useful for checking the last camera movement offset
	//// for e.g. adjusting the blur effect
	//deltaPosition = position - oldPosition;

	//if (Window::GetKeyboard()->KeyDown(KEYBOARD_CONTROL)) {
	//	position += deltaPosition * 4.0f;
	//	deltaPosition = position - oldPosition;
	//}

}

glm::mat4 Camera::BuildViewMatrix() const {

	//add the parent transform, as Camera can be in 
	return	glm::rotate(glm::mat4(1.0f), pitch, glm::vec3(-1, 0, 0)) *
			glm::rotate(glm::mat4(1.0f), yaw, glm::vec3(0, -1, 0)) *
			glm::rotate(glm::mat4(1.0f), roll, glm::vec3(0, 0, -1));
			glm::translate(glm::mat4(1.0f), -position);
		
		//Matrix4::Rotation(pitch, Vector3(-1, 0, 0)) *
		//Matrix4::Rotation(yaw, Vector3(0, -1, 0)) *
		//Matrix4::Rotation(roll, Vector3(0, 0, -1)) *
		//Matrix4::Translation(-position) *
		////also the world transform position from parent SceneNodes needs to be inverted
		//Matrix4::Translation(-worldTransform.GetPositionVector());

}

/************************************************************************/
/* SETTERS AND GETTERS                                                  */
/************************************************************************/
glm::vec3 Camera::GetPosition() const {
	return position;
}

///-------------------------------------------------------------------------------------------------
/// <summary>Gets the delta position as a positive value. The positive value is required, because
/// 	it does logically not make sense to return a negative value and functions like the
/// 	blurring expect a positive value to be returned to determine a blur factor.</summary>
///
/// <returns>The delta position.</returns>
///-------------------------------------------------------------------------------------------------
float Camera::GetDeltaPosition() const {
	return (float) deltaPosition.length();
}

glm::vec3 Camera::GetUpVector() const {
	const glm::mat4 m = BuildViewMatrix();
	glm::vec3 v = glm::vec3(m[0][0], m[1][0], m[2][0]);
	return glm::normalize(v);
}

void Camera::SetPosition(glm::vec3 val) {
	position = val;
}

float Camera::GetYaw() const {
	return yaw;
}

void Camera::SetYaw(float y) {
	yaw = y;
}

float Camera::GetPitch() const {
	return pitch;
}

void Camera::SetPitch(float p) {
	pitch = p;
}

float Camera::GetRoll() const {
	return roll;
}

void Camera::SetRoll(float r) {
	roll = r;
}

float Camera::GetSpeed() const {
	return speed;
}