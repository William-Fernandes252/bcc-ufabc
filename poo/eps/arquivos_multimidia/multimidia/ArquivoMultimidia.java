package multimidia;

public abstract class ArquivoMultimidia {
    private String nomeArquivo;

    public ArquivoMultimidia(String nomeArquivo) {
        this.nomeArquivo = nomeArquivo;
    }
    
    public final String getNomeArquivo() {
        return this.nomeArquivo;
    }
}