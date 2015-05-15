/*-------------------------------------
periferikoak.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definizioak.h"
#include "periferikoak.h"
#include "fondoak.h"
#include "spriteak.h"
#include "egoerak.h"
#include "lagungarriak.h"

void tekEten ()
{
	if (SakatutakoTekla()==A && EGOERA == EGOERA_IRABAZTEN)
	{
		EGOERA = EGOERA_RESET;
	}
}

void tenpEten()
{
	static int tik=0;
	static int seg=0;
	if (EGOERA==EGOERA_IRABAZTEN)
	{
		iprintf("\x1b[11;5HJokoa berriro hasteko");
		iprintf("\x1b[12;8HA tekla pultsatu");
		iprintf("\x1b[13;4Hedo %02d segundu itxaron.", 10-seg);

		tik++;
		if (tik==5)
		{
			seg++;
			tik=0;
			if (seg==10)
			{
				EGOERA = EGOERA_RESET;
				seg = 0;
			}				
		}
	}
	else
	{
		ezabatu_lerroa(9);
		ezabatu_lerroa(10);
	}
}

void etenZerbErrutEzarri()
{
	irqSet(IRQ_KEYS, tekEten);
	irqSet(IRQ_TIMER0, tenpEten);
}
