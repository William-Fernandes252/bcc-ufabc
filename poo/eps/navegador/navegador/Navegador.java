package navegador;

public class Navegador {
    private static final int MAX_HISTORICO = 100;
    private int limiteAbas;
    private int indexUltimaAba = -1;
    private int indexUltimaAcao = -1;
    private AbaNavegador[] abas;
    private String[] historico = new String[MAX_HISTORICO];

    public Navegador(int limiteAbas) {
        this.limiteAbas = limiteAbas;
        abas = new AbaNavegador[this.limiteAbas];
    }

    public AbaNavegador abrirAba(int tipo, String titulo) {
        if (indexUltimaAba < limiteAbas - 1) {
            switch (tipo) {
                case 1: return abas[++indexUltimaAba] = new AbaBuscador(this, titulo);
                case 2: return abas[++indexUltimaAba] = new AbaRedeSocial(this, titulo);
            }
        }
        return null;
    }

    boolean pushHistorico(String historico) {
        if (indexUltimaAcao < MAX_HISTORICO - 1) {
            this.historico[++indexUltimaAcao] = historico;
            return true;
        }
        return false;
    }

    public void fecharAba(AbaNavegador aba) {
        for (int i = 0; i < indexUltimaAba; i++) {
            if (abas[i] == aba) {
                for (int j = i; j < indexUltimaAba; j++) {
                    abas[j] = abas[j + 1];
                }
                indexUltimaAba--;
                break;
            }
        }
    }

    public String[] getAbas() {
        String abas[] = new String[indexUltimaAba + 1];
        for (int i = 0; i <= indexUltimaAba; i++) {
            abas[i] = this.abas[i].toString();
        }
        return abas;
    }

    public String[] getHistorico() {
        int countAcoes = 0;
        for (int i = 0; i < MAX_HISTORICO; i++) {
            if (historico[i] != null) {
                countAcoes++;
            }
        }
        String cleanedHistorico[] = new String[countAcoes];

        int count = 0;
        for (int i = 0; i < MAX_HISTORICO; i++) {
            if (historico[i] != null) {
                cleanedHistorico[count] = historico[i];
                count++;
            }
        }
        return cleanedHistorico;
    }
}