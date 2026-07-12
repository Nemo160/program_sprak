public enum Type {
    INTEGER(4), REAL(8), BOOLEAN(4), UNDEFINED(0), ERROR(0);
    public final int size;
    Type(int size) { this.size = size; }
}
