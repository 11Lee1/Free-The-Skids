class RenderView
{
public:

	// Draw normal brush model.
	// If pMaterialOverride is non-null, then all the faces of the bmodel will
	// set this material rather than their regular material.
	/*0*/virtual void			DrawBrushModel(BaseEntity *baseentity, model_t *model, const Vector& origin, const QAngle& angles, bool bUnused) = 0;

	// Draw brush model that has no origin/angles change ( uses identity transform )
	// FIXME, Material proxy IClientEntity *baseentity is unused right now, use DrawBrushModel for brushes with
	//  proxies for now.
	/*1*/virtual void			DrawIdentityBrushModel(IWorldRenderList *pList, model_t *model) = 0;

	// Mark this dynamic light as having changed this frame ( so light maps affected will be recomputed )
	/*2*/virtual void			TouchLight(struct dlight_t *light) = 0;
	// Draw 3D Overlays
	/*3*/virtual void			Draw3DDebugOverlays(void) = 0;
	// Sets global blending fraction
	/*4*/virtual void			SetBlend(float blend) = 0;
	/*5*/virtual float			GetBlend(void) = 0;

	// Sets global color modulation
	/*6*/virtual void			SetColorModulation(float const* blend) = 0;
	/*7*/virtual void			GetColorModulation(float* blend) = 0;

	// Wrap entire scene drawing
	/*8*/virtual void			SceneBegin(void) = 0;
	/*9*/virtual void			SceneEnd(void) = 0;

	// Gets the fog volume for a particular point
	/*10*/virtual void			GetVisibleFogVolume(const Vector& eyePoint, VisibleFogVolumeInfo_t *pInfo) = 0;

	// Wraps world drawing
	// If iForceViewLeaf is not -1, then it uses the specified leaf as your starting area for setting up area portal culling.
	// This is used by water since your reflected view origin is often in solid space, but we still want to treat it as though
	// the first portal we're looking out of is a water portal, so our view effectively originates under the water.
	/*11*/virtual IWorldRenderList * CreateWorldList() = 0;

	/*12*/virtual void			BuildWorldLists(IWorldRenderList *pList, WorldListInfo_t* pInfo, int iForceFViewLeaf, const VisOverrideData_t* pVisData = NULL, bool bShadowDepth = false, float *pReflectionWaterHeight = NULL) = 0;
	/*13*/virtual void			DrawWorldLists(IWorldRenderList *pList, unsigned long flags, float waterZAdjust) = 0;

	// Optimization for top view
	/*14*/virtual void			DrawTopView(bool enable) = 0;
	/*15*/virtual void			TopViewBounds(Vector2D const& mins, Vector2D const& maxs) = 0;

	// Draw lights
	/*16*/virtual void			DrawLights(void) = 0;

	// FIXME:  This function is a stub, doesn't do anything in the engine right now
	/*17*/virtual void			stub__DrawMaskEntities(void) = 0; // FIXME:  This function is a stub, doesn't do anything in the engine right now


	// Draw surfaces with alpha
	/*18*/virtual void			DrawTranslucentSurfaces(IWorldRenderList *pList, int sortIndex, unsigned long flags, bool bShadowDepth) = 0;

	// Draw Particles ( just draws the linefine for debugging map leaks )
	/*19*/virtual void			DrawLineFile(void) = 0;
	// Draw lightmaps
	/*20*/virtual void			DrawLightmaps(IWorldRenderList *pList, int pageId) = 0;
	// Wraps view render sequence, sets up a view
	/*21*/virtual void			ViewSetupVis(bool novis, int numorigins, const Vector origin[]) = 0;

	// Return true if any of these leaves are visible in the current PVS.
	/*22*/virtual bool			AreAnyLeavesVisible(int *leafList, int nLeaves) = 0;

	/*23*/virtual	void			VguiPaint(void) = 0;
	// Sets up view fade parameters
	/*24*/virtual void			ViewDrawFade(byte *color, IMaterial *pMaterial) = 0;
	// Sets up the projection matrix for the specified field of view
	/*25*/virtual void			stub__OLD_SetProjectionMatrix(float fov, float zNear, float zFar) = 0;
	// Determine lighting at specified position
	/*26*/virtual colorVec		GetLightAtPoint(Vector& pos) = 0;
	// Whose eyes are we looking through?
	/*27*/virtual int				GetViewEntity(void) = 0;
	// Get engine field of view setting
	/*28*/	virtual float			GetFieldOfView(void) = 0;
	// 1 == ducking, 0 == not
	/*30*/virtual unsigned char	**GetAreaBits(void) = 0;

	// Set up fog for a particular leaf
	/*31*/virtual void			SetFogVolumeState(int nVisibleFogVolume, bool bUseHeightFog) = 0;

	// Installs a brush surface draw override method, null means use normal renderer
	/*32*/virtual void			InstallBrushSurfaceRenderer(IBrushRenderer* pBrushRenderer) = 0;

	// Draw brush model shadow
	/*33*/virtual void			DrawBrushModelShadow(IClientRenderable *pRenderable) = 0;

	// Does the leaf contain translucent surfaces?
	/*34*/virtual	bool			LeafContainsTranslucentSurfaces(IWorldRenderList *pList, int sortIndex, unsigned long flags) = 0;

	/*35*/virtual bool			DoesBoxIntersectWaterVolume(const Vector &mins, const Vector &maxs, int leafWaterDataID) = 0;

	/*36*/virtual void			SetAreaState(
		unsigned char chAreaBits[MAX_AREA_STATE_BYTES],
		unsigned char chAreaPortalBits[MAX_AREA_PORTAL_STATE_BYTES]) = 0;

	// See i
	/*37*/virtual void			VGui_Paint(int mode) = 0;

	// Push, pop views (see PushViewFlags_t above for flags)
	/*38*/virtual void			Push3DView(const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes) = 0;
	/*39*/virtual void			Push3DView(const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes, ITexture* pDepthTexture) = 0;
	/*40*/virtual void			Push2DView(const CViewSetup &view, int nFlags, ITexture* pRenderTarget, Frustum frustumPlanes) = 0;
	/*41*/virtual void			PopView(Frustum frustumPlanes) = 0;

	// Sets the main view
	/*42*/virtual void			SetMainView(const Vector &vecOrigin, const QAngle &angles) = 0;

	enum
	{
		VIEW_SETUP_VIS_EX_RETURN_FLAGS_USES_RADIAL_VIS = 0x00000001
	};

	// Wraps view render sequence, sets up a view
	/*43*/virtual void			ViewSetupVisEx(bool novis, int numorigins, const Vector origin[], unsigned int &returnFlags) = 0;

	//replaces the current view frustum with a rhyming replacement of your choice
	/*44*/virtual void			OverrideViewFrustum(Frustum custom) = 0;

	/*45*/virtual void			DrawBrushModelShadowDepth(BaseEntity *baseentity, model_t *model, const Vector& origin, const QAngle& angles, ERenderDepthMode DepthMode) = 0;
	/*46*/virtual void			UpdateBrushModelLightmap(model_t *model, IClientRenderable *pRenderable) = 0;
	/*47*/virtual void			BeginUpdateLightmaps(void) = 0;
	/*48*/virtual void			EndUpdateLightmaps(void) = 0;

	/*49*/virtual void			stub__01(void) = 0;
	/*50*/virtual void			stub__02(void) = 0;

	/*51*/virtual void			GetMatricesForView(const CViewSetup &view, VMatrix *pWorldToView, VMatrix *pViewToProjection, VMatrix *pWorldToProjection, VMatrix *pWorldToPixels) = 0;
	/*52*/virtual void			DrawBrushModelEx(BaseEntity *baseentity, model_t *model, const Vector& origin, const QAngle& angles, DrawBrushModelMode_t mode) = 0;
};