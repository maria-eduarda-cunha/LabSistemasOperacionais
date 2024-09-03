#include <fcntl.h>  // open e suas flags
#include <unistd.h> // read, write e close
#include <stdio.h>  // printf
#include <stdlib.h> // EXIT_SUCCESS e EXIT_FAILURE

#define BUFFER_SIZE 128

int main() {

    const char *arquivo_entrada = "lab2_ex2.txt";

    int fd_in;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read;

    // Abrir o arquivo em modo de leitura
    fd_in = open(arquivo_entrada, O_RDONLY);

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

    // Exibe a quantidade de linhas lidas na tela
    int numLinhas = 0;
    for(int i=0; i<bytes_read; i++){
        if(buffer[i] == '\n')
            numLinhas++;
    }
    // Exibe o conteúdo lido na tela
    printf("Quantidade de linhas do arquivo: %d\n", numLinhas);

    // Fecha o arquivo após a leitura
    close(fd_in);

    return EXIT_SUCCESS;
}
