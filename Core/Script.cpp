#include "Script.h"

void ScriptHandler::update()
{

}

void ScriptHandler::sendEvent(Event toSend)
{
	eventsSet.push_back(toSend);
}

void ScriptHandler::addScriptFromFile(string name, string path)
{
	luaL_dofile(L, path.c_str());
}

void ScriptHandler::addScriptToObject(string objectName, string scriptName)
{

}

ScriptChanges ScriptHandler::getScriptChanges()
{
	return changes;
}

ScriptHandler::ScriptHandler()
{
	luaL_openlibs(L);
}
