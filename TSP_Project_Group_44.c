/******** Library Includes ********/
#include <stdio.h>
#include <string.h>

/******** Struct Declarations ********/
typedef struct
{
	int id;
	int xCoordinate;
	int yCoordinate;
}city2dGrid;

/******** Global Variable Declarations & Initialization ********/
// Read Only char strings.
char* tour = ".tour";
char* testInputFile = "tsp_example_1.txt";
char* testOutputFile = "test.txt.tour";

/******** Function Prototypes ********/
int countFilelines(char *filename);

/******** Error Handling ********/
//void error(const char *msg) { fprintf(stderr,"%s", msg); return(1); } // Error function used for reporting issues

/******** Main Program ********/
int main(int argc, char **argv)
{
    char c;
    FILE *fp;
	int numberOfCities = 0;
	city2dGrid *gridOf2dcities;

	int vertId, xcoord, ycoord;

    if (argc >= 2)
	{
		numberOfCities =  countFilelines(argv[1]);
		printf("Number of lines: %d\n", numberOfCities);
		fp = fopen(argv[1], "r");
	}
    else // error("File error: file does not exist.\n");
    {
		numberOfCities =  countFilelines(testInputFile);
		printf("Number of lines: %d\n", numberOfCities);
        fp = fopen(testInputFile, "r");
    }


	if (fp)
	{
		gridOf2dcities = malloc(sizeof(city2dGrid)*numberOfCities);
		int currentCity = 0;

		char line[256];
		while(fgets(line, sizeof(line), fp))
		{
			sscanf(line, "%d %d %d", &vertId, &xcoord, &ycoord);
//            printf("vertex ID: %d, xcoord: %d, ycoord: %d", vertId, xcoord, ycoord);
//            printf("\n");
            gridOf2dcities[currentCity].id = vertId;
            gridOf2dcities[currentCity].xCoordinate = xcoord;
            gridOf2dcities[currentCity].yCoordinate = ycoord;
            currentCity++;
		}

		fclose(fp);
	}
//	else error("File error: could not open file.\n");

////////////////////// PERFORM FUNCTIONS /////////////////////////////



//////////////////////////////////////////////////////////////////////
	// char compositeFilePath[256];
	// memset(compositeFilePath, '\0', sizeof(compositeFilePath)); // Clear out the array before using it
	// stpcpy(compositeFilePath, argv[1]);

	// strcat(compositeFilePath, tour);

    // fp = fopen(compositeFilePath, "w");// "w" means that we are going to write on this file
    fp = fopen(testOutputFile, "w");// "w" means that we are going to write on this file
    int counter;
    for(counter = 0; counter < numberOfCities; counter++)
    {
        fprintf(fp, "vertex ID: %d, xcoord: %d, ycoord: %d", gridOf2dcities[counter].id, gridOf2dcities[counter].xCoordinate, gridOf2dcities[counter].yCoordinate);
        fprintf(fp, "\n");
    }
    fclose(fp);
}

/******** Functions ********/

int countFilelines(char *filename)
{
	FILE *fp = fopen(filename,"r");
	int character = 0;
	int lines = 0;

	if (fp == NULL)
        return 0;

	while(!feof(fp))
	{
		character = fgetc(fp);
		if(character == '\n')
		{
			lines++;
		}
	}

	fclose(fp);

	return lines;
}
