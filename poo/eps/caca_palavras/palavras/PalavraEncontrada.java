package palavras;

public class PalavraEncontrada {
    private String palavra;
    private int[] posicao;
    private int tipo;
    private int direcao;

    public PalavraEncontrada(String palavra, int[] posicao, int tipo, int direcao) {
        this.palavra = palavra;
        this.posicao = posicao;
        this.tipo = tipo;
        this.direcao = direcao;        
    }

    public String getPalavra() {
        return palavra;
    }

    public int[] getPosicao() {
        return posicao;
    }

    public int getTipo() {
        return tipo;
    }

    protected void setTipo(int tipo) {
        this.tipo = tipo;
    }

    public int getDirecao() {
        return direcao;
    }

    protected void setDirecao(int direcao) {
        this.direcao = direcao;
    }

    protected void setPosicao(int[] posicao) {
        this.posicao = posicao;
    }
}
