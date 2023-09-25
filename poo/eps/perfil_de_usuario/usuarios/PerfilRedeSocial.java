package usuarios;

public class PerfilRedeSocial extends PerfilUsuario {
    private String mensagemPaginaInicial;

    public PerfilRedeSocial(String nome, String login, String mensagemPaginaInicial) {
        super(nome, login);
        this.mensagemPaginaInicial = mensagemPaginaInicial;
    }

    public PerfilRedeSocial(String nome, String login) {
        this(nome, login, "Sem mensagem");
    }

    public String getMensagemPaginaInicial() {
        return mensagemPaginaInicial;
    }

    public String getPerfil() {
        return String.format("%s %s", this.getNome(), this.getMensagemPaginaInicial());
    }
}
