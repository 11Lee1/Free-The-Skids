class CBoneBitList;
class CMouthInfo;
class IBoneSetup;
class CBoneAccessor;
struct ModelRenderInfo_t
{
	Vector origin;
	QAngle angles;
	IClientRenderable *pRenderable;
	const model_t *pModel;
	const matrix3x4_t *pModelToWorld;
	const matrix3x4_t *pLightingOffset;
	const Vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	ModelInstanceHandle_t instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};
struct ClientModelRenderInfo_t : public ModelRenderInfo_t
{
	// Added space for lighting origin override. Just allocated space, need to set base pointer
	matrix3x4_t lightingOffset;

	// Added space for model to world matrix. Just allocated space, need to set base pointer
	matrix3x4_t modelToWorld;
};
class C_BaseAnimating : public BaseEntity, private IModelLoadCallback
{
public: // 259 - 59
	DECLARE_CLASS(C_BaseAnimating, BaseEntity);

	
	virtual void nofuckingidea0() = 0;
	virtual void nofuckingidea1() = 0;


	virtual void				GetBoneControllers(float controllers[MAXSTUDIOBONECTRLS]) = 0;
	virtual float				SetBoneController(int iController, float flValue) = 0;
	virtual float				GetBoneController(int) = 0;
	virtual void				GetPoseParameters(CStudioHdr *pStudioHdr, float poseParameter[MAXSTUDIOPOSEPARAM]) = 0;
	virtual void				BuildTransformations(CStudioHdr *pStudioHdr, Vector *pos, Quaternion q[], const matrix3x4_t& cameraTransform, int boneMask, CBoneBitList &boneComputed) = 0;
	virtual void				ApplyBoneMatrixTransform(matrix3x4_t& transform) = 0;
	virtual int					VPhysicsGetObjectList(IPhysicsObject **pList, int listMax) = 0;
	virtual bool				/*fix me*/C_BaseAnimatingSetupBones(matrix3x4_t *pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime) = 0;
	virtual int					InternalDrawModel(int flags) = 0;
	virtual bool				OnInternalDrawModel(ClientModelRenderInfo_t *pInfo) = 0;
	virtual void*				GetMouth() = 0;
	virtual void				ControlMouth(CStudioHdr *pStudioHdr) = 0;
	virtual void				DoAnimationEvents(CStudioHdr *pStudio) = 0;
	virtual void				FireEvent(const Vector& origin, const QAngle& angles, int event, const char *options) = 0;
	virtual void				FireObsoleteEvent(const Vector& origin, const QAngle& angles, int event, const char *options) = 0;
	virtual const char*			ModifyEventParticles(const char* token) = 0;
	virtual void				ResetEventsParity() = 0;
	virtual bool				DispatchMuzzleEffect(const char *options, bool isFirstPerson) = 0;
	virtual	void				StandardBlendingRules(CStudioHdr *pStudioHdr, Vector pos[], Quaternion q[], float currentTime, int boneMask) = 0;
	virtual void				AccumulateLayers(IBoneSetup &boneSetup, Vector pos[], Quaternion q[], float currentTime) = 0;
	virtual void				ChildLayerBlend(Vector pos[], Quaternion q[], float currentTime, int boneMask) = 0;
	virtual void				AttachEntityToBone(C_BaseAnimating* attachTarget, int boneIndexAttached = -1, Vector bonePosition = Vector(0, 0, 0), QAngle boneAngles = QAngle(0, 0, 0)) = 0;
	virtual void				NotifyBoneAttached(C_BaseAnimating* attachTarget) = 0;
	virtual void				UpdateBoneAttachments(void) = 0;
	virtual bool				IsRagdoll() = 0;
	virtual C_BaseAnimating*	BecomeRagdollOnClient() = 0;
	virtual void				SaveRagdollInfo(int numbones, const matrix3x4_t &cameraTransform, CBoneAccessor &pBoneToWorld) = 0;
	virtual bool				RetrieveRagdollInfo(Vector *pos, Quaternion *q) = 0;
	virtual bool				GetRagdollInitBoneArrays(matrix3x4_t *pDeltaBones0, matrix3x4_t *pDeltaBones1, matrix3x4_t *pCurrentBones, float boneDt) = 0;
	virtual	void				RefreshCollisionBounds(void) = 0;
	virtual void				SetSequence(int nSequence) = 0;
	virtual void				StudioFrameAdvance() = 0; // advance animation frame to some time in the future
	virtual float				FrameAdvance(float flInterval = 0.0f) = 0;
	virtual float				GetSequenceCycleRate(CStudioHdr *pStudioHdr, int iSequence) = 0;
	virtual void				UpdateClientSideAnimation() = 0;
	virtual unsigned int		ComputeClientSideAnimationFlags() = 0;
	virtual void				ResetClientsideFrame(void) = 0;
	virtual bool				IsActivityFinished(void) = 0;
	virtual void				UncorrectViewModelAttachment(Vector &vOrigin) = 0;
	virtual void				DoMuzzleFlash() = 0;
	virtual void				ProcessMuzzleFlashEvent() = 0;
	virtual void				SetServerIntendedCycle(float intended) = 0;
	virtual float				GetServerIntendedCycle(void) = 0;
	virtual bool				ShouldResetSequenceOnNewModel(void) = 0;
	virtual bool				IsViewModel() = 0;
	virtual void				FormatViewModelAttachment(int nAttachment, matrix3x4_t &attachmentToWorld) = 0;
	virtual bool				IsMenuModel() = 0;
	virtual bool				CalcAttachments() = 0;
	virtual float				LastBoneChangedTime() = 0;
	virtual void				SetOverrideViewTarget(Vector) = 0;
	virtual int					GetNumPhysicsBones() = 0;
	virtual int					GetForcedLod() = 0;
	virtual void				SetForcedLod(int) = 0;
	virtual int					GetPhysBoneNumber(int) = 0;
	virtual int					GetBoneManipulator(bool) = 0;
	virtual int					GetFlexManipulator(bool) = 0;
	virtual int					UnqueueSetupBones() = 0;
	virtual void				StartMeshOverride(ClientModelRenderInfo_t *) = 0;
	virtual void				StopMeshOverride() = 0;
public:
	int LookupBone(const char *szName)
	{
		if (!GetModelPtr())
			return -1;

		return Studio_BoneIndexByName(GetModelPtr(), szName);
	}
	int LookupBone(Joints joint)
	{
		switch (joint)
		{
		case Pelvis:
			return LookupBone("ValveBiped.Bip01_Pelvis");
			break;
		case Spine:
			return LookupBone("ValveBiped.Bip01_Spine");
			break;
		case Spine1:
			return LookupBone("ValveBiped.Bip01_Spine1");
			break;
		case Spine2:
			return LookupBone("ValveBiped.Bip01_Spine2");
			break;
		case Spine3:
			return LookupBone("ValveBiped.Bip01_Spine4");
			break;
		case Neck:
			return LookupBone("ValveBiped.Bip01_Neck1");
			break;
		case Head:
			return LookupBone("ValveBiped.Bip01_Head1");
			break;
		case RCalvicle:
			return LookupBone("ValveBiped.Bip01_R_Calvicle");
			break;
		case RShoulder:
			return LookupBone("ValveBiped.Bip01_R_UpperArm");
			break;
		case RForearm:
			return LookupBone("ValveBiped.Bip01_R_Forearm");
			break;
		case RHand:
			return LookupBone("ValveBiped.Bip01_R_Hand");
			break;
		case LCalvicle:
			return LookupBone("ValveBiped.Bip01_L_Calvicle");
			break;
		case LShoulder:
			return LookupBone("ValveBiped.Bip01_L_UpperArm");
			break;
		case LForearm:
			return LookupBone("ValveBiped.Bip01_L_Forearm");
			break;
		case LHand:
			return LookupBone("ValveBiped.Bip01_L_Hand");
			break;
		case RHip:
			return LookupBone("ValveBiped.Bip01_R_Thigh");
			break;
		case RCalf:
			return LookupBone("ValveBiped.Bip01_R_Calf");
			break;
		case RFoot:
			return LookupBone("ValveBiped.Bip01_R_Foot");
			break;
		case RToe:
			return LookupBone("ValveBiped.Bip01_R_Toe0");
			break;
		case LHip:
			return LookupBone("ValveBiped.Bip01_L_Thigh");
			break;
		case LCalf:
			return LookupBone("ValveBiped.Bip01_L_Calf");
			break;
		case LFoot:
			return LookupBone("ValveBiped.Bip01_L_Foot");
			break;
		case LToe:
			return LookupBone("ValveBiped.Bip01_R_Toe0");
			break;
		default:
			return LookupBone("ValveBiped.Bip01_Head1");
			break;
		}
	}
public:
	float& m_flPlaybackRate()
	{
		return *(float*)((uintptr_t)this + offsets::DT_BaseAnimating::m_flPlaybackRate);
	}
};