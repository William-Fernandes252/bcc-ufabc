package plano;

public class PlanoDeAulas {
	Aula[] vetor = new Aula[5];
	int ultimaAula = -1;
	
	public final void adicionar(Aula novaAula) throws Exception {
		if (ultimaAula + 1 >= vetor.length)
			throw new Exception("Vetor cheio.");
		vetor[++ultimaAula] = novaAula;
	}
	
	public void imprimir() {
		for (int i = 0; i <= ultimaAula; i++)
			System.out.println(
				String.format("- [%s]: %s",
					vetor[i].getTipo(),
					vetor[i].getDescricao()));
	}
	
	public String getFormula() {
		String formula = "";
		for (int i = 0; i <= ultimaAula; i++) {
			if (vetor[i] instanceof Avaliacao) {
				if (!formula.equals(""))
					formula += " + ";
				formula += String.format("%.1f x %s",
					((Avaliacao)vetor[i]).getPeso(),
					vetor[i].getDescricao()
					);
			}
		}
		return formula;
	}
}