#include "base.h"
#include "thefont.h"

void invert_line(const word line)
{
	word i = 0;
	word j = 0;
	word offset = (line<<9);
	for(i = 0; i < 512; i++)
	{
		deref(0xF037) = 0;
		deref(0xF800+i+offset) = (~deref(0xF800+i+offset));
		deref(0xF037) = 4;
		deref(0xF800+i+offset) = (~deref(0xF800+i+offset));
	}
}


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
	B_9 = 0x2d,
	
	B_A = 0x3c,
	B_B = 0x34,
	B_C = 0x2c,
	B_D = 0x24,
	B_E = 0x1c,
	B_F = 0x14,
	
	B_G = 0x3d,
	B_H = 0x35,
	B_I = 0x2d,
	B_J = 0x25,
	B_K = 0x1d,
	
	B_L = 0x3e,
	B_M = 0x36,
	B_N = 0x2e,
	B_O = 0x26,
	B_P = 0x1e,
	
	B_Q = 0x3f,
	B_R = 0x37,
	B_S = 0x2f,
	B_T = 0x27,
	B_U = 0x1f,
	
	B_V = 0xb,
	B_W = 0xc,
	B_X = 0xd,
	B_Y = 0xe,
	B_Z = 0xf,
	
	
	
	BUTTON_COUNT = 0x40
};

enum SPECIAL_CHARS
{
	SP_EXE = '\n',
	SP_TAB = '\t',
	SP_SPACE = ' ',
	SP_BACKSPACE = '\b',
	
	SP_HOME = 0x80,
	SP_END = 0x1A,
	SP_YES = 0x3A,
	SP_NO = 0x12,
	SP_OK = 0x21,
	SP_UP = 0x20,
	SP_DOWN = 0x22,
	SP_LEFT = 0x29,
	SP_RIGHT = 0x19,
	SP_PLUS = 0x10,
	SP_MINUS = 0x11,
	SP_ALT = 0x31,
	SP_ABC = 0x30,
	SP_ESC = 0x39,
	SP_SELECTLEFT,
	SP_SELECTRIGHT,
	SP_PASTE,
	SP_COPY,
	
	SPECIAL_MAX
};
const byte button_to_char[64] = {
	  0,        0,       0,    0,    0,    0,   0,    0,
	  0,        0,       0,  '0',  ' ',  ',', '.', '\n',
SP_PLUS, SP_MINUS,   SP_NO,  ']',  ')',    0,   0,    0,
	  0, SP_RIGHT,  SP_END,  '[',  '(', '\b', '#',  '%',
  SP_UP,    SP_OK, SP_DOWN, '\'',  '/',  '!', '@',  '$',
	  0,  SP_LEFT, SP_HOME,  ';', '\\',  '9', '6',  '3',
 SP_ABC,   SP_ALT,     '*',  '-',  '=',  '8', '5',  '2',
	  0,   SP_ESC,  SP_YES, '\t',  '`',  '7', '4',  '1',
};

const byte button_to_char_abc[64] = {
	0,   0,   0,   0,   0,   0,   0,   0,
	0,   0,   0, 'V', 'W', 'X', 'Y', 'Z',
	0,   0,   0,   0, 'F',   0,   0,   0,
	0,   0,   0,   0, 'E', 'K', 'P', 'U',
	0,   0,   0,   0, 'D', 'J', 'O', 'T',
	0,   0,   0,   0, 'C', 'I', 'N', 'S',
	0,   0,   0,   0, 'B', 'H', 'M', 'R',
	0,   0,   0,   0, 'A', 'G', 'L', 'Q',
};

const byte button_to_char_alt[64] = {
	0,              0,        0,   0,   0,   0,   0,   0,
	0,              0,        0,   0,   0, '<', '>',   0,
	0,              0, SP_PASTE, '}', '^',   0,   0,   0,
	0, SP_SELECTRIGHT,        0, '{', '*',   0,   0,   0,
	0,              0,        0, '"', '?',   0,   0,   0,
	0,  SP_SELECTLEFT,        0, ':', '|',   0,   0,   0,
	0,              0,      '&', '_', '+',   0,   0,   0,
	0,              0,  SP_COPY,   0, '~',   0,   0,   0,
};

byte lastbutton = 0xff;
byte CheckButtons()
{
	byte x;
	byte y;
	byte i = 0;
	for(x = 0x80; x != 0; x = x >> 1)
	{
		deref(0xf046) = x;
		for(y = 0x80; y != 0; y = y >> 1)
		{
			if((deref(0xf040) & y) == 0)
			{
				if(i != lastbutton)
				{
					lastbutton = i;
					return i;
				}
				return 0xff;
			}
			++i;
		}
	}
	lastbutton = 0x50;
	return 0xff;
}

byte tempbuffer[2] = " ";
char filename[] = " ";
void main()
{
	char filename[] = "Test.txt";
	byte KEY_ABC = 0;
	byte KEY_ALT = 0;
	word i = 0;
	word j = 1;

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

	//very sloppy text editor
	//My emu has alot of junk on screen, clearing both screen buffers helps.
	deref(0xf037) = 0;
	for(i = 0; i < 2048; i++)
	{
		deref(0xf800+i) = 0x00;
	}
	deref(0xf037) = 4;
	for(i = 0; i < 2048; i++)
	{
		deref(0xf800+i) = 0x00;
	}
	print(filename,0,0,1); //test
	invert_line(0); //test
	while(1)
	{
		byte pressedbutton = CheckButtons();
		if(pressedbutton == 0xff)
		{
			continue;
		}

		if(pressedbutton == SP_DOWN)
		{
			j--;
			i = 0;
			continue;
		} else if(pressedbutton == SP_UP) {
			j++;
			i = 0;
			continue;
		} else if(pressedbutton == SP_LEFT) {
			i--;
			continue;
		} else if(pressedbutton == SP_RIGHT) {
			i++;
			continue;
		} else if(pressedbutton == SP_ABC) {
			KEY_ABC = (~KEY_ABC);
			KEY_ALT = 0;
		} else if(pressedbutton == SP_ALT) {
			KEY_ALT = (~KEY_ALT);
			KEY_ABC = 0;
		} else {
			if(KEY_ABC)
			{
				tempbuffer[0] = button_to_char_abc[pressedbutton];
			} else if(KEY_ALT) {
				tempbuffer[0] = button_to_char_alt[pressedbutton];
			} else {
				tempbuffer[0] = button_to_char[pressedbutton];
			}
			print(tempbuffer,i,j,2);
			deref(0xE000+i+(j*24)) = tempbuffer[0];
			
			i++;
			
			if(i == 23)
			{
				i = 0;
				j++;
			}
		}
		//PrintWord(tempbuffer,0,1,2);
	
	}
	/*
	deref(0xf037) = 0;
	for(i = 0; i < 2048; i++)
	{
		deref(0xf800+i) = 0x3c;
	}
	*/
}
