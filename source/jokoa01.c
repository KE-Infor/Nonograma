/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

	
#include "definizioak.h"
#include "periferikoak.h"
#include "zerbitzuErrutinak.h"
#include "fondoak.h"
#include "laukia.h"
#include "spriteak.h"
#include "egoerak.h"

#define X_OFFSET 112
#define Y_OFFSET 48

#define TILES 9
#define TILE_SIZE 16


void init();
void reset();
bool giltza_da(int tx, int ty);
bool piztuta_dago(int tx, int ty);
void karratua_klikatu(int tx, int ty);

int last_tx = -1, last_ty = -1;

int kontagailua;

void jokoa01()
{
	init();
	erakutsiAtea();
	reset();

	while(1)
	{
		if(EGOERA == EGOERA_BETE_GABE || EGOERA == EGOERA_BETETA)
		{
			touchRead(&PANT_DAT);
			if((PANT_DAT.px != 0 || PANT_DAT.py != 0))
			{
			 	int px = PANT_DAT.px;
			 	int py = PANT_DAT.py;

			 	if(px > X_OFFSET && py > Y_OFFSET)
			 	{
			 		int tx = (px - X_OFFSET) / TILE_SIZE;
			 		int ty = (py - Y_OFFSET) / TILE_SIZE;
			 		if (tx != last_tx || ty != last_ty)
			 		{
			 			if (EGOERA == EGOERA_BETE_GABE)
			 			{
				 			karratua_klikatu(tx, ty);
				 			last_tx = tx;
				 			last_ty = ty;
			 			}
				 		else if (EGOERA == EGOERA_BETETA && giltza_da(tx, ty))
				 		{
				 			EGOERA = EGOERA_IRABAZI;
				 		}
			 		}
				}
				iprintf("\x1b[15;5H  Kontagailua=%d           ", kontagailua);
			}
			else
			{
				last_ty = last_tx = -1;
			}
		}
		else if (EGOERA == EGOERA_IRABAZI)
		{
			iprintf("\x1b[15;5H                            "); // Kontagailua borratu
			iprintf("\x1b[7;0H    Zorionak, lortu duzu!  :D");
		}
	}
}

bool giltza_da(int tx, int ty)
{
	return giltza[tx + ty*TILES] == 1;
}

bool piztuta_dago(int tx, int ty)
{
	return piztuta[tx + ty*TILES] == 1;
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

void aldatu_karratua(int tx, int ty)
{
	piztuta[tx + ty*TILES] = piztuta[tx + ty*TILES] == 1 ? 0 : 1;
	if(piztuta_dago(tx, ty))
	{
		ErakutsiBeltza(tx + ty*TILES, X_OFFSET + tx * TILE_SIZE, Y_OFFSET +  ty * TILE_SIZE);
	}
	else
	{
		EzabatuBeltza(tx + ty*TILES, X_OFFSET + tx * TILE_SIZE, Y_OFFSET +  ty * TILE_SIZE);
	}
}

void karratua_klikatu(int tx, int ty)
{

	aldatu_karratua(tx, ty);

	if (giltza_da(tx, ty) != !piztuta_dago(tx, ty))
	{
		kontagailua--;
	}
	else
	{
		kontagailua++;
	}

	if(kontagailua == 0)
	{
		EGOERA = EGOERA_BETETA;
	}
}

void reset()
{
	kontagailua = 18;
	int i;
	for(i = 0; i<TILES*TILES; i++) piztuta[i] = 0;
	EGOERA = EGOERA_BETE_GABE;
}