#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void main()
{
	system("hex2bin.exe Cosine.HEX");
	int orig = open("Cosine.bin",O_RDONLY);
	int result = open("Q:/CasioEmuX/models/test/rom.bin",O_WRONLY);
	lseek(orig,0,SEEK_END);
	unsigned long len = tell(orig);
	lseek(orig,0,SEEK_SET);
	char* buffer = malloc(len);
	read(orig,buffer,len);
	write(result,buffer,len);
	ftruncate(result,512*1024);
	close(orig);
	close(result);
}