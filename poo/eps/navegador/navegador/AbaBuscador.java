package navegador;

public class AbaBuscador extends AbaNavegador {
    public AbaBuscador(Navegador navegador, String titulo) {
        super(navegador, titulo);
    }

    public String getTipo() {
        return "Buscador";
    }

    public void buscar(String expressao) {
        this.getNavegador().pushHistorico(String.format("Busca: %s", expressao));
    }
}