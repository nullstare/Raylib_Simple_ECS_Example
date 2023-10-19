#include "main.h"
#include "entity_system.h"
#include "player.h"
#include "enemy.h"
#include "resources.h"

void playerInit( Vector2 pos ) {
	Player* player = malloc( sizeof( Player ) );

	*player = (Player){
		.pos = pos,
		.size = 32,
		.sprite = (Sprite){
			.texture = resGetTexture( "player" ),
			.animation = resGetAnimation( "idle" ),
			.animPos = 0.0
		}
	};
	esAddEntity( (Entity){
		.data = player,
		.type = ENTITY_TYPE_PLAYER,
		.process = playerProcess,
		.draw = playerDraw
	} );
}

void playerProcess( Entity* entity, float delta ) {
	Player* player = (Player*)entity->data;

	/* Movement. */
	if ( IsKeyDown( KEY_RIGHT ) ) {
		player->pos.x += PLAYER_SPEED * delta;
	}
	else if ( IsKeyDown( KEY_LEFT ) ) {
		player->pos.x -= PLAYER_SPEED * delta;
	}

	if ( IsKeyDown( KEY_DOWN ) ) {
		player->pos.y += PLAYER_SPEED * delta;
	}
	else if ( IsKeyDown( KEY_UP ) ) {
		player->pos.y -= PLAYER_SPEED * delta;
	}

	bool spacePressed = IsKeyPressed( KEY_SPACE );

	/* Check to destroy enemy. */
	for ( int i = 0; i < es->entityCount; i++ ) {
		if ( es->entities[i].type == ENTITY_TYPE_ENEMY ) {
			Enemy* enemy = (Enemy*)es->entities[i].data;

			if ( CheckCollisionCircleRec( enemy->pos, enemy->radius,
			(Rectangle){ player->pos.x, player->pos.y, player->size, player->size } ) ) {
				enemy->sprite.animation = resGetAnimation( "angry" );

				if ( spacePressed ) {
					esRemoveEntity( i );
				}
			}
			else {
					enemy->sprite.animation = resGetAnimation( "idle" );
			}
		}
	}
}

void playerDraw( Entity* entity ) {
	Player* player = (Player*)entity->data;

	if ( player->sprite.animation != NULL ) {
		spriteDraw(
			&player->sprite,
			(Rectangle){
				player->pos.x,
				player->pos.y,
				player->sprite.texture->width,
				player->sprite.texture->height
			},
			BLUE
		);
	}
	else {
		DrawRectangle( player->pos.x, player->pos.y, player->size, player->size, BLUE );
		TraceLog( LOG_WARNING, "Player Sprite animation is NULL" );
	}
	DrawText( TextFormat( "Player ID: %d", entity->id ), player->pos.x - 32, player->pos.y - 22, 20, BLACK );
}
