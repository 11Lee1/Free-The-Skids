class IPooledVBAllocator;
enum
{
	MODEL_INSTANCE_INVALID = (ModelInstanceHandle_t)~0
};
enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};
enum
{
	ADDDECAL_TO_ALL_LODS = -1
};
struct StaticPropRenderInfo_t
{
	const matrix3x4_t		*pModelToWorld;
	const model_t			*pModel;
	IClientRenderable		*pRenderable;
	Vector					*pLightingOrigin;
	short					skin;
	ModelInstanceHandle_t	instance;
};
struct DrawModelState_t
{
	studiohdr_t*			m_pStudioHdr;
	studiohwdata_t*			m_pStudioHWData;
	IClientRenderable*		m_pRenderable;
	const matrix3x4_t		*m_pModelToWorld;
	StudioDecalHandle_t		m_decals;
	int						m_drawFlags;
	int						m_lod;
};
struct ColorMeshInfo_t
{
	// A given color mesh can own a unique Mesh, or it can use a shared Mesh
	// (in which case it uses a sub-range defined by m_nVertOffset and m_nNumVerts)
	IMesh				*	m_pMesh;
	IPooledVBAllocator	*	m_pPooledVBAllocator;
	int						m_nVertOffsetInBytes;
	int						m_nNumVerts;
};
struct DrawModelInfo_t
{
	studiohdr_t		*m_pStudioHdr;
	studiohwdata_t	*m_pHardwareData;
	StudioDecalHandle_t m_Decals;
	int				m_Skin;
	int				m_Body;
	int				m_HitboxSet;
	void			*m_pClientEntity;
	int				m_Lod;
	ColorMeshInfo_t	*m_pColorMeshes;
	bool			m_bStaticLighting;
	Vector			m_vecAmbientCube[6];		// ambient, and lights that aren't in locallight[]
	int				m_nLocalLightCount;
	LightDesc_t		m_LocalLightDescs[4];
};
struct Ray_t;
class IVModelRender
{
public:
	virtual int		DrawModel(int flags,
		IClientRenderable *pRenderable,
		ModelInstanceHandle_t instance,
		int entity_index,
		const model_t *model,
		Vector const& origin,
		QAngle const& angles,
		int skin,
		int body,
		int hitboxset,
		const matrix3x4_t *modelToWorld = NULL,
		const matrix3x4_t *pLightingOffset = NULL) = 0;

	// This causes a material to be used when rendering the model instead 
	// of the materials the model was compiled with
	virtual void	ForcedMaterialOverride(IMaterial *newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL) = 0;

	virtual void	SetViewTarget(const CStudioHdr *pStudioHdr, int nBodyIndex, const Vector& target) = 0;

	// Creates, destroys instance data to be associated with the model
	virtual ModelInstanceHandle_t CreateInstance(IClientRenderable *pRenderable, LightCacheHandle_t *pCache = NULL) = 0;
	virtual void DestroyInstance(ModelInstanceHandle_t handle) = 0;

	// Associates a particular lighting condition with a model instance handle.
	// FIXME: This feature currently only works for static props. To make it work for entities, etc.,
	// we must clean up the lightcache handles as the model instances are removed.
	// At the moment, since only the static prop manager uses this, it cleans up all LightCacheHandles 
	// at level shutdown.
	virtual void SetStaticLighting(ModelInstanceHandle_t handle, LightCacheHandle_t* pHandle) = 0;
	virtual LightCacheHandle_t GetStaticLighting(ModelInstanceHandle_t handle) = 0;

	// moves an existing InstanceHandle to a nex Renderable to keep decals etc. Models must be the same
	virtual bool ChangeInstance(ModelInstanceHandle_t handle, IClientRenderable *pRenderable) = 0;

	// Creates a decal on a model instance by doing a planar projection
	// along the ray. The material is the decal material, the radius is the
	// radius of the decal to create.
	virtual void AddDecal(ModelInstanceHandle_t handle, Ray_t const& ray,
		Vector const& decalUp, int decalIndex, int body, bool noPokeThru = false, int maxLODToDecal = ADDDECAL_TO_ALL_LODS) = 0;

	virtual void GMODAddDecal(ModelInstanceHandle_t handle, Vector const&, Vector const&, IMaterial *Material, int thing, float thing2, float thing3) = 0;
	// Removes all the decals on a model instance
	virtual void RemoveAllDecals(ModelInstanceHandle_t handle) = 0;

	// Remove all decals from all models
	virtual void RemoveAllDecalsFromAllModels() = 0;

	// Shadow rendering, DrawModelShadowSetup returns the address of the bone-to-world array, NULL in case of error
	virtual matrix3x4_t* DrawModelShadowSetup(IClientRenderable *pRenderable, int body, int skin, DrawModelInfo_t *pInfo, matrix3x4_t *pCustomBoneToWorld = NULL) = 0;
	virtual void DrawModelShadow(IClientRenderable *pRenderable, const DrawModelInfo_t &info, matrix3x4_t *pCustomBoneToWorld = NULL) = 0;

	// This gets called when overbright, etc gets changed to recompute static prop lighting.
	virtual bool RecomputeStaticLighting(ModelInstanceHandle_t handle) = 0;

	virtual void ReleaseAllStaticPropColorData(void) = 0;
	virtual void RestoreAllStaticPropColorData(void) = 0;

	// Extended version of drawmodel
	virtual int	DrawModelEx(ModelRenderInfo_t &pInfo) = 0;

	virtual int	DrawModelExStaticProp(ModelRenderInfo_t &pInfo) = 0;

	virtual bool DrawModelSetup(ModelRenderInfo_t &pInfo, DrawModelState_t *pState, matrix3x4_t *pCustomBoneToWorld, matrix3x4_t** ppBoneToWorldOut) = 0;
	virtual void DrawModelExecute(const DrawModelState_t &state, const ModelRenderInfo_t &pInfo, matrix3x4_t *pCustomBoneToWorld = NULL) = 0;

	// Sets up lighting context for a point in space
	virtual void SetupLighting(const Vector &vecCenter) = 0;

	// doesn't support any debug visualization modes or other model options, but draws static props in the
	// fastest way possible
	virtual int DrawStaticPropArrayFast(StaticPropRenderInfo_t *pProps, int count, bool bShadowDepth) = 0;

	// Allow client to override lighting state
	virtual void SuppressEngineLighting(bool bSuppress) = 0;

	virtual void SetupColorMeshes(int nTotalVerts) = 0;


};