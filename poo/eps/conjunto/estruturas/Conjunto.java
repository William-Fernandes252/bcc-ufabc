package estruturas;

public class Conjunto implements Lista {
    private int[] elementos = new int[0];

    public int getQtd() {
        return elementos.length;
    }

    public void adicionar(int numero) {
        if (buscar(numero) == -1) {
            int[] newElementos = new int[elementos.length + 1];
            for (int i = 0; i < elementos.length; i++) {
                newElementos[i] = elementos[i];
            }
            newElementos[elementos.length] = numero;
            elementos = newElementos;
        }
    }

    public void remover(int numero) {
        if (buscar(numero) != -1) {
            int[] newElementos = new int[elementos.length - 1];
            for (int i = 0, j = 0; i < elementos.length; i++) {
                if (elementos[i] != numero) {
                    newElementos[j] = elementos[i];
                    j++;
                }
            }
            elementos = newElementos;
        }
    }

    public int buscar(int numero) {
        for (int i = 0; i < elementos.length; i++) {
            if (elementos[i] == numero) {
                return i;
            }
        }
        return -1;
    }

    @Override
    public String toString() {
        String string = "";
        for (int i = 0; i < elementos.length; i++) {
            string += elementos[i] + (i == elementos.length - 1 ? "" : " ");
        }
        return string;
    }

    public Conjunto uniao(Conjunto outro) {
        Conjunto conjunto = new Conjunto();
        for (int i = 0; i < elementos.length; i++) {
            conjunto.adicionar(elementos[i]);
        }
        for (int i = 0; i < outro.elementos.length; i++) {
            conjunto.adicionar(outro.elementos[i]);
        }
        return conjunto;
    }

    public static Conjunto uniao(Conjunto a, Conjunto b) {
        return a.uniao(b);
    }

    public Conjunto intersecao(Conjunto outro) {
        Conjunto conjunto = new Conjunto();
        for (int i = 0; i < elementos.length; i++) {
            if (outro.buscar(elementos[i]) != -1) {
                conjunto.adicionar(elementos[i]);
            }
        }
        return conjunto;
    }

    public static Conjunto intersecao(Conjunto a, Conjunto b) {
        return a.intersecao(b);
    }
}
