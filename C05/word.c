// On my honor:
//
// - I have not discussed the C language code in my program with
// anyone other than my instructor or the teaching assistants
// assigned to this course.
//
// - I have not used C language code obtained from another student,
// the Internet, or any other unauthorized source, either modified
// or unmodified.
//
// - If any C language code or documentation used in my program
// was obtained from an authorized source, such as a text book or
// course notes, that has been clearly noted with a proper citation
// in the comments of my program.
//
// - I have not designed this program in such a way as to defeat or
// interfere with the normal operation of the Curator System.
//
// Nathaniel Dunlap

#include "word.h"

uint32_t strlength(const char* const word){
    //Counting characters until the terminating charachter is found.
    int cnt = 0;
    while (*(word+cnt) != '\0')
        cnt++;
    return cnt;
}

void strcopy(char* const destination, const char* const source){
    //Copying characters over until the terminating character is reached. pos starts at -1 and is iterated
    //before it is used to allow the terminating character to be copied.
    int pos = -1;
    do{
        pos++;
        *(destination+pos) = *(source+pos);
    }while(*(source+pos) != '\0');
}

void init_word(struct Word *word){
    word->word = NULL;
    word->offset = 0;
}

void update_word(struct Word* word, const char* const wrd, uint16_t offset){
    if(word->word != NULL)
        free(word->word);

    word->word = calloc(strlength(wrd)+1, sizeof(char));
    strcopy(word->word, wrd);

    word->offset = offset;
}

void display_word(FILE* out, struct Word word){
    fprintf(out, "%-20s @ Offset: %02x\n", word.word, word.offset);
}

void free_word(struct Word word){
    free(word.word);
    word.word = NULL;
}

void init_list(struct Word_List *word_list, uint16_t size){
    word_list->words = calloc(size, sizeof(struct Word));
    word_list->size = size;
    word_list->count = 0;
}

void add_word(struct Word_List *word_list, struct Word word){
    if(word_list->count >= word_list->size){
        word_list->size *= 2;
        word_list->words = realloc(word_list->words, word_list->size*sizeof(struct Word));
    }

    *(word_list->words+word_list->count++) = word;
}

struct Word get_word_at_index(struct Word_List word_list, uint16_t index){
    if(index >= word_list.count){
        struct Word out;
        init_word(&out);
        update_word(&out, "Word Not Found", 0);
        return out;
    }

    struct Word out;
    struct Word toCopy = *(word_list.words+index);
    init_word(&out);
    update_word(&out, toCopy.word, toCopy.offset);
    return out;
}

void free_list(struct Word_List word_list){
    for(int i = 0; i < word_list.count; i++)
        free_word(*(word_list.words+i));

    free(word_list.words);
}

void display_words(FILE* out, struct Word_List word_list){
    for(int i = 0; i < word_list.count; i++)
        display_word(out, *(word_list.words+i));
}