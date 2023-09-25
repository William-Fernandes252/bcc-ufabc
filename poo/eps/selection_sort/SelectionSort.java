import java.util.Scanner;

public class SelectionSort {
    public static int ordenar (int arr[]){
        int swaps = 0;
        int min;
        for (int i = 0; i < arr.length - 1; i++) {
            min = i;
            for (int j = i + 1; j < arr.length; j++) {
                if (arr[j] < arr[min]) {
                    min = j;
                }
            }
            if (min != i) {
                swaps++;
                int temp = arr[i];
                arr[i] = arr[min];
                arr[min] = temp;
            }
        }
        return swaps;
    }

    public static void printArray(int arr[]){
        for (int i = 0; i < arr.length; i++) {
            System.out.print(arr[i] + " ");
        }
        System.out.println();
    } 

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);

        int n = input.nextInt();
        int arr[] = new int[n];
        for (int i = 0; i < n; i++) {
            arr[i] = input.nextInt();
        }

        printArray(arr);
        int swaps = ordenar(arr);
        printArray(arr);
        System.out.println("Trocas: " + swaps);

        input.close();
    }
}
