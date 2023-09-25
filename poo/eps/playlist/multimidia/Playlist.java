package multimidia;

public class Playlist {
    public static final int TAMANHO_MAXIMO = 100;
    private ArquivoMultimidia arquivos[] = new ArquivoMultimidia[TAMANHO_MAXIMO];
    private int indiceUltimoArquivo = -1;

    public void adicionarItem(ArquivoMultimidia arquivo) {
        arquivos[indiceUltimoArquivo + 1] = arquivo;
        indiceUltimoArquivo++;
    }

    public void renomearItem(int indiceArquivo, String novoNomeArquivo) {
        arquivos[indiceArquivo].setNomeArquivo(novoNomeArquivo);
    }

    public void moverParaInicio(int indiceArquivo) {
        for (int i = indiceArquivo; i > 0; i--) {
            ArquivoMultimidia temp = arquivos[i - 1];
            arquivos[i - 1] = arquivos[i];
            arquivos[i] = temp;
        }
    }

    public String[] listarArquivos() {
        String lista[] = new String[indiceUltimoArquivo + 1];
        for (int i = 0; i < indiceUltimoArquivo + 1; i++) {
            lista[i] = arquivos[i].getNomeArquivo();
        }
        return lista;
    }

    @Override
    public Playlist clone() {
        Playlist playlist = new Playlist();
        for (int i = 0; i < indiceUltimoArquivo + 1; i++) {
            playlist.adicionarItem(this.arquivos[i].clone());
        }
        return playlist;
    }
}
