#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "hacking.h"

#define FILENAME "/var/notes"

int print_notes(int, int, char *); // note printing function
int find_user_note(int, int);      // seek in file for a note for user
int search_note(char *, char *);   // search for keyword function
void fatal(char *);                // fatal error handler

int main(int argc, char *argv[]) {
    int userid, printing=1, fd;
    char searchstring[100];

    if (argc > 1)
        strcpy(searchstring, argv[1]);
    else
        searchstring[0] = 0;

    userid = getuid();
    fd = open(FILENAME, O_RDONLY);
    if (fd == -1)
        fatal("in main() while opening file for reading");

    while (printing)
        printing = print_notes(fd, userid, searchstring);
    printf("------[ end of note data ]------\n");
    close(fd);
}

// a function to print the notes for a given uid that
// match an optional search string
int print_notes(int fd, int uid, char *searchstring) {
    int note_length;
    char byte=0, note_buffer[100];

    note_length = find_user_note(fd, uid);
    if (note_length == -1)
        return 0;

    read(fd, note_buffer, note_length);
    note_buffer[note_length] = 0;

    if (search_note(note_buffer, searchstring))
        printf(note_buffer);
    printf(note_buffer);
    return -1;
}

// a function to find the next note for a given user id
// returns -1 if the end of the file is reached
// otherwise, it returns the length of the found note
int find_user_note(int fd, int user_uid) {
    int note_uid = -1;
    unsigned char byte;
    int length;

    while (note_uid != user_uid) {
        if (read(fd, &note_uid, 4) != 4)
            return -1;
        if (read(fd, &byte, 1) != 1)
            return -1;

        byte = length = 0;
        while (byte != '\n') {
            if (read(fd, &byte, 1) != 1)
                return -1;
            length++;
        }
    }

    lseek(fd, length * -1, SEEK_CUR); // rewind file reading by length bytes

    printf("[DEBUG] found a %d byte note for user id %d\n", length, note_uid);
    return length;
}

// a function to search a note for a given keyword
// returns 1 if a match is found, 0 if there is no match
int search_note(char *note, char *keyword) {
    int i, keyword_length, match = 0;

    keyword_length = strlen(keyword);
    if (keyword_length == 0)
        return 1;

    for (i=0; i<strlen(note); i++) {
        if (note[i] == keyword[match])
            match++;
        else {
            if (note[i] == keyword[0])
                match = 1;
            else 
                match = 0;
        }
        if (match == keyword_length)
            return 1;
    }

    return 0;
}
