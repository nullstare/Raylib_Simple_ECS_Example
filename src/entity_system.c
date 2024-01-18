#include "main.h"
#include "entity_system.h"

EntitySystem* es;

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

static void checkEntityRealloc( int id ) {
	if ( id == es->entityCount ) {
		es->entityCount++;
	}

	if ( es->entityCount == es->entityAlloc ) {
		es->entityAlloc += ALLOC_PAGE_SIZE;
		es->entities = realloc( es->entities, es->entityAlloc * sizeof( Entity ) );

		for ( id = es->entityCount; id < es->entityAlloc; id++ ) {
			es->entities[id] = formatEntity();
		}
	}
}

static int newEntity() {
	int id = 0;

	for ( id = 0; id < es->entityCount; id++ ) {
		if ( es->entities[id].data == NULL ) {
			break;
		}
	}
	checkEntityRealloc( id );

	return id;
}

void esInit() {
	es = malloc( sizeof( EntitySystem ) );
	es->entityCount = 0;
	es->entityAlloc = ALLOC_PAGE_SIZE;
	es->entities = malloc( es->entityAlloc * sizeof( Entity ) );

	for ( int id = 0; id < es->entityAlloc; id++ ) {
		es->entities[id] = formatEntity();
	}
}

void esAddEntity( Entity entity ) {
	int id = newEntity();
	entity.id = id;
	es->entities[id] = entity;
}

void esRemoveEntity( int id ) {
	if ( id < es->entityCount && es->entities[id].data != NULL ) {
		free( es->entities[id].data );
		es->entities[id] = formatEntity();
	}
	else {
		TraceLog( LOG_WARNING, "Trying to remove invalid enemy. ID: %u", id );
	}
}

void esProcess( float delta ) {
	for ( int id = 0; id < es->entityCount; id++ ) {
		if ( es->entities[id].process != NULL ) {
			es->entities[id].process( &es->entities[id], delta );
		}
	}
}

void esDraw() {
	for ( int id = 0; id < es->entityCount; id++ ) {
		if ( es->entities[id].draw != NULL ) {
			es->entities[id].draw( &es->entities[id] );
		}
	}
}

void esFree() {
	for ( int id = 0; id < es->entityCount; id++ ) {
		if ( es->entities[id].data != NULL ) {
			free( es->entities[id].data );
		}
	}
	free( es->entities );
	free( es );

	TraceLog( LOG_INFO, "Entity System Freed" );
}