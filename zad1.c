#include <stdlib.h> 
#include <unistd.h> 
#include <stdio.h> 

int main(int argc, char **argv)
{

	FILE * plik;
	
	int i = 0, a = 0;
	int fd[2];

	plik = fopen(argv[1], "r");

	if(plik == NULL)
	{
		printf("Brak pliku\n");
		return -1;
	}
	
	fseek(plik, 0l, SEEK_END);
	a = ftell(plik);
	rewind(plik);
	
	char  tekst[a], tekst2[a];

	while((tekst[i] = fgetc(plik)) != EOF)
	{
		i++;
	}

	fclose(plik);

	pipe(fd);

	int potomek = fork();
	
	switch(potomek)

	{
		case 0:
		close(fd[1]);
		read(fd[0], tekst2, sizeof(tekst));
		printf("#%s#", tekst2);
		close(fd[0]);
		break;

		default:
		close(fd[0]);
		write(fd[1], tekst, sizeof(tekst));
		
		close(fd[1]);
		break;
	}

	


	return 0;
}

