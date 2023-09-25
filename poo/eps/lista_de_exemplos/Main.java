import classificacao.KNN;
import classificacao.ListaExemplos;

public class Main {
    public static void main(String[] args) {
        ListaExemplos l = new ListaExemplos(100);
        l.adicionarExemplo(new double[] { 1.00, 0.90, 1.10 }, 111);
        l.adicionarExemplo(new double[] { 1.10, 0.80, 1.00 }, 111);
        l.adicionarExemplo(new double[] { 4.00, 8.00, 0.90 }, 222);
        l.adicionarExemplo(new double[] { 1.20, 1.10, 0.90 }, 111);
        l.adicionarExemplo(new double[] { 4.00, 6.00, 0.10 }, 222);
        KNN knn = new KNN(3);
        knn.setDadosTreinamento(l);
        try {
            int rotuloPredicao = knn.predizer(new double[] { 5, 7, 1 });
            System.out.println(rotuloPredicao);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
