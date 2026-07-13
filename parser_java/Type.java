public enum Type {
    INTEGER(4, "integer"), REAL(8, "real"), BOOLEAN(4, "boolean"),
    UNDEFINED(0, "undef"), ERROR(0, "error"), PROGRAM(0, "program");

    public final int size;
    private final String label;

    Type(int size, String label) {
        this.size = size;
        this.label = label;
    }

    @Override
    public String toString() {
        return label;
    }
}
