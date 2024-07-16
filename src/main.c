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



word print(const byte* str, byte x, byte y,byte color)
{
	const byte* what = str;
	word curoffset = (word)x+((word)y<<8)+((word)y<<7);
	//derefw(0xB510) = (word)(what);
	word i = 0;
	while(*what)
	{
		//deref(0xB500+i) = *what;

		drawbitmap(image_raw+((word)(*what)<<4),curoffset,1,16,color);
		++curoffset;
		++what;
		++i;
		//++i;
	}
	return i;
}

char printdwordbuf[5] = "\x00\x00\x00\x00";

void PrintWord(word num, byte x, byte y, byte color)
{
	byte luup = 0;
	byte* out = &printdwordbuf[3];
	for(luup = 0; luup < 3; luup++)
	{
		if((num&0xf) > 0x9)
		{
			*out = 'a'+(num&0xf)-0xa;
		}
		else
		{
			*out = '0'+(num&0xf);
		}
		num = num>>4;
		if(!num)
		{
			print(out,x,y,color);
			return;
		}
		out--;
	}
	if((num&0xf) > 0x9)
	{
		*out = 'a'+(num&0xf)-0xa;
	}
	else
	{
		*out = '0'+(num&0xf);
	}
	print(out,x,y,color);
}

enum BUTTON
{
	B_0 = 0xb,
	B_1 = 0x3f,
	B_2 = 0x37,
	B_3 = 0x2f,
	B_4 = 0x3e,
	B_5 = 0x36,
	B_6 = 0x2e,
	B_7 = 0x3d,
	B_8 = 0x35,
	B_9 = 0x2d
};

const byte button_to_char[64] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0, '0',   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0,   0,   0, '9', '6', '3',
	0,   0,   0,   0,   0, '8', '5', '2',
	0,   0,   0,   0,   0, '7', '4', '1',
};

byte tempprintpos = 0;

void CheckButtons()
{
	byte x;
	byte y;
	byte b[] = "0";
	byte x2 = 0;
	byte y2;
	byte i = 0;
	for(x = 0x80; x != 0; x = x >> 1)
	{
		deref(0xf046) = x;
		y2 = 0;
		for(y = 0x80; y != 0; y = y >> 1)
		{
			if((deref(0xf040) & y) == 0)
			{
				b[0] = button_to_char[i];
				tempprintpos += print(b,tempprintpos,0,2);
				b[0] = '0'+x2;
				print(b,0,1,2);
				b[0] = '0'+y2;
				print(b,0,2,2);
				print("  ",0,3,2);
				PrintWord(i,0,3,2);
				break;
			}
			++i;
			++y2;
		}
		++x2;
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
	
	while(1) //I dont think this is needed for a signle print... 
	{
		//print(why,0,0,2);
		CheckButtons();

		//drawbitmap(image_raw+(i&0xfff),i&0x1ff,1,16);
		//i += 1;
	}
	/*
	deref(0xf037) = 0;
	for(i = 0; i < 2048; i++)
	{
		deref(0xf800+i) = 0x3c;
	}
	*/
}
