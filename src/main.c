#include "main.h"
#include "player.h"
#include "enemy.h"
#include "entity_system.h"
#include "resources.h"

static void centerWindow( Vector2 windowSize, int monitor ) {
	Vector2 monitorSize = (Vector2){ GetMonitorWidth( monitor ), GetMonitorHeight( monitor ) };
	Vector2 monitorPos = GetMonitorPosition( monitor );

	SetWindowPosition(
		monitorPos.x + monitorSize.x / 2 - windowSize.x / 2,
		monitorPos.y + monitorSize.y / 2 - windowSize.y / 2
	);
}

int main() {
	Vector2 windowSize = (Vector2){ 1024, 720 };

	InitWindow( windowSize.x, windowSize.y, "Entity System Test");
	centerWindow( windowSize, 0 );
	SetTargetFPS( 60 );

	esInit();
	resInit();

	resLoadTexture( "../images/player.png" );
	resLoadTexture( "../images/enemy.png" );

	Rectangle idle[1] = { { 0.0, 0.0, 32.0, 32.0 } };
	resLoadAnimation( "idle", 1, idle );
	Rectangle angry[2] = { { 0.0, 0.0, 32.0, 32.0 }, { 32.0, 0.0, 32.0, 32.0 } };
	resLoadAnimation( "angry", 2, angry );

	playerInit( (Vector2){ 20, 96 } );
	enemyInit( (Vector2){ 720, 300 }, 32.0, 2, RED );
	enemyInit( (Vector2){ 400, 200 }, 16.0, 1, GREEN );

	while ( !WindowShouldClose() ) {
		esProcess( GetFrameTime() );

		/* Add random enemy entity. */
		if ( IsKeyPressed( KEY_ENTER ) ) {
			enemyInit(
				(Vector2){ GetRandomValue( 0, windowSize.x ), GetRandomValue( 0, windowSize.y ) },
				(float)GetRandomValue( 4, 64 ),
				(float)GetRandomValue( 1, 10 ),
				(Color){
					GetRandomValue( 0, 255 ),
					GetRandomValue( 0, 255 ),
					GetRandomValue( 0, 255 ),
					255
				}
			);
		}

		BeginDrawing();
			ClearBackground( RAYWHITE );
			esDraw();
			DrawText( "Press Enter to add random entity and Space when player over enemy to remove entity", 10, 10, 20, BLACK );
		EndDrawing();
	}
	CloseWindow();

	esFree();
	resFree();

	return 1;
}
