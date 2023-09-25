import java.util.Optional;
import java.util.Scanner;

public class ProgramaLista {
    public static void ordenar(int[] v, Optional<Integer> n) {
        int length = n.isPresent() ? n.get().intValue() : v.length;
        for (int i = 0; i < length; i++) {
            for (int j = 0; j < length; j++) {
                if (v[j] > v[j + 1]) {
                    int temp = v[j];
                    v[j] = v[j + 1];
                    v[j + 1] = temp;
                }
            }
        }
    }

    public static int achar(int numero, int[] v) {
        for (int i = 0; i < v.length; i++) {
            if (v[i] == numero) {
                return i;
            }
        }
        return -1;
    }

    public static boolean inserir(int numero, int[] v) {
        for (int i = 0; i < v.length; i++) {
            if (v[i] == -1) {
                v[i] = numero;
                ordenar(v, Optional.of(i));
                return true;
            }
        }
        return false;
    }
    
    public static boolean remover(int numero, int[] v) {
        int indice = achar(numero, v);
        if (indice != -1) {
            for (int i = indice; i < v.length - 1; i++) {
                v[i] = v[i + 1];
            }
            v[v.length - 1] = -1;
            return true;
        }
        return false;
    }

    public static void imprimirLista(int arr[]){
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    } 

    public static String booleanParaString (boolean b) {
        return b ? "true" : "false";
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);        

        int n = input.nextInt();
        int v[] = new int[n];
        for (int i = 0; i < n; i++) {
            v[i] = input.nextInt();
        }

        imprimirLista(v);

        int operacao = input.nextInt();
        switch (operacao) {
            case 1:
                System.out.println("Inserir: " + booleanParaString(inserir(input.nextInt(), v)));
                break;
            case 2:
                System.out.println("Remover: " + booleanParaString(remover(input.nextInt(), v)));
                break;
        }

        imprimirLista(v);

        input.close();
    }
}
