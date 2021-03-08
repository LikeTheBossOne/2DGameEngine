#pragma once
#include <string>
#include "duktape.h"
#include <vector>
#include <unordered_map>
#include "ScriptReturnValue.h"

class ScriptManager
{
public:
	~ScriptManager();
	static ScriptManager* getInstance();

	void registerScript(std::string name, std::string fileName, std::string functionName);
	void run(std::string script, std::vector<Parameter*>& parameters, ScriptReturnValue* retVal, duk_context* ctx = nullptr);
	
	duk_context* getContext() { return _context; }
private:
	ScriptManager();
	static ScriptManager* _instance;

	duk_context* _context;
	
	std::unordered_map<std::string, std::pair<std::string, std::string>> _scriptsToFileFuncName;
};
