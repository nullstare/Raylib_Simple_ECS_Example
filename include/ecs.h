#pragma once

#define ALLOC_PAGE_SIZE 32

enum EntityTypes{
	ENTITY_TYPE_NULL,
	ENTITY_TYPE_PLAYER,
	ENTITY_TYPE_ENEMY
};

typedef struct Entity Entity;

struct Entity {
	unsigned int id;
	int type;
	void* data;
	void (*process)( Entity* entity, float delta );
	void (*draw)( Entity* entity );
};

typedef struct {
	int entityCount;
	int entityAlloc;
	Entity* entities;
} ECS;

extern ECS* ecs;

void ecsInit();
void ecsAddEntity( Entity entity );
void ecsRemoveEntity( unsigned int id );
void ecsProcess( float delta );
void ecsDraw();
void ecsFree();
