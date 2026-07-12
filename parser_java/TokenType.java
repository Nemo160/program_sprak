public enum TokenType {
    ID("identifier", false), NUMBER("number", false), ASSIGN(":=", false), UNDEFINED("undefined", false),
    PROGRAM("program", true), INPUT("input", true), OUTPUT("output", true), VAR("var", true),
    BEGIN("begin", true), END("end", true), BOOLEAN("boolean", true),
    INTEGER("integer", true), REAL("real", true),
    LPAREN("(", false), RPAREN(")", false), COMMA(",", false), SEMI(";", false),
    COLON(":", false), DOT(".", false),
    PLUS("+", false), MINUS("-", false), TIMES("*", false), SLASH("/", false), EQUALS("=", false),
    EOF("<eof>", false);

    public final String lexeme;
    public final boolean isKeyword;

    TokenType(String lexeme, boolean isKeyword) {
        this.lexeme = lexeme;
        this.isKeyword = isKeyword;
    }
}
