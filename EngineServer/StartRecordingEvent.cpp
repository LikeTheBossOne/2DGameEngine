#include "StartRecordingEvent.h"

StartRecordingEvent::StartRecordingEvent(Replay* replay) : Event(1, 0)
{
	this->replay = replay;
}
