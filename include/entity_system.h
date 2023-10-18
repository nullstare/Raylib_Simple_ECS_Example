#pragma once

enum EntityTypes{
	ENTITY_TYPE_NULL,
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_ENEMY
};

typedef struct Entity Entity;

struct Entity {
	int id;
	int type;
	void* data;
	void (*process)( Entity* entity, float delta );
	void (*draw)( Entity* entity );
};

typedef struct {
	int entityCount;
	int entityAlloc;
	Entity* entities;
} EntitySystem;

extern EntitySystem* es;

void esInit();
void esAddEntity( Entity entity );
void esRemoveEntity( int id );
void esProcess( float delta );
void esDraw();
void esFree();
