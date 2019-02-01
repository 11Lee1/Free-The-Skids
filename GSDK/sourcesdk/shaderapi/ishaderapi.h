#define SHADER_VIEWPORT_VERSION 1
struct ShaderViewport_t
{
	int m_nVersion;
	int m_nTopLeftX;
	int m_nTopLeftY;
	int m_nWidth;
	int m_nHeight;
	float m_flMinZ;
	float m_flMaxZ;

	ShaderViewport_t() : m_nVersion(SHADER_VIEWPORT_VERSION) {}

	void Init()
	{
		memset(this, 0, sizeof(ShaderViewport_t));
		m_nVersion = SHADER_VIEWPORT_VERSION;
	}

	void Init(int x, int y, int nWidth, int nHeight, float flMinZ = 0.0f, float flMaxZ = 1.0f)
	{
		m_nVersion = SHADER_VIEWPORT_VERSION;
		m_nTopLeftX = x; m_nTopLeftY = y; m_nWidth = nWidth; m_nHeight = nHeight;
		m_flMinZ = flMinZ;
		m_flMaxZ = flMaxZ;
	}
};
enum ShaderFillMode_t
{
	SHADER_FILL_SOLID = 0,
	SHADER_FILL_WIREFRAME,
};
struct ShaderRasterState_t
{
	ShaderFillMode_t m_FillMode;
	MaterialCullMode_t m_CullMode;
	bool m_bCullEnable : 1;
	bool m_bDepthBias : 1;
	bool m_bScissorEnable : 1;
	bool m_bMultisampleEnable : 1;
};
#define SHADER_DISPLAY_MODE_VERSION 1

struct ShaderDisplayMode_t
{
	ShaderDisplayMode_t() { memset(this, 0, sizeof(ShaderDisplayMode_t)); m_nVersion = SHADER_DISPLAY_MODE_VERSION; }

	int m_nVersion;
	int m_nWidth;					// 0 when running windowed means use desktop resolution
	int m_nHeight;
	ImageFormat m_Format;			// use ImageFormats (ignored for windowed mode)
	int m_nRefreshRateNumerator;	// Refresh rate. Use 0 in numerator + denominator for a default setting.
	int m_nRefreshRateDenominator;	// Refresh rate = numerator / denominator.
};

#define SHADER_DEVICE_INFO_VERSION 1

struct ShaderDeviceInfo_t
{
	ShaderDeviceInfo_t() { memset(this, 0, sizeof(ShaderDeviceInfo_t)); m_nVersion = SHADER_DEVICE_INFO_VERSION; m_DisplayMode.m_nVersion = SHADER_DISPLAY_MODE_VERSION; }

	int m_nVersion;
	ShaderDisplayMode_t m_DisplayMode;
	int m_nBackBufferCount;				// valid values are 1 or 2 [2 results in triple buffering]
	int m_nAASamples;					// Number of AA samples to use
	int m_nAAQuality;					// AA quality level
	int m_nDXLevel;						// 0 means use recommended DX level for this adapter
	int m_nWindowedSizeLimitWidth;		// Used if m_bLimitWindowedSize is set, defines max bounds for the back buffer
	int m_nWindowedSizeLimitHeight;

	bool m_bWindowed : 1;
	bool m_bResizing : 1;				// Only is meaningful when using windowed mode; means the window can be resized.
	bool m_bUseStencil : 1;
	bool m_bLimitWindowedSize : 1;		// In windowed mode, should we prevent the back buffer from getting too large?
	bool m_bWaitForVSync : 1;			// Would we not present until vsync?
	bool m_bScaleToOutputResolution : 1;			// 360 ONLY: sets up hardware scaling
	bool m_bProgressive : 1;			// 360 ONLY: interlaced or progressive
	bool m_bUsingMultipleWindows : 1; 	// Forces D3DPresent to use _COPY instead
};
enum ShaderShadeMode_t
{
	SHADER_FLAT = 0,
	SHADER_SMOOTH
};
enum ShaderTexCoordComponent_t
{
	SHADER_TEXCOORD_S = 0,
	SHADER_TEXCOORD_T,
	SHADER_TEXCOORD_U
};
enum ShaderTexFilterMode_t
{
	SHADER_TEXFILTERMODE_NEAREST,
	SHADER_TEXFILTERMODE_LINEAR,
	SHADER_TEXFILTERMODE_NEAREST_MIPMAP_NEAREST,
	SHADER_TEXFILTERMODE_LINEAR_MIPMAP_NEAREST,
	SHADER_TEXFILTERMODE_NEAREST_MIPMAP_LINEAR,
	SHADER_TEXFILTERMODE_LINEAR_MIPMAP_LINEAR,
	SHADER_TEXFILTERMODE_ANISOTROPIC
};
enum ShaderTexWrapMode_t
{
	SHADER_TEXWRAPMODE_CLAMP,
	SHADER_TEXWRAPMODE_REPEAT,
	SHADER_TEXWRAPMODE_BORDER
	// MIRROR? - probably don't need it.
};
enum ShaderRenderTarget_t
{
	SHADER_RENDERTARGET_BACKBUFFER = -1,
	SHADER_RENDERTARGET_DEPTHBUFFER = -1,
	// GR - no RT, used to disable depth buffer
	SHADER_RENDERTARGET_NONE = -2,
};
enum Sampler_t;
enum VertexTextureSampler_t;
enum StandardTextureId_t;
typedef unsigned int VertexShaderHandle_t;
typedef unsigned int GeometryShaderHandle_t;
typedef unsigned int PixelShaderHandle_t;
typedef unsigned int ShaderAPIOcclusionQuery_t;
typedef short StateSnapshot_t;
typedef int ShaderAPITextureHandle_t;
class IShaderUtil;
class IFileSystem;
class CPixelWriter;
class CMeshBuilder;
class IMesh;
class IVertexBuffer;
class IIndexBuffer;
struct MeshDesc_t;
enum MaterialCullMode_t;
class IDataCache;
struct MorphWeight_t;
class IVTFTexture;

class IShaderAPI
{
public:
	virtual void SetViewports(int nCount, const ShaderViewport_t* pViewports) = 0;
	/*1*/	virtual int GetViewports(ShaderViewport_t* pViewports, int nMax) const = 0;
	/*2*/	virtual void ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil, int renderTargetWidth, int renderTargetHeight) = 0;
	/*3*/	virtual void ClearColor3ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	/*4*/	virtual void ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a) = 0;
	/*5*/	virtual void BindVertexShader(VertexShaderHandle_t hVertexShader) = 0;
	/*6*/	virtual void BindGeometryShader(GeometryShaderHandle_t hGeometryShader) = 0;
	/*7*/	virtual void BindPixelShader(PixelShaderHandle_t hPixelShader) = 0;
	/*8*/	virtual void SetRasterState(const ShaderRasterState_t& state) = 0;
	/*9*/	virtual bool SetMode(void* hwnd, int nAdapter, const ShaderDeviceInfo_t &info) = 0;
	/*10*/	virtual void ChangeVideoMode(const ShaderDeviceInfo_t &info) = 0;
	/*11*/	virtual StateSnapshot_t	 TakeSnapshot() = 0;
	/*12*/	virtual void TexMinFilter(ShaderTexFilterMode_t texFilterMode) = 0;
	/*13*/	virtual void TexMagFilter(ShaderTexFilterMode_t texFilterMode) = 0;
	/*14*/	virtual void TexWrap(ShaderTexCoordComponent_t coord, ShaderTexWrapMode_t wrapMode) = 0;
	/*15*/	virtual void CopyRenderTargetToTexture(ShaderAPITextureHandle_t textureHandle) = 0;
	/*16*/	virtual void Bind(IMaterial* pMaterial) = 0;
	/*17*/	virtual void FlushBufferedPrimitives() = 0;
	/*18*/	virtual IMesh* GetDynamicMesh(IMaterial* pMaterial, int nHWSkinBoneCount, bool bBuffered = true, IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0) = 0;
	/*19*/	virtual IMesh* GetDynamicMeshEx(IMaterial* pMaterial, VertexFormat_t vertexFormat, int nHWSkinBoneCount, bool bBuffered = true, IMesh* pVertexOverride = 0, IMesh* pIndexOverride = 0) = 0;
	/*20*/	virtual bool IsTranslucent(StateSnapshot_t id) const = 0;
	/*21*/	virtual bool IsAlphaTested(StateSnapshot_t id) const = 0;
	/*22*/	virtual bool UsesVertexAndPixelShaders(StateSnapshot_t id) const = 0;
	/*23*/	virtual bool IsDepthWriteEnabled(StateSnapshot_t id) const = 0;
	/*24*/	virtual VertexFormat_t ComputeVertexFormat(int numSnapshots, StateSnapshot_t* pIds) const = 0;
	/*25*/	virtual VertexFormat_t ComputeVertexUsage(int numSnapshots, StateSnapshot_t* pIds) const = 0;
	/*26*/	virtual void BeginPass(StateSnapshot_t snapshot) = 0;
	/*27*/	virtual void RenderPass(int nPass, int nPassCount) = 0;
	/*28*/	virtual void SetNumBoneWeights(int numBones) = 0;
	/*29*/	virtual void SetLight(int lightNum, const LightDesc_t& desc) = 0;
	/*30*/	virtual void SetLightingOrigin(Vector vLightingOrigin) = 0;
	/*31*/	virtual void SetAmbientLight(float r, float g, float b) = 0;
	/*32*/	virtual void SetAmbientLightCube(Vector4D cube[6]) = 0;
	/*33*/	virtual void ShadeMode(ShaderShadeMode_t mode) = 0;
	/*34*/	virtual void CullMode(MaterialCullMode_t cullMode) = 0;
	/*35*/	virtual void ForceDepthFuncEquals(bool bEnable) = 0;
	/*36*/	virtual void OverrideDepthEnable(bool bEnable, bool bDepthEnable) = 0;
	/*37*/	virtual void SetHeightClipZ(float z) = 0;
	/*38*/	virtual void SetHeightClipMode(enum MaterialHeightClipMode_t heightClipMode) = 0;
	/*39*/	virtual void SetClipPlane(int index, const float *pPlane) = 0;
	/*40*/	virtual void EnableClipPlane(int index, bool bEnable) = 0;
	/*41*/	virtual void SetSkinningMatrices() = 0;
	/*42*/	virtual ImageFormat GetNearestSupportedFormat(ImageFormat fmt, bool bFilteringRequired = true) const = 0;
	/*43*/	virtual ImageFormat GetNearestRenderTargetFormat(ImageFormat fmt) const = 0;
	/*44*/	virtual bool DoRenderTargetsNeedSeparateDepthBuffer() const = 0;
	/*45*/	virtual ShaderAPITextureHandle_t CreateTexture(int width, int height, int depth, ImageFormat dstImageFormat, int numMipLevels, int numCopies, int flags, const char *pDebugName, const char *pTextureGroupName) = 0;
	/*46*/	virtual void DeleteTexture(ShaderAPITextureHandle_t textureHandle) = 0;
	/*47*/	virtual ShaderAPITextureHandle_t CreateDepthTexture(ImageFormat renderTargetFormat, int width, int height, const char *pDebugName, bool bTexture) = 0;
	/*48*/	virtual bool IsTexture(ShaderAPITextureHandle_t textureHandle) = 0;
	/*49*/	virtual bool IsTextureResident(ShaderAPITextureHandle_t textureHandle) = 0;
	/*50*/	virtual void ModifyTexture(ShaderAPITextureHandle_t textureHandle) = 0;
	/*51*/	virtual void TexImage2D(int level, int cubeFaceID, ImageFormat dstFormat, int zOffset, int width, int height, ImageFormat srcFormat, bool bSrcIsTiled, void *imageData) = 0;
	/*52*/	virtual void TexSubImage2D(int level, int cubeFaceID, int xOffset, int yOffset, int zOffset, int width, int height, ImageFormat srcFormat, int srcStride, bool bSrcIsTiled, void *imageData) = 0;
	/*53*/	virtual void TexImageFromVTF(IVTFTexture* pVTF, int iVTFFrame) = 0;
	/*54*/	virtual bool TexLock(int level, int cubeFaceID, int xOffset, int yOffset, int width, int height, CPixelWriter& writer) = 0;
	/*55*/	virtual void TexUnlock() = 0;
	/*56*/	virtual void TexSetPriority(int priority) = 0;
	/*57*/	virtual void BindTexture(Sampler_t sampler, ShaderAPITextureHandle_t textureHandle) = 0;
	/*58*/	virtual void SetRenderTarget(ShaderAPITextureHandle_t colorTextureHandle = SHADER_RENDERTARGET_BACKBUFFER, ShaderAPITextureHandle_t depthTextureHandle = SHADER_RENDERTARGET_DEPTHBUFFER) = 0;
	/*59*/	virtual void ClearBuffersObeyStencil(bool bClearColor, bool bClearDepth) = 0;
	/*60*/	virtual void ReadPixels(int x, int y, int width, int height, unsigned char *data, ImageFormat dstFormat) = 0;
	/*61*/	virtual void ReadPixels(Rect_t *pSrcRect, Rect_t *pDstRect, unsigned char *data, ImageFormat dstFormat, int nDstStride) = 0;
	/*62*/	virtual void FlushHardware() = 0;
	/*63*/	virtual void BeginFrame() = 0;
	/*64*/	virtual void EndFrame() = 0;

	// Selection mode methods
	virtual int  SelectionMode(bool selectionMode) = 0;
	virtual void SelectionBuffer(unsigned int* pBuffer, int size) = 0;
	virtual void ClearSelectionNames() = 0;
	virtual void LoadSelectionName(int name) = 0;
	virtual void PushSelectionName(int name) = 0;
	virtual void PopSelectionName() = 0;

	// Force the hardware to finish whatever it's doing
	virtual void ForceHardwareSync() = 0;

	// Used to clear the transition table when we know it's become invalid.
	virtual void ClearSnapshots() = 0;

	virtual void FogStart(float fStart) = 0;
	virtual void FogEnd(float fEnd) = 0;
	virtual void SetFogZ(float fogZ) = 0;
	// Scene fog state.
	virtual void SceneFogColor3ub(unsigned char r, unsigned char g, unsigned char b) = 0;
	virtual void GetSceneFogColor(unsigned char *rgb) = 0;
	virtual void SceneFogMode(MaterialFogMode_t fogMode) = 0;

	// Can we download textures?
	virtual bool CanDownloadTextures() const = 0;

	virtual void ResetRenderState(bool bFullReset = true) = 0;

	// We use smaller dynamic VBs during level transitions, to free up memory
	virtual int  GetCurrentDynamicVBSize(void) = 0;
	virtual void DestroyVertexBuffers(bool bExitingLevel = false) = 0;

	virtual void EvictManagedResources() = 0;

	// Level of anisotropic filtering
	virtual void SetAnisotropicLevel(int nAnisotropyLevel) = 0;

	// For debugging and building recording files. This will stuff a token into the recording file,
	// then someone doing a playback can watch for the token.
	virtual void SyncToken(const char *pToken) = 0;

	// Setup standard vertex shader constants (that don't change)
	// This needs to be called anytime that overbright changes.
	virtual void SetStandardVertexShaderConstants(float fOverbright) = 0;

	//
	// Occlusion query support
	//

	// Allocate and delete query objects.
	virtual ShaderAPIOcclusionQuery_t CreateOcclusionQueryObject(void) = 0;
	virtual void DestroyOcclusionQueryObject(ShaderAPIOcclusionQuery_t) = 0;

	// Bracket drawing with begin and end so that we can get counts next frame.
	virtual void BeginOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t) = 0;
	virtual void EndOcclusionQueryDrawing(ShaderAPIOcclusionQuery_t) = 0;

	// OcclusionQuery_GetNumPixelsRendered
	//	Get the number of pixels rendered between begin and end on an earlier frame.
	//	Calling this in the same frame is a huge perf hit!
	// Returns iQueryResult:
	//	iQueryResult >= 0					-	iQueryResult is the number of pixels rendered
	//	OCCLUSION_QUERY_RESULT_PENDING		-	query results are not available yet
	//	OCCLUSION_QUERY_RESULT_ERROR		-	query failed
	// Use OCCLUSION_QUERY_FINISHED( iQueryResult ) to test if query finished.
	virtual int OcclusionQuery_GetNumPixelsRendered(ShaderAPIOcclusionQuery_t hQuery, bool bFlush = false) = 0;

	virtual void SetFlashlightState(const FlashlightState_t &state, const VMatrix &worldToTexture) = 0;

	virtual void ClearVertexAndPixelShaderRefCounts() = 0;
	virtual void PurgeUnusedVertexAndPixelShaders() = 0;

	// Called when the dx support level has changed
	virtual void DXSupportLevelChanged() = 0;

	// By default, the material system applies the VIEW and PROJECTION matrices	to the user clip
	// planes (which are specified in world space) to generate projection-space user clip planes
	// Occasionally (for the particle system in hl2, for example), we want to override that
	// behavior and explictly specify a View transform for user clip planes. The PROJECTION
	// will be mutliplied against this instead of the normal VIEW matrix.
	virtual void EnableUserClipTransformOverride(bool bEnable) = 0;
	virtual void UserClipTransform(const VMatrix &worldToView) = 0;

	// ----------------------------------------------------------------------------------
	// Everything after this point added after HL2 shipped.
	// ----------------------------------------------------------------------------------

	// What fields in the morph do we actually use?
	virtual MorphFormat_t ComputeMorphFormat(int numSnapshots, StateSnapshot_t* pIds) const = 0;

	// Set the render target to a texID.
	// Set to SHADER_RENDERTARGET_BACKBUFFER if you want to use the regular framebuffer.
	// Set to SHADER_RENDERTARGET_DEPTHBUFFER if you want to use the regular z buffer.
	virtual void SetRenderTargetEx(int nRenderTargetID,
		ShaderAPITextureHandle_t colorTextureHandle = SHADER_RENDERTARGET_BACKBUFFER,
		ShaderAPITextureHandle_t depthTextureHandle = SHADER_RENDERTARGET_DEPTHBUFFER) = 0;

	virtual void CopyRenderTargetToTextureEx(ShaderAPITextureHandle_t textureHandle, int nRenderTargetID, Rect_t *pSrcRect = NULL, Rect_t *pDstRect = NULL) = 0;
	virtual void CopyTextureToRenderTargetEx(int nRenderTargetID, ShaderAPITextureHandle_t textureHandle, Rect_t *pSrcRect = NULL, Rect_t *pDstRect = NULL) = 0;

	// For dealing with device lost in cases where SwapBuffers isn't called all the time (Hammer)
	virtual void HandleDeviceLost() = 0;

	virtual void EnableLinearColorSpaceFrameBuffer(bool bEnable) = 0;

	// Lets the shader know about the full-screen texture so it can 
	virtual void SetFullScreenTextureHandle(ShaderAPITextureHandle_t h) = 0;

	// Rendering parameters control special drawing modes withing the material system, shader
	// system, shaders, and engine. renderparm.h has their definitions.
	virtual void SetFloatRenderingParameter(int parm_number, float value) = 0;
	virtual void SetIntRenderingParameter(int parm_number, int value) = 0;
	virtual void SetVectorRenderingParameter(int parm_number, Vector const &value) = 0;

	virtual float GetFloatRenderingParameter(int parm_number) const = 0;
	virtual int GetIntRenderingParameter(int parm_number) const = 0;
	virtual Vector GetVectorRenderingParameter(int parm_number) const = 0;

	virtual void SetFastClipPlane(const float *pPlane) = 0;
	virtual void EnableFastClip(bool bEnable) = 0;

	// Returns the number of vertices + indices we can render using the dynamic mesh
	// Passing true in the second parameter will return the max # of vertices + indices
	// we can use before a flush is provoked and may return different values 
	// if called multiple times in succession. 
	// Passing false into the second parameter will return
	// the maximum possible vertices + indices that can be rendered in a single batch
	virtual void GetMaxToRender(IMesh *pMesh, bool bMaxUntilFlush, int *pMaxVerts, int *pMaxIndices) = 0;

	// Returns the max number of vertices we can render for a given material
	virtual int GetMaxVerticesToRender(IMaterial *pMaterial) = 0;
	virtual int GetMaxIndicesToRender() = 0;

	// stencil methods
	virtual void SetStencilEnable(bool onoff) = 0;
	virtual void SetStencilFailOperation(StencilOperation_t op) = 0;
	virtual void SetStencilZFailOperation(StencilOperation_t op) = 0;
	virtual void SetStencilPassOperation(StencilOperation_t op) = 0;
	virtual void SetStencilCompareFunction(StencilComparisonFunction_t cmpfn) = 0;
	virtual void SetStencilReferenceValue(int ref) = 0;
	virtual void SetStencilTestMask(UINT32 msk) = 0;
	virtual void SetStencilWriteMask(UINT32 msk) = 0;
	virtual void ClearStencilBufferRectangle(int xmin, int ymin, int xmax, int ymax, int value) = 0;

	// disables all local lights
	virtual void DisableAllLocalLights() = 0;
	virtual int CompareSnapshots(StateSnapshot_t snapshot0, StateSnapshot_t snapshot1) = 0;

	virtual IMesh *GetFlexMesh() = 0;

	virtual void SetFlashlightStateEx(const FlashlightState_t &state, const VMatrix &worldToTexture, ITexture *pFlashlightDepthTexture) = 0;

	virtual bool SupportsMSAAMode(int nMSAAMode) = 0;

#if defined( _X360 )
	virtual HXUIFONT OpenTrueTypeFont(const char *pFontname, int tall, int style) = 0;
	virtual void CloseTrueTypeFont(HXUIFONT hFont) = 0;
	virtual bool GetTrueTypeFontMetrics(HXUIFONT hFont, XUIFontMetrics *pFontMetrics, XUICharMetrics charMetrics[256]) = 0;
	// Render a sequence of characters and extract the data into a buffer
	// For each character, provide the width+height of the font texture subrect,
	// an offset to apply when rendering the glyph, and an offset into a buffer to receive the RGBA data
	virtual bool GetTrueTypeGlyphs(HXUIFONT hFont, int numChars, wchar_t *pWch, int *pOffsetX, int *pOffsetY, int *pWidth, int *pHeight, unsigned char *pRGBA, int *pRGBAOffset) = 0;
	virtual ShaderAPITextureHandle_t CreateRenderTargetSurface(int width, int height, ImageFormat format, const char *pDebugName, const char *pTextureGroupName) = 0;
	virtual void PersistDisplay() = 0;
	virtual bool PostQueuedTexture(const void *pData, int nSize, ShaderAPITextureHandle_t *pHandles, int nHandles, int nWidth, int nHeight, int nDepth, int nMips, int *pRefCount) = 0;
	virtual void *GetD3DDevice() = 0;

	virtual void PushVertexShaderGPRAllocation(int iVertexShaderCount = 64) = 0;
	virtual void PopVertexShaderGPRAllocation(void) = 0;

	virtual void EnableVSync_360(bool bEnable) = 0; //360 allows us to bypass vsync blocking up to 60 fps without creating a new device
#endif

	virtual bool OwnGPUResources(bool bEnable) = 0;

	//get fog distances entered with FogStart(), FogEnd(), and SetFogZ()
	virtual void GetFogDistances(float *fStart, float *fEnd, float *fFogZ) = 0;

	// Hooks for firing PIX events from outside the Material System...
	virtual void BeginPIXEvent(unsigned long color, const char *szName) = 0;
	virtual void EndPIXEvent() = 0;
	virtual void SetPIXMarker(unsigned long color, const char *szName) = 0;

	// Enables and disables for Alpha To Coverage
	virtual void EnableAlphaToCoverage() = 0;
	virtual void DisableAlphaToCoverage() = 0;

	// Computes the vertex buffer pointers 
	virtual void ComputeVertexDescription(unsigned char* pBuffer, VertexFormat_t vertexFormat, MeshDesc_t& desc) const = 0;

	virtual bool SupportsShadowDepthTextures(void) = 0;

	virtual void SetDisallowAccess(bool) = 0;
	virtual void EnableShaderShaderMutex(bool) = 0;
	virtual void ShaderLock() = 0;
	virtual void ShaderUnlock() = 0;

	virtual ImageFormat GetShadowDepthTextureFormat(void) = 0;

	virtual bool SupportsFetch4(void) = 0;
	virtual void SetShadowDepthBiasFactors(float fShadowSlopeScaleDepthBias, float fShadowDepthBias) = 0;

	// ------------ New Vertex/Index Buffer interface ----------------------------
	virtual void BindVertexBuffer(int nStreamID, IVertexBuffer *pVertexBuffer, int nOffsetInBytes, int nFirstVertex, int nVertexCount, VertexFormat_t fmt, int nRepetitions = 1) = 0;
	virtual void BindIndexBuffer(IIndexBuffer *pIndexBuffer, int nOffsetInBytes) = 0;
	virtual void Draw(MaterialPrimitiveType_t primitiveType, int nFirstIndex, int nIndexCount) = 0;
	// ------------ End ----------------------------


		// Apply stencil operations to every pixel on the screen without disturbing depth or color buffers
	virtual void PerformFullScreenStencilOperation(void) = 0;

	virtual void SetScissorRect(const int nLeft, const int nTop, const int nRight, const int nBottom, const bool bEnableScissor) = 0;

	// nVidia CSAA modes, different from SupportsMSAAMode()
	virtual bool SupportsCSAAMode(int nNumSamples, int nQualityLevel) = 0;

	//Notifies the shaderapi to invalidate the current set of delayed constants because we just finished a draw pass. Either actual or not.
	virtual void InvalidateDelayedShaderConstants(void) = 0;

	// Gamma<->Linear conversions according to the video hardware we're running on
	virtual float GammaToLinear_HardwareSpecific(float fGamma) const = 0;
	virtual float LinearToGamma_HardwareSpecific(float fLinear) const = 0;

	//Set's the linear->gamma conversion textures to use for this hardware for both srgb writes enabled and disabled(identity)
	virtual void SetLinearToGammaConversionTextures(ShaderAPITextureHandle_t hSRGBWriteEnabledTexture, ShaderAPITextureHandle_t hIdentityTexture) = 0;

	virtual ImageFormat GetNullTextureFormat(void) = 0;

	virtual void BindVertexTexture(VertexTextureSampler_t nSampler, ShaderAPITextureHandle_t textureHandle) = 0;

	// Enables hardware morphing
	virtual void EnableHWMorphing(bool bEnable) = 0;

	// Sets flexweights for rendering
	virtual void SetFlexWeights(int nFirstWeight, int nCount, const MorphWeight_t* pWeights) = 0;

	virtual void FogMaxDensity(float flMaxDensity) = 0;

	// Create a multi-frame texture (equivalent to calling "CreateTexture" multiple times, but more efficient)
	virtual void CreateTextures(
		ShaderAPITextureHandle_t *pHandles,
		int count,
		int width,
		int height,
		int depth,
		ImageFormat dstImageFormat,
		int numMipLevels,
		int numCopies,
		int flags,
		const char *pDebugName,
		const char *pTextureGroupName) = 0;

	virtual void AcquireThreadOwnership() = 0;
	virtual void ReleaseThreadOwnership() = 0;

	virtual bool SupportsNormalMapCompression() const = 0;

	// Only does anything on XBox360. This is useful to eliminate stalls
	virtual void EnableBuffer2FramesAhead(bool bEnable) = 0;

	virtual void SetDepthFeatheringPixelShaderConstant(int iConstant, float fDepthBlendScale) = 0;

	// debug logging
	// only implemented in some subclasses
	virtual void PrintfVA(char *fmt, va_list vargs) = 0;
	virtual void Printf(PRINTF_FORMAT_STRING const char *fmt, ...) = 0;
	virtual float Knob(char *knobname, float *setvalue = NULL) = 0;
	// Allows us to override the alpha write setting of a material
	virtual void OverrideAlphaWriteEnable(bool bEnable, bool bAlphaWriteEnable) = 0;
	virtual void OverrideColorWriteEnable(bool bOverrideEnable, bool bColorWriteEnable) = 0;

	//extended clear buffers function with alpha independent from color
	virtual void ClearBuffersObeyStencilEx(bool bClearColor, bool bClearAlpha, bool bClearDepth) = 0;

	// Allows copying a render target to another texture by specifying them both.
	virtual void CopyRenderTargetToScratchTexture(ShaderAPITextureHandle_t srcRt, ShaderAPITextureHandle_t dstTex, Rect_t *pSrcRect = NULL, Rect_t *pDstRect = NULL) = 0;

	// Allows locking and unlocking of very specific surface types.
	virtual void LockRect(void** pOutBits, int* pOutPitch, ShaderAPITextureHandle_t texHandle, int mipmap, int x, int y, int w, int h, bool bWrite, bool bRead) = 0;
	virtual void UnlockRect(ShaderAPITextureHandle_t texHandle, int mipmap) = 0;

};