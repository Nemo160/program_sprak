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
    private void in(String s){
        if(ParserMain.DEBUG) {System.out.println("*** IN " + s);}
    }

    private void out(String s){
        if(ParserMain.DEBUG){System.out.println("*** OUT " + s);}
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
        in("Program Header");
        match(TokenType.PROGRAM);
        symtab.declareProgram(lookahead.lexeme());
        match(TokenType.ID);
        match(TokenType.LPAREN);
        match(TokenType.INPUT);
        match(TokenType.COMMA);
        match(TokenType.OUTPUT);
        match(TokenType.RPAREN);
        match(TokenType.SEMI);
        out("Program Header");
    }
    private void varPart(){
        in("vart part");
        if(lookahead.type() == TokenType.VAR){
            match(TokenType.VAR);
            varDecList();
        }
        out("vart part");
    }
    private void varDecList(){
        in("var dec list");
        varDec();
        while(lookahead.type() == TokenType.ID){
            varDec();
        }
        out("var dec list");
    }

    private void varDec(){
        in("var dec");
        idList();
        match(TokenType.COLON);
        Type declaredType = type();
        symtab.setWaitingType(declaredType);
        match(TokenType.SEMI);
        out("var dec");
    }

    private void idList(){
        in("id list");
        declareId();
        match(TokenType.ID);
        while(lookahead.type() == TokenType.COMMA){
            match(TokenType.COMMA);
            declareId();
            match(TokenType.ID);
        }
        out("id list");
    }

    private void declareId(){
        String name = lookahead.lexeme();
        if(symtab.isDeclared(name)){
            isOk = false;
            System.out.println("SEMANTIC: ID already declared: " + name);
        }
        symtab.declareVariable(name);
    }

    private Type type(){
        in("type");
        Type t;
        if(lookahead.type() == TokenType.INTEGER){
            t = Type.INTEGER;
            match(TokenType.INTEGER);
        }
        else if(lookahead.type() == TokenType.REAL){
            t = Type.REAL;
            match(TokenType.REAL);
        }
        else if(lookahead.type() == TokenType.BOOLEAN){
            t = Type.BOOLEAN;
            match(TokenType.BOOLEAN);
        }
        else{
            isOk = false;
            System.out.println("SYNTAX: Type name expected found " + lookahead.lexeme());
            t = Type.ERROR;
        }
        out("type");
        return t;
    }

    //STAT PART ##########################################
    private void statPart(){
        in("stat part");
        match(TokenType.BEGIN);
        statList();
        match(TokenType.END);
        match(TokenType.DOT);
        out("stat part");
    }

    private void statList(){
        in("stat list");
        stat();
        while(lookahead.type() == TokenType.SEMI){
            match(TokenType.SEMI);
            stat();
        }
        out("stat list");
    }

    private void stat(){
        in("stat");
        assignStat();
        out("stat");
    }

    private void assignStat(){
        in("assign stat");
        String varName = lookahead.lexeme();
        Type typeL = Type.UNDEFINED;

        //get the type of the declared variable
        if(!symtab.isDeclared(varName)){
            isOk = false;
            System.out.println("SEMANTIC: ID NOT declared: " + varName);
        }
        else{
            typeL = symtab.typeOf(varName);
        }

        match(TokenType.ID);
        match(TokenType.ASSIGN);
        Type typeR = expr();

        if(typeL != typeR){
            isOk = false;
            System.out.println("SEMANTIC: Assign types: " + typeL + " := " + typeR);
        }
        out("assign stat");
    }

    //EXPRESSIONS ##########################################
    private Type expr(){
        in("expr");
        Type t = term();
        while(lookahead.type() == TokenType.PLUS){
            match(TokenType.PLUS);
            Type t2 = term();
            Type result = optab.resultType(TokenType.PLUS, t, t2);
            if(result == Type.UNDEFINED && t != Type.ERROR && t != Type.UNDEFINED
                    && t2 != Type.ERROR && t2 != Type.UNDEFINED){
                isOk = false;
                System.out.println("SEMANTIC: Assign types: " + t + " := " + t2);
            }
            t = result;
        }
        out("expr");
        return t;
    }

    private Type term(){
        in("term");
        Type t = factor();
        while(lookahead.type() == TokenType.TIMES){
            match(TokenType.TIMES);
            Type t2 = factor();
            Type result = optab.resultType(TokenType.TIMES, t, t2);
            if(result == Type.UNDEFINED && t != Type.ERROR && t != Type.UNDEFINED
                    && t2 != Type.ERROR && t2 != Type.UNDEFINED){
                isOk = false;
                System.out.println("SEMANTIC: Assign Types: " + t + " := " + t2);
            }
            t = result;
        }
        out("term");
        return t;
    }

    private Type factor(){
        in("factor");
        Type t;
        if(lookahead.type() == TokenType.LPAREN){
            match(TokenType.LPAREN);
            t = expr();
            match(TokenType.RPAREN);
        }
        else{
            t = operand();
        }
        out("factor");
        return t;
    }

    private Type operand(){
        in("operand");
        Type t = Type.UNDEFINED;
        if(lookahead.type() == TokenType.ID){
            String name = lookahead.lexeme();
            if(!symtab.isDeclared(name)){
                isOk = false;
                System.out.println("SEMANTIC: ID NOT declared: " + name);
            }
            else{
                t = symtab.typeOf(name);
            }
            match(TokenType.ID);
        }
        else if(lookahead.type() == TokenType.NUMBER){
            t = Type.INTEGER;
            match(TokenType.NUMBER);
        }
        out("operand");
        return t;
    }
}
