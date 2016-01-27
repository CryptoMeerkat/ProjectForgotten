//#pragma once
//
//#include "Mesh.h"
//#include <vector>
//#include <string>
//#include <glm.hpp>
//
/////-------------------------------------------------------------------------------------------------
///// <summary>A SceneNode comprises a single logical object.
///// 		 A logical object is assessed to have a Mesh, Shaders, Transformation and further information
///// 		 attached. A logical object can contain other SceneNodes which will end in a Scene
///// 		 Graph.</summary>
/////-------------------------------------------------------------------------------------------------
//class SceneNode {
//
//	public:
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Constructor for a SceneNode.</summary>
//	///
//	/// <param name="m">	 [in,out] (Optional) If non-null, the Mesh* to process.</param>
//	/// <param name="colour">(Optional) The colour. Defaults to white.</param>
//	///-------------------------------------------------------------------------------------------------
//	SceneNode(Mesh* m = NULL, glm::vec4 colour = glm::vec4(1, 1, 1, 1));
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Constructor for a SceneNode.</summary>
//	///
//	/// <param name="name">  The name of the SceneNode.</param>
//	/// <param name="m">	 [in,out] (Optional) If non-null, the Mesh* to process.</param>
//	/// <param name="colour">(Optional) The colour. Defaults to white.</param>
//	///-------------------------------------------------------------------------------------------------
//	SceneNode(std::string name, Mesh* m = NULL, glm::vec4 colour = glm::vec4(1, 1, 1, 1));
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Destructor.</summary>
//	///-------------------------------------------------------------------------------------------------
//	virtual ~SceneNode();
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Adds a child to the list of children.</summary>
//	///
//	/// <param name="s">[in,out] If non-null, the SceneNode* to add as a child.</param>
//	///-------------------------------------------------------------------------------------------------
//	void AddChild(SceneNode* s);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Updates the attributes of this SceneNode.</summary>
//	///
//	/// <param name="msec">The msec since the last update to be frame independent..</param>
//	///-------------------------------------------------------------------------------------------------
//	virtual void Update(float msec);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Draws this SceneNode.</summary>
//	///
//	/// <param name="r">		   [in,out] The OGLRenderer to process.</param>
//	/// <param name="useGlobalShader">True, if no custom shader is loaded but a global shader used.</param>
//	///-------------------------------------------------------------------------------------------------
//	virtual void Draw(OGLRenderer &r, bool useGlobalShader = false);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Removes the child pointed by s.
//	/// 		 This is single level deletion. This function is not called recursively to 
//	/// 		 delete probably every reference of s in the scene tree.</summary>
//	///
//	/// <param name="s">[in,out] The SceneNode* to process.</param>
//	///
//	/// <returns>true if it succeeds, false if the child is not found.</returns>
//	///-------------------------------------------------------------------------------------------------
//	bool RemoveChild(SceneNode* s);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets the transform matrix.</summary>
//	///
//	/// <param name="matrix">The new transform matrix.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetTransform(const Matrix4 &matrix);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets the transform matrix.</summary>
//	///
//	/// <returns>The transform matrix.</returns>
//	///-------------------------------------------------------------------------------------------------
//	const Matrix4& GetTransform() const;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets the shader program.</summary>
//	///
//	/// <param name="s">[in,out] If non-null, the Shader* to process.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetShader(Shader* s);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets the world transformation.</summary>
//	///
//	/// <returns>The world transformation.</returns>
//	///-------------------------------------------------------------------------------------------------
//	Matrix4 GetWorldTransform() const;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets the colour of the node.
//	/// 		 This is NOT retrieving a color of a single vertex.</summary>
//	///
//	/// <returns>The colour.</returns>
//	///-------------------------------------------------------------------------------------------------
//	Vector4 GetColour() const;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets the colour for the node.
//	/// 		 Does NOT overwrite the colour a single vertex.</summary>
//	///
//	/// <param name="c">The new node color.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetColour(Vector4 c);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets the model scale.</summary>
//	///
//	/// <returns>The model scale.</returns>
//	///-------------------------------------------------------------------------------------------------
//	Vector3 GetModelScale() const;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets the model scale.</summary>
//	///
//	/// <param name="s">The Vector3 to process.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetModelScale(Vector3 s);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets the mesh.</summary>
//	///
//	/// <returns>null if it fails, else the mesh.</returns>
//	///-------------------------------------------------------------------------------------------------
//	Mesh* GetMesh() const;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets a mesh.</summary>
//	///
//	/// <param name="m">[in,out] If non-null, the Mesh* to process.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetMesh(Mesh* m);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets the name.</summary>
//	///
//	/// <returns>The name.</returns>
//	///-------------------------------------------------------------------------------------------------
//	std::string GetName() const;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets a name.</summary>
//	///
//	/// <param name="s">The new name.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetName(std::string s);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets the bounding volume.</summary>
//	///
//	/// <returns>Will be a specific type of
//	/// 		 bounding volumes.</returns>
//	///-------------------------------------------------------------------------------------------------
//	BoundingVolume* GetBoundingVolume() const;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets the bounding volume to be the given sphere.</summary>
//	///
//	/// <param name="sphere">The sphere to be the bounding volume.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetBoundingVolume(const BoundingSphere& sphere);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets the bounding volume to be the given box.</summary>
//	///
//	/// <param name="box">The bounding box to be the bounding volume.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetBoundingVolume(const BoundingBox& box);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets camera distance.
//	/// 		 The camera distance will not be calculated on run time on behind. You need
//	/// 		 to set the camera distance for the SceneNode manually beforehand.</summary>
//	///
//	/// <returns>The distance to the camera.</returns>
//	///-------------------------------------------------------------------------------------------------
//	float GetCameraDistance() const;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets camera distance.
//	/// 		 The SceneNode has no information about the camera. Thence, the distance
//	/// 		 must be set manually.</summary>
//	///
//	/// <param name="f">The distance to the camera.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetCameraDistance(float f);
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets a child iterator start.</summary>
//	///
//	/// <returns>null if it fails, else the child iterator start.</returns>
//	///-------------------------------------------------------------------------------------------------
//	std::vector<SceneNode*>::const_iterator GetChildIteratorStart();
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Gets a child iterator end.</summary>
//	///
//	/// <returns>null if it fails, else the child iterator end.</returns>
//	///-------------------------------------------------------------------------------------------------
//	std::vector<SceneNode*>::const_iterator GetChildIteratorEnd();
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Query if this object has transperency.</summary>
//	///
//	/// <returns>true if transparence, false if not.</returns>
//	///-------------------------------------------------------------------------------------------------
//	bool IsTransparent();
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Calculates the memory size for this SceneNode and all its children.</summary>
//	///-------------------------------------------------------------------------------------------------
//	virtual void CalculateMemorySize();
//
//	/************************************************************************/
//	/* STATIC PUBLIC                                                        */
//	/************************************************************************/
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Comparison method to decide which SceneNode is closer to the camera distance.
//	/// 		 This method is handy when sorting SceneNodes corresponding to their distance
//	/// 		 to the camera.</summary>
//	///
//	/// <param name="a">[in,out] If non-null, the SceneNode* to compare.</param>
//	/// <param name="b">[in,out] If non-null, the SceneNode* to compare.</param>
//	///
//	/// <returns>True if the first SceneNode is closer, false otherwise.</returns>
//	///-------------------------------------------------------------------------------------------------
//	static bool CompareByCameraDistance(SceneNode* a, SceneNode* b) {
//		return (a->distanceFromCamera < b->distanceFromCamera) ? true : false;
//	}
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Query if this object is casting shadows.</summary>
//	///
//	/// <returns>true if casting shadows, false if not.</returns>
//	///-------------------------------------------------------------------------------------------------
//	bool IsCastingShadows() const {
//		return isCastingShadows;
//	}
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Sets casting shadows. The settings will be applied to all childs, too.</summary>
//	///
//	/// <param name="val">true to value.</param>
//	///-------------------------------------------------------------------------------------------------
//	void SetCastingShadows(bool val) {
//		isCastingShadows = val;
//
//		//populate to all children
//		for (auto it = children.begin(); it != children.end(); it++) {
//			(*it)->SetCastingShadows(val);
//		}
//	}
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>Query if this object is a particle node.</summary>
//	///
//	/// <returns>true if particle node, false if not.</returns>
//	///-------------------------------------------------------------------------------------------------
//	bool IsParticleNode() const {
//		return isParticle;
//	}
//
//
//	protected:
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The distance from the camera.</summary>
//	///-------------------------------------------------------------------------------------------------
//	float distanceFromCamera;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The bounding volume object.
//	/// 		 This can be a generic type of a BoundingVolume.</summary>
//	///-------------------------------------------------------------------------------------------------
//	BoundingVolume* boundingVolume;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The parent SceneNode.</summary>
//	///-------------------------------------------------------------------------------------------------
//	SceneNode* parent;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The mesh for this SceneNode.</summary>
//	///-------------------------------------------------------------------------------------------------
//	Mesh* mesh;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The world transform is required for the children to know.
//	/// 		 Otherwise they do not know their final transformation.</summary>
//	///-------------------------------------------------------------------------------------------------
//	Matrix4 worldTransform;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The transformation of this single SceneNode.
//	/// 		 If this SceneNode has no parent, then the transform will be
//	/// 		 equal to the worldTransform.</summary>
//	///-------------------------------------------------------------------------------------------------
//	Matrix4 transform;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The model scale of this SceneNode.</summary>
//	///-------------------------------------------------------------------------------------------------
//	Vector3 modelScale;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The colour of this SceneNode.
//	/// 		 A colour of a vertex has still priority!</summary>
//	///-------------------------------------------------------------------------------------------------
//	Vector4 colour;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The children of this SceneNode.</summary>
//	///-------------------------------------------------------------------------------------------------
//	std::vector<SceneNode*> children;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The name of this SceneNode. Makes it easy to recognize
//	/// 		 the SceneNode.</summary>
//	///-------------------------------------------------------------------------------------------------
//	std::string name;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>The shaders attached to this node.
//	/// 		 They will overwrite the general shaders.</summary>
//	///-------------------------------------------------------------------------------------------------
//	Shader* shader;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>true if this object is casting shadows.</summary>
//	///-------------------------------------------------------------------------------------------------
//	bool isCastingShadows;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>True if this object is partly transparent.</summary>
//	///-------------------------------------------------------------------------------------------------
//	bool isTransparent;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>True if this object is or has particles.</summary>
//	///-------------------------------------------------------------------------------------------------
//	bool isParticle;
//
//	///-------------------------------------------------------------------------------------------------
//	/// <summary>True if this object is scaled in a non-uniform way.</summary>
//	///-------------------------------------------------------------------------------------------------
//	bool isScaledNonUniform;
//};