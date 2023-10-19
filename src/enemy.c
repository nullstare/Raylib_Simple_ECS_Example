#include "main.h"
#include "entity_system.h"
#include "resources.h"
#include "player.h"
#include "enemy.h"

void enemyInit( Vector2 pivot, float radius, float speed, Color color ) {
	Enemy* enemy = malloc( sizeof( Enemy ) );

	*enemy = (Enemy){
		.pivot = pivot,
		.pos = pivot,
		.radius = radius,
		.phase = 0.0,
		.speed = speed,
		.color = color,
		.sprite = (Sprite){
			.texture = resGetTexture( "enemy" ),
			.animation = resGetAnimation( "idle" ),
			.animPos = 0.0
		}
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
	spriteProcess( &enemy->sprite, delta * enemy->speed );
}

void enemyDraw( Entity* entity ) {
	Enemy* enemy = (Enemy*)entity->data;
	
	if ( enemy->sprite.animation != NULL ) {
		spriteDraw(
			&enemy->sprite,
			(Rectangle){
				enemy->pos.x - enemy->radius,
				enemy->pos.y - enemy->radius,
				enemy->radius * 2,
				enemy->radius * 2
			},
			enemy->color
		);
	}
	else {
		DrawCircle( enemy->pos.x, enemy->pos.y, enemy->radius, enemy->color );
		TraceLog( LOG_WARNING, "Enemy Sprite animation is NULL" );
	}
	DrawText( TextFormat( "ID: %d", entity->id ), enemy->pos.x - 10, enemy->pos.y - 22 - enemy->radius, 20, BLACK );
}
