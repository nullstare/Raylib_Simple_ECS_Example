#include "main.h"
#include "resources.h"

Resources* res;

static void checkTextureRealloc( int id ) {
	if ( id == res->textureCount ) {
		res->textureCount++;
	}

	if ( res->textureCount == res->textureAlloc ) {
		res->textureAlloc += ALLOC_PAGE_SIZE;
		res->textures = realloc( res->textures, res->textureAlloc * sizeof( Texture ) );
		res->textureNames = realloc( res->textureNames, res->textureAlloc * sizeof( char* ) );

		for ( id = res->textureCount; id < res->textureAlloc; id++ ) {
			res->textures[id] = (Texture){ 0 };
			res->textureNames[id] = NULL;
		}
	}
}

static int newTexture() {
	int id = 0;

	for ( id = 0; id < res->textureCount; id++ ) {
		if ( res->textureNames[id] == NULL ) {
			break;
		}
	}
	checkTextureRealloc( id );

	return id;
}

static void checkAnimationRealloc( int id ) {
	if ( id == res->animCount ) {
		res->animCount++;
	}

	if ( res->animCount == res->animAlloc ) {
		res->animAlloc += ALLOC_PAGE_SIZE;
		res->animations = realloc( res->animations, res->animAlloc * sizeof( SpriteAnimation ) );
		res->animNames = realloc( res->animNames, res->animAlloc * sizeof( char* ) );

		for ( id = res->animCount; id < res->animAlloc; id++ ) {
			res->animations[id] = (SpriteAnimation){ 0 };
			res->animNames[id] = NULL;
		}
	}
}

static int newAnimation() {
	int id = 0;

	for ( id = 0; id < res->animCount; id++ ) {
		if ( res->animNames[id] == NULL ) {
			break;
		}
	}
	checkAnimationRealloc( id );

	return id;
}

void resInit() {
	res = malloc( sizeof( Resources ) );
	/* Textures. */
	res->textureCount = 0;
	res->textureAlloc = ALLOC_PAGE_SIZE;
	res->textures = malloc( res->textureAlloc * sizeof( Texture ) );
	res->textureNames = malloc( res->textureAlloc * sizeof( char* ) );

	for ( int id = 0; id < res->textureAlloc; id++ ) {
		res->textures[id] = (Texture){ 0 };
		res->textureNames[id] = NULL;
	}
	/* Animations. */
	res->animCount = 0;
	res->animAlloc = ALLOC_PAGE_SIZE;
	res->animations = malloc( res->animAlloc * sizeof( SpriteAnimation ) );
	res->animNames = malloc( res->animAlloc * sizeof( char* ) );

	for ( int id = 0; id < res->animAlloc; id++ ) {
		res->animations[id] = (SpriteAnimation){ 0 };
		res->animNames[id] = NULL;
	}
}

void resLoadTexture( const char* path ) {
	int id = newTexture();

	res->textures[id] = LoadTexture( path );
	res->textureNames[id] = malloc( ( TextLength( GetFileNameWithoutExt( path ) ) + 1 ) * sizeof( char ) );
	TextCopy( res->textureNames[id], GetFileNameWithoutExt( path ) );
}

void resLoadAnimation( const char* name, int frameCount, Rectangle* src ) {
	int id = newAnimation();

	res->animations[id] = (SpriteAnimation){
		.frameCount = frameCount,
		.src = malloc( frameCount * sizeof( Rectangle ) ),
	};
	for ( int i = 0; i < frameCount; i++ ) {
		res->animations[id].src[i] = src[i];
	}
	res->animNames[id] = malloc( ( TextLength( name ) + 1 ) * sizeof( char ) );
	TextCopy( res->animNames[id], name );
}

Texture* resGetTexture( const char* name ) {
	for ( int id = 0; id < res->textureCount; id++ ) {
		if ( TextIsEqual( res->textureNames[id], name ) ) {
			return &res->textures[id];
		}
	}
	return NULL;
}

SpriteAnimation* resGetAnimation( const char* name ) {
	for ( int id = 0; id < res->animCount; id++ ) {
		if ( TextIsEqual( res->animNames[id], name ) ) {
			return &res->animations[id];
		}
	}
	return NULL;
}

void resFree() {
	/* Textures. */
	for ( int id = 0; id < res->textureCount; id++ ) {
		if ( res->textureNames[id] != NULL ) {
			free( res->textureNames[id] );
		}
	}
	free( res->textures );
	free( res->textureNames );
	/* Animations. */
	for ( int id = 0; id < res->animCount; id++ ) {
		if ( res->animNames[id] != NULL ) {
			free( res->animations[id].src );
			free( res->animNames[id] );
		}
	}
	free( res->animations );
	free( res->animNames );

	free( res );

	TraceLog( LOG_INFO, "Resources Freed" );
}
