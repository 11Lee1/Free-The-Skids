#define	VERTEX_POSITION					0x0001
#define	VERTEX_NORMAL					0x0002
#define	VERTEX_COLOR					0x0004
#define	VERTEX_SPECULAR					0x0008

#define	VERTEX_TANGENT_S				0x0010
#define	VERTEX_TANGENT_T				0x0020
#define	VERTEX_TANGENT_SPACE			( VERTEX_TANGENT_S | VERTEX_TANGENT_T )

// Indicates we're using wrinkle
#define	VERTEX_WRINKLE					0x0040

// Indicates we're using bone indices
#define	VERTEX_BONE_INDEX				0x0080

// Indicates this is a vertex shader
#define	VERTEX_FORMAT_VERTEX_SHADER		0x0100

// Indicates this format shouldn't be bloated to cache align it
// (only used for VertexUsage)
#define	VERTEX_FORMAT_USE_EXACT_FORMAT	0x0200

// Indicates that compressed vertex elements are to be used (see also VertexCompressionType_t)
#define	VERTEX_FORMAT_COMPRESSED		0x400

// Update this if you add or remove bits...
#define	VERTEX_LAST_BIT					10

#define	VERTEX_BONE_WEIGHT_BIT			(VERTEX_LAST_BIT + 1)
#define	USER_DATA_SIZE_BIT				(VERTEX_LAST_BIT + 4)
#define	TEX_COORD_SIZE_BIT				(VERTEX_LAST_BIT + 7)

#define	VERTEX_BONE_WEIGHT_MASK			( 0x7 << VERTEX_BONE_WEIGHT_BIT )
#define	USER_DATA_SIZE_MASK				( 0x7 << USER_DATA_SIZE_BIT )

#define	VERTEX_FORMAT_FIELD_MASK		0x0FF

// If everything is off, it's an unknown vertex format
#define	VERTEX_FORMAT_UNKNOWN	0

class IMaterialProxyFactory;
class ITexture;
class IMaterialSystemHardwareConfig;
class CShadowMgr;
class IIndexBuffer;
class IVertexBuffer;
class ICallQueue;
class IMatRenderContext;
class IMaterial;
class IMesh;
class IVertexBuffer;
class IIndexBuffer;
struct MaterialSystem_Config_t;
class VMatrix;
struct matrix3x4_t;
struct MaterialSystemHardwareIdentifier_t;
class KeyValues;
class IShader;
class IVertexTexture;
class IMorph;
class IMatRenderContext;
class ICallQueue;
struct MorphWeight_t;
class IFileList;
struct MorphWeight_t;
struct DeformationBase_t;
typedef UINT64 VertexFormat_t;
typedef unsigned int MorphFormat_t;
typedef unsigned int ColorCorrectionHandle_t;
typedef unsigned int OcclusionQueryObjectHandle_t;
typedef int VertexBufferHandle_t;
typedef unsigned short MaterialHandle_t;
typedef void(*MaterialBufferReleaseFunc_t)();
typedef void(*MaterialBufferRestoreFunc_t)(int nChangeFlags);	// see RestoreChangeFlags_t
typedef void(*ModeChangeCallbackFunc_t)(void);
DECLARE_POINTER_HANDLE(MaterialLock_t);
class BaseEntity;
class ITexture;
struct BrushVertex_t
{
	Vector		m_Pos;
	Vector		m_Normal;
	Vector		m_TangentS;
	Vector		m_TangentT;
	Vector2D	m_TexCoord;
	Vector2D	m_LightmapCoord;

private:
	BrushVertex_t(const BrushVertex_t& src);
};
typedef unsigned short LeafIndex_t;
typedef short LeafFogVolume_t;
enum
{
	INVALID_LEAF_INDEX = (LeafIndex_t)~0
};
struct WorldListInfo_t
{
	int		m_ViewFogVolume;
	int		m_LeafCount;
	LeafIndex_t*		m_pLeafList;
	LeafFogVolume_t*	m_pLeafFogVolume;
};
class IWorldRenderList
{
};
struct VisibleFogVolumeInfo_t
{
	int		m_nVisibleFogVolume;
	int		m_nVisibleFogVolumeLeaf;
	bool	m_bEyeInFogVolume;
	float	m_flDistanceToWater;
	float	m_flWaterHeight;
	IMaterial *m_pFogVolumeMaterial;
};
struct VisOverrideData_t
{
	Vector		m_vecVisOrigin;					// The point to to use as the viewpoint for area portal backface cull checks.
	float		m_fDistToAreaPortalTolerance;	// The distance from an area portal before using the full screen as the viewable portion.
};
class IBrushSurface
{
public:
	// Computes texture coordinates + lightmap coordinates given a world position
	virtual void ComputeTextureCoordinate(Vector const& worldPos, Vector2D& texCoord) = 0;
	virtual void ComputeLightmapCoordinate(Vector const& worldPos, Vector2D& lightmapCoord) = 0;

	// Gets the vertex data for this surface
	virtual int  GetVertexCount() const = 0;
	virtual void GetVertexData(BrushVertex_t* pVerts) = 0;

	// Gets at the material properties for this surface
	virtual IMaterial* GetMaterial() = 0;
};
class IBrushRenderer
{
public:
	// Draws the surface; returns true if decals should be rendered on this surface
	virtual bool RenderBrushModelSurface(BaseEntity* pBaseEntity, IBrushSurface* pBrushSurface) = 0;
};
enum ERenderDepthMode
{
	DEPTH_MODE_NORMAL = 0,
	DEPTH_MODE_SHADOW = 1,
	DEPTH_MODE_SSA0 = 2,
	DEPTH_MODE_OVERRIDE = 3,

	DEPTH_MODE_MAX
};
enum DrawBrushModelMode_t
{
	DBM_DRAW_ALL = 0,
	DBM_DRAW_OPAQUE_ONLY,
	DBM_DRAW_TRANSLUCENT_ONLY,
};

typedef VPlane Frustum[FRUSTUM_NUMPLANES];
enum MaterialThreadMode_t
{
	MATERIAL_SINGLE_THREADED,
	MATERIAL_QUEUED_SINGLE_THREADED,
	MATERIAL_QUEUED_THREADED
};
enum
{
	MATERIAL_ADAPTER_NAME_LENGTH = 512
};
struct MaterialAdapterInfo_t
{
	char m_pDriverName[MATERIAL_ADAPTER_NAME_LENGTH];
	unsigned int m_VendorID;
	unsigned int m_DeviceID;
	unsigned int m_SubSysID;
	unsigned int m_Revision;
	int m_nDXSupportLevel;			// This is the *preferred* dx support level
	int m_nMaxDXSupportLevel;
	unsigned int m_nDriverVersionHigh;
	unsigned int m_nDriverVersionLow;
};
enum MaterialRenderTargetDepth_t
{
	MATERIAL_RT_DEPTH_SHARED = 0x0,
	MATERIAL_RT_DEPTH_SEPARATE = 0x1,
	MATERIAL_RT_DEPTH_NONE = 0x2,
	MATERIAL_RT_DEPTH_ONLY = 0x3,
};
enum RenderTargetSizeMode_t
{
	RT_SIZE_NO_CHANGE = 0,			// Only allowed for render targets that don't want a depth buffer
	// (because if they have a depth buffer, the render target must be less than or equal to the size of the framebuffer).
	RT_SIZE_DEFAULT = 1,				// Don't play with the specified width and height other than making sure it fits in the framebuffer.
	RT_SIZE_PICMIP = 2,				// Apply picmip to the render target's width and height.
	RT_SIZE_HDR = 3,					// frame_buffer_width / 4
	RT_SIZE_FULL_FRAME_BUFFER = 4,	// Same size as frame buffer, or next lower power of 2 if we can't do that.
	RT_SIZE_OFFSCREEN = 5,			// Target of specified size, don't mess with dimensions
	RT_SIZE_FULL_FRAME_BUFFER_ROUNDED_UP = 6, // Same size as the frame buffer, rounded up if necessary for systems that can't do non-power of two textures.
	RT_SIZE_REPLAY_SCREENSHOT = 7,	// Rounded down to power of 2, essentially...
	RT_SIZE_LITERAL = 8				// Use the size passed in. Don't clamp it to the frame buffer size. Really.
};
struct MaterialSystem_SortInfo_t
{
	IMaterial	*material;
	int			lightmapPageID;
};
enum MaterialContextType_t
{
	MATERIAL_HARDWARE_CONTEXT,
	MATERIAL_QUEUED_CONTEXT,
	MATERIAL_NULL_CONTEXT
};
enum RenderViewInfo_t
{
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
};
enum ImageFormat
{
	IMAGE_FORMAT_UNKNOWN = -1,
	IMAGE_FORMAT_RGBA8888 = 0,
	IMAGE_FORMAT_ABGR8888,
	IMAGE_FORMAT_RGB888,
	IMAGE_FORMAT_BGR888,
	IMAGE_FORMAT_RGB565,
	IMAGE_FORMAT_I8,
	IMAGE_FORMAT_IA88,
	IMAGE_FORMAT_P8,
	IMAGE_FORMAT_A8,
	IMAGE_FORMAT_RGB888_BLUESCREEN,
	IMAGE_FORMAT_BGR888_BLUESCREEN,
	IMAGE_FORMAT_ARGB8888,
	IMAGE_FORMAT_BGRA8888,
	IMAGE_FORMAT_DXT1,
	IMAGE_FORMAT_DXT3,
	IMAGE_FORMAT_DXT5,
	IMAGE_FORMAT_BGRX8888,
	IMAGE_FORMAT_BGR565,
	IMAGE_FORMAT_BGRX5551,
	IMAGE_FORMAT_BGRA4444,
	IMAGE_FORMAT_DXT1_ONEBITALPHA,
	IMAGE_FORMAT_BGRA5551,
	IMAGE_FORMAT_UV88,
	IMAGE_FORMAT_UVWQ8888,
	IMAGE_FORMAT_RGBA16161616F,
	IMAGE_FORMAT_RGBA16161616,
	IMAGE_FORMAT_UVLX8888,
	IMAGE_FORMAT_R32F,			// Single-channel 32-bit floating point
	IMAGE_FORMAT_RGB323232F,
	IMAGE_FORMAT_RGBA32323232F,

	// Depth-stencil texture formats for shadow depth mapping
	IMAGE_FORMAT_NV_DST16,		// 
	IMAGE_FORMAT_NV_DST24,		//
	IMAGE_FORMAT_NV_INTZ,		// Vendor-specific depth-stencil texture
	IMAGE_FORMAT_NV_RAWZ,		// formats for shadow depth mapping 
	IMAGE_FORMAT_ATI_DST16,		// 
	IMAGE_FORMAT_ATI_DST24,		//
	IMAGE_FORMAT_NV_NULL,		// Dummy format which takes no video memory

	// Compressed normal map formats
	IMAGE_FORMAT_ATI2N,			// One-surface ATI2N / DXN format
	IMAGE_FORMAT_ATI1N,			// Two-surface ATI1N format

	NUM_IMAGE_FORMATS
};
enum MaterialNonInteractiveMode_t
{
	MATERIAL_NON_INTERACTIVE_MODE_NONE = -1,
	MATERIAL_NON_INTERACTIVE_MODE_STARTUP = 0,
	MATERIAL_NON_INTERACTIVE_MODE_LEVEL_LOAD,

	MATERIAL_NON_INTERACTIVE_MODE_COUNT,
};
enum MaterialPrimitiveType_t
{
	MATERIAL_POINTS = 0x0,
	MATERIAL_LINES,
	MATERIAL_TRIANGLES,
	MATERIAL_TRIANGLE_STRIP,
	MATERIAL_LINE_STRIP,
	MATERIAL_LINE_LOOP,	// a single line loop
	MATERIAL_POLYGON,	// this is a *single* polygon
	MATERIAL_QUADS,
	MATERIAL_INSTANCED_QUADS, // (X360) like MATERIAL_QUADS, but uses vertex instancing

	// This is used for static meshes that contain multiple types of
	// primitive types.	When calling draw, you'll need to specify
	// a primitive type.
	MATERIAL_HETEROGENOUS
};
enum StencilOperation_t
{
	STENCILOPERATION_KEEP = 1,
	STENCILOPERATION_ZERO = 2,
	STENCILOPERATION_REPLACE = 3,
	STENCILOPERATION_INCRSAT = 4,
	STENCILOPERATION_DECRSAT = 5,
	STENCILOPERATION_INVERT = 6,
	STENCILOPERATION_INCR = 7,
	STENCILOPERATION_DECR = 8,
	STENCILOPERATION_FORCE_DWORD = 0x7fffffff
};
enum StencilComparisonFunction_t
{
	STENCILCOMPARISONFUNCTION_NEVER = 1,
	STENCILCOMPARISONFUNCTION_LESS = 2,
	STENCILCOMPARISONFUNCTION_EQUAL = 3,
	STENCILCOMPARISONFUNCTION_LESSEQUAL = 4,
	STENCILCOMPARISONFUNCTION_GREATER = 5,
	STENCILCOMPARISONFUNCTION_NOTEQUAL = 6,
	STENCILCOMPARISONFUNCTION_GREATEREQUAL = 7,
	STENCILCOMPARISONFUNCTION_ALWAYS = 8,
	STENCILCOMPARISONFUNCTION_FORCE_DWORD = 0x7fffffff
};
struct FlashlightState_t
{
	FlashlightState_t()
	{
		m_bEnableShadows = false;						// Provide reasonable defaults for shadow depth mapping parameters
		m_bDrawShadowFrustum = false;
		m_flShadowMapResolution = 1024.0f;
		m_flShadowFilterSize = 3.0f;
		m_flShadowSlopeScaleDepthBias = 16.0f;
		m_flShadowDepthBias = 0.0005f;
		m_flShadowJitterSeed = 0.0f;
		m_flShadowAtten = 0.0f;
		m_bScissor = false;
		m_nLeft = -1;
		m_nTop = -1;
		m_nRight = -1;
		m_nBottom = -1;
		m_nShadowQuality = 0;
	}

	Vector m_vecLightOrigin;
	Quaternion m_quatOrientation;
	float m_NearZ;
	float m_FarZ;
	float m_fHorizontalFOVDegrees;
	float m_fVerticalFOVDegrees;
	float m_fQuadraticAtten;
	float m_fLinearAtten;
	float m_fConstantAtten;
	float m_Color[4];
	ITexture *m_pSpotlightTexture;
	int m_nSpotlightTextureFrame;

	// Shadow depth mapping parameters
	bool  m_bEnableShadows;
	bool  m_bDrawShadowFrustum;
	float m_flShadowMapResolution;
	float m_flShadowFilterSize;
	float m_flShadowSlopeScaleDepthBias;
	float m_flShadowDepthBias;
	float m_flShadowJitterSeed;
	float m_flShadowAtten;
	int   m_nShadowQuality;

	// Getters for scissor members
	bool DoScissor() { return m_bScissor; }
	int GetLeft() { return m_nLeft; }
	int GetTop() { return m_nTop; }
	int GetRight() { return m_nRight; }
	int GetBottom() { return m_nBottom; }
private:

	friend class CShadowMgr;

	bool m_bScissor;
	int m_nLeft;
	int m_nTop;
	int m_nRight;
	int m_nBottom;
};
enum MaterialFogMode_t
{
	MATERIAL_FOG_NONE,
	MATERIAL_FOG_LINEAR,
	MATERIAL_FOG_LINEAR_BELOW_FOG_Z,
};
enum MaterialIndexFormat_t
{
	MATERIAL_INDEX_FORMAT_UNKNOWN = -1,
	MATERIAL_INDEX_FORMAT_16BIT = 0,
	MATERIAL_INDEX_FORMAT_32BIT,
};
enum MaterialCullMode_t
{
	MATERIAL_CULLMODE_CCW,	// this culls polygons with counterclockwise winding
	MATERIAL_CULLMODE_CW	// this culls polygons with clockwise winding
};
enum MaterialHeightClipMode_t
{
	MATERIAL_HEIGHTCLIPMODE_DISABLE,
	MATERIAL_HEIGHTCLIPMODE_RENDER_ABOVE_HEIGHT,
	MATERIAL_HEIGHTCLIPMODE_RENDER_BELOW_HEIGHT
};
enum LightType_t
{
	MATERIAL_LIGHT_DISABLE = 0,
	MATERIAL_LIGHT_POINT,
	MATERIAL_LIGHT_DIRECTIONAL,
	MATERIAL_LIGHT_SPOT,
};
enum MaterialMatrixMode_t
{
	MATERIAL_VIEW = 0,
	MATERIAL_PROJECTION,

	// Texture matrices
	MATERIAL_TEXTURE0,
	MATERIAL_TEXTURE1,
	MATERIAL_TEXTURE2,
	MATERIAL_TEXTURE3,
	MATERIAL_TEXTURE4,
	MATERIAL_TEXTURE5,
	MATERIAL_TEXTURE6,
	MATERIAL_TEXTURE7,

	MATERIAL_MODEL,

	// Total number of matrices
	NUM_MATRIX_MODES = MATERIAL_MODEL + 1,

	// Number of texture transforms
	NUM_TEXTURE_TRANSFORMS = MATERIAL_TEXTURE7 - MATERIAL_TEXTURE0 + 1
};
struct LightDesc_t
{
	LightType_t		m_Type;
	Vector			m_Color;
	Vector	m_Position;
	Vector  m_Direction;
	float   m_Range;
	float   m_Falloff;
	float   m_Attenuation0;
	float   m_Attenuation1;
	float   m_Attenuation2;
	float   m_Theta;
	float   m_Phi;
	// These aren't used by DX8. . used for software lighting.
	float	m_ThetaDot;
	float	m_PhiDot;
	unsigned int	m_Flags;


	LightDesc_t() {}

private:
	// No copy constructors allowed
	LightDesc_t(const LightDesc_t& vOther);
};
class IMaterialVar;
enum MaterialPropertyTypes_t
{
	MATERIAL_PROPERTY_NEEDS_LIGHTMAP = 0,					// bool
	MATERIAL_PROPERTY_OPACITY,								// int (enum MaterialPropertyOpacityTypes_t)
	MATERIAL_PROPERTY_REFLECTIVITY,							// vec3_t
	MATERIAL_PROPERTY_NEEDS_BUMPED_LIGHTMAPS				// bool
};
enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),

	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
	MATERIAL_VAR_IGNORE_ALPHA_MODULATION = (1 << 30),

	// NOTE: Only add flags here that either should be read from
	// .vmts or can be set directly from client code. Other, internal
	// flags should to into the flag enum in imaterialinternal.h
};
enum PreviewImageRetVal_t
{
	MATERIAL_PREVIEW_IMAGE_BAD = 0,
	MATERIAL_PREVIEW_IMAGE_OK,
	MATERIAL_NO_PREVIEW_IMAGE,
};
enum VertexElement_t
{
	VERTEX_ELEMENT_NONE = -1,

	// Deliberately explicitly numbered so it's a pain in the ass to change, so you read this:
	// #!#!#NOTE#!#!# update GetVertexElementSize, VertexElementToDeclType and
	//                CVBAllocTracker (elementTable) when you update this!
	VERTEX_ELEMENT_POSITION = 0,
	VERTEX_ELEMENT_NORMAL = 1,
	VERTEX_ELEMENT_COLOR = 2,
	VERTEX_ELEMENT_SPECULAR = 3,
	VERTEX_ELEMENT_TANGENT_S = 4,
	VERTEX_ELEMENT_TANGENT_T = 5,
	VERTEX_ELEMENT_WRINKLE = 6,
	VERTEX_ELEMENT_BONEINDEX = 7,
	VERTEX_ELEMENT_BONEWEIGHTS1 = 8,
	VERTEX_ELEMENT_BONEWEIGHTS2 = 9,
	VERTEX_ELEMENT_BONEWEIGHTS3 = 10,
	VERTEX_ELEMENT_BONEWEIGHTS4 = 11,
	VERTEX_ELEMENT_USERDATA1 = 12,
	VERTEX_ELEMENT_USERDATA2 = 13,
	VERTEX_ELEMENT_USERDATA3 = 14,
	VERTEX_ELEMENT_USERDATA4 = 15,
	VERTEX_ELEMENT_TEXCOORD1D_0 = 16,
	VERTEX_ELEMENT_TEXCOORD1D_1 = 17,
	VERTEX_ELEMENT_TEXCOORD1D_2 = 18,
	VERTEX_ELEMENT_TEXCOORD1D_3 = 19,
	VERTEX_ELEMENT_TEXCOORD1D_4 = 20,
	VERTEX_ELEMENT_TEXCOORD1D_5 = 21,
	VERTEX_ELEMENT_TEXCOORD1D_6 = 22,
	VERTEX_ELEMENT_TEXCOORD1D_7 = 23,
	VERTEX_ELEMENT_TEXCOORD2D_0 = 24,
	VERTEX_ELEMENT_TEXCOORD2D_1 = 25,
	VERTEX_ELEMENT_TEXCOORD2D_2 = 26,
	VERTEX_ELEMENT_TEXCOORD2D_3 = 27,
	VERTEX_ELEMENT_TEXCOORD2D_4 = 28,
	VERTEX_ELEMENT_TEXCOORD2D_5 = 29,
	VERTEX_ELEMENT_TEXCOORD2D_6 = 30,
	VERTEX_ELEMENT_TEXCOORD2D_7 = 31,
	VERTEX_ELEMENT_TEXCOORD3D_0 = 32,
	VERTEX_ELEMENT_TEXCOORD3D_1 = 33,
	VERTEX_ELEMENT_TEXCOORD3D_2 = 34,
	VERTEX_ELEMENT_TEXCOORD3D_3 = 35,
	VERTEX_ELEMENT_TEXCOORD3D_4 = 36,
	VERTEX_ELEMENT_TEXCOORD3D_5 = 37,
	VERTEX_ELEMENT_TEXCOORD3D_6 = 38,
	VERTEX_ELEMENT_TEXCOORD3D_7 = 39,
	VERTEX_ELEMENT_TEXCOORD4D_0 = 40,
	VERTEX_ELEMENT_TEXCOORD4D_1 = 41,
	VERTEX_ELEMENT_TEXCOORD4D_2 = 42,
	VERTEX_ELEMENT_TEXCOORD4D_3 = 43,
	VERTEX_ELEMENT_TEXCOORD4D_4 = 44,
	VERTEX_ELEMENT_TEXCOORD4D_5 = 45,
	VERTEX_ELEMENT_TEXCOORD4D_6 = 46,
	VERTEX_ELEMENT_TEXCOORD4D_7 = 47,

	VERTEX_ELEMENT_NUMELEMENTS = 48
};
struct MaterialVideoMode_t
{
	int m_Width;			// if width and height are 0 and you select 
	int m_Height;			// windowed mode, it'll use the window size
	ImageFormat m_Format;	// use ImageFormats (ignored for windowed mode)
	int m_RefreshRate;		// 0 == default (ignored for windowed mode)
};