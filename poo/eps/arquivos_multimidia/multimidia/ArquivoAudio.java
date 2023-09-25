package multimidia;

public class ArquivoAudio extends ArquivoMultimidia {
    private boolean audioHD;

    public ArquivoAudio(String nomeArquivo, boolean audioHD) {
        super(nomeArquivo);
        this.audioHD = audioHD;
    }

    public boolean getAudioHD() {
        return audioHD;
    }

    @Override
    public String toString() {
        return String.format(
            "Audio: %s (HD = %s)",
            this.getNomeArquivo(),
            this.getAudioHD() ? "true" : "false"
        );
    }
}
