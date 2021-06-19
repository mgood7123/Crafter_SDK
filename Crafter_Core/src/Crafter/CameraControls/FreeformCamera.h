#ifndef FreeformCamera_GUARD
#define FreeformCamera_GUARD

#include <cmath>
#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/GL/DefaultFramebuffer.h>

/*
Class for camera for mosra/magnum
Author: Konstantinos Chatzilygeroudis (costashatz@gmail.com)
*/
template <typename Scene3D, typename Object3D>
class FreeformCamera {
public:

	explicit FreeformCamera(Scene3D & scene) {
		using namespace Magnum::Math::Literals;

		_fov = 35.0_degf;
		_aspectRatio = 1.0f;
		_nearPlane = 0.01f;
		_farPlane = 100.f;

		_up = Magnum::Vector3{0.f, 1.f, 0.f};
		_yaw = -Magnum::Math::Constants<Magnum::Float>::piHalf();
		_pitch = 0.f;
		_front = (Magnum::Vector3{
				std::cos(_yaw) * std::cos(_pitch), std::sin(_pitch),
				std::sin(_yaw) * std::cos(_pitch)})
				.normalized();

		/* Every scene needs a camera */
		_cameraObject = new Object3D{&scene};
		Magnum::Vector3 cameraPos = _cameraObject->transformation().translation();
		_cameraObject->transformation().lookAt(cameraPos, cameraPos + _front, _up);
		(*(_camera = new Magnum::SceneGraph::Camera3D{*_cameraObject}))
				.setAspectRatioPolicy(Magnum::SceneGraph::AspectRatioPolicy::Extend)
				.setProjectionMatrix(
						Magnum::Matrix4::perspectiveProjection(_fov, _aspectRatio, _nearPlane,
															   _farPlane))
				.setViewport(Magnum::GL::defaultFramebuffer.viewport().size());
	}

	Object3D * cameraObject() {
		return _cameraObject;
	}

	Magnum::SceneGraph::Camera3D *camera() {
		return _camera;
	}

	FreeformCamera & zoom(Magnum::Float percentage) {
		Magnum::Float perc = std::max(-1.f, std::min(1.f, percentage));

		_fov += perc * _fov;

		_camera->setProjectionMatrix(
				Magnum::Matrix4::perspectiveProjection(_fov, _aspectRatio, _nearPlane, _farPlane));

		return *this;
	}

	FreeformCamera & rotate(Magnum::Float dYaw, Magnum::Float dPitch, Magnum::Float sensitivity = 0.001f) {
		_pitch += dPitch * sensitivity;
		_pitch = std::max(-Magnum::Math::Constants<Magnum::Float>::piHalf(),
						  std::min(Magnum::Math::Constants<Magnum::Float>::piHalf(), _pitch));
		_yaw += dYaw * sensitivity;

		_front = (Magnum::Vector3{
				std::cos(_yaw) * std::cos(_pitch), std::sin(_pitch),
				std::sin(_yaw) * std::cos(_pitch)})
				.normalized();
		Magnum::Vector3 cameraPos = _cameraObject->transformation().translation();

		_cameraObject->setTransformation(
				Magnum::Matrix4::lookAt(cameraPos, cameraPos + _front, _up));

		return *this;
	}

	// pitch is rotation around horizontal. yaw is rotation around vertical. Combine these to orbit around mesh
	// https://www.opengl.org/discussion_boards/showthread.php/198988-Implementing-an-orbit-camera
	FreeformCamera & rotateAndTranslateInSphere(Magnum::Float dYaw, Magnum::Float dPitch,
											   Magnum::Float sensitivity = 0.001f) {
		float distanceToOrigin = 5.0;
		_pitch += dPitch * sensitivity;
		_pitch = std::max(-Magnum::Math::Constants<Magnum::Float>::piHalf(),
						  std::min(Magnum::Math::Constants<Magnum::Float>::piHalf(), _pitch));
		_yaw += dYaw * sensitivity;
		//recalculate front vector
		_front = (Magnum::Vector3{
				std::cos(_yaw) * std::cos(_pitch), std::sin(_pitch),
				std::sin(_yaw) * std::cos(_pitch)})
				.normalized();
		//now I need to get a position on sphere
		//_cameraObject->translate();
		Magnum::Vector3 cameraPosOld = _cameraObject->transformation().translation();

		Magnum::Vector3 cameraPosNew = distanceToOrigin *
									   Magnum::Vector3{std::cos(_yaw) * std::cos(_pitch),
													   std::sin(_pitch),
													   std::sin(_yaw) * std::cos(_pitch)};
		Magnum::Vector3 translationVector = cameraPosOld + cameraPosNew;
		_cameraObject->translate(translationVector);

		Magnum::Vector3 cameraPos = _cameraObject->transformation().translation();

		_cameraObject->setTransformation(
				Magnum::Matrix4::lookAt(cameraPos, /*_front*/Magnum::Vector3{0.0f, 0.0f, 0.0f},
										_up));
		return *this;
	}

	FreeformCamera & move(Magnum::Float speed) {
		_cameraObject->translate(speed * _front);

		return *this;
	}

	// strafe to left and to right
	FreeformCamera & strafe(Magnum::Float speed) {
		_cameraObject->translate(speed * Magnum::Math::cross(_front, _up).normalized());

		return *this;
	}

	FreeformCamera & upDown(Magnum::Float speed) {
		_cameraObject->translate(speed * _up.normalized());
		return *this;
	}

protected:
	// no need to delete these manually, they'll be deleted on scene destruction
	Object3D * _cameraObject;
	Magnum::SceneGraph::Camera3D * _camera;

	Magnum::Float _aspectRatio, _nearPlane, _farPlane;
	Magnum::Rad _fov;

	Magnum::Vector3 _up, _front;
	Magnum::Float _yaw, _pitch;
};

#endif