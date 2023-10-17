#include "main.h"
#include "ecs.h"

ECS* ecs;

static Entity formatEntity() {
	Entity entity = {
		.id = 0,
		.type = ENTITY_TYPE_NULL,
		.data = NULL,
		.process = NULL,
		.draw = NULL
	};

	return entity;
}

static void checkEntityRealloc( unsigned int id ) {
	if ( id == ecs->entityCount ) {
		ecs->entityCount++;
	}

	if ( ecs->entityCount == ecs->entityAlloc ) {
		ecs->entityAlloc += ALLOC_PAGE_SIZE;
		ecs->entities = realloc( ecs->entities, ecs->entityAlloc * sizeof( Entity ) );

		for ( id = ecs->entityCount; id < ecs->entityAlloc; id++ ) {
			ecs->entities[id] = formatEntity();
		}
	}
}

static unsigned int newEntity() {
	unsigned int id = 0;

	for ( id = 0; id < ecs->entityCount; id++ ) {
		if ( ecs->entities[id].data == NULL ) {
			break;
		}
	}
	checkEntityRealloc( id );

	return id;
}

void ecsInit() {
	ecs = malloc( sizeof( ECS ) );
	ecs->entityCount = 0;
	ecs->entityAlloc = ALLOC_PAGE_SIZE;
	ecs->entities = malloc( ecs->entityAlloc * sizeof( Entity ) );

	for ( unsigned int id = 0; id < ecs->entityAlloc; id++ ) {
		ecs->entities[id] = formatEntity();
	}
}

void ecsAddEntity( Entity entity ) {
	unsigned int id = newEntity();
	entity.id = id;
	ecs->entities[id] = entity;
}

void ecsRemoveEntity( unsigned int id ) {
	if ( id < ecs->entityCount && ecs->entities[id].data != NULL ) {
		free( ecs->entities[id].data );
		ecs->entities[id] = formatEntity();
	}
	else {
		TraceLog( LOG_WARNING, "Trying to remove invalid enemy. ID: %u", id );
	}
}

void ecsProcess( float delta ) {
	for ( unsigned int id = 0; id < ecs->entityCount; id++ ) {
		if ( ecs->entities[id].process != NULL ) {
			ecs->entities[id].process( &ecs->entities[id], delta );
		}
	}
}

void ecsDraw() {
	for ( unsigned int id = 0; id < ecs->entityCount; id++ ) {
		if ( ecs->entities[id].draw != NULL ) {
			ecs->entities[id].draw( &ecs->entities[id] );
		}
	}
}

void ecsFree() {
	for ( unsigned int id = 0; id < ecs->entityCount; id++ ) {
		if ( ecs->entities[id].data != NULL ) {
			free( ecs->entities[id].data );
		}
	}
	free( ecs->entities );
	free( ecs );

	TraceLog( LOG_INFO, "ECS Freed" );
}