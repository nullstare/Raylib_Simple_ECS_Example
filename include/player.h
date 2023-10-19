#pragma once

#include "entity_system.h"
#include "sprite.h"

#define PLAYER_SPEED 150

typedef struct {
	Vector2 pos;
	float size;
	Sprite sprite;
} Player;

void playerInit( Vector2 pos );
void playerProcess( Entity* entity, float delta );
void playerDraw( Entity* entity );
