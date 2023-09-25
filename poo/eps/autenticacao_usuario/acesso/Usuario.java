package acesso;

public class Usuario {
    private String login;
    private String senha;
    private int tentativasLogin;
    protected static int MAX_TENTATIVAS = 3;

    public Usuario(String login, String senha) {
        this.login = login;
        this.senha = senha;
        this.tentativasLogin = 0;
    }

    public String getLogin() {
        return login;
    }

    public void autenticar(String senha) throws SenhaInvalida, UsuarioBloqueado {
        if (tentativasLogin >= MAX_TENTATIVAS) {
            throw new UsuarioBloqueado(senha);
        }

        if (this.senha.equals(senha)) {
            System.out.println("Autenticado com sucesso");
        } else {
            this.tentativasLogin += 1;
            throw new SenhaInvalida(this.getLogin());
        }
    }
}
