package plano;
 
public class PlanoDeAulasExtended extends PlanoDeAulas {
    public void removerAvalicoes() {
        for (int i = 0; i <= this.ultimaAula; i++) {
            if (vetor[i] instanceof Avaliacao) {
                for (int j = i; j < this.ultimaAula; j++) {
                    vetor[j] = vetor[j + 1];
                }
                this.ultimaAula--;
                i--;
            }
        }
    }

    @Override
	public void imprimir() {
		for (int i = 0; i <= ultimaAula; i++)
			System.out.println(
				String.format("- [%s]: %s (%sh)",
					vetor[i].getTipo(),
					vetor[i].getDescricao(),
                    vetor[i].getCargaHoraria()
                )
            );
	}

    public int getCargaHoraria() {
        int cargaHorariaTotal = 0;
        for (int i = 0; i <= this.ultimaAula; i++) {
            if (vetor[i] instanceof Aula) {
                cargaHorariaTotal += vetor[i].getCargaHoraria();
            }
        }
        return cargaHorariaTotal;
    }

    public static int compararPlanos (PlanoDeAulasExtended plano1, PlanoDeAulasExtended plano2) {
        if (plano1.getCargaHoraria() > plano2.getCargaHoraria()) {
            return 1;
        } else if (plano1.getCargaHoraria() < plano2.getCargaHoraria()) {
            return -1;
        } else {
            return 0;
        }
    }

    public int comparar(PlanoDeAulasExtended outro) {
        return compararPlanos(this, outro);
    }
}