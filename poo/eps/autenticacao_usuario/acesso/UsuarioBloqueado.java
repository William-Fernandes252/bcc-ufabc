package acesso;

public class UsuarioBloqueado extends Exception {
    private String login;

    public UsuarioBloqueado(String login) {
        super("Usuário bloqueado");
        this.login = login;
    }

    public String getLogin() {
        return login;
    }
}