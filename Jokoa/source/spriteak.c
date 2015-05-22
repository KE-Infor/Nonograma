/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		
#include "spriteak.h"
#include "definizioak.h"

u16* gfx_beltza;

void memoriaErreserbatu()
{
	gfx_beltza= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
}

void PaletaNagusiaEzarri() {

	SPRITE_PALETTE[1] = RGB15(0,0,0);
}

u8 beltza[256] = 
{
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,

	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
};

void SpriteakMemorianGorde(){ 
	
int i;
	
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfx_beltza[i] = beltza[i*2] | (beltza[(i*2)+1]<<8);				
	}
}

void ErakutsiBeltza(int indizea, int x, int y)
{ 
 
oamSet(&oamMain,
		indizea,
		x, y,
		0,
		0,
		SpriteSize_16x16,
		SpriteColorFormat_256Color,
		gfx_beltza,
		-1,
		false,
		false,
		false, false,
		false
		); 
	  
oamUpdate(&oamMain);  
}


void EzabatuBeltza(int indizea, int x, int y)
{
	oamSet(&oamMain, 
			indizea,           
			x, y,   
			0,                    
			0,					  
			SpriteSize_16x16,     
			SpriteColorFormat_256Color, 
			gfx_beltza,
			-1,                  
			false,               
			true,			
			false, false, 
			false	
			); 
	oamUpdate(&oamMain); 

}
