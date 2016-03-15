#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <stdio.h>
#include <string.h>

/* Prototypes for the functions */
char * s_gets(char * st, int n);
void clear(char[], int n);
void authenticator(char [], char [], char []);
void displayCommnads();
void welcomeMessage();
void parameterFix(char [], char [], char []);

/* Directive functions */
void assemble(char []);


// Opcode Table
typedef struct {
        char name[6];
        int code;
} Optab;

Optab opcodeTable [31] =
{ {"ADD\0", 24}, {"AND\0", 88}, {"COMP\0", 40}, {"DIV\0", 36}, {"J\0", 60},
  {"JEQ\0", 48}, {"JGT\0", 52}, {"JLT\0", 56}, {"JSUB\0", 72}, {"LDA\0", 0},
  {"LDCH\0", 80}, {"LDL\0", 8}, {"LDX\0", 4}, {"MUL\0", 32}, {"OR\0", 68},
  {"RD\0", 216}, {"RSUB\0", 76}, {"STA\0", 12}, {"STCH\0", 84}, {"STL\0", 20},
  {"STX\0", 16}, {"SUB\0", 28}, {"TD\0", 224}, {"TIX\0", 44}, {"WD\0", 220},
  {"START\0", 250}, {"END\0", 251}, {"BYTE\0", 252}, {"WORD\0", 253}, {"RESB\0", 254},
  {"RESW\0", 255}};

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
                        else{
                               assemble(p1);
                               while ( getchar() != '\n' )
                                        continue;
                        }
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
        printf("Welcome to Sim OS 2.0\n");
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
        char p1[50], p2[50], p3[50];
        char * pch;

        // initialize
        p1[0], p2[0], p3[0] = '\0';

	// get file names from user
	printf("Enter name of output file: ");
	scanf("%63s", outName);

	// open input and output files

	if ( (in = fopen(fileName, "r")) == NULL  )
	{
		printf("Can't open %s for reading.\n", fileName);
		return;
	}
        else {
                
                // Traverses any comments
               while (fgets(line, sizeof(line), in) && line[0] == '.' )
		        continue;

                // The first line is a special case
                printf("This is the first line of code: %s\n", line);
                sscanf(line,"%s %s %s %*s", p1, p2, p3);
                clear(p1, 50);
                clear(p2, 50);
                clear(p3, 50);

             	while (fgets(line, sizeof(line), in) )
	        {

                        if(line[0] == '.')
                                continue;

		        printf("%s\n", line);

                        sscanf(line,"%s %s %s %*s", p1, p2, p3);

                        parameterFix(p1, p2, p3);

                        printf("label: %s\n", p1);
                        printf("instruction: %s\n", p2);
                        printf("operand: %s\n", p3);

                        clear(p1, 50);
                        clear(p2, 50);
                        clear(p3, 50);
	        }   
        }

	if ( (out = fopen (outName, "w")) == NULL )
	{
		printf("Can't open %s for writing.\n", outName);
		//return 2;
	}

	// copy in to out

	//while( (c = getc (in)) != EOF )
	//	putc (c, out);

	// Close open files
	fclose(in);
	fclose(out);


}

void parameterFix(char p1[], char p2[], char p3[])
{
        _Bool found = 0;
        int i;

        // Check to see if label is a mnemonic
        for( i = 0; i < 30; i++)
                if(strcmp(p1, opcodeTable[i].name) == 0)
                {       
                        found = 1;
                        break;
                }

        // If label is a mnemonic place in correct parameter
        if (found == 1)
        {
                clear(p3, 50);
                strcpy(p3, p2);
                clear(p2, 50);
                strcpy(p2, p1);
                clear(p1, 50);

                // Special case for RSUB
                if(strcmp(p2, "RSUB") == 0)
                        clear(p3, 50);
        }

}



#endif
