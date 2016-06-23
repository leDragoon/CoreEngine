#pragma once
#include<Systems.h>

void onGameStart(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene);

void onTick(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene);

void onGameExit(Renderer *renderer, AudioHandler *audioHandler, InputHandler *inputHandler, PhysicsHandler *physicsHandler, ScriptHandler *scriptHandler, Scene *currentScene);
