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
    /*
    pbuf trakcs current position in pgrm buffer
    lexbuf contains current lexem that is being built.  (reset it)
    plex trakcs current position in lexem buffer

    Increment plex as lexem is build with each get_char
    */
    /*
    Functionallity:
    First read of input file. boolean since get_token gets called multiple times
    Check if end of input -> return '$' for end of file
    Skip whitespaces

    reset lexem buffer perhaps
    check for character operators := (Check the lexbuf[i] and lexbuf[i++])
    after operator check, skip 2 
    
    Check for single character operators ()+-*,;./:=
    check for numbers 
    check for keywords
    
    
    */

    int a; 
    static int first_run = 1;
    if(first_run){
        get_prog();
        first_run = 0;
        
    }
  
    
    //skips white space
    while(buffer[pbuf] != '\0' && isspace(buffer[pbuf])){
        pbuf++;
    }

    //check for end of input buffer
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

    //check for single-character operators and add to lexem
    if(strchr("()+-*,;./:=", a)){
        lexbuf[0] = a;
        lexbuf[1] = '\0';
        pbuf++;
        return lex2tok(lexbuf);
    }

    //check for number
    if(isdigit(a)){
        //check if the character is a number and if the lexem is not full
        while(buffer[pbuf] != '\0' && isdigit(buffer[pbuf]) && plex < LEXSIZE - 1){
            get_char();
        }
        lexbuf[plex] = '\0';
        return lex2tok("number");
    }

    //check for identifiers and keywords
    if(isalpha(a)){
        //check if its alphanumeric number & if lexem not full
        while(buffer[pbuf] != '\0' && isalnum(buffer[pbuf]) && plex < LEXSIZE - 1){
            get_char();
        }
        lexbuf[plex] = '\0';

        //if is valid otherwise default to id
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
