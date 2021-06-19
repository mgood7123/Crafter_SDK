#ifndef BASECAMERA_GUARD
#define BASECAMERA_GUARD

#include <Magnum/SceneGraph/Camera.h>
#include <Magnum/SceneGraph/Scene.h>
#include <Magnum/GL/DefaultFramebuffer.h>

// https://www.opengl.org/discussion_boards/showthread.php/198988-Implementing-an-orbit-camera
// https://en.wikipedia.org/wiki/Spherical_coordinate_system#Cartesian_coordinates
// https://upload.wikimedia.org/wikipedia/commons/thumb/d/dc/3D_Spherical_2.svg/240px-3D_Spherical_2.svg.png
template <typename Scene3D, typename Object3D>
class OrbitingCamera
{
public:
	explicit OrbitingCamera(Scene3D& scene, float in_distanceToOrigin, Magnum::Vector3 in_originPoint) {
		using namespace Magnum::Math::Literals;
		this->distanceToOrigin = in_distanceToOrigin;
		this->storedOriginPoint = in_originPoint;

		_fov = 35.0_degf;
		_aspectRatio = 1.0f;
		_nearPlane = 0.01f;
		_farPlane = 100.f;

		_up = Magnum::Vector3{ 0.f, 1.f, 0.f };
		//rotate around up axis
		phi = Magnum::Constants::piHalf();
		theta = 0.0f;

		float x = distanceToOrigin * sin(phi) * cos(theta);
		float y = distanceToOrigin * cos(phi);
		float z = distanceToOrigin * sin(phi) * sin(theta);

		_front = Magnum::Vector3(x, y, z).normalized();

		/* Every scene needs a camera */
		(*(_cameraObject = new Object3D{ &scene }));
		_cameraObject->setTransformation(Magnum::Matrix4::lookAt(Magnum::Vector3(x, y, z) + storedOriginPoint, storedOriginPoint, _up));

		(*(_camera = new Magnum::SceneGraph::Camera3D{ *_cameraObject }))
				.setAspectRatioPolicy(Magnum::SceneGraph::AspectRatioPolicy::Extend)
				.setProjectionMatrix(Magnum::Matrix4::perspectiveProjection(_fov, _aspectRatio, _nearPlane, _farPlane))
				.setViewport(Magnum::GL::defaultFramebuffer.viewport().size());
	};
	//getter
	Object3D* cameraObject() {
		return _cameraObject;
	};
	//getter
	Magnum::SceneGraph::Camera3D* camera() {
		return _camera;
	};

	OrbitingCamera& zoom(Magnum::Float percentage) {
		Magnum::Float perc = std::max(-1.f, std::min(1.f, percentage));

		_fov += perc * _fov;

		_camera->setProjectionMatrix(
				Magnum::Matrix4::perspectiveProjection(_fov, _aspectRatio, _nearPlane, _farPlane));
		return *this;
	};
	OrbitingCamera& rotate(Magnum::Float dYaw, Magnum::Float dPitch, Magnum::Float sensitivity = 0.001f) {
		return *this;
	};
	// pitch is rotation around horizontal. yaw is rotation around vertical. Combine these to orbit around mesh
	OrbitingCamera& rotateAndTranslateInSphere(Magnum::Float dPhi, Magnum::Float dTheta, Magnum::Float sensitivity = 0.001f) {
		phi += dPhi * sensitivity;
		phi = std::max(1e-5f,
					   std::min(1.0f*Magnum::Math::Constants<Magnum::Float>::pi(), phi));
		theta += dTheta * sensitivity;
		//theta = std::max(0.0f, std::min(2.0f*Magnum::Math::Constants<Magnum::Float>::pi(), theta));
		/*
        _front = (Magnum::Vector3{
        std::cos(_yaw) * std::cos(_pitch), std::sin(_pitch), std::sin(_yaw) * std::cos(_pitch) })
        .normalized();
        Magnum::Vector3 cameraPos = _cameraObject->transformation().translation();
        */
		float x = distanceToOrigin * sin(phi) * cos(theta);
		float y = distanceToOrigin * cos(phi);
		float z = distanceToOrigin * sin(phi) * sin(theta);

		_front = Magnum::Vector3(x, y, z).normalized();

		//it performs translation to origin point. Params: eye position, target, up
		_cameraObject->setTransformation(Magnum::Matrix4::lookAt(Magnum::Vector3(x, y, z) + storedOriginPoint, storedOriginPoint, _up));
		return *this;
	};
	OrbitingCamera& move(Magnum::Float speed) {
		float currentDeltaDistance = distanceToOrigin;
		if (speed < 0) {
			currentDeltaDistance = distanceToOrigin - (speed*_front).length();
		}
		else {
			currentDeltaDistance = distanceToOrigin + (speed*_front).length();
		}
		distanceToOrigin = currentDeltaDistance;
		_cameraObject->translate(speed * _front);

		return *this;
	};
	// strafe to left and to right. Changes origin point
	OrbitingCamera& strafe(Magnum::Float speed) {
		Magnum::Vector3 translationVector = speed * Magnum::Math::cross(_front, _up).normalized();
		// translation is simply vector addition
		storedOriginPoint = storedOriginPoint + translationVector;
		_cameraObject->translate(translationVector);
		return *this;
	};
	// strafe up and down. Changes origin point
	OrbitingCamera& upDown(Magnum::Float speed) {
		Magnum::Vector3 translationVector = speed * _up.normalized();
		storedOriginPoint = storedOriginPoint + translationVector;
		_cameraObject->translate(translationVector);
		return *this;
	};
protected:
	// no need to delete these manually, they'll be deleted on scene destruction
	Object3D * _cameraObject;
	Magnum::SceneGraph::Camera3D* _camera;

	Magnum::Float _aspectRatio, _nearPlane, _farPlane;
	Magnum::Rad _fov;

	Magnum::Vector3 _up, _front;
	//phi is angle between vertical direction.
	//theta is angle in horizontal plane
	Magnum::Float theta, phi;
	Magnum::Float distanceToOrigin;
	Magnum::Vector3 storedOriginPoint;
};

#endif