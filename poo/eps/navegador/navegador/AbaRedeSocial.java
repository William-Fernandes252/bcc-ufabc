package navegador;

public class AbaRedeSocial extends AbaNavegador {
    public AbaRedeSocial(Navegador navegador, String titulo) {
        super(navegador, titulo);
    }

    public String getTipo() {
        return "RedeSocial";
    }

    public void postar(String texto) {
        this.getNavegador().pushHistorico(String.format("Post: %s", texto));
    }
}