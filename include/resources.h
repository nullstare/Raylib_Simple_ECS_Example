#pragma once

typedef struct {
	int frameCount;
	Rectangle* src;
} SpriteAnimation;

typedef struct {
	/* Textures. */
	int textureCount;
	int textureAlloc;
	Texture* textures;
	char** textureNames;
	/* SpriteAnimations. */
	int animCount;
	int animAlloc;
	SpriteAnimation* animations;
	char** animNames;
} Resources;

extern Resources* res;

void resInit();
void resLoadTexture( const char* path );
void resLoadAnimation( const char* name, int frameCount, Rectangle* src );
Texture* resGetTexture( const char* name );
SpriteAnimation* resGetAnimation( const char* name );
void resFree();
