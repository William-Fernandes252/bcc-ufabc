package classificacao;

public class KNN {
    private int k;
    private ListaExemplos dadosTreinamento;

    public KNN(int k) {
        this.k = k;
    }

    public void setDadosTreinamento(ListaExemplos dadosTreinamento) {
        this.dadosTreinamento = dadosTreinamento;
    }

    private void validateDadosTreinamento(double[] atributosEntrada) throws Exception, ExcecaoDadosInvalidos {
        if (dadosTreinamento == null) {
            throw new Exception("Dados de treinamento - nao inicializado");
        }

        for (Exemplo exemplo : dadosTreinamento.getExemplos()) {
            if (exemplo.getAtributosEntrada().length != atributosEntrada.length) {
                throw new ExcecaoDadosInvalidos(exemplo.getAtributosEntrada().length, atributosEntrada.length);
            }
        }
    }

    private int getRotuloMaisFrequente() {
        int ocorrenciaMaxima = 0, contagemOcorrencias, rotuloMaisFrequente = 0;
        Exemplo[] primeirosExemplos = dadosTreinamento.getPrimeirosExemplos(k);
        for (Exemplo exemplo : primeirosExemplos) {
            contagemOcorrencias = 0;
            for (Exemplo teste : primeirosExemplos) {
                if (exemplo.getRotuloClasse() == teste.getRotuloClasse()) {
                    contagemOcorrencias += 1;
                }
            }
            if (contagemOcorrencias > ocorrenciaMaxima) {
                ocorrenciaMaxima = contagemOcorrencias;
                rotuloMaisFrequente = exemplo.getRotuloClasse();
            }
        }
        return rotuloMaisFrequente;
    }

    public int predizer(double[] atributosEntrada) throws Exception, ExcecaoDadosInvalidos {
        validateDadosTreinamento(atributosEntrada);
        dadosTreinamento.ordenarPelaDistancia(atributosEntrada);
        return getRotuloMaisFrequente();
    }

}
