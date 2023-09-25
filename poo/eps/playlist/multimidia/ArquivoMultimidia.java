package multimidia;

public abstract class ArquivoMultimidia implements Cloneable {
    private String nomeArquivo;

    public ArquivoMultimidia(String nomeArquivo) {
        this.nomeArquivo = nomeArquivo;
    }

    public final String getNomeArquivo() {
        return this.nomeArquivo;
    }

    public void setNomeArquivo(String nomeArquivo) {
        this.nomeArquivo = nomeArquivo;
    }

    @Override
    public ArquivoMultimidia clone() {
        try {
            return (ArquivoMultimidia) super.clone();
        } catch (CloneNotSupportedException e) {
            return null;
        }
    }
}