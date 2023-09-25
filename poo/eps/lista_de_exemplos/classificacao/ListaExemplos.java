package classificacao;

interface Comparator<T> {
    int compare(T o1, T o2);
}

class ExcecaoDadosInvalidos extends Exception {
    private int qtdAtributosTreinamento;
    private int qtdAtributosPredizer;

    public ExcecaoDadosInvalidos(int qtdAtributosTreinamento, int qtdAtributosPredizer) {
        super("Dados inválidos");
        this.qtdAtributosTreinamento = qtdAtributosTreinamento;
        this.qtdAtributosPredizer = qtdAtributosPredizer;
    }

    public int getQtdAtributosTreinamento() {
        return qtdAtributosTreinamento;
    }

    public int getQtdAtributosPredizer() {
        return qtdAtributosPredizer;
    }
}

class Exemplo {
    private double[] atributosEntrada;
    private int rotuloClasse;

    public Exemplo(double[] atributosEntrada, int rotuloClasse) {
        this.atributosEntrada = atributosEntrada;
        this.rotuloClasse = rotuloClasse;
    }

    public double[] getAtributosEntrada() {
        return atributosEntrada.clone();
    }

    public int getRotuloClasse() {
        return rotuloClasse;
    }
}

class ExemploComparator implements Comparator<Exemplo> {
    private double[] atributosEntrada;

    public ExemploComparator(double[] atributosEntrada) {
        this.atributosEntrada = atributosEntrada;
    }

    public double getAtributoFromExemplo(Exemplo exemplo, int atributoIndex) {
        try {
            return exemplo.getAtributosEntrada()[atributoIndex];
        } catch (ArrayIndexOutOfBoundsException e) {
            return 0.0;
        }
    }

    protected double distanciaFromAtributos(Exemplo exemplo) {
        double distancia = 0;
        for (int i = 0; i < atributosEntrada.length; i++) {

            distancia += Math.pow(getAtributoFromExemplo(exemplo, i) - atributosEntrada[i], 2);
        }
        return Math.sqrt(distancia);
    }

    @Override
    public int compare(Exemplo o1, Exemplo o2) {
        return Double.compare(distanciaFromAtributos(o1), distanciaFromAtributos(o2));
    }
}

public class ListaExemplos {
    private int maxQtd;
    private int ultimoExemploIndex = -1;
    private Exemplo[] exemplos;

    public ListaExemplos(int maxQtd) {
        this.maxQtd = maxQtd;
        this.exemplos = new Exemplo[maxQtd];
    }

    public void adicionarExemplo(double[] atributosEntrada, int rotuloClasse) {
        adicionarExemplo(new Exemplo(atributosEntrada, rotuloClasse));
    }

    public void adicionarExemplo(Exemplo exemplo) {
        if (ultimoExemploIndex < maxQtd - 1) {
            ultimoExemploIndex++;
            exemplos[ultimoExemploIndex] = exemplo;
        }
    }

    public int getQtdExemplos() {
        return ultimoExemploIndex + 1;
    }

    public Exemplo[] getExemplos() {
        Exemplo[] cleanedExemplos = new Exemplo[ultimoExemploIndex + 1];
        for (int i = 0; i < ultimoExemploIndex + 1; i++) {
            cleanedExemplos[i] = exemplos[i];
        }
        return cleanedExemplos;
    }

    public Exemplo[] getPrimeirosExemplos(int n) {
        if (n > ultimoExemploIndex + 1) {
            n = ultimoExemploIndex + 1;
        }
        Exemplo[] exemplosPrimeiros = new Exemplo[n];
        for (int i = 0; i < n; i++) {
            exemplosPrimeiros[i] = exemplos[i];
        }
        return exemplosPrimeiros;
    }

    public Exemplo[] getUltimosExemplos(int n) {
        if (n > ultimoExemploIndex + 1) {
            n = ultimoExemploIndex + 1;
        }
        Exemplo[] exemplosUltimos = new Exemplo[n];
        for (int i = ultimoExemploIndex, j = n - 1; i >= ultimoExemploIndex - n + 1; i--, j--) {
            exemplosUltimos[j] = exemplos[i];
        }
        return exemplosUltimos;
    }

    public void ordenarPelaDistancia(double[] atributosEntrada) {
        ExemploComparator exemploComparator = new ExemploComparator(atributosEntrada);
        int trocas;
        do {
            trocas = 0;
            for (int i = 0; i < ultimoExemploIndex; i++) {
                if (exemploComparator.compare(exemplos[i], exemplos[i + 1]) > 0) {
                    trocas++;
                    Exemplo temp = exemplos[i];
                    exemplos[i] = exemplos[i + 1];
                    exemplos[i + 1] = temp;
                }
            }
        } while (trocas > 0);
    }
}
