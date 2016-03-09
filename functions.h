#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <string.h>

/* Prototypes for the functions */
char * s_gets(char * st, int n);
void split (char [], char [], char [], char [], char []);
void clear(char[], int n);
void authenticator(char [], char [], char []);
void displayCommnads();
void welcomeMessage();

/* Directive functions */
void assemble(char []);

/********************************************************
*               authenticator()                         *
*                                                       *
*  This fucntion takes three char arrays as paramters.  *
*  Using embedded if/else statements it determines      *
*  which commands require paramaters as well as which   *
*  don't.                                               *
********************************************************/
void authenticator(char comm[], char p1[], char p2[])
{

        /* If no paramaters needed only parameter 1 is checked.
           If only one parameter is needed both parameters are checked.
           If two parameters are needed both are checked.
        */
        if(!strcmp(comm,"load"))
                 {
                        if(p1[0] == '\0')
                                printf("Error: Parameter needed.\n");
                        else if(p2[0] != '\0')
                                printf("Error: Second parameter not required.\n");
                        else
                                printf("Command is %s.\n", comm);
                }
        else if(!strcmp(comm,"execute"))
                {
                        if(p1[0] != '\0')
                                printf("Error: No parameters needed.\n");
                        else
                                printf("Command is %s.\n", comm);
                }
        else if(!strcmp(comm,"debug"))
                {
                        if(p1[0] != '\0')
                                printf("Error: No parameters needed.\n");
                        else
                                printf("Command is %s.\n", comm);
                }
        else if(!strcmp(comm,"dump"))
                {
                        if(p1[0] == '\0')
                                printf("Error: First parameter incorrect.\n");
                        else if(p2[0] == '\0')
                                printf("Error: Second parameter incorrect.\n");
                        else
                                printf("Command is %s.\n", comm);
                }
        else if(!strcmp(comm,"help"))
                {
                        if(p1[0] != '\0')
                                printf("Error: No parameters needed.\n");
                        else
                                displayCommnads();
                }
        else if(!strcmp(comm,"assemble"))
                {
                        if(p1[0] == '\0')
                                printf("Error: Parameter needed.\n");
                        else if(p2[0] != '\0')
                                printf("Error: Second parameter not required.\n");
                        else
                               assemble(p1);
                }
        else if(!strcmp(comm,"directory"))
                system("ls");
        else if(!strcmp(comm,"exit"))
                 {
                        if(p1[0] != '\0')
                                printf("Error: No parameters needed.\n");
                }
        else
        {
               printf("Error: %s in not a valid command.\n", comm); // ¯\_(ツ)_/¯
               displayCommnads();
        }
}

/********************************************************
*                       clear()                         *
*                                                       *
*  This fucntion takes any given char array and fills   * 
*  it with null characters to erase previous inputs.    *
********************************************************/
void clear( char string[], int n)
{
        int i;
        for (i = 0; i < n; i++)
                string[i] = '\0';

}

/********************************************************
*                  displayCommnads()                    *
*                                                       *
*  This fucntion displays all available commands and    *
*  parameters.                                          *
********************************************************/
void displayCommnads()
{

        printf("\nload filename: Loads the specified file.\n\n");
	printf(	"execute: Executes the program that was previously loaded in memory.\n\n");
	printf(	"debug: Executes in debug mode.\n\n");
	printf(	"dump start end: Calls the dump function, passing the values of start and end.\n\n");
	printf(	"help: Prints out a list of available commands.\n\n");
	printf(	"assemble filename: Assembles an SIC assembly language program into a load module and store it in a file.\n\n");
	printf(	"directory: Lists the files stored in the current directory.\n\n");
	printf(	"exit: Exit from the simulator.\n\n");

}

/********************************************************
*                     s_gets()                          *
*                                                       *
*  This fucntion takes in a char array and array length *
*  to get rid of any '\n'.				*
********************************************************/
char * s_gets(char * st, int n)
{
	char * ret_val;
	char * find;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		find = strchr(st, '\n');	// Look for newline
		if(find)			// if the address is not NULL,
			*find = '\0';		// place a null character there
		else
			while (getchar() != '\n')
				continue;	//dispose of rest of line
	}
	return ret_val;
}


/********************************************************
*                       split()                         *
*                                                       *
*  This fucntion takes in the users input and divides   *
*  into the cammand and two parameters. Any more        *
*  parameters than two are placed in extra char array.  *
********************************************************/
void split( char line[], char comm[], char p1[], char p2[], char extra[])
{

	int i, j;

	i = 0;
	j = 0;

	// Traverses any spaces to the first character
	while ( line[i] == ' ' || line[i] == '\t' )
		i++;

	// Once a character is found copy into comm
	// until another space or null character.
	while( line[i] != '\0')
	{

		comm[j] = line[i];
                
		++j;
		++i;
 
		if (line[i] == ' ' || line[i] == '\0' || line[i] == '\t')
		{
			comm[j] = '\0';
			break;
		}
    
	}

	// Find the next string to be copied into first paramenter.
	while ( line[i] == ' ' || line[i] == '\t')
		i++;

	if ( line[i] != '\0' )
	{
		j = 0;
		while( line[i] != '\0')
		{

			p1[j] = line[i];

			++j;
			++i;

			if (line[i] == ' ' || line[i] == '\0' || line[i] == '\t')
			{
				p1[j] = '\0';
				break;
			}
		}
	}


	// Find the next string to be copied into second paramenter.
	while ( line[i] == ' ' || line[i] == '\t')
		i++;

	if ( line[i] != '\0' )
	{
		j = 0;
		while( line[i] != '\0')
		{

			p2[j] = line[i];

			++j;
			++i;

			if (line[i] == ' ' || line[i] == '\0' || line[i] == '\t')
			{
				p2[j] = '\0';
				break;
			}
		}
	}

	// Find the next string
	while ( line[i] == ' ' || line[i] == '\t')
		i++;

	if ( line[i] != '\0' )
	{
		j = 0;
		while( line[i] != '\0')
		{

			extra[j] = line[i];

			++j;
			++i;

			if ( line[i] == '\0')
			{
				extra[j] = '\0';
				break;
			}
		}

	}

}


/********************************************************
*              welcomeMessage()                         *
*                                                       *
*  This fucntion displays a welcome message to the user *
*  as well as which command to start with.		*
********************************************************/
void welcomeMessage()
{
        static unsigned char asciipic_txt[] = {                                                
        0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x5f, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x5f, 0x5f, 0x5f,
        0x5f, 0x5f, 0x20, 0x5f, 0x5f, 0x5f, 0x5f, 0x5f, 0x20, 0x0a, 0x2f, 0x20,
        0x20, 0x5f, 0x5f, 0x5f, 0x28, 0x5f, 0x29, 0x20, 0x20, 0x20, 0x20, 0x20,
        0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x7c, 0x20, 0x20, 0x5f, 0x20, 0x20,
        0x2f, 0x20, 0x20, 0x5f, 0x5f, 0x5f, 0x7c, 0x0a, 0x5c, 0x20, 0x60, 0x2d,
        0x2d, 0x2e, 0x20, 0x5f, 0x20, 0x5f, 0x20, 0x5f, 0x5f, 0x20, 0x5f, 0x5f,
        0x5f, 0x20, 0x20, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x5c, 0x20,
        0x60, 0x2d, 0x2d, 0x2e, 0x20, 0x0a, 0x20, 0x60, 0x2d, 0x2d, 0x2e, 0x20,
        0x7c, 0x20, 0x7c, 0x20, 0x27, 0x5f, 0x20, 0x60, 0x20, 0x5f, 0x20, 0x5c,
        0x20, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x60, 0x2d, 0x2d,
        0x2e, 0x20, 0x5c, 0x0a, 0x2f, 0x5c, 0x5f, 0x5f, 0x2f, 0x20, 0x7c, 0x20,
        0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20, 0x7c, 0x20,
        0x5c, 0x20, 0x5c, 0x5f, 0x2f, 0x20, 0x2f, 0x5c, 0x5f, 0x5f, 0x2f, 0x20,
        0x2f, 0x0a, 0x5c, 0x5f, 0x5f, 0x5f, 0x5f, 0x2f, 0x7c, 0x5f, 0x7c, 0x5f,
        0x7c, 0x20, 0x7c, 0x5f, 0x7c, 0x20, 0x7c, 0x5f, 0x7c, 0x20, 0x20, 0x5c,
        0x5f, 0x5f, 0x5f, 0x2f, 0x5c, 0x5f, 0x5f, 0x5f, 0x5f, 0x2f, 0x0a

        };

        system("clear");
        printf("%s\n", asciipic_txt);
        printf("Welcome to Sim OS 1.0\n");
        printf("For supported commands type: help\n\n");

} 

// This is the fucntion for the assmble directive

void assemble(char fileName [])
{

	char outName[64];
	char line[256];
	FILE *in, *out;
	int c;

        // Variables for split
        char label[50], instruction[50], operand[50], comment[50];
        char * pch;

        // initialize
        label[0], instruction[0], operand[0],comment[0] = '\0';

	// get file names from user
	//printf("Enter name of file to be copied: ");
	//scanf("%63s", inName);
	printf("Enter name of output file: ");
	scanf("%63s", outName);

	// open input and output files

	if ( (in = fopen(fileName, "r")) == NULL  )
	{
		printf("Can't open %s for reading.\n", fileName);
		//return 1;
	}

	if ( (out = fopen (outName, "w")) == NULL )
	{
		printf("Can't open %s for writing.\n", outName);
		//return 2;
	}

	// copy in to out

	//while( (c = getc (in)) != EOF )
	//	putc (c, out);

	// Get line from file

	while (fgets(line, sizeof(line), in) )
	{
		printf("%s", line);

                split(line, label, instruction, operand, comment);

                //sscanf(line,"%s %s %s %s %*s", label, instruction, operand, comment);

                printf("label: %s\n", label);
                printf("instruction: %s\n", instruction);
                printf("operand: %s\n", operand);
                printf("comment: %s\n", comment);
	}

	// Close open files
	fclose(in);
	fclose(out);


}



#endif
