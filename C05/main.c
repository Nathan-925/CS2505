#include "word.h"
#include "unscramble.h"

int main(int argc, char** argv){
	//checking arguments
	if(argc != 3){
		printf("Must provide input and output file names.");
		return 1;
	}

	FILE* inputFile = fopen(argv[1], "r");

	//reading commands
	int numBytes;
	fscanf(inputFile, "%d", &numBytes);
	char dataName[256];
	fscanf(inputFile, "%s", dataName);
	char fuzzed[256];
	fscanf(inputFile, "%s", fuzzed);

	FILE* dataFile = fopen(dataName, "rb");

	//calls the appropriate function based on the clear/fuzzy command
	struct Word_List list = fuzzed[0] == 'c' ?
		unscrambleClear(dataFile) :
		unscrambleFuzzy(dataFile);

	FILE* outputFile = fopen(argv[2], "w");
	
	//writing output
	fprintf(outputFile, "Bytes in file:\t%d\n", numBytes);
	fprintf(outputFile, "Name of file:\t%s\n", dataName);
	fprintf(outputFile, "Clear|Fuzzy:\t%s\n", fuzzed);
	display_words(outputFile, list);

	free_list(list);
	fclose(inputFile);
	fclose(dataFile);
	fclose(outputFile);
}