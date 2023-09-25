import java.util.Scanner;
import java.util.Arrays;

public class TestesDiscosVoadores {
    public static int[][] girarMatriz(int[][] matriz) {
        int linhas = matriz.length;
        int colunas = matriz[0].length;

        int[][] matrizGirada = new int[colunas][linhas];

        for (int i = 0; i < linhas; i++) {
            for (int j = 0; j < colunas; j++) {
                matrizGirada[j][i] = matriz[i][j];
            }
        }

        return matrizGirada;
    }

    public static int ordemLexicografica(int[] a, int[] b) {
        return Arrays.compare(a, b);
    }

    public static void ordenarLinhas(int[][] dados) {
        int inversoes;
        do {
            inversoes = 0;
            for (int i = 0; i < dados.length - 1; i++) {
                if (ordemLexicografica(dados[i], dados[i + 1]) > 0) {
                    int[] temp = dados[i];
                    dados[i] = dados[i + 1];
                    dados[i + 1] = temp;
                    inversoes++;
                }
            }
        } while (inversoes > 0);
    }

    public static void imprimirMatriz(int[][] matriz) {
        for (int i = 0; i < matriz.length; i++) {
            for (int j = 0; j < matriz[i].length; j++) {
                System.out.print(matriz[i][j] + (j < matriz[i].length - 1 ? " " : ""));
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        
        int nLinhas = input.nextInt();
        int nColunas = input.nextInt();
        int[][] dados = new int[nLinhas][nColunas];
        int[][] resultado = new int[nLinhas][nColunas];

        for (int i = 0; i < dados.length; i++) {
            for (int j = 0; j < dados[i].length; j++) {
                dados[i][j] = input.nextInt();
            }
        }

        ordenarLinhas(dados);        

        imprimirMatriz(dados);
        System.out.println();

        dados = girarMatriz(dados);
        ordenarLinhas(dados);
        for (int i = 0; i < dados.length; i++) {
            for (int j = 0; j < dados[i].length; j++) {
                resultado[j][i] = dados[i][j];
            }
        }

        imprimirMatriz(resultado);

        input.close();
    }
}