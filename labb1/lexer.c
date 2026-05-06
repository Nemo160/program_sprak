//Edinson Uribe

/**********************************************************************/
/* lab 1 DVG C01 - Lexer OBJECT                                       */
/**********************************************************************/

/**********************************************************************/
/* Include files                                                      */
/**********************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

/**********************************************************************/
/* Other OBJECT's METHODS (IMPORTED)                                  */
/**********************************************************************/
#include "keytoktab.h"

/**********************************************************************/
/* OBJECT ATTRIBUTES FOR THIS OBJECT (C MODULE)                       */
/**********************************************************************/
#define BUFSIZE 1024
#define LEXSIZE   30
static char buffer[BUFSIZE];
static char lexbuf[LEXSIZE];
static int  pbuf  = 0;               /* current index program buffer  */
static int  plex  = 0;               /* current index lexeme  buffer  */

/**********************************************************************/
/*  PRIVATE METHODS for this OBJECT  (using "static" in C)            */
/**********************************************************************/
/**********************************************************************/
/* buffer functions                                                   */
/**********************************************************************/

/**********************************************************************/
/* Read the input file into the buffer                                */
/**********************************************************************/
static void pbuffer()
{
    printf("\n______________________________________________________________");
    printf("\n THE PROGRAM TEXT");
    printf("\n______________________________________________________________");
    printf("\n%s\n", buffer);
    printf("\n______________________________________________________________");

}

static void get_prog()
{
    int c;
    int i = 0;
    
    while ((c = getchar()) != EOF && i < BUFSIZE - 1) {
        buffer[i++] = c;
    }
    buffer[i] = '\0';
    pbuffer(); 
}

/**********************************************************************/
/* Display the buffer                                                 */
/**********************************************************************/



/**********************************************************************/
/* Copy a character from the program buffer to the lexeme buffer      */
/**********************************************************************/

static void get_char()
{
    if (pbuf < strlen(buffer) && plex < LEXSIZE -1) {
        lexbuf[plex++] = buffer[pbuf++];
    }
}

/**********************************************************************/
/* End of buffer handling functions                                   */
/**********************************************************************/

/**********************************************************************/
/*  PUBLIC METHODS for this OBJECT  (EXPORTED)                        */
/**********************************************************************/
/**********************************************************************/
/* Return a token                                                     */
/**********************************************************************/
int get_token()
{

    int a; 
    static int first_run = 1;
    if(first_run){
        get_prog();
        first_run = 0;
        
    }

    while(buffer[pbuf] != '\0' && isspace(buffer[pbuf])){
        pbuf++;
    }

    if(buffer[pbuf] == '\0'){
        return '$';
    }

    plex = 0;
    
    a = buffer[pbuf];
    size_t blen = strlen(buffer);
    //check for :=
    if(a == ':' && pbuf +1 < blen && buffer[pbuf+1] == '='){
        lexbuf[0] = ':';
        lexbuf[1] = '=';
        lexbuf[2] = '\0';
        pbuf += 2;
        plex = 2;
        return lex2tok(":=");
    }

    //check for single-character operators and add to lexbuf
    if(strchr("()+-*,;./:=", a)){
        lexbuf[0] = a;
        lexbuf[1] = '\0';
        pbuf++;
        return lex2tok(lexbuf);
    }

    if(isdigit(a)){
        //check if the character is a number and if the lexem is not full
        while(buffer[pbuf] != '\0' && isdigit(buffer[pbuf]) && plex < LEXSIZE - 1){
            get_char();
        }
        lexbuf[plex] = '\0';
        return lex2tok("number");
    }

    //identifiers and keywords
    if(isalpha(a)){

        while(buffer[pbuf] != '\0' && isalnum(buffer[pbuf]) && plex < LEXSIZE - 1){
            get_char();
        }
        lexbuf[plex] = '\0';

        toktyp token = key2tok(lexbuf);
        if(token != nfound){
            return token;
        }
        return lex2tok("id");
    }

    //unknown character
    pbuf++;
    return get_token();
}

/**********************************************************************/
/* Return a lexeme                                                    */
/**********************************************************************/
char * get_lexeme()
{
    return lexbuf;
}

/**********************************************************************/
/* End of code                                                        */
/**********************************************************************/
