package jogo;

public class TabuleiroEstrategia extends Tabuleiro {
    private EstrategiaJogo strategyJogador1;
    private EstrategiaJogo strategyJogador2;
    private char jogadorAtual;

    public void setStrategyJogador1(EstrategiaJogo strategyJogador1) {
        this.strategyJogador1 = strategyJogador1;
    }

    public void setStrategyJogador2(EstrategiaJogo strategyJogador2) {
        this.strategyJogador2 = strategyJogador2;
    }

    public char getJogadorAtual() {
        return jogadorAtual;
    }

    public void setJogadorAtual(char jogadorAtual) {
        if (jogadorAtual != 'X' && jogadorAtual != 'O') {
            throw new RuntimeException(String.format("setJogadorAtual(): jogador invalido: [%c].", jogadorAtual));
        }
        this.jogadorAtual = jogadorAtual;
    }

    public void toggleJogadorAtual() {
        if (jogadorAtual == 'X') {
            setJogadorAtual('O');
        } else {
            setJogadorAtual('X');
        }
    }

    public EstrategiaJogo getStrategyJogadorAtual() {
        if (jogadorAtual == 'X') {
            return strategyJogador1;
        } else {
            return strategyJogador2;
        }
    }

    public int[] getJogada() {
        return this.getStrategyJogadorAtual().getProximaJogada(this.getTabuleiro(), this.getJogadorAtual());
    }

    public void jogarPartida() {
        this.setJogadorAtual('X');
        while (this.getJogadorVencedor() == '.') {
            this.jogar(
                    jogadorAtual,
                    this.getJogada()[0],
                    this.getJogada()[1]);
            this.toggleJogadorAtual();
        }
    }
}
