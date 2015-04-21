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

void tekEten ()
{
	if (SakatutakoTekla()==A && EGOERA == EGOERA_IRABAZI)
	{
		EGOERA = EGOERA_RESET;
	}
}

void tenpEten()
{
	static int tik=0;
	static int seg=0;
	if (EGOERA==EGOERA_IRABAZI)
	{
		tik++;
		if (tik==5)
		{
			seg ++;
			tik=0;
			if (seg==3)
			{
				EGOERA = EGOERA_RESET;
			}				
		}
	}
}

void etenZerbErrutEzarri()
{
	irqSet(IRQ_KEYS, tekEten);
	irqSet(IRQ_TIMER0, tenpEten);
}

