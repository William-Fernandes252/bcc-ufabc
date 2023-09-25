package jogo;

class EstrategiaA implements EstrategiaJogo {
    public int[] getProximaJogada(char[][] dadosTabuleiro, char jogador) {
        for (int linha = 0; linha < dadosTabuleiro.length; linha++) {
            for (int coluna = 0; coluna < dadosTabuleiro[linha].length; coluna++) {
                if (dadosTabuleiro[linha][coluna] == '.')
                    return new int[] { linha, coluna };
            }
        }
        return null;
    }
}

class EstrategiaB implements EstrategiaJogo {
    public int[] getProximaJogada(char[][] dadosTabuleiro, char jogador) {
        if (dadosTabuleiro[1][1] == '.') {
            return new int[] { 1, 1 };
        }
        if (dadosTabuleiro[0][0] == '.') {
            return new int[] { 0, 0 };
        }
        if (dadosTabuleiro[0][2] == '.') {
            return new int[] { 0, 2 };
        }
        if (dadosTabuleiro[2][0] == '.') {
            return new int[] { 2, 0 };
        }
        if (dadosTabuleiro[2][2] == '.') {
            return new int[] { 2, 2 };
        }
        if (dadosTabuleiro[0][1] == '.') {
            return new int[] { 0, 1 };
        }
        if (dadosTabuleiro[1][0] == '.') {
            return new int[] { 1, 0 };
        }
        if (dadosTabuleiro[1][2] == '.') {
            return new int[] { 1, 2 };
        }
        if (dadosTabuleiro[2][1] == '.') {
            return new int[] { 2, 1 };
        }
        return null;
    }
}