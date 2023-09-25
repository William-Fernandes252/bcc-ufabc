import java.util.Scanner;
import acesso.Usuario;
import acesso.UsuarioBloqueado;
import acesso.SenhaInvalida;
import acesso.Impressao;

public class AutenticacaoUsuario {
    private static Usuario[] usuarios;
    private static Scanner input = new Scanner(System.in);

    public static void usuariosFromConsole() {
        int qtdUsuarios = input.nextInt();
        usuarios = new Usuario[qtdUsuarios];
        for (int i = 0; i < qtdUsuarios; i++) {
            String login = input.next();
            String senha = input.next();
            usuarios[i] = new Usuario(login, senha);
        }
    }

    public static void autenticarUsuario(String login, String senha) {
        try {
            getUsuario(login).autenticar(senha);
            Impressao.imprimirUsuarioAutenticado(login);
        } catch (SenhaInvalida exc) {
            Impressao.imprimirSenhaInvalida(login);
        } catch (UsuarioBloqueado exc) {
            Impressao.imprimirUsuarioBloqueado(login);
        }
    }

    public static Usuario getUsuario(String login) {
        for (Usuario usuario : usuarios) {
            if (usuario.getLogin().equals(login)) {
                return usuario;
            }
        }
        return null;
    }

    public static void main(String[] args) {
        usuariosFromConsole();
        int qtdTentativasAutenticacao = input.nextInt();
        for (int i = 0; i < qtdTentativasAutenticacao; i++) {
            String login = input.next();
            String senha = input.next();
            autenticarUsuario(login, senha);
        }
    }
}
