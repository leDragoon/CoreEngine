#pragma once
#include<Systems.h>
#include<Editor.h>

void onGameStart(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene, bool editMode);

void onTick(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene, bool editMode);

void onGameExit(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene, bool editMode);
