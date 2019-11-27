#include "ScriptManager.h"
#include <iostream>
#include "dukglue/dukglue.h"
#include "TransformComponent.h"
#include "MovementComponent.h"
#include "JumpComponent.h"
#include "IntParameter.h"
#include "NumberParameter.h"
#include "StringParameter.h"
#include "TransformComponentParameter.h"
#include "MovementComponentParameter.h"
#include "JumpComponentParameter.h"
#include "DeathEventParameter.h"
#include "EventManagerParameter.h"
#include "DeathEvent.h"
#include "EventManager.h"
#include "GameObject.h"
#include "SpawnEvent.h"

ScriptManager* ScriptManager::_instance;

void ScriptManager::registerScript(std::string name, std::string fileName, std::string functionName)
{
	_scriptsToFileFuncName[name] =  std::pair<std::string, std::string>(fileName, functionName);
}

static void push_file_as_string(duk_context* ctx, const char* filename) {
	FILE* f;
	size_t len;
	char buf[4096];

	f = fopen(filename, "rb");
	if (f) {
		len = fread((void*)buf, 1, sizeof(buf), f);
		fclose(f);
		duk_push_lstring(ctx, (const char*)buf, (duk_size_t)len);
	}
	else {
		duk_push_undefined(ctx);
	}
}

void ScriptManager::run(std::string script, std::vector<Parameter*>& parameters, ScriptReturnValue* retVal, duk_context* ctx)
{
	if (ctx == nullptr)
	{
		ctx = _context;
	}
	const auto pair = _scriptsToFileFuncName[script];
	const auto filename = pair.first;
	const auto functionName = pair.second;

	if (!ctx) { exit(1); }

	push_file_as_string(ctx, filename.c_str());
	if (duk_peval(ctx) != 0) {
		printf("Error: %s\n", duk_safe_to_string(ctx, -1));
		exit(1);
	}
	duk_pop(ctx);  /* ignore result */

	duk_push_global_object(ctx);

	duk_get_prop_string(ctx, -1, functionName.c_str());

	// Add parameters
	for (Parameter* parameter : parameters)
	{
		switch (parameter->getType())
		{
		case ParameterType::INTEGER:
			duk_push_int(ctx, static_cast<IntParameter*>(parameter)->value);
			break;
		case ParameterType::NUMBER:
			duk_push_number(ctx, static_cast<NumberParameter*>(parameter)->value);
			break;
		case ParameterType::STRING:
			duk_push_string(ctx, static_cast<StringParameter*>(parameter)->value.c_str());
			break;
		case ParameterType::TRANSFORM_COMPONENT:
			dukglue_push(ctx, static_cast<TransformComponentParameter*>(parameter)->value);
			break;
		case ParameterType::MOVEMENT_COMPONENT:
			dukglue_push(ctx, static_cast<MovementComponentParameter*>(parameter)->value);
			break;
		case ParameterType::JUMP_COMPONENT:
			dukglue_push(ctx, static_cast<JumpComponentParameter*>(parameter)->value);
			break;
		case ParameterType::DEATH_EVENT:
			dukglue_push(ctx, static_cast<DeathEventParameter*>(parameter)->value);
			break;
		case ParameterType::EVENT_MANAGER:
			dukglue_push(ctx, static_cast<EventManagerParameter*>(parameter)->value);
			break;
		default:
			break;
		}
	}
	duk_call(ctx, parameters.size());

	switch (retVal->type)
	{
	case ParameterType::INTEGER:
		static_cast<IntParameter*>(retVal->value)->value = duk_get_int(ctx, -1);
		break;
	case ParameterType::NUMBER:
		static_cast<NumberParameter*>(retVal->value)->value = duk_get_number(ctx, -1);
		break;
	case ParameterType::STRING:
		static_cast<StringParameter*>(retVal->value)->value = std::string(duk_get_string(ctx, -1));
		break;
	case ParameterType::NONE:
		
		break;
	default:
		break;
	}
	// duk_pop(ctx);
}

ScriptManager::~ScriptManager()
{
	duk_destroy_heap(_context);
}

ScriptManager* ScriptManager::getInstance()
{
	if (_instance == nullptr)
	{
		_instance = new ScriptManager();
	}
	return _instance;
}

ScriptManager::ScriptManager()
{
	_scriptsToFileFuncName = std::unordered_map <std::string, std::pair<std::string, std::string>>();

	_context = duk_create_heap_default();
	
}
