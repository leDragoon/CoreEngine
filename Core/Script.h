#pragma once
#include<string>
#include<vector>
#include<Util.h>
#include<FileManager.h>
#include<lua.hpp>
#include<lualib.h>
#include<lauxlib.h>
#include<LuaBridge.h>

using std::string;
using std::vector;
using namespace luabridge;

struct Event
{
	string name;
	string sender;
	string target;
	string message;
};

struct ScriptChanges
{
	vector<string> names;
	vector<string> changes;
};

struct ScriptConditional
{
	vector<string> variableNames;
	vector<string> comparisons;
	vector<string> contents;
};

struct Script
{
	string name;
	vector<string> triggerEvents;
	vector<string> scriptContents;
	vector<ScriptConditional> conditionals;
};

class ScriptHandler
{
private:
	lua_State *L = luaL_newstate();
	ScriptChanges changes;
	vector<Event> eventsSet;
public:
	void update();
	void sendEvent(Event toSend);
	void addScriptFromFile(string name, string path);
	void addScriptToObject(string objectName, string scriptName);
	ScriptChanges getScriptChanges();
	ScriptHandler();
};