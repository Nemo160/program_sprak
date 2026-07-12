public class Parser {

    private final Lexer lexer;
    private final SymbolTable symtab;
    private final OperatorTable optab;

    private Token lookahead;
    private boolean isOk = true;



    public Parser(Lexer lexer, SymbolTable symbolTable, OperatorTable operatorTable) {
        this.lexer = lexer;
        this.symtab = symbolTable;
        this.optab = operatorTable;
    }

    public boolean parse() {
        lookahead = lexer.nextToken();
        program();
        symtab.print();
        return isOk;
    }

    private void match(TokenType expected){
        if(lookahead.type() == expected){
            if(ParserMain.DEBUG) System.out.println("Expected: " + expected + " Found: " + lookahead.lexeme());
            lookahead = lexer.nextToken();
        }
        else{
            isOk = false;
            System.out.println("SYNTAX: Symbol expected " + expected.lexeme + " found " + lookahead.lexeme());
        }
    }

    //PARSER PART
    private void program(){
        programHeader();
        varPart();
        statPart();
    }

    private void programHeader(){
        match(TokenType.PROGRAM);
        symtab.declareProgram(lookahead.lexeme());
        match(TokenType.ID);
        match(TokenType.LPAREN);
        match(TokenType.INPUT);
        match(TokenType.COMMA);
        match(TokenType.OUTPUT);
        match(TokenType.RPAREN);
        match(TokenType.SEMI);
    }
    private void varPart(){}
    private void  statPart(){}

    //expr(), term, factor, operand
}
