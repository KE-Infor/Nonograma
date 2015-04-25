
void ezabatu_lerroa(int y)
{
	iprintf("\x1b[%d;0H                                ", y);
}

void ezabatu_pantaila()
{
	int i;
	for(i = 0; i<24; i++)
	{
		ezabatu_lerroa(i);
	}
}

void ezabatu_pantaila_ezik(int y)
{
	int i;
	for(i = 0; i<24; i++)
	{
		if(i != y) ezabatu_lerroa(i);
	}
}