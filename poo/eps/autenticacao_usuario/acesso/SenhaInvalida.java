package acesso;

public class SenhaInvalida extends Exception {
    private String login;

    public String getLogin() {
        return login;
    }

    public SenhaInvalida(String login) {
        super("Senha inválida");
        this.login = login;
    }
}
