package usuarios;

public class PerfilUsuario {
    private String nome, login;

    public PerfilUsuario(String nome) {
        this.nome = nome;
    }
    
    public PerfilUsuario(String nome, String login) {
        this(nome);
        this.login = login;
    }
    
    public final void imprimir() {
        System.out.println(String.format("Nome=%s Login=%s", nome, login));
    }
    
    public final String getNome() {
        return this.nome;
    }
}