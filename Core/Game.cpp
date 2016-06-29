#include "Game.h"

void onGameStart(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene, bool editMode)
{
	if (editMode)
	{
		onEditorStart(renderer, audioHandler, inputHandler, physicsHandler, scriptHandler, currentScene);
	}
}

void onTick(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene, bool editMode)
{
	if (editMode)
	{
		onEditorTick(renderer, audioHandler, inputHandler, physicsHandler, scriptHandler, currentScene);
	}
}

void onGameExit(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene, bool editMode)
{
	if (editMode)
	{
		onEditorExit(renderer, audioHandler, inputHandler, physicsHandler, scriptHandler, currentScene);
	}
}
