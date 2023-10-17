#include "main.h"
#include "player.h"
#include "enemy.h"
#include "ecs.h"

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

	InitWindow( windowSize.x, windowSize.y, "ECS Test");
	centerWindow( windowSize, 0 );
	SetTargetFPS( 60 );

	ecsInit();

	playerInit( (Vector2){ 20, 96 } );
	enemyInit( (Vector2){ 720, 300 }, 32.0, 2, RED );
	enemyInit( (Vector2){ 400, 200 }, 16.0, 1, GREEN );

	while ( !WindowShouldClose() ) {
		ecsProcess( GetFrameTime() );

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
			ecsDraw();
			DrawText( "Press Enter to add random entity and Space when player over enemy to remove entity", 10, 10, 20, BLACK );
		EndDrawing();
	}
	CloseWindow();

	ecsFree();

	return 1;
}
