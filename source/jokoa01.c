/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h> 		//nds-rako garatuta dagoen liburutegia
#include <stdio.h>		//c-ko liburutegi estandarra sarrera eta irteerako funtzioak definitzen dituena
#include <stdlib.h>		//c-ko liburutegi estandarra memoria erreserbak eta zenbaki konbertsioak egiteko
#include <unistd.h>		//Sistema eragileen arteko konpatibilitatea ziurtatzeko liburutegia

//Geuk garatutako fitxategiak
	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"
#include "laukia.h"

#define X_OFFSET 113
#define Y_OFFSET 48

#define TILES 9
#define TILE_SIZE 16


void init();
void ikutua(int tx, int ty);
void reset();

int kontagailua;

void jokoa01()
{
	init();
	erakutsiAtea();
	reset();

	while(1)
	{
		touchRead(&PANT_DAT);
		 if(PANT_DAT.px != 0 || PANT_DAT.py != 0)
		 {
		 	int px = PANT_DAT.px;
		 	int py = PANT_DAT.py;

		 	if(px > X_OFFSET && py > Y_OFFSET)
		 	{
		 		int tx = (px - X_OFFSET) / TILE_SIZE;
		 		int ty = (py - Y_OFFSET) / TILE_SIZE;
		
		 		ikutua(tx, ty);
		
			}
			else
			{
				iprintf("\x1b[13;0H                                            ");
			}
		 }

	}
}

bool gitzaDa(int tx, int ty)
{
	return giltza[tx + ty*TILES] == 1;
}

void init()
{
	IME = 1;
	konfiguratuTeklatua(0x00004001);
	konfiguratuTenporizadorea(39322,0x00000042);
	TekEtenBaimendu();
	DenbEtenBaimendu();
	etenZerbErrutEzarri();
}

void reset()
{
	kontagailua = 18;
	for(int i = 0; i<TILES*TILES; i++) piztuta[i] = 0;
}