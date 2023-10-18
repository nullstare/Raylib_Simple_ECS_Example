#pragma once

#include "entity_system.h"

typedef struct {
	Vector2 pivot;
	Vector2 pos;
	float radius;
	float phase;
	float speed;
	Color color;
	Texture* texture;
} Enemy;

void enemyInit( Vector2 pivot, float radius, float speed, Color color );
void enemyProcess( Entity* entity, float delta );
void enemyDraw( Entity* entity );
