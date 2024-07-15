#include "base.h"
#include "thefont.h"

void drawbitmap(const byte* ptr, word offset, byte width, byte height)
{
	word x;
	word y;
	word i = 0;
	word j = 0;
	for(y = 0; y < offset; y++)
	{
		++j;
		if((j&0x1f) == 0x18)
		{
			j += 0x8;
		}
	}
	
	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{	
			deref(0xf800+j) = ptr[i];
			++j;
			if((j&0x1f) == 0x18)
			{
				j += 0x8;
			}
			++i;
		}
		j += 32-width;
		if((j&0x1f) == 0x18)
		{
			j += 0x8;
		}
	}
}



void print(const byte* str, word x, word y)
{
	const byte* what = str;
	word curoffset = x+y*384;
	byte* charptr;
	word i = 0;
	while(*what)
	{
		charptr = image_raw;
		charptr += ((word)(*what)<<4);
		drawbitmap(charptr,curoffset,1,16);
		++curoffset;
		++what;
	}
}

void main()
{
	word i = 0;
	//const byte why[] = {'H','e','l','l','o','\x00'};
	const byte why[] = "Hello world!";
	deref(0xf030) = 4;
	deref(0xf031) = 0x55;
	deref(0xf032) = 0x12;
	deref(0xf033) = 0x03;
	deref(0xf034) = 0x06;
	deref(0xf035) = 0x17;
	deref(0xf036) = 8;
	deref(0xf037) = 0x04;
	deref(0xf039) = 0;
	deref(0xf03d) = 0x07;
	
	while(1)
	{
		//deref(0xF046) = 0xff;
		//drawbitmap(image_raw+(i&0xfff),i&0x1ff,1,16);
		//i += 1;
		print(why,0,0);
	}
	/*
	deref(0xf037) = 0;
	for(i = 0; i < 2048; i++)
	{
		deref(0xf800+i) = 0x3c;
	}
	*/
}