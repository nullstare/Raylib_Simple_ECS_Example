#include "main.h"
#include "resources.h"
#include "sprite.h"

void spriteDraw( Sprite* sprite, Rectangle dst, Color color ) {
	int frame = floor( Lerp( 0.0, (float)sprite->animation->frameCount, sprite->animPos ) );

	Rectangle src = sprite->animation->src[ frame ];

	DrawTexturePro(
		*sprite->texture,
		src,
		dst,
		(Vector2){ 0.0, 0.0 },
		0.0,
		color
	);
}

void spriteProcess( Sprite* sprite, float delta ) {
	sprite->animPos += delta;

	if ( 1.0 < sprite->animPos ) {
		sprite->animPos -= 1.0;
	}
}
