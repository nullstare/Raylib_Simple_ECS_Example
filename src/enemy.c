#include "main.h"
#include "entity_system.h"
#include "enemy.h"

void enemyInit( Vector2 pivot, float radius, float speed, Color color ) {
	Enemy* enemy = malloc( sizeof( Enemy ) );

	*enemy = (Enemy){
		.pivot = pivot,
		.pos = pivot,
		.radius = radius,
		.phase = 0.0,
		.speed = speed,
		.color = color
	};

	esAddEntity( (Entity){
		.data = enemy,
		.type = ENTITY_TYPE_ENEMY,
		.process = enemyProcess,
		.draw = enemyDraw
	} );
}

void enemyProcess( Entity* entity, float delta ) {
	Enemy* enemy = (Enemy*)entity->data;

	/* Circle around pivot. */
	enemy->phase += delta * enemy->speed;
	enemy->pos = (Vector2){
		enemy->pivot.x + cosf( enemy->phase ) * enemy->radius,
		enemy->pivot.y + sinf( enemy->phase ) * enemy->radius
	};
}

void enemyDraw( Entity* entity ) {
	Enemy* enemy = (Enemy*)entity->data;
	
	DrawCircle( enemy->pos.x, enemy->pos.y, enemy->radius, enemy->color );
	DrawText( TextFormat( "ID: %d", entity->id ), enemy->pos.x - 10, enemy->pos.y - 22 - enemy->radius, 20, BLACK );
}
