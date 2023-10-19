#pragma once

#include "resources.h"

typedef struct {
	Texture* texture;
	SpriteAnimation* animation;
	float animPos;
} Sprite;

void spriteDraw( Sprite* sprite, Rectangle dst, Color color );
void spriteProcess( Sprite* sprite, float delta );
