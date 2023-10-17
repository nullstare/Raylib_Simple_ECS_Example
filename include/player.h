#pragma once

#include "ecs.h"

#define PLAYER_SPEED 150

typedef struct {
	Vector2 pos;
	float size;
} Player;

void playerInit( Vector2 pos );
void playerProcess( Entity* entity, float delta );
void playerDraw( Entity* entity );
