import palavras.PalavraEncontrada;
import palavras.Tabuleiro;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.function.Predicate;

public class TestePalavras {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        char[][] letras = new char[input.nextInt()][input.nextInt()];
        for (int i = 0; i < letras.length; i++) {
            for (int j = 0; j < letras[i].length; j++) {
                letras[i][j] = input.next().charAt(0);
            }
        }

        Tabuleiro tabuleiro = new Tabuleiro(letras);

        int nPalavras = input.nextInt();
        ArrayList<PalavraEncontrada> palavrasEncontradas = new ArrayList<PalavraEncontrada>(nPalavras);
        for (int i = 0; i < nPalavras; i++) {
            String palavra = input.next();
            palavrasEncontradas.add(tabuleiro.buscar(palavra));
        }

        Predicate<? super PalavraEncontrada> isNotNull = p -> p != null;
        System.out.println("Palavras encontradas: " + palavrasEncontradas.stream().filter(isNotNull).count());

        palavrasEncontradas.stream().filter(isNotNull).forEach(p -> {
            String tipo;
            switch (p.getTipo()) {
                case 1: tipo = "linha"; break;
                case 2: tipo = "coluna"; break;
                case 3: tipo = "diagonal"; break;
                default: tipo = "erro";
            }

            int[] posicao = p.getPosicao();

            System.out.println(p.getPalavra() + " (L: " + posicao[0] + ", C: " + posicao[1] + ", T: " + tipo + ", D: " + p.getDirecao() + ")");
        });

        input.close();
    }    
}
