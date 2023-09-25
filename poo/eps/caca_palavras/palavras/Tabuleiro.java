package palavras;

public class Tabuleiro {
    private char[][] letras;

    public Tabuleiro(char[][] matriz) {
        this.letras = matriz;
    }

    public Tabuleiro(int qtdLinhas, int qtdColunas, char[] dadosMatriz) {
        this(new char[qtdLinhas][qtdColunas]);
        for (int i = 0; i < qtdLinhas; i++) {
            for (int j = 0; j < qtdColunas; j++) {
                this.letras[i][j] = dadosMatriz[i * qtdColunas + j];
            }
        }
    }

    private String getStringFromTipoEDirecao(int linha, int coluna, int tipo, int direcao, int maxSize) {
        String result = "";
        switch (tipo) {
            case 1: {
                if (direcao == 1) {
                    for (int i = 0; i < maxSize && coluna + i < this.letras[linha].length; i++) {
                        result += this.letras[linha][coluna + i];
                    }
                } else if (direcao == 2) {
                    for (int i = coluna; i >= coluna - maxSize && i >= 0; i--) {
                        result += this.letras[linha][i];
                    }   
                }
            }; break;
            case 2: {
                if (direcao == 1) {
                    for (int i = 0; i < maxSize && linha + i < this.letras.length; i++) {
                        result += this.letras[linha + i][coluna];
                    }
                } else if (direcao == 2) {
                    for (int i = linha; i >= linha - maxSize && i >= 0; i--) {
                        result += this.letras[i][coluna];
                    }
                }
            }; break;
            case 3: {        
                for (int k = 0; k < maxSize; k++) {
                    int i = linha + (direcao == 1 || direcao == 4 ? -k : k);
                    int j = coluna + (direcao == 3 || direcao == 4 ? -k : k);
                    if (i >= 0 && i < this.letras.length && j >= 0 && j < this.letras[i].length) {
                        result += this.letras[i][j];
                    }
                }
            }; break;
        }

        return result;
    }

    private int[] checkPalavraInDirecoes(int linha, int coluna, String palavra) {
        for (
                int[] caso : new int[][]{
                new int []{1, 1}, // Linha-1
                new int []{1, 2}, // Linha-2
                new int []{2, 1}, // Coluna-1
                new int []{2, 2}, // Coluna-2
                new int []{3, 1}, // Diagonal-1
                new int []{3, 2}, // Diagonal-2
                new int []{3, 3}, // Diagonal-3
                new int []{3, 4}, // Diagonal-4
            }
        ) {
            String stringFromTipoEDirecao = getStringFromTipoEDirecao(
                linha,
                coluna,
                caso[0], 
                caso[1], 
                palavra.length()
            );
            if (stringFromTipoEDirecao.contains(palavra)) {
                return caso;
            }
        }

        return null;
    }

    public PalavraEncontrada buscar(String palavra) {
        for (int i = 0; i < this.letras.length; i++) {
            for (int j = 0; j < this.letras[i].length; j++) {
                if (this.letras[i][j] == palavra.charAt(0)) {
                    int[] tipoEDirecao = this.checkPalavraInDirecoes(i, j, palavra);
                    if (tipoEDirecao != null) {
                        return new PalavraEncontrada(palavra, new int[]{i, j}, tipoEDirecao[0], tipoEDirecao[1]);
                    }
                }   
            }
        }
        return null;
    }

    public PalavraEncontrada[] buscar(String[] palavras) {
        int palavrasEncontradasCount = 0;
        PalavraEncontrada[] palavrasEncontradas = new PalavraEncontrada[palavras.length];

        for (String palavra : palavras) {
            PalavraEncontrada palavraEncontrada = this.buscar(palavra);
            if (palavraEncontrada != null) {
                palavrasEncontradas[palavrasEncontradasCount++] = palavraEncontrada;
            }
        }

        PalavraEncontrada[] resultado = new PalavraEncontrada[palavrasEncontradasCount];
        for (int i = 0; i < palavrasEncontradasCount; i++) {
            resultado[i] = palavrasEncontradas[i];
        }

        return resultado;
    }
}