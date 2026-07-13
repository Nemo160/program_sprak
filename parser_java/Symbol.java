public final class Symbol {
    private final String name;
    private final Role role;
    private Type type = Type.UNDEFINED;
    private int size;
    private int addr;
    Symbol(final String name, final Role role) {
        this.name = name;
        this.role = role;
    }
    public String getName() {
        return name;
    }
    public Role getRole() {
        return role;
    }

    //getters
    public Type getType() {
        return type;
    }
    public int getSize() {
        return size;
    }
    public int getAddr() {
        return addr;
    }

    //setters
    void setType(final Type type) {
        this.type = type;
    }
    void setSize(final int size) {
        this.size = size;
    }
    void setAddr(final int addr) {
        this.addr = addr;
    }




}
