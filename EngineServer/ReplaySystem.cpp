#include "ReplaySystem.h"
#include "EventManager.h"
#include "StartRecordingEvent.h"
#include "StopRecordingEvent.h"
#include "StartReplayEvent.h"
#include "StopReplayEvent.h"
#include "Replay.h"
#include "ChangeReplaySpeedEvent.h"

ReplaySystem::ReplaySystem()
{
	_isReplaying = false;
	_isRecording = false;
	_lastReplay = nullptr;
	_replaySpeed = 1.0f;
	
	EventManager::getInstance()->registerFor(this, "START_REC");
	EventManager::getInstance()->registerFor(this, "STOP_REC");
	EventManager::getInstance()->registerFor(this, "START_REP");
	EventManager::getInstance()->registerFor(this, "STOP_REP");
	EventManager::getInstance()->registerFor(this, "REP_SPEED");
}

void ReplaySystem::onEvent(Event* e)
{
	if (e->getType() == "START_REC")
	{
		handleStartRecording(static_cast<StartRecordingEvent*>(e));
	}
	else if (e->getType() == "STOP_REC")
	{
		handleStopRecording(static_cast<StopRecordingEvent*>(e));
	}
	else if (e->getType() == "START_REP")
	{
		handleStartReplay(static_cast<StartReplayEvent*>(e));
	}
	else if (e->getType() == "STOP_REP")
	{
		handleStopReplay(static_cast<StopReplayEvent*>(e));
	}
	else if (e->getType() == "REP_SPEED")
	{
		handleChangeReplaySpeed(static_cast<ChangeReplaySpeedEvent*>(e));
	}
}

void ReplaySystem::handleStartRecording(StartRecordingEvent* e)
{
	_isRecording = true;
	_lastReplay = e->replay;
}

void ReplaySystem::handleStopRecording(StopRecordingEvent* e)
{
	_isRecording = false;
	EventManager::getInstance()->raiseEvent(new StartReplayEvent(_lastReplay->getInitialEntitiesState()));
}

void ReplaySystem::handleStartReplay(StartReplayEvent* e)
{
	_isReplaying = true;
	_replaySpeed = 1.0f;
}

void ReplaySystem::handleStopReplay(StopReplayEvent* e)
{
	_isReplaying = false;
}

void ReplaySystem::handleChangeReplaySpeed(ChangeReplaySpeedEvent* e)
{
	_replaySpeed *= e->speed;
	if (_replaySpeed > 2.0) _replaySpeed = 2.0;
	if (_replaySpeed < 0.5) _replaySpeed = 0.5;
}

