#include "unscramble.h"

//unscrambles a clear problem, returning the unscrambled Word_List
struct Word_List unscrambleClear(FILE* dataFile){
    int numWords;
	fread(&numWords, sizeof(uint16_t), 1, dataFile);
	struct Word_List list;
	init_list(&list, numWords);

	uint16_t offset;
	fread(&offset, sizeof(uint16_t), 1, dataFile);

	while(offset != 0){
		//moving to the position in file provided by offset
		fseek(dataFile, offset, SEEK_SET);

		//reading length of word and next offset
		uint8_t wordBytes;
		fread(&wordBytes, sizeof(uint8_t), 1, dataFile);
        uint16_t newOffset;
		fread(&newOffset, sizeof(uint16_t), 1, dataFile);

		//reading string
		char string[wordBytes-2];
		fread(string, sizeof(char), wordBytes-3, dataFile);
		string[sizeof(string)-1] = '\0';
		
		//creating Word and adding it to the list
		struct Word word;
		init_word(&word);
		update_word(&word, string, offset+3);
		add_word(&list, word);

		//updating offset
        offset = newOffset;
	}

    return list;
}

//unscrambles a fuzzy problem, returning the unscrambled Word_List
struct Word_List unscrambleFuzzy(FILE* dataFile){
    int numWords;
	fread(&numWords, sizeof(uint16_t), 1, dataFile);
	struct Word_List list;
	init_list(&list, numWords);

	uint16_t offset;
	fread(&offset, sizeof(uint16_t), 1, dataFile);

	while(offset != 0){
		//moving to the position in file provided by offset
		fseek(dataFile, offset, SEEK_SET);

		//reading length of word and next offset
		uint8_t wordBytes;
		fread(&wordBytes, sizeof(uint8_t), 1, dataFile);
        uint16_t newOffset;
		fread(&newOffset, sizeof(uint16_t), 1, dataFile);

		//reading string
		char string[wordBytes-2];
		fread(string, sizeof(char), wordBytes-3, dataFile);
		string[sizeof(string)-1] = '\0';

		//flipping the length of the word and blending with every letter
        uint8_t flippedLength = (wordBytes>>4)|(wordBytes<<4);
        for(unsigned int i = 0; i < sizeof(string)-1; i++)
            string[i] ^= flippedLength;
		
		//creating Word and adding it to the list
		struct Word word;
		init_word(&word);
		update_word(&word, string, offset+3);
		add_word(&list, word);

		//applying mask to new offset
        offset = newOffset^((string[0]<<8)|string[0]);
	}

    return list;
}