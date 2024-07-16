#include "base.h"
#include "thefont.h"

void drawbitmap(const byte* ptr, word offset, byte width, byte height,int color)
{
	word x;
	word y;
	word i = 0;
	word j = 0;
	deref(0xF037) = 0;
	if(color == 1)
	{
		deref(0xF037) = 4;
	} 
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
			if(color == 2)
			{
				deref(0xF037) = 0;
				deref(0xf800+j) = ptr[i];
				deref(0xF037) = 4;
			}
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



void print(const byte* str, word x, word y,int color)
{
	const byte* what = str;
	word curoffset = x+(y<<8)+(y<<7);
	//word i = 0;
	//derefw(0xB510) = (word)(what);
	while(*what)
	{
		//deref(0xB500+i) = *what;

		drawbitmap(image_raw+((word)(*what)<<4),curoffset,1,16,color);
		++curoffset;
		++what;
		//++i;
	}
}



const byte why[] = "Hello world!";
void CheckButtons()
{
	byte x;
	byte y;
	char b[] = "a";
	for(x = 0x80; x != 0; x = x >> 1)
	{
		deref(0xf046) = x;
		for(y = 0x80; y != 0; y = y >> 1)
		{
			if((deref(0xf040) & y) == 0)
			{
				b[0] = y;
				print(b,0,1,2);
				b[0] = x;
				print(b,0,2,2);
				break;
			}
		}
	}
}


void main()
{
	word i = 0;
	//const byte why[] = {'H','e','l','l','o','\x00'};
	
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
	
	//while(1) //I dont think this is needed for a signle print... 
	//{
		print(why,0,0,2);
		//CheckButtons();

		//drawbitmap(image_raw+(i&0xfff),i&0x1ff,1,16);
		//i += 1;
	//}
	/*
	deref(0xf037) = 0;
	for(i = 0; i < 2048; i++)
	{
		deref(0xf800+i) = 0x3c;
	}
	*/
}
