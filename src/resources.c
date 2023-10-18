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

void resInit() {
	res = malloc( sizeof( Resources ) );
	res->textureCount = 0;
	res->textureAlloc = ALLOC_PAGE_SIZE;
	res->textures = malloc( res->textureAlloc * sizeof( Texture ) );
	res->textureNames = malloc( res->textureAlloc * sizeof( char* ) );

	for ( int id = 0; id < res->textureAlloc; id++ ) {
		res->textures[id] = (Texture){ 0 };
		res->textureNames[id] = NULL;
	}
}

void resLoadTexture( const char* path ) {
	int id = newTexture();

	res->textures[id] = LoadTexture( path );
	res->textureNames[id] = malloc( TextLength( GetFileNameWithoutExt( path ) + 1 ) * sizeof( char ) );
	TextCopy( res->textureNames[id], GetFileNameWithoutExt( path ) );
}

Texture* resGetTexture( const char* name ) {
	for ( int id = 0; id < res->textureCount; id++ ) {
		if ( TextIsEqual( res->textureNames[id], name ) ) {
			return &res->textures[id];
		}
	}
	return NULL;
}

void resFree() {
	for ( int id = 0; id < res->textureCount; id++ ) {
		if ( res->textureNames[id] != NULL ) {
			free( res->textureNames[id] );
		}
	}
	free( res->textures );
	free( res->textureNames );
	free( res );

	TraceLog( LOG_INFO, "Resources Freed" );
}
