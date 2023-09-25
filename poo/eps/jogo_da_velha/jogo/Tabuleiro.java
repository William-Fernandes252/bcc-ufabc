package jogo;

public class Tabuleiro {

    private char[][] tabuleiro;

    public Tabuleiro() {
        this.tabuleiro = new char[3][3];
        for (int linha = 0; linha < 3; linha++)
            for (int coluna = 0; coluna < 3; coluna++)
                this.tabuleiro[linha][coluna] = '.';
    }

    public char[][] getTabuleiro() {
        char[][] copia = this.tabuleiro.clone();
        for (int i = 0; i < this.tabuleiro.length; i++)
            copia[i] = this.tabuleiro[i].clone();
        return copia;
    }

    public char getJogadorVencedor() {
        for (int linha = 0; linha < 3; linha++) {
            if (tabuleiro[linha][0] != '.' && tabuleiro[linha][0] == tabuleiro[linha][1]
                    && tabuleiro[linha][1] == tabuleiro[linha][2])
                return tabuleiro[linha][0];
        }
        for (int coluna = 0; coluna < 3; coluna++) {
            if (tabuleiro[0][coluna] != '.' && tabuleiro[0][coluna] == tabuleiro[1][coluna]
                    && tabuleiro[1][coluna] == tabuleiro[2][coluna])
                return tabuleiro[0][coluna];
        }
        if (tabuleiro[0][0] != '.' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])
            return tabuleiro[0][0];
        if (tabuleiro[0][2] != '.' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])
            return tabuleiro[0][2];

        for (int linha = 0; linha < 3; linha++)
            for (int coluna = 0; coluna < 3; coluna++)
                if (this.tabuleiro[linha][coluna] == '.')
                    return '.';

        return '-';
    }

    public void jogar(char jogador, int linha, int coluna) {
        if (jogador != 'X' && jogador != 'O')
            throw new RuntimeException(String.format("jogar(): jogador invalido: [%c].", jogador));
        if (tabuleiro[linha][coluna] != '.')
            throw new RuntimeException(
                    String.format("jogar(): Posicao ja preenchida - linha=%d coluna=%d", linha, coluna));
        if (getJogadorVencedor() != '.')
            throw new RuntimeException(String.format("jogar(): O jogo esta encerrado.", linha, coluna));

        tabuleiro[linha][coluna] = jogador;

        for (int i = 0; i < 3; i++)
            System.out.println(String.format("%c %c %c", tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]));

        System.out.println("-----");
    }
}