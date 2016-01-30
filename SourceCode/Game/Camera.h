#pragma once

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

///-------------------------------------------------------------------------------------------------
/// <summary>The camera class is used to handle the view matrix within our graphic program.
/// 		 It can be used rendering independent and also controls the camera movement
/// 		 itself, i.e. checking keyboard input.</summary>
///-------------------------------------------------------------------------------------------------
class Camera {

	public:

	///-------------------------------------------------------------------------------------------------
	/// <summary>Default constructor for the camera.
	/// 		 Initializes the camera properties to 0.</summary>
	///-------------------------------------------------------------------------------------------------
	Camera();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Advanced constructor to set pitch yaw and a position.</summary>
	///
	/// <param name="pitch">   The pitch.</param>
	/// <param name="yaw">	   The yaw.</param>
	/// <param name="roll">	   The roll.</param>
	/// <param name="speed">   The speed.</param>
	/// <param name="position">The position.</param>
	///-------------------------------------------------------------------------------------------------
	Camera::Camera(float pitch, float yaw, float roll, float speed, glm::vec3 position);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Destructor.</summary>
	///-------------------------------------------------------------------------------------------------
	virtual ~Camera();

	///-------------------------------------------------------------------------------------------------
	/// <summary>Updates the camera. Called with the msec passed since last updating it.
	/// 		 The camera might be update frame independent.
	/// 		 The keyboard might be checked here for user inputs to move the camera.</summary>
	///
	/// <param name="msec">The msec passed since last updating it</param>
	///-------------------------------------------------------------------------------------------------
	void UpdateCamera(float msec = 10.0f);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Returns the view matrix.
	/// 		 Might be any kind of view matrix (projection, orthogonal, ...).</summary>
	///
	/// <returns>The view matrix.</returns>
	///-------------------------------------------------------------------------------------------------
	virtual glm::mat4 BuildViewMatrix() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets the position.</summary>
	///
	/// <returns>The position.</returns>
	///-------------------------------------------------------------------------------------------------
	glm::vec3 GetPosition() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets the up vector of the camera. Useful for having objects relative on top of the
	/// 	camera. Like a minimap camera.</summary>
	///
	/// <returns>The up vector.</returns>
	///-------------------------------------------------------------------------------------------------
	glm::vec3 GetUpVector() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Returns the global camera position in world space.</summary>
	/// 
	/// <returns>The global position.</returns>
	///-------------------------------------------------------------------------------------------------
	glm::vec3 GetGlobalPosition() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Sets a position.</summary>
	///
	/// <param name="val">The value.</param>
	///-------------------------------------------------------------------------------------------------
	void SetPosition(glm::vec3 val);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets the yaw.</summary>
	///
	/// <returns>The yaw.</returns>
	///-------------------------------------------------------------------------------------------------
	float GetYaw() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Sets a yaw.</summary>
	///
	/// <param name="y">The new yaw.</param>
	///-------------------------------------------------------------------------------------------------
	void SetYaw(float y);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets the pitch.</summary>
	///
	/// <returns>The pitch.</returns>
	///-------------------------------------------------------------------------------------------------
	float GetPitch() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Sets a pitch.</summary>
	///
	/// <param name="p">The new pitch.</param>
	///-------------------------------------------------------------------------------------------------
	void SetPitch(float p);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Gets the roll.</summary>
	///
	/// <returns>The roll.</returns>
	///-------------------------------------------------------------------------------------------------
	float GetRoll() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Sets a roll.</summary>
	///
	/// <param name="r">The new roll.</param>
	///-------------------------------------------------------------------------------------------------
	void SetRoll(float r);

	///-------------------------------------------------------------------------------------------------
	/// <summary>Returns a position difference in world units at the last update.</summary>
	///
	/// <returns>The delta position.</returns>
	///-------------------------------------------------------------------------------------------------
	float GetDeltaPosition() const;

	///-------------------------------------------------------------------------------------------------
	/// <summary>Returns the speed.</summary>
	///
	/// <returns>The speed in world units per second.</returns>
	///-------------------------------------------------------------------------------------------------
	float GetSpeed() const;


	protected:


	///-------------------------------------------------------------------------------------------------
	/// <summary>The yaw.</summary>
	///-------------------------------------------------------------------------------------------------
	float yaw;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The pitch.</summary>
	///-------------------------------------------------------------------------------------------------
	float pitch;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The roll.</summary>
	///-------------------------------------------------------------------------------------------------
	float roll;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The position of the camera.</summary>
	///-------------------------------------------------------------------------------------------------
	glm::vec3 position;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The position delta to the last movement. Will be update when the camera is updated.</summary>
	///-------------------------------------------------------------------------------------------------
	glm::vec3 deltaPosition;

	///-------------------------------------------------------------------------------------------------
	/// <summary>The speed of the camera.
	/// 		 Defines how many units per second the camera can move in each single direction.
	/// 		 Two directions currently adds up. Thence, W+A ends up with the double speed.</summary>
	///-------------------------------------------------------------------------------------------------
	float speed;

};