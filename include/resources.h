#pragma once

typedef struct {
	int textureCount;
	int textureAlloc;
	Texture* textures;
	char** textureNames;
} Resources;

extern Resources* res;

void resInit();
void resLoadTexture( const char* path );
Texture* resGetTexture( const char* name );
void resFree();
