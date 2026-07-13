public enum Role {
    PROGRAM("program"), VARIABLE("var");

    private final String label;

    Role(String label) {
        this.label = label;
    }

    @Override
    public String toString() {
        return label;
    }
}
