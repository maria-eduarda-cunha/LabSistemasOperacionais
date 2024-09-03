#include <fcntl.h>  // open e suas flags
#include <unistd.h> // read, write e close
#include <stdio.h>  // printf
#include <stdlib.h> // EXIT_SUCCESS e EXIT_FAILURE

#define BUFFER_SIZE 128

int main() {

    const char *arquivo_entrada = "lab2_ex3_origem.txt";
    const char *arquivo_saida = "lab2_ex3_destino.txt";

    int fd_in, fd_out;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // ********** ARQUIVO ORIGEM **********
    // Abrir o arquivo em modo de leitura
    fd_in = open(arquivo_entrada, O_RDONLY);

    // Verifica se o arquivo foi aberto com sucesso
    if (fd_in == -1) {
        perror("Não foi possível abrir o arquivo de origem");
        return EXIT_FAILURE;
    }
    // *************************************


    // ********** ARQUIVO DESTINO **********
    // Abrir ou criar o arquivo em modo de escrita
    fd_out = open(arquivo_saida, O_WRONLY | O_CREAT | O_TRUNC);

    // Verifica se o arquivo foi aberto com sucesso
    if (fd_out == -1) {
        perror("Não foi possível abrir ou criar o arquivo de destino");
        close(fd_in);
        return EXIT_FAILURE;
    }
    // *************************************


    // Loop para ler o conteúdo do arquivo de origem e escrever no arquivo de destino
    while ((bytes_read = read(fd_in, buffer, BUFFER_SIZE)) > 0) {
        if (write(fd_out, buffer, bytes_read) != bytes_read) {
            perror("Erro ao escrever no arquivo de destino");
            close(fd_in);
            close(fd_out);
            return EXIT_FAILURE;
        }
    }

    // Verifica se ocorreu erro na leitura
    if (bytes_read == -1) {
        perror("Erro ao ler o arquivo de origem");
        close(fd_in);
        close(fd_out);
        return EXIT_FAILURE;
    }

    // Fecha os arquivos após a operação
    close(fd_in);
    close(fd_out);

    printf("Conteúdo copiado com sucesso de '%s' para '%s'.\n", arquivo_entrada, arquivo_saida);

    return EXIT_SUCCESS;
}
