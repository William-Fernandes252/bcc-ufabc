package navegador;

public abstract class AbaNavegador {
    protected String titulo;
    private Navegador navegador;
    
    public AbaNavegador(Navegador navegador, String titulo) {
        this.navegador = navegador;
        this.titulo = titulo;
    }

    public String getTitulo() {
        return titulo;
    }

    public final Navegador getNavegador() {
        return navegador;
    }

    @Override
    public String toString() {
        return String.format("%s %s", this.getTipo(), this.getTitulo());
    }
    
    public abstract String getTipo();
}