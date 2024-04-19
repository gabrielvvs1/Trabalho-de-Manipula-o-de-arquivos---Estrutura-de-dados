#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 93

typedef struct aluno { // Essa estrutura chamada "Aluno" armazena informações de cada aluno, como nome, notas, média e situação "aprovado ou reprovado"
    char nome_aluno[100];
    float nota_primeira_avaliacao;
    float nota_segunda_avaliacao;
    float media;
    char situacao_aluno[100];
} Aluno;

void lerArquivo(char *nomeArquivo, Aluno *listaAlunos);
void calcularMedia(Aluno *listaAlunos, int tamanhoArray);
void determinarSituacao(Aluno *listaAlunos, int tamanhoArray);
void gerarArquivo(char *nomeArquivo, Aluno *listaAlunos, int tamanhoArray);

int main() { // FUNÇÃO PRINCIPALL
    Aluno listaAlunos[MAX_LEN];
    int tamanhoArray = sizeof(listaAlunos) / sizeof(listaAlunos[0]);

    lerArquivo("DadosEntrada.csv", listaAlunos);
    calcularMedia(listaAlunos, tamanhoArray);
    determinarSituacao(listaAlunos, tamanhoArray);
    gerarArquivo("SituacaoFinal.cvs", listaAlunos, tamanhoArray);

    return 0;
}

void gerarArquivo(char *nomeArquivo, Aluno *listaAlunos, int tamanhoArray){ // função que gera um novo arquivo CSV com os resultados das médias e situação final dos alunos.
    FILE *f;
    f = fopen(nomeArquivo, "w");

    if(f == NULL){
        printf("O arquivo não pode ser aberto!\n");
        exit(1);
    }

    for (int i = 0; i < tamanhoArray; ++i){
        fprintf(f,"%s, %.2f, %s", listaAlunos[i].nome_aluno, listaAlunos[i].media, listaAlunos[i].situacao_aluno);
        fprintf(f,"\n");
    }
    fclose(f);
    printf("Arquivo gerado com sucesso! - %s\n", nomeArquivo);
}

void calcularMedia(Aluno *listaAlunos, int tamanhoArray){ //  função que calcula a média das notas e determinam se o aluno foi aprovado ou reprovado usando a base da media
    for (int i = 0; i < tamanhoArray; ++i) {
        listaAlunos[i].media = (listaAlunos[i].nota_primeira_avaliacao + listaAlunos[i].nota_segunda_avaliacao) / 2;
    }
    printf("Calculando média dos alunos!\n");
}

void determinarSituacao(Aluno *listaAlunos, int tamanhoArray){ // determina a situação do aluno se esta aprovado ou reprovadoo.
    for (int i = 0; i < tamanhoArray; ++i) {
        if(listaAlunos[i].media >= 7) strcpy(listaAlunos[i].situacao_aluno, "APROVADO");
        else strcpy(listaAlunos[i].situacao_aluno, "REPROVADO");
    }
    printf("Determinando situação dos alunos!\n");
}

void lerArquivo(char *nomeArquivo, Aluno *listaAlunos) { //função que ler os dados de "DadosEntrada.csv" e armazena esses dados na estrutura Aluno.
    FILE *fp;
    int numeroLinha = 0;
    char linha[MAX_LEN];
    char *token;

    fp = fopen(nomeArquivo, "r");

    if (fp == NULL) {
        printf("O arquivo não pode ser aberto!\n");
        exit(1);
    }

    while (fgets(linha, MAX_LEN, fp) != NULL) {
        if (numeroLinha > 0) {
            token = strtok(linha, ",");
            strcpy(listaAlunos[numeroLinha - 1].nome_aluno, token);

            token = strtok(NULL, ",");
            token = strtok(NULL, ",");

            token = strtok(NULL, ",");
            listaAlunos[numeroLinha - 1].nota_primeira_avaliacao = atof(token);

            token = strtok(NULL, ",");
            listaAlunos[numeroLinha - 1].nota_segunda_avaliacao = atof(token);
        }
        numeroLinha++;
    }
    printf("Lendo arquivo!\n");
    fclose(fp);
}