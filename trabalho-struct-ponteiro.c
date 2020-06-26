#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>

//struct
typedef struct{
    int ra;
    char nome[20];
    float nota1;
    float nota2;
}Aluno;

//auto increment RA
int autoRA = 0;

//var Aluno
Aluno aluno;

//ponteiro
FILE *ponteiro;

//CADASTRO
void inserir(){
    //var de continuar cadastro
    char resp;

    //usa o ponteiro p abrir o arquivo
    ponteiro = fopen("registro.txt", "ab");
    system("cls");

    //cadastro
    if(ponteiro == NULL){
        printf("Arquivo nao encontrado");
    }
    else{
        printf("Arquivo aberto, pronto para iniciar registro...\n");
        system("pause");
        system("cls");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("------------------------------------***FATEC Americana***------------------------------------\n");
        printf("-------------------------------------------CADASTRO------------------------------------------\n");
        printf("---------------------------------------------------------------------------------------------\n\n");

        do{

            fflush(stdin);
            autoRA++;
            aluno.ra = autoRA;

            printf("Digite o NOME do aluno: ");
            gets(aluno.nome);
            fflush(stdin);


            printf("Digite a NOTA 1 do aluno: ");
            scanf("%f", &aluno.nota1);
            fflush(stdin);


            printf("Digite a NOTA 2 do aluno: ");
            scanf("%f", &aluno.nota2);
            fflush(stdin);

            fwrite(&aluno, sizeof(Aluno),1,ponteiro);

            printf("Gravado com sucesso...Continuar ? [S/N] \n");
            scanf("%c", &resp);
            printf("\n\n");
        } while(resp == 's');


        system("pause");
    }
    fclose(ponteiro);
}

//EXIBE CADASTROS
void exibir(){
    ponteiro = fopen("registro.txt","rb");

    if(ponteiro == NULL){
        printf("Erro ao abrir o arquivo ou nao existe conteudo dentro do arquivo\n");
        system("pause");
    }
    else{
        system("cls");
        printf("---------------------------------------------------------------------------------------------\n");
        printf("------------------------------------***FATEC Americana***------------------------------------\n");
        printf("-------------------------------------------ALUNOS--------------------------------------------\n");
        printf("---------------------------------------------------------------------------------------------\n\n");

        printf("RA\t\tNOME\t\tNOTA1\t\tNOTA2\t\t\n");
        while(fread(&aluno, sizeof(Aluno), 1, ponteiro)){
            printf("%d\t\t%s\t\t%.2f\t\t%.2f\n", aluno.ra, aluno.nome, aluno.nota1, aluno.nota2);
        }
        system("pause");
    }
    fclose(ponteiro);
}

//ALTERA ALGUEM DO CADASTRO
void alterar(){

    //variaveis da funçao
    int contador = 0;
    int raPesquisa = 0;

    //abre ponteiro
    ponteiro = fopen("registro.txt", "rb+");

    //ra de quem vai ser buscado
    system("cls");
    printf("Digite o RA de quem deseja alterar os dados: ");
    scanf("%d", &raPesquisa);
    fflush(stdin);

    //se houver problema na abertura do arquivo, ou se estiver vazio
    if(ponteiro == NULL){
        printf("Erro ao abrir o arquivo ou nao existe conteudo dentro do arquivo\n");
        system("pause");
    }
    else{
        //le a primeira linha do arquivo
        fread(&aluno, sizeof(Aluno), 1, ponteiro);

        //enquanto o arquivo nao chegar ao final, e o RA for diferente do registrado
        while((!feof(ponteiro) && raPesquisa != aluno.ra)) {

            //continua lendo o arquivo e soma 1 ao contador
            fread(&aluno, sizeof(Aluno), 1, ponteiro);
            contador++;
        }

        //se o arquivo chegar ao final
        if(feof(ponteiro)){
            printf("\nRA NAO ENCONTRADO!\n");
            system("pause");
        }

        //se for encontado
        else{

            //a partir do ponteiro, pule x linhas do arquivo (x definido pelo contador), a partir do inicio do arquivo (seek_set)
            fseek(ponteiro, contador * sizeof(Aluno), SEEK_SET);

            printf("\nENCONTRADO...\n");
            printf("Informar os novos valores\nRA: %d -- Aluno: %s", aluno.ra, aluno.nome);

            printf("\n\nNOVA NOTA 1: ");
            scanf("%f", &aluno.nota1);
            fflush(stdin);

            printf("NOVA NOTA 2: ");
            scanf("%f", &aluno.nota2);
            fflush(stdin);

            //grava alteraçoes
            fwrite(&aluno, sizeof(Aluno),1,ponteiro);
            printf("\nRegistro alterado com sucesso\n\n");
            system("pause");
        }

    }


    fclose(ponteiro);
}

//menuzin
void menu(int op){
    while(op != 4) {
        system("cls");
        printf("[1] Inserir novo registro...\n");
        printf("[2] Exibir os registros...\n");
        printf("[3] Alterar registro...\n");
        printf("[4] Sair do sistema...\n");

        printf("Informe a opcao desejada...");
        scanf("%d", &op);
        fflush(stdin);

        switch(op) {
        case 1:
            inserir();
            break;
        case 2:
            exibir();
            break;
        case 3:
            alterar();
            break;
        case 4:
            break;
        default:

            break;
        }

    }
}

//main
int main(){

    menu(0);

    return 0;
}





/**

Exercicio :  (Inserir, Alterar e Exibir)
Desenvolva uma programa que permita inserção de registros e alteração dos registros conforme layout abaixo:

    Int ra
    Char nome[20]
    Float nota1
    Float nota 2

Procedimento - Inserção
-  Abrir o arquivo para inserir os registros;
- Consistir se abertura foi feita com sucesso;
- Se o arquivo existir partir para o cadastro;
- gravar registros e fechar o arquivo;

Procedimentos – Alterar
- Abrir o arquivo para leitura  rb+
- Se o arquivo estiver vazio enviar mensagem;
- Digitar o campo-chave para localizar o registro;
- Se o arquivo não estiver vazio, percorrer o arquivo de forma a encontrar o registro;
- Ao encontrar o registro exibir na tela, e permitir alterar somente os campos nota1 e nota2;
- gravar o registro;
- caso o Registro não exista enviar mensagem;

**/
