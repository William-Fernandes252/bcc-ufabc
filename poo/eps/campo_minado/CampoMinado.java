import java.util.Scanner;

public class CampoMinado {
    public static int minesAround(int[][] matrix, int x, int y) {
        int mines = 0;
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (i >= 0 && i < matrix.length && j >= 0 && j < matrix[0].length) {
                    if (matrix[i][j] == 1) {
                        mines++;
                    }
                }
            }
        }
        return mines;        
    }

    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);        

        int nLines = input.nextInt();
        int nColumns = input.nextInt();

        int matrix[][] = new int[nLines][nColumns];
        for (int i = 0; i < nLines; i++) {
            for (int j = 0; j < nColumns; j++) {
                matrix[i][j] = input.nextInt();
            }
        }

        int x = input.nextInt();
        int y = input.nextInt();
        int mines = minesAround(matrix, x, y);

        System.out.println(mines);

        input.close();
    }
}
