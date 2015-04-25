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
#include "lagungarriak.h"

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
			iprintf("\x1b[4;1HAtea ireki dadin aurrean ikus");
			iprintf("\x1b[5;2Hdezakezun puzzle japoniarra");
			iprintf("\x1b[6;1H(nonograma) bete beharko duzu.");

			iprintf("\x1b[8;2HBehin irudia beteta dagoela");
			iprintf("\x1b[9;4H(kontagailua=0), irudia");
			iprintf("\x1b[10;3Hklikatu ezazu irabazteko.");

			iprintf("\x1b[12;1HOharra: kontagailuak erakusten");
			iprintf("\x1b[13;3Hduen zenbakia, irabazteko");
			iprintf("\x1b[14;2Hzenbat karratu aldatu behar");
			iprintf("\x1b[15;6Hdiren adierazten du.");

			iprintf("\x1b[18;7HKontagailua = %d           ", kontagailua);

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
				
			}
			else
			{
				last_ty = last_tx = -1;
			}
		}
		else if (EGOERA == EGOERA_IRABAZI)
		{
			ezabatu_pantaila();
			iprintf("\x1b[7;4HZorionak, lortu duzu! :D");

			ErlojuaMartxanJarri();
			EGOERA = EGOERA_IRABAZTEN;
		}
		else if (EGOERA == EGOERA_RESET)
		{
			ezabatu_pantaila();
			reset();
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
	int x, y;
	for(x = 0; x<TILES; x++) 
	{
		for(y = 0; y<TILES; y++)
		{
			piztuta[x+y*TILES] = 0;
			EzabatuBeltza(x + y*TILES, X_OFFSET + x * TILE_SIZE, Y_OFFSET +  y * TILE_SIZE);
		}
	}
	EGOERA = EGOERA_BETE_GABE;
	ezabatu_pantaila();
}