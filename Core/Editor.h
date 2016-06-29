#pragma once
#include<Systems.h>

void onEditorStart(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene);

void onEditorTick(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene);

void onEditorExit(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene);
