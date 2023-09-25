import plano.PlanoDeAulas;
import plano.PlanoDeAulasExtended;
import plano.Teorica;
import plano.Prova;

public class ProgramaAvaliacao {
	public static void main(String[] args) {
		try {
			PlanoDeAulas plano1 = new PlanoDeAulas();
			// Adiciona uma nova aula Teorica com descricao "Introducao" (e carga horaria = 2h)
			// Quando a carga horaria nao eh especificada, o padrao sera 2h
			plano1.adicionar(new Teorica("Introducao"));
			
			// Adiciona uma nova Prova com peso 2 e descricao "P1" (e carga horaria = 2h)
			// Quando a carga horaria nao eh especificada, o padrao sera 2h
			plano1.adicionar(new Prova(2, "P1"));
			
			plano1.adicionar(new Teorica("POO"));
			plano1.adicionar(new Teorica("Revisao"));
			plano1.adicionar(new Prova(3, "P2"));
			
			System.out.println("--- Plano 1 ---");
			plano1.imprimir();
			System.out.println(plano1.getFormula());
			System.out.println("---------------\n");

            // Observe o tipo da variável e o tipo do objeto instanciado
			PlanoDeAulas plano2 = new PlanoDeAulasExtended();
			
			// Adiciona uma nova aula Teorica com descricao "Introducao" e carga horaria = 1h
			// Observe que a carga horaria foi especificada neste caso: 1h
			plano2.adicionar(new Teorica("Introducao", 1));
			
			// Adiciona uma nova Prova com peso 2, descricao "P1" e carga horaria = 3h
			// Observe que a carga horaria foi especificada neste caso: 3h
			plano2.adicionar(new Prova(2, "P1", 3));
			
			plano2.adicionar(new Teorica("POO", 5));
			plano2.adicionar(new Teorica("Revisao", 2));
			System.out.println("--- Plano 2(a) ---");
			
			// Observe que a impressão aqui mostra a carga horária de cada aula
			plano2.imprimir();
			System.out.println("---------------\n");

			plano2.adicionar(new Prova(3, "P2", 2));
			System.out.println("--- Plano 2(b) ---");
			plano2.imprimir();
			System.out.println("---------------\n");

			// Observe que a variavel plano3 referencia o mesmo objeto referenciado por plano2
			PlanoDeAulasExtended plano3 = (PlanoDeAulasExtended) plano2;

			// O metodo removerAvaliacoes remove do vetor do plano todos os objetos que implementam a interface Avaliacao
			plano3.removerAvalicoes();
			
			System.out.println("--- Plano 3(a) ---");
			plano3.imprimir();
			System.out.println("---------------\n");

			plano3.adicionar(new Prova(2, "P1", 1));
			plano3.adicionar(new Prova(2, "P2", 1));
			System.out.println("--- Plano 3(b) ---");
			plano3.imprimir();
			System.out.println("---------------\n");

			PlanoDeAulasExtended plano4 = new PlanoDeAulasExtended();
			plano4.adicionar(new Prova(2, "P1", 1));
			plano4.adicionar(new Prova(2, "P2", 2));
			plano4.adicionar(new Prova(2, "P3", 3));
			plano4.adicionar(new Teorica("Revisao", 4));
			System.out.println("--- Plano 4(a) ---");
			plano4.imprimir();
			System.out.println("---------------\n");

			plano4.removerAvalicoes();
			System.out.println("--- Plano 4(b) ---");
			plano4.imprimir();
			System.out.println("---------------\n");

			// O metodo comparar compara as cargas horarias totais de dois planos de aula.
			// Para obter a carga horaria total, eh necessario somar os valores de carga horaria de cada uma das aulas no vetor do plano.
			// O retorno do método é um valor int:
			//  -1: se a carga horaria do plano3 eh menor que a carga horaria do plano4
			//  0: se a carga horaria do plano3 eh igual à carga horaria do plano4
			//  +1: se a carga horaria do plano3 eh maior que a carga horaria do plano4
			System.out.println(String.format("Comparar plano3 e plano4: %d", plano3.comparar(plano4)));
			
			// O metodo compararPlanos compara as cargas horarias totais de dois planos de aula (PlanoDeAulasExtended), de forma similar ao metodo comparar na linha anterior.
			System.out.println(String.format("Comparar plano3 e plano4: %d", PlanoDeAulasExtended.compararPlanos(plano3, plano4)));

			System.out.println(String.format("Comparar plano4 e plano3: %d", plano4.comparar(plano3)));
			System.out.println(String.format("Comparar plano4 e plano3: %d", PlanoDeAulasExtended.compararPlanos(plano4, plano3)));			
			System.out.println(String.format("Comparar plano4 e plano4: %d", plano4.comparar(plano4)));
			System.out.println(String.format("Comparar plano4 e plano4: %d", PlanoDeAulasExtended.compararPlanos(plano4, plano4)));
		} catch (Exception e) {
			System.out.println(e);
		}
	}
}
