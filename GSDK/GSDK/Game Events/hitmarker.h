class Event_HitMarker : public IGameEventListener
{
public:
	Event_HitMarker(void) { GameEventManager()->AddListener(this, "player_hurt", false); }
	~Event_HitMarker(void) { GameEventManager()->RemoveListener(this); }
	void FireGameEvent(IGameEvent *event) override;
	int GetEventDebugID(void);
	void Paint();
private:
	float Duration = 0;
};

void Event_HitMarker::FireGameEvent(IGameEvent* event)
{
	if (!event)
		return;

	int LocalPlayer = engine()->GetLocalPlayer();
	int Attacker = engine()->GetPlayerForUserID(event->GetInt("attacker"));
	int Player = engine()->GetPlayerForUserID(event->GetInt("userid"));

	if ( Attacker == LocalPlayer && Player != LocalPlayer)
	{
		surface()->ISPlaySound("buttons\\arena_switch_press_02.wav");
		Duration = globals()->curtime + 0.25;
	}
}
void Event_HitMarker::Paint()
{
	if (Duration >= globals()->curtime)
	{
		int centerW, centerH;
		engine()->GetScreenSize(centerW, centerH); centerW = centerW / 2; centerH = centerH / 2;
		surface()->DrawSetColor(Color(255, 255, 255, 255));
		// Top L
		surface()->DrawLine(centerW - 20, centerH - 20, centerW - 7, centerH - 7);
		// Bot L
		surface()->DrawLine(centerW - 20, centerH + 20, centerW - 7, centerH + 7);

		// Top R
		surface()->DrawLine(centerW + 20, centerH - 20, centerW + 7, centerH - 7);
		// Bot R
		surface()->DrawLine(centerW + 20, centerH + 20, centerW + 7, centerH + 7);
	}
}
int Event_HitMarker::GetEventDebugID(void)
{
	return EVENT_DEBUG_ID_INIT;
}