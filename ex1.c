#include <fcntl.h>  // open e suas flags
#include <unistd.h> // read, write e close
#include <stdio.h>  // printf
#include <stdlib.h> // EXIT_SUCCESS e EXIT_FAILURE

#define BUFFER_SIZE 128

int main() {
    
    const char *arquivo_entrada = "lab2_ex1.txt";

    int fd_in;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Abrir o arquivo em modo de leitura
    fd_in = open(arquivo_entrada, O_RDONLY);

    // Se o arquivo não existe, cria-se
    if (fd_in == -1) {
        fd_in = open(arquivo_entrada, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);

        if (fd_in == -1) {
            perror("Não foi possível criar o arquivo");
            return EXIT_FAILURE;
        }

        // Se o arquivo foi criado, fechamos e reabrimos em modo de leitura
        close(fd_in);
        fd_in = open(arquivo_entrada, O_RDONLY);
    }

    // Verifica se o arquivo foi aberto com sucesso
    if (fd_in == -1) {
        perror("Não foi possível abrir o arquivo");
        return EXIT_FAILURE;
    }

    // Lê o conteúdo do arquivo para o buffer
    bytes_read = read(fd_in, buffer, BUFFER_SIZE - 1);

    // Verifica se ocorreu erro na leitura
    if (bytes_read == -1) {
        perror("Erro ao ler o arquivo");
        close(fd_in);
        return EXIT_FAILURE;
    }

    // Adiciona um caractere nulo (\0) ao final do buffer
    buffer[bytes_read] = '\0';

    // Exibe o conteúdo lido na tela
    printf("Conteúdo do arquivo:\n%s\n", buffer);

    // Fecha o arquivo após a leitura
    close(fd_in);

    return EXIT_SUCCESS;
}
