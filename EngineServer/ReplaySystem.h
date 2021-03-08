#pragma once
#include "EventHandler.h"

class ChangeReplaySpeedEvent;
class StopReplayEvent;
class StartReplayEvent;
class StopRecordingEvent;
class StartRecordingEvent;
class Replay;

class ReplaySystem : public EventHandler
{
public:
	ReplaySystem();

	void onEvent(Event* e) override;
	void handleStartRecording(StartRecordingEvent* e);
	void handleStopRecording(StopRecordingEvent* e);
	void handleStartReplay(StartReplayEvent* e);
	void handleStopReplay(StopReplayEvent* e);
	void handleChangeReplaySpeed(ChangeReplaySpeedEvent* e);

	bool isRecording() { return _isRecording; }
	bool isReplaying() { return _isReplaying; }
	float getReplaySpeed() { return _replaySpeed; }

	Replay* getLastReplay() { return _lastReplay; };
private:
	bool _isRecording;
	bool _isReplaying;
	float _replaySpeed;

	Replay* _lastReplay;
};

