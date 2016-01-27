#pragma once

///-------------------------------------------------------------------------------------------------
/// <summary>Used to index the bufferObject variable in the Mesh class.
/// 		 MAX_BUFFER will result to two, which defines the size of the
/// 		 bufferObject array in the Mesh class. The first two indices can be used 
/// 		 to access the specific data at the positions in the array.</summary>
///-------------------------------------------------------------------------------------------------
enum MeshBuffer {
	VERTEX_BUFFER,
	COLOUR_BUFFER,
	/*TEXTURE_BUFFER,
	INDEX_BUFFER,
	NORMAL_BUFFER,
	TANGENT_BUFFER,*/
	MAX_BUFFER
};