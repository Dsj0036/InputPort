#pragma once
#ifndef MCGL
#define MCGL
#include "System.h"

#define MC_GL_ZERO                  0
#define MC_GL_ONE                   1
#define MC_GL_SRC_ALPHA             4
#define MC_GL_ONE_MINUS_SRC_ALPHA   5

#define MC_GL_TRIANGLES             0
#define MC_GL_TRIANGLE_FAN          1
#define MC_GL_QUADS                 2
#define MC_GL_QUADS_STRIP           3
#define MC_GL_LINES                 4
#define MC_GL_LINES_STRIP           5
#define MC_GL_RGB			3
#define MC_GL_RGBA					4
#define MC_GL_MODELVIEW             0
#define MC_GL_PROJECTION            1
#define MC_GL_TEXTURE               2
#define MC_GL_UNSIGNED_BYTE			5121
#define WIDTH 1280
#define HEIGHT 720

namespace GLStateManager
{

	// Matrix Operations
	// Translates the current matrix by (x, y, z)
	void translatef(float x, float y, float z);

	// Scales the current matrix by the factors (s1, s2, s3) along x, y, and z axes
	void scalef(float s1, float s2, float s3);

	// Rotates the current matrix by w degrees around the axis (x, y, z)
	void rotatef(float x, float y, float z, float w);

	// Rotates the current matrix by the specified amount 'rot' (typically around the z-axis)
	void rotate(float rot);

	// Pops the top matrix off the stack, restoring the previous matrix
	void popMatrix();

	// Pushes the current matrix onto the matrix stack
	void pushMatrix();

	// Blending Operations
	// Enables blending, allowing for transparency and other effects
	void EnableBlend();

	// Disables blending, turning off transparency
	void DisableBlend();

	// Enables alpha testing, which discards pixels based on their alpha value
	void EnableAlpha();

	// Disables alpha testing
	void DisableAlpha();

	// Sets the alpha test function and reference value for pixel transparency
	void AlphaFunc(int func, float ref);

	// Disables color material mode
	void DisableColorMaterial();

	// Lighting Operations
	// Enables lighting calculations
	void EnableLighting();

	// Disables lighting calculations
	void DisableLighting();

	// Enables a specific light source
	void EnableLight(int light);

	// Disables a specific light source
	void DisableLight(int light);

	// Specifies how material colors are assigned in lighting calculations
	void ColorMaterial(uint32_t face, int mode);

	// Depth Operations
	// Enables depth testing, which ensures that objects are rendered in the correct order
	void EnableDepth();

	// Disables depth testing
	void DisableDepth();

	// Sets the function used to compare depth values
	void DepthFunc(int depthFunc);

	// Enables or disables writing to the depth buffer
	void DepthMask(int flagIn);

	// Sets the blending factors for the source and destination colors
	void BlendFunc(int srcFactor, int dstFactor);

	// Fog Operations
	// Enables fog calculations
	void EnableFog();

	// Disables fog calculations
	void DisableFog();

	// Sets fog parameters (e.g., mode or color)
	void setFog(int param);

	// Sets the fog density (used for exponential fog)
	void SetFogDensity(double param);

	// Sets the start distance for linear fog
	void SetFogStart(double param);

	// Sets the end distance for linear fog
	void SetFogEnd(double param);

	// Sets fog parameters (alternative form)
	void GlFog();

	// Sets integer fog parameters
	void GlFogI();

	// Culling Operations
	// Enables face culling, where certain faces of polygons are not drawn
	void EnableCull();

	// Disables face culling
	void DisableCull();

	// Specifies which faces (front or back) are culled
	void CullFace(int mode);

	// Polygon Offset Operations
	// Enables polygon offset, which shifts depth values to prevent z-fighting
	void EnablePolygonOffset();

	// Disables polygon offset
	void DisablePolygonOffset();

	// Specifies the scale factor and units for polygon offset
	void doPolygonOffset(double factor, double units);

	// Color Logic Operations
	// Enables color logic operations
	void EnableColorLogic();

	// Disables color logic operations
	void DisableColorLogic();

	// Sets the logic operation for pixel blending
	void ColorLogic(int texGen);

	// Texture Generation and Management
	// Enables texture coordinate generation for a specific texture generation mode
	void EnableTexGenCoord(int texGen);

	// Disables texture coordinate generation
	void DisableTexGenCoord(int texGen);

	// Specifies the texture coordinate generation parameters
	void TexGen(int texGen, int param);

	// Specifies which texture unit is active
	void SetActiveTexture(int texture);

	// Enables 2D texturing
	void EnableTexture2D();

	// Disables 2D texturing
	void DisableTexture2D();

	// Generates a texture object and returns its identifier
	int GenerateTexture();

	// Deletes a texture object
	void DeleteTexture(int texture);

	// Binds a texture to the current context
	void BendTexture(int texture);

	// Specifies a 2D texture image
	void GlTexImage2D(uint32_t target, uint32_t level, uint32_t internalFormat, uint32_t width, int height, int border, int type, int r8, int r9, int r10);

	// Normalization and Rescaling
	// Enables normalization of normals (used in lighting)
	void EnableNormalize();

	// Disables normalization of normals
	void DisableNormalize();

	// Sets the shading model (e.g., flat or smooth shading)
	void ShadeModel(int mode);

	// Enables rescaling of normals, which adjusts for scaling transformations
	void EnableRescaleNormal();

	// Disables rescaling of normals
	void DisableRescaleNormal();

	// Color and Depth Buffer Operations
	// Sets the mask to control whether each color component (red, green, blue, alpha) is written to the frame buffer
	void ColorMask(char red, char green, char blue, char alpha);

	// Clears the depth buffer to the specified depth value
	void ClearDepth(double depth);

	// Clears the color buffer to the specified color
	void ClearColor(double red, double green, double blue, double alpha);

	// Retrieves a floating-point value from OpenGL
	void GetFloat(int32_t pname, int32_t param);

	// Color Operations
	// Sets the current color with red, green, blue, and alpha components
	void Color1(float colorRed, float colorGreen, float colorBlue, float colorAlpha);

	// Sets the current color with red, green, and blue components (no alpha)
	void Color2(float colorRed, float colorGreen, float ColorBlue);

	// Matrix Mode Operations
	// Specifies which matrix stack is the target for subsequent matrix operations
	void matrixMode(int32_t m);

	// Projection Operations
	// Sets an orthographic projection matrix
	void ortho(double arg1, double arg2, double arg3, double arg4, double arg5, double arg6);


}
namespace GLES = GLStateManager;
namespace gl = GLStateManager;
#endif