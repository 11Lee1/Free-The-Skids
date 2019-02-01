struct SpatializationInfo_t;
class IClientEntity : public IClientUnknown
{
public:
	virtual Vector& GetRenderOrigin(void) = 0;
	virtual QAngle& GetRenderAngles(void) = 0;
	virtual void*	GetMouth() = 0;
	virtual bool	GetSoundSpatialization(SpatializationInfo_t& info) = 0;
};