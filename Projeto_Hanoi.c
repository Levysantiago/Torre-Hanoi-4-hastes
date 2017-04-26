/****
*
* TÍTULO: FUNÇÃO INICIALIZA IMPRESSOES
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 23/06/2016
* ÚLTIMA MODIFICAÇÃO: 20/07/2016
*
* DESCRIÇÃO: O PROGRAMA RESOLVE O PROBLEMA DA TORRE DE HANOI COM QUATRO HASTES DE FORMA RECURSIVA
*            COM A MENOR QUANTIDADE DE MOVIMENTOS POSSÍVEL, A PARTIR DA QUANTIDADE DE DISCOS RECEBIDA,
*            E IMPRIME DE FORMA GRÁFICA, NA TELA E EM UM ARQUIVO (OU SOMENTE NO ARQUIVO SE A QUANTIDADE
*            DE DISCOS FOR MUITO GRANDE), OS MOVIMENTOS QUE SÃO NECESSÁRIOS PARA RESOLVER TAL PROBLEMA,
*            ALÉM DE INFORMAR TAMBÉM QUANTOS MOVIMENTOS FORAM REALIZADOS.
*
*
* ENTRADA: O PROJETO TEM COMO ENTRADAS UMA VARIÁVEL DE OPÇÃO PARA QUE O USUÁRIO ESCOLHA SE QUER INICIAR
*          O PROCEDIMENTO DA TORRE OU SE QUER SABER MAIS INFORMAÇÕES SOBRE O PROGRAMA, E UMA VARIÁVEL
*          QUE IRÁ RECEBER DE UM ARQUIVO A QUANTIDADE DE DISCOS PARA INICIAR O PROCEDIMENTO DA TORRE DE HANOI.
*
* SAÍDA: O PROGRAMA TEM COMO SAÍDA, A IMPRESSÃO DA TORRE COM O MOVIMENTO DOS DISCOS NA TELA E EM UM ARQUIVO,
*        A QUANTIDADE DE MOVIMENTOS QUE FORAM REALIZADOS E CADA MOVIMENTO QUE FOI FEITO PARA CADA HASTE
*        CORRESPONDENTE.
*
****/

#include<stdio.h>
#include<stdlib.h>

#define qtdHastes 4 /*QUANTIDADE DE HASTES*/

//PROTOTIPOS DAS FUNÇÕES
int ** AlocaMatrizInt(int,int);
void LiberaMatrizInt(int,int **);
void ImprimeMatriz(int,int,char **);
void VerificaFile(FILE *);
void InicializaEsqueleto(int **,int);
void InicializaImpressoes(int **,int **,int **,int **,int **,int,int);
void ValorImpressoes(int **,int **,int,int,int);
void SomaCont(int *);
void PrnGrafico(int **,int **,int **,int **,int,int,FILE *,int *);
void PrnMatrizImpressao(int,int,int **);
void PrnGraficoFile(int **,int **,int **,int **,int,int,FILE *);
void PrnMatrizImpressaoFile(int,int,int **,FILE *);
void MoveEsqueleto(int,int,int **,int,int,int,int,int **,int **,int **,int **,int,FILE *,int *);
char Menu(void);

int main(void){
    char stringTxt[25] //USADO SIMPLESMENTE PARA AVANÇAR O CURSOR NO ARQUIVO
    ,op; //USADO PARA RECEBER AS OPÇÕES DO USUARIO
    int i,j //CONTADORES
    ,cont //CONTADOR DE MOVIMENTOS
    ,**matImpressao1,**matImpressao2,**matImpressao3,**matImpressao4 /*MATRIZES DE IMPRESSÃO, SERÃO
                                                                       REPRESENTAÇÕES DE CADA HASTE*/
    ,qtdDiscos /*QUANTIDADE DE DISCOS*/
    ,tamDiscoMaior /*TAMANHO DO MAIOR DISCO EM ASTERISCOS*/
    ,**matEsqueleto;//MATRIZ PARA GUARDAR AS POSIÇÕES E TAMANHOS DOS DISCOS
    FILE *disco,*torreH; //PONTEIROS A FILE PARA ACESSAR OS ARQUIVOS

    system("TITLE ########### TORRE DE HANOI 4 HASTES ###########");//TÍTULO

    printf("\n\n");
    op= Menu(); //IMPRIMINDO O MENU E LENDO A OPÇÃO ESCOLHIDA
    do{
        //ABRINDO ARQUIVO "Discos.txt" PARA A LEITURA DA QUANTIDADE DE DISCOS
        disco = fopen("Discos.txt","r");
        VerificaFile(disco);

        fgets(stringTxt,22*sizeof(char),disco); //AVANÇANDO O CURSOR PARA GUARDAR A QUANTIDADE DE DISCOS
        fscanf(disco,"%d",&qtdDiscos);
        fclose(disco); //LIBERANDO O FLUXO "disco"

        /*CONDIÇÃO PARA SABER SE A QUANTIDADE DE DISCOS EH VALIDA.
          SE NAO FOR VALIDA, OP RECEBE 'X' E O SWITCH ENTRARÁ NO DEFAULT*/
        if(qtdDiscos <= 0){
            printf("\n\nErro, a quantidade de discos nao eh valida. Insira uma quantidade maior que 0."
                   "\n\nPara mais informacoes acesse o item [1](INSTRUCOES) do menu.\n\n");
            system("PAUSE");
            op='X';
        }

        //OPÇÕES QUE O USUARIO PODE ESCOLHER
        switch(op){
        case '0' ://---------------------------------------- CASO 0 ------------------------------------------

            cont=0;//INICIALIZANDO O CONTADOR DE MOVIMENTOS
            /*CALCULANDO O TAMANHO DO MAIOR DISCO PARA ALOCAÇÃO DA MATRIZ GRAFICO*/
            tamDiscoMaior=1;
            for(i=1;i<qtdDiscos;i++) tamDiscoMaior += 2;

            /*ALOCAÇÃO E INICIALIZAÇÃO MATRIZES IMPRESSAO*/
            matImpressao1 = AlocaMatrizInt(qtdDiscos,tamDiscoMaior);
            matImpressao2 = AlocaMatrizInt(qtdDiscos,tamDiscoMaior);
            matImpressao3 = AlocaMatrizInt(qtdDiscos,tamDiscoMaior);
            matImpressao4 = AlocaMatrizInt(qtdDiscos,tamDiscoMaior);

            /*ALOCAÇÃO E INICIALIZAÇÃO MATRIZ ESQUELETO*/
            matEsqueleto = AlocaMatrizInt(qtdDiscos,qtdHastes);
            InicializaEsqueleto(matEsqueleto,qtdDiscos);

            //INICIALIZA AS MATRIZES IMPRESSAO EM RELAÇÃO À MATRIZ ESQUELETO
            InicializaImpressoes(matEsqueleto,matImpressao1,matImpressao2,matImpressao3,matImpressao4,qtdDiscos,tamDiscoMaior);

            //ABRINDO ARQUIVO "Torre_Hanoi.txt" PARA IMPRIMIR O GRAFICO
            torreH = fopen("Torre_Hanoi.txt","w");
            VerificaFile(torreH);

            /*CONDIÇÃO: SE A QUANTIDADE DE DISCOS FOR MAIOR DO QUE 9, O GRAFICO IRÁ EXTRAPOLAR A TELA
              E A CONFIGURAÇÃO GRÁFICA EH IMPRESSA SOMENTE NO ARQUIVO, SENÃO, IMPRIME A PRIMEIRA
              CONFIGURAÇÃO DO GRAFICO*/
            if(qtdDiscos<10){
                system("CLS");
                PrnGrafico(matImpressao1,matImpressao2,matImpressao3,matImpressao4,qtdDiscos,tamDiscoMaior,torreH,&cont);
            }
            else{
                printf("\n A quantidade de discos informada ao programa eh maior do que 9.\n"
                       "Para essa quantidade, o programa ira imprimir os resultados no arquivo Torre_Hanoi.txt "
                       "que se encontra na mesma pasta do programa em questão.\n");
                PrnGraficoFile(matImpressao1,matImpressao2,matImpressao3,matImpressao4,qtdDiscos,tamDiscoMaior,torreH);
            }

            printf("\n\n");
            system("PAUSE");

            //MUDA O ESQUELETO E IMPRIME A MUDANÇA NO GRÁFICO
            MoveEsqueleto(qtdDiscos,qtdDiscos,matEsqueleto,0,1,2,3,matImpressao1,matImpressao2,matImpressao3,matImpressao4,tamDiscoMaior,torreH,&cont);

            fclose(torreH);//LIBERANDO O FLUXO "torreH"

            //LIBERANDO AS MATRIZES
            LiberaMatrizInt(qtdDiscos,matEsqueleto);
            LiberaMatrizInt(qtdDiscos,matImpressao1);
            LiberaMatrizInt(qtdDiscos,matImpressao2);
            LiberaMatrizInt(qtdDiscos,matImpressao3);
            LiberaMatrizInt(qtdDiscos,matImpressao4);

            printf("\n\n");
            break;

        case '1' : //---------------------------------------- CASO 1 ------------------------------------------
            system("CLS");
            printf("\n -> INSTRUCOES <-");
            printf("\n\n Para inicializar a Torre de Hanoi com 4 Hastes, antes voce precisa escolher \n a "
                   "quantidade de discos que sera utilizada para a realizacao dos movimentos.\n\n");
            system("PAUSE");
            printf("________________________________________________________________________________");
            printf("\n\n Voce pode estar mudando a quantidade de discos atraves de um arquivo que esta \n na "
                   "mesma pasta onde se encontra esse programa. Ao abrir o arquivo 'Discos.txt', voce "
                   "ira trocar o numero que esta apos a frase 'Quantidade de Discos:', salvar  o arquivo, "
                   "voltar ao menu e escolher a opcao '0' para iniciar a Torre com o \n numero de discos escolhido.\n\n");
            system("PAUSE");
            printf("________________________________________________________________________________");
            printf("\n\n Depois de ter iniciado a Torre de Hanoi, basta apertar 'ENTER' para que os \n discos se "
                   "movimentem. Importante lembrar que as quatro hastes da Torre estao\n enumeradas de 0 ate 3.\n\n");
            system("PAUSE");
            break;
        case '2' ://---------------------------------------- CASO 2 ------------------------------------------
            system("CLS");
            printf("\n -> A TORRE DE HANOI <-");
            printf("\n\n A Torre de Hanoi eh um 'quebra-cabeca' que consiste em uma base contendo tres \n pinos, "
                   "em um dos quais sao dispostos alguns discos uns sobre os outros, "
                   "em \n ordem crescente de diametro, de cima para baixo.\n\n");
            system("PAUSE");
            printf("________________________________________________________________________________");
            printf("\n\n O quebra-cabeca foi inventado pelo matematico frances Edouard Lucas. "
                   "Ele teve \n inspiracao de uma lenda para construir o jogo das Torres de Hanoi em 1883. "
                   "Ja \n seu nome foi inspirado na torre simbolo da cidade de Hanoi, no Vietna."
                   "\n\n FONTE: https://pt.wikipedia.org\n\n");
            system("PAUSE");
            system("CLS");
            printf("\n -> A TORRE DE HANOI - OBJETIVO <-");
            printf("\n\n O problema consiste em passar todos os discos de um pino para outro qualquer, "
                   "\n usando um dos pinos como auxiliar, de maneira que um disco maior nunca fique "
                   "\n em cima de outro menor em nenhuma situacao. "
                   "O numero de discos pode variar\n sendo que o mais simples contem apenas tres."
                   "\n\n FONTE: https://pt.wikipedia.org\n\n");
            system("PAUSE");
            system("CLS");
            printf("\n -> A TORRE DE HANOI - 4 HASTES? <-");
            printf("\n\n Uma extensao do problema foi proposto por Henry Dudeney em 1908 e chamado de "
                   "\n 'The Reves Puzzle'. Henry modificou o quebra-cabeca para 4 hastes. As regras"
                   "\n para o problema sao os mesmos do problema classico de 3 hastes, porem com um"
                   "\n pensamento diferente para resolver o mesmo. Para saber mais sobre as\n instrucoes, "
                   "volte para o menu e acesse o item 1.\n\n");

            system("PAUSE");
            break;

        case '3' ://---------------------------------------- CASO 3 ------------------------------------------
            system("CLS");
            printf("\n -> CURIOSIDADE <-");
            printf("\n\n Existem varias lendas a respeito da origem do jogo, "
                   "a mais conhecida diz\n respeito a um templo Hindu, situado no centro do universo. "
                   "Diz-se que Brama\n supostamente havia criado uma torre com 64 discos de ouro e "
                   "mais duas estacas\n equilibradas sobre uma plataforma. \n\n");
            system("PAUSE");
            printf("________________________________________________________________________________");
            printf("\n\n Brama ordenara-lhes que movessem todos os discos de uma estaca para outra\n segundo as suas instrucoes."
                   "\n\n As regras eram simples: "
                   "apenas um disco poderia ser movido por vez e nunca um\n disco maior deveria ficar por cima de um disco menor.\n\n"
                   " Segundo a lenda, quando todos os discos fossem transferidos de uma estaca para  a outra, "
                   "o templo iria desmoronar e o mundo desapareceria."
                   "\n\n FONTE: https://pt.wikipedia.org\n\n");
            system("PAUSE");
            break;
        case '4' ://---------------------------------------- CASO 4 ------------------------------------------
            exit(-1);
            break;
        default : //---------------------------------------- DEFAULT ------------------------------------------
            break;
        }//FECHA_SWITCH
        system("CLS");
        printf("\n\n");
        op= Menu();
    }while(op!=4);

    return 0;
}//FIM DA FUNÇÃO MAIN

/****
*
* TÍTULO: FUNÇÃO INICIALIZA IMPRESSOES
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 05/07/2016
* ÚLTIMA MODIFICAÇÃO: 21/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ INICIALIZAR AS MATRIZES DE IMPRESSÃO COM 0's E 1's
*            DE ACORDO COM A MATRIZ ESQUELETO PARA PREPARAR PARA A IMPRESSAO
*            DOS DISCOS E HASTES COM '*' e '|'. EXEMPLO:
*            MATRIZ ESQUELETO      MATRIZES DE IMRPESSÃO
*            1  0  0               -------------    -------------    -------------    -------------
*            3  0  0               0  0  1  0  0    0  0  0  0  0    0  0  0  0  0    0  0  0  0  0
*            5  0  0               0  1  1  1  0    0  0  0  0  0    0  0  0  0  0    0  0  0  0  0
*                                  1  1  1  1  1    0  0  0  0  0    0  0  0  0  0    0  0  0  0  0
*
* PARÂMETROS: - (matEsqueleto): PONTEIRO A MATRIZ INTEIRA PARA MANIPULAR A MATRIZ ESQUELETO
*             - (mat1,mat2,mat3,mat4): PONTEIRO A MATRIZ INTEIRA PARA MANIPULAR AS MATRIZES DE IMPRESSÃO
*             - (qtdDiscos): A QUANTIDADE DE DISCOS
*             - (tdMaior): O TAMANHO DO DISCO MAIOR
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA NULO
*
****/

void InicializaImpressoes(int **matEsqueleto,int **mat1,int **mat2,int **mat3,int **mat4,int qtdDiscos,int tdMaior){
    int i,j; //CONTADORES

    /*INICIALIZA AS MATRIZES DE IMPRESSÃO COM '0'*/
    for(i=0;i<qtdDiscos;i++){
        for(j=0;j<tdMaior;j++){
            mat1[i][j] = 0;
            mat2[i][j] = 0;
            mat3[i][j] = 0;
            mat4[i][j] = 0;
        }
    }

    /*ADICIONA VALOR '1' ÀS MATRIZES DE IMPRESSÃO PARA REPRESENTAR A CONFIGURAÇÃO DE CADA HASTE*/
    ValorImpressoes(matEsqueleto,mat1,qtdDiscos,tdMaior,0);
    ValorImpressoes(matEsqueleto,mat2,qtdDiscos,tdMaior,1);
    ValorImpressoes(matEsqueleto,mat3,qtdDiscos,tdMaior,2);
    ValorImpressoes(matEsqueleto,mat4,qtdDiscos,tdMaior,3);

}//FIM DA FUNÇÃO INICIALIZA_IMPRESSOES

/****
*
* TÍTULO: FUNÇÃO VALOR DAS IMPRESSOES
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 21/07/2016
* ÚLTIMA MODIFICAÇÃO: 21/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO SERÁ UTILIZADA PELA FUNÇÃO INICIALIZA IMPRESSÕES. ELA IRÁ
*            INICIALIZAR UMA MATRIZ DE IMPRESSÃO COM O VALOR 1 DE ACORDO COM A MATRIZ
*            ESQUELETO E SERÁ CHAMADA QUATRO VEZES NA FUNÇÃO INICIALIZA IMPRESSÕES.
*
* PARÂMETROS: - (matEsqueleto):PONTEIRO A MATRIZ INTEIRA PARA MANIPULAR A MATRIZ ESQUELETO
*             - (matriz): PONTEIRO A MATRIZ INTEIRA PARA MANIPULAR UMA MATRIZ DE IMPRESSÃO
*             - (qtdDiscos): QUANTIDADE DE DISCOS
*             - (tdMaior): TAMANHO DO MAIOR DISCO
*             - (col): É UMA COLUNA DA MATRIZ ESQUELETO, QUE VAI REPRESENTAR CADA MATRIZ DE IMPRESSÃO.
*                      A COLUNA '0' REPRESENTA A PRIMEIRA MATRIZ DE IMPRESSÃO, A COLUNA '1' REPRESENTA
*                      A SEGUNDA MATRIZ DE IMPRESSÃO, E ASSIM POR DIANTE ATÉ A COLUNA 3.
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA NULO
*
****/

void ValorImpressoes(int **matEsqueleto,int **matriz,int qtdDiscos,int tdMaior,int col){
    int i //CONTADOR
    ,lateral; /*A LATERAL SERÁ UTILIZADA PARA SABER OS VALORES DAS LATERAIS EM RELAÇÃO AO
                VALOR CENTRAL DAS MATRIZES DE IMPRESSÃO, DE ACORDO COM OS VALORES DA MATRIZ
                ESQUELETO*/

    /*A METADE DO ELEMENTO DA MATRIZ ESQUELETO IRÁ DEFINIR QUANTOS VALORES LATERAIS O ELEMENTO CENTRAL DA
      MATRIZ DE IMPRESSÃO TEM. DEPOIS EH ADICIONADO O VALOR '1' ÀS LATERAIS PARA REPRESENTAR OS DISCOS.*/
    for(i=0;i<qtdDiscos;i++){
        if(matEsqueleto[i][col]!=0){ //SÓ PROSSEGUIRÁ SE O ELEMENTO DA MATRIZ ESQUELETO FOR DIFERENTE DE '0'
            matriz[i][tdMaior/2]= 1; //ADICIONA '1' AO ELEMENTO CENTRAL
            lateral = matEsqueleto[i][col]/2;
            while(lateral){
                matriz[i][(tdMaior/2)- lateral] = 1; //ADICIONA '1' À LATERAL ESQUERDA AO ELEMENTO CENTRAL
                matriz[i][(tdMaior/2)+ lateral] = 1; //ADICIONA '1' À LATERAL DIREITA AO ELEMENTO CENTRAL
                lateral--;
            }
        }//FECHA IF
    }//FECHA FOR
}//FECHA FUNÇÃO VALOR IMPRESSOES

/****
*
* TÍTULO: FUNÇÃO IMPRESSÃO DE GRAFICO
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 05/07/2016
* ÚLTIMA MODIFICAÇÃO: 20/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ IMPRIMIR O GRAFICO DA TORRE DE HANOI. ELA UTILIZARÁ COMO
*            AUXILIO A FUNÇÃO 'PRN MATRIZ IMPRESSÃO' PARA IMPRIMIR AS CONFIGURAÇÕES DE
*            CADA HASTE. IRÁ UTILIZAR TAMBÉM A FUNÇÃO 'PRN GRAFICO FILE' PARA IMPRIMIR
*            O GRAFICO NO ARQUIVO.
*
* PARÂMETROS: - (mat1,mat2,mat3,mat4): PONTEIROS A MATRIZ INTEIRA PARA MANIPULAR AS MATRIZES DE IMPRESSÃO
*             - (qtdDiscos): A QUANTIDADE DE DISCOS
*             - (tamDiscoMaior): O TAMANHO DO DISCO MAIOR
*             - (torre): PONTEIRO A FILE. IRÁ APONTAR PARA O "Torre_Hanoi.txt"
*             - (pcont): PONTEIRO A INTEIRO, PARA MANIPULAR O CONTADOR DE MOVIMENTOS
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA NULO
*
****/

void PrnGrafico(int **mat1,int **mat2,int **mat3,int **mat4,int qtdDiscos,int tamDiscoMaior,FILE *torre,int *pcont){
    int i,j; //CONTADORES

    //INFORMA A QUANTIDADE DE MOVIMENTOS ATUAL
    SomaCont(pcont);

    /*IMPRIMINDO A CONFIGURAÇÃO DAS HASTES COM AS MATRIZES DE IMPRESSAO*/
    for(i=0;i<qtdDiscos;i++){
        printf(" ");
        //IMPRIMINDO CONFIGURAÇÃO DA PRIMEIRA HASTE DE ACORDO COM A MATRIZ DE IMPRESSÃO 1
        PrnMatrizImpressao(i,tamDiscoMaior,mat1);
        printf("  ");

        //IMPRIMINDO CONFIGURAÇÃO DA PRIMEIRA HASTE DE ACORDO COM A MATRIZ DE IMPRESSÃO 2
        PrnMatrizImpressao(i,tamDiscoMaior,mat2);
        printf("  ");

        //IMPRIMINDO CONFIGURAÇÃO DA TERCEIRA HASTE DE ACORDO COM A MATRIZ DE IMPRESSÃO 3
        PrnMatrizImpressao(i,tamDiscoMaior,mat3);
        printf("  ");

        //IMPRIMINDO CONFIGURAÇÃO DA TERCEIRA HASTE DE ACORDO COM A MATRIZ DE IMPRESSÃO 4
        PrnMatrizImpressao(i,tamDiscoMaior,mat4);
        printf("\n");
    }//FECHA FOR

    /*IMPRIMINDO A BASE DA TORRE*/
    printf(" ");
    for(i=0;i<qtdHastes;i++){
        for(j=0;j<tamDiscoMaior/2;j++){
            printf("-");
        }
        printf("+");

        for(j=0;j<tamDiscoMaior/2;j++){
            printf("-");
        }
        printf("--");
    }//FECHA FOR

    //CHAMANDO A FUNÇÃO QUE IMPRIME NO ARQUIVO
    PrnGraficoFile(mat1,mat2,mat3,mat4,qtdDiscos,tamDiscoMaior,torre);

}//FIM DA FUNÇÃO DE IMPRESSÃO DO GRAFICO

/****
*
* TÍTULO: FUNÇÃO PRINTA MATRIZ IMPRESSAO
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 20/07/2016
* ÚLTIMA MODIFICAÇÃO: 20/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ IMPRIMIR A CONFIGURAÇÃO DE UMA MATRIZ DE IMPRESSÃO EM '*' E '|' NA TELA.
*            SERÁ UTILIZADA NA FUNÇÃO 'PRN GRAFICO' QUATRO VEZES PARA IMPRIMIR A CONFIGURAÇÃO DAS
*            QUATRO MATRIZES DE IMPRESSÃO
*
* PARÂMETROS: - (i): UM CONTADOR
*             - (tamDiscoMaior): TAMANHO DO MAIOR DISCO
*             - (matriz): PONTEIRO A MATRIZ INTEIRA, PARA MANIPULAR UMA MATRIZ DE IMPRESSÃO
*
* VALOR DE RETORNO: RETORNA NULO
*
****/

void PrnMatrizImpressao(int i,int tamDiscoMaior,int **matriz){
    int j; //CONTADOR

    /*IMPRIMINDO A CONFIGURAÇÃO DE UMA HASTE NA TELA A PARTIR DE UMA MATRIZ DE IMPRESSÃO*/
    for(j=0;j<tamDiscoMaior;j++){
        if(j == tamDiscoMaior/2 && matriz[i][j]==0) printf("|");
        else if(matriz[i][j]==0) printf(" ");
        else if(matriz[i][j]==1) printf("*");
    }
}//FECHA FUNÇÃO PRN MATRIZ IMPRESSÃO

/****
*
* TÍTULO: FUNÇÃO SOMA CONT
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 25/07/2016
* ÚLTIMA MODIFICAÇÃO: 25/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ IMPRIMIR NA TELA O VALOR DO CONTADOR DE MOVIMENTOS E TAMBÉM IRÁ INCREMENTÁ-LO
*
* PARÂMETROS: - (pcont): PONTEIRO A INTEIRO, PARA ACESSAR O CONTADOR DE MOVIMENTOS
*
* VALOR DE RETORNO: RETORNA NULO
*
****/

void SomaCont(int *pcont){
    printf("\n -> A TORRE DE HANOI COM 4 HASTES <-\n\n");
    printf("\n\n Quantidade de movimentos: %d\n\n\n",*pcont);
    *pcont+=1; //SOMA 1 AO CONTADOR DE MOVIMENTOS
}//FECHA FUNÇÃO SOMA CONT

/****
*
* TÍTULO: FUNÇÃO IMPRESSÃO DE GRAFICO NO ARQUIVO
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 20/07/2016
* ÚLTIMA MODIFICAÇÃO: 20/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ IMPRIMIR O GRAFICO DA TORRE DE HANOI NO ARQUIVO 'Torre_Hanoi.txt'.
*            ELA UTILIZARÁ COMO AUXILIO A FUNÇÃO 'PRN MATRIZ IMPRESSÃO FILE' PARA IMPRIMIR AS
*            CONFIGURAÇÕES DE CADA HASTE NO ARQUIVO.
*
* PARÂMETROS: - (mat1,mat2,mat3,mat4): PONTEIROS A MATRIZ INTEIRA PARA MANIPULAR AS MATRIZES DE IMPRESSÃO
*             - (qtdDiscos): A QUANTIDADE DE DISCOS
*             - (tamDiscoMaior): O TAMANHO DO DISCO MAIOR
*             - (torre): PONTEIRO A FILE. IRÁ APONTAR PARA O "Torre_Hanoi.txt"
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA NULO
*
****/

void PrnGraficoFile(int **mat1,int **mat2,int **mat3,int **mat4,int qtdDiscos,int tamDiscoMaior,FILE *torre){
    int i,j;//CONTADORES

    fprintf(torre,"\n\n");

    /*IMPRIMINDO A CONFIGURAÇÃO DAS HASTES NO ARQUIVO COM AS MATRIZES DE IMPRESSAO*/
    for(i=0;i<qtdDiscos;i++){
        //IMPRIMINDO CONFIGURAÇÃO DA PRIMEIRA HASTE DE ACORDO COM A MATRIZ DE IMPRESSÃO 1
        PrnMatrizImpressaoFile(i,tamDiscoMaior,mat1,torre);
        fprintf(torre,"  ");

        //IMPRIMINDO CONFIGURAÇÃO DA PRIMEIRA HASTE DE ACORDO COM A MATRIZ DE IMPRESSÃO 1
        PrnMatrizImpressaoFile(i,tamDiscoMaior,mat2,torre);
        fprintf(torre,"  ");

        //IMPRIMINDO CONFIGURAÇÃO DA TERCEIRA HASTE DE ACORDO COM A MATRIZ DE IMPRESSÃO 3
        PrnMatrizImpressaoFile(i,tamDiscoMaior,mat3,torre);
        fprintf(torre,"  ");

        //IMPRIMINDO CONFIGURAÇÃO DA TERCEIRA HASTE DE ACORDO COM A MATRIZ DE IMPRESSÃO 4
        PrnMatrizImpressaoFile(i,tamDiscoMaior,mat4,torre);
        fprintf(torre,"\n");
    }//FECHA FOR

    /*IMPRIMINDO A BASE DA TORRE*/
    for(i=0;i<qtdHastes;i++){
        for(j=0;j<tamDiscoMaior/2;j++){
            fprintf(torre,"-");
        }
        fprintf(torre,"+");

        for(j=0;j<tamDiscoMaior/2;j++){
            fprintf(torre,"-");
        }
        fprintf(torre,"--");
    }//FECHA FOR

}//FIM DA FUNÇÃO DE IMPRESSÃO DO GRAFICO FILE

/****
*
* TÍTULO: FUNÇÃO PRINTA MATRIZ IMPRESSAO NO ARQUIVO
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 20/07/2016
* ÚLTIMA MODIFICAÇÃO: 20/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ IMPRIMIR A CONFIGURAÇÃO DE UMA MATRIZ DE IMPRESSÃO EM '*' E '|' NA TELA.
*            SERÁ UTILIZADA NA FUNÇÃO 'PRN GRAFICO' QUATRO VEZES PARA IMPRIMIR A CONFIGURAÇÃO DAS
*            QUATRO MATRIZES DE IMPRESSÃO
*
* PARÂMETROS: - (i): UM CONTADOR
*             - (tamDiscoMaior): TAMANHO DO MAIOR DISCO
*             - (matriz): PONTEIRO A MATRIZ INTEIRA, PARA MANIPULAR UMA MATRIZ DE IMPRESSÃO
*             - (torre): PONTEIRO A FILE, PARA MANIPULAR O ARQUIVO 'Torre_Hanoi.txt'
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA NULO
*
****/

void PrnMatrizImpressaoFile(int i,int tamDiscoMaior,int **matriz,FILE *torre){
    int j; //CONTADOR

    /*IMPRIMINDO A CONFIGURAÇÃO DE UMA HASTE NO ARQUIVO A PARTIR DE UMA MATRIZ DE IMPRESSÃO*/
    for(j=0;j<tamDiscoMaior;j++){
        if(j == tamDiscoMaior/2 && matriz[i][j]==0) fprintf(torre,"|");
        else if(matriz[i][j]==0) fprintf(torre," ");
        else if(matriz[i][j]==1) fprintf(torre,"*");
    }
}//FECHA FUNÇÃO PRN MATRIZ IMPRESSÃO FILE

/****
*
* TÍTULO: FUNÇÃO ALOCAÇÃO DE MATRIZ INTEIROS
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 17/07/2016
* ÚLTIMA MODIFICAÇÃO: 17/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO EH UTILIZADA PARA ALOCAR UMA MATRIZ DE INTEIROS. UTILIZAREMOS PARA
*             ALOCAR AS QUATRO MATRIZES DE IMPRESSÃO E TAMBÉM A MATRIZ ESQUELETO.
*
* PARÂMETROS: - (lin): EH A QUANTIDADE DE LINHAS QUE A MATRIZ TEM
*             - (col): EH A QUANTIDADE DE COLUNAS QUE A MATRIZ TEM
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA UM PONTEIRO A MATRIZ INTEIRA.
*
****/

int ** AlocaMatrizInt(int lin, int col){
    int i,j //CONTADORES
    ,**matriz; //MATRIZ A SER ALOCADA

    //ALOCAÇÃO DE UM VETOR DE PONTEIROS
    matriz = malloc(lin*sizeof(int *));
    if(matriz == NULL){
        printf("\n\nERRO!Memoria insuficiente!\n\n");
        system("PAUSE");
        exit(-1);
    }

    //ALOCAÇÃO DE UM VETOR PARA CADA PONTEIRO
    for(i=0;i<lin;i++){
        matriz[i] = malloc(col*sizeof(int));
        if(matriz[i] == NULL){
            printf("\n\nERRO!Memoria insuficiente!\n\n");
            system("PAUSE");
            exit(-1);
        }
    }

    //INICIALIZA A MATRIZ COM 0
    for(i=0;i<lin;i++){
        for(j=0;j<col;j++){
            matriz[i][j]=0;
        }
    }

    return matriz;
}//FIM DA FUNÇÃO ALOCA_MATRIZ_INT

/****
*
* TÍTULO: FUNÇÃO LIBERAÇÃO DE MATRIZ INTEIROS
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 17/07/2016
* ÚLTIMA MODIFICAÇÃO: 17/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ LIBERAR O ESPAÇO QUE FOI ALOCADO NA MEMÓRIA PARA UMA MATRIZ
*
* PARÂMETROS: - (lin): QUANTIDADE DE LINHAS DE UMA MATRIZ
*             - (matriz): PONTEIRO A MATRIZ INTEIRA
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA UM VALOR NULO
*
****/

void LiberaMatrizInt(int lin,int **matriz){
    int i;//CONTADOR

    for(i=0;i<lin;i++) free(matriz[i]); //LIBERA OS VETORES APONTADOS PELOS PONTEIROS
    free(matriz); //LIBERA O VETOR DE PONTEIROS
}

/****
*
* TÍTULO: VERIFICAÇÃO AO ABRIR ARQUIVOS
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 10/07/2016
* ÚLTIMA MODIFICAÇÃO: 10/07/2016
*
* DESCRIÇÃO: A FUNÇÃO VERIFICA SE FOI POSSÍVEL ABRIR UM ARQUIVO OU NÃO. SE SIM, A FUNÇÃO NÃO FAZ NADA,
             SE NÃO, ELA IRÁ IMPRIMIR NA TELA UMA MENSAGEM DE ERRO E IRÁ FINALIZAR O PROGRAMA
*
* PARÂMETROS: - (fil): EH UM PONTEIRO A FILE, UTILIZADO PARA ACESSAR O ARQUIVO
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA NULO
*
****/

void VerificaFile(FILE *fil){
    //SE O PONTEIRO RETORNAR NULL, ENTÃO NÃO FOI POSSÍVEL ABRIR O ARQUIVO
    if(fil == NULL){
        printf("\n\nERRO AO ABRIR ARQUIVO!\n\n");
        exit(-1);
    }
}

/****
*
* TÍTULO: INICIALIZAÇÃO ESQUELETO DO JOGO
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 10/07/2016
* ÚLTIMA MODIFICAÇÃO: 10/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ INICIALIZAR A MATRIZ ESQUELETO COM OS VALORES INICIAIS PARA A
*            FUTURA IMPRESSÃO DOS DISCOS. IRÁ INICIALIZAR SEMPRE DA SEGUINTE FORMA:
*               1   0   0
*               3   0   0
*               5   0   0   PARA QUANTIDADE DE DISCOS IGUAL A 3
*
* PARÂMETROS: - (mat): PONTEIRO A MATRIZ INTEIRA
*             - (lin): QUANTIDADE DE LINHAS DA MATRIZ
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA NULL
*
****/

void InicializaEsqueleto(int **mat,int lin){
    int i,val=1;

    /*INICIALIZA A MATRIZ ESQUELETO COM A CONFIGURAÇÃO INICIAL DA TORRE*/
    for(i=0;i<lin;i++){
        mat[i][0] = val;
        mat[i][1] = 0;
        mat[i][2] = 0;
        mat[i][3] = 0;
        val+= 2;
    }
}

/****
*
* TÍTULO: FUNÇÃO MOVE ESQUELETO
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 18/07/2016
* ÚLTIMA MODIFICAÇÃO: 18/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ MODIFICAR A MATRIZ ESQUELETO DE ACORDO COM A ORIGEM E DESTINO RECEBIDOS
*            COMO PARÂMETROS. APÓS MODIFICAR ESSA MATRIZ, SERÁ UTILIZADO OUTRAS FUNÇÕES CRIADAS
*            ANTERIORMENTE PARA MODIFICAR TAMBÉM AS MATRIZES DE IMPRESSÃO E DEPOIS IMPRIMIR NA TELA
*            A CONFIGURAÇÃO ATUAL. A FUNÇÃO IRÁ FAZER ISSO ATÉ QUE TODOS OS DISCOS ESTEJAM NA HASTE
*            DE DESTINO.
*
* PARÂMETROS: - (qDiscos): QUANTIDADE DE DISCOS. SERÁ UTILIZADA PARA CONTROLAR QUANDO QUE A RECORRENCIA
                           DEVE PARAR
*             - (qtdDiscos): QUANTIDADE DE DISCOS. SERÁ ENVIADO COMO PARAMETRO PARA AS OUTRAS FUNÇÕES
*             - (matEsqueleto): PONTEIRO A MATRIZ INTEIRA. UTILIZADO PARA CONTROLAR A MATRIZ ESQUELETO
*             - (origem): VALOR QUE REPRESENTA A HASTE DA QUAL UM DISCO SERÁ RETIRADO
*             - (aux): VALOR QUE REPRESENTA UMA HASTE AUXILIAR
*             - (aux2): VALOR QUE REPRESENTA OUTRA HASTE AUXILIAR
*             - (destino): VALOR QUE REPRESENTA A HASTE PARA QUAL UM DISCO SERÁ MOVIDO
              - (mat1,mat2,mat3,mat4): PONTEIROS A MATRIZ INTEIRA PARA MANIPULAR AS MATRIZES DE IMPRESSÃO
*             - (tamDiscoMaior): TAMANHO DO DISCO MAIOR
*             - (torre): PONTEIRO A FILE. UTILIZADO PARA ACESSAR O ARQUIVO "Torre_Hanoi.txt"
*             - (pcont): PONTEIRO A INTEIRO. UTILIZADO PARA ACESSAR A VARIAVEL CONTADOR DECLARADA NA MAIN
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA NULO
*
****/

void MoveEsqueleto(int qDiscos,int qtdDiscos,int **matEsqueleto,int origem,int aux,int aux2,int destino,int **mat1,int **mat2,int **mat3,int **mat4,int tamDiscoMaior,FILE *torre,int *pcont){
    int i,j;//CONTADORES

    //CONDIÇÃO BASE DA RECURSIVIDADE
    /*OS CONTADORES SÃO INVERSOS, OU SEJA, UM INICIARÁ DA PRIMEIRA LINHA E O OUTRO DA ULTIMA
      ASSIM, FICA MAIS FÁCIL DE MUDAR O DISCO DA ORIGEM PARA UM DESTINO*/
    if(qDiscos==1){
        for(i=0;i<qtdDiscos;i++){
            if(matEsqueleto[i][origem]){
                for(j=qtdDiscos - 1;j>=0;j--)
                    if(matEsqueleto[j][destino]==0){ //SE A CONDIÇÃO FOR VERDADEIRA, A TROCA SERÁ FEITA
                        matEsqueleto[j][destino] = matEsqueleto[i][origem];
                        matEsqueleto[i][origem] = 0;
                        break;
                    }
                break;
            }
        }//FECHA FOR
        system("CLS");
        //INICIALIZA AS MATRIZES IMPRESSORAS COM A NOVA CONFIGURAÇÃO
        InicializaImpressoes(matEsqueleto, mat1,mat2,mat3,mat4, qtdDiscos,tamDiscoMaior);

        /*CASO QUANTIDADE DE DISCOS SEJA MAIOR DO QUE 9, O GRAFICO SERÁ IMPRESSO SOMENTE NO
          ARQUIVO "Torre_Hanoi.txt"*/
        if(qtdDiscos<10){
            //IMPRIME O GRAFICO COM A NOVA CONFIGURAÇÃO
            PrnGrafico(mat1,mat2,mat3,mat4,qtdDiscos,tamDiscoMaior,torre,pcont);
            printf("\n\n Move da Haste %d para a Haste %d\n\n",origem,destino);
            printf("\n\n");
            system("PAUSE");
        }
        else{
            printf("\n\nPor favor, aguarde o programa terminar a gravacao...");
            PrnGraficoFile(mat1,mat2,mat3,mat4,qtdDiscos,tamDiscoMaior,torre);
        }

    }//FECHA IF CONDIÇÃO BASE

    //INÍCIO DA RECURSIVIDADE:
    /*CASO A QUANTIDADE DE DISCOS SEJA 2, SERÁ UTILIZADO SOMENTE 3 HASTES, PORTANTO, A LOGICA UTILIZADA
      PARA 2 DISCOS EH A LOGICA DA RECURSIVIDADE DA TORRE DE 3 HASTES. A PARTIR DE 3 DISCOS EH UTILIZADA
      A LOGICA RECURSIVA PARA 4 HASTES*/
    else if(qDiscos==2) {
        MoveEsqueleto(qDiscos-1,qtdDiscos,matEsqueleto,origem,destino,aux2,aux,mat1,mat2,mat3,mat4,tamDiscoMaior,torre,pcont);
        MoveEsqueleto(1,qtdDiscos,matEsqueleto,origem,aux,aux2,destino,mat1,mat2,mat3,mat4,tamDiscoMaior,torre,pcont);
        MoveEsqueleto(qDiscos-1,qtdDiscos,matEsqueleto,aux,origem,aux2,destino,mat1,mat2,mat3,mat4,tamDiscoMaior,torre,pcont);
    }
    else{ //PARA qDiscos >= 3
        MoveEsqueleto(qDiscos-2,qtdDiscos,matEsqueleto,origem,destino,aux2,aux,mat1,mat2,mat3,mat4,tamDiscoMaior,torre,pcont);
        MoveEsqueleto(1,qtdDiscos,matEsqueleto,origem,destino,aux,aux2,mat1,mat2,mat3,mat4,tamDiscoMaior,torre,pcont);
        MoveEsqueleto(1,qtdDiscos,matEsqueleto,origem,aux,aux2,destino,mat1,mat2,mat3,mat4,tamDiscoMaior,torre,pcont);
        MoveEsqueleto(1,qtdDiscos,matEsqueleto,aux2,origem,aux,destino,mat1,mat2,mat3,mat4,tamDiscoMaior,torre,pcont);
        MoveEsqueleto(qDiscos-2,qtdDiscos,matEsqueleto,aux,origem,aux2,destino,mat1,mat2,mat3,mat4,tamDiscoMaior,torre,pcont);
    }
}//FIM DA FUNÇÃO MOVE_ESQUELETO

/****
*
* TÍTULO: FUNÇÃO IMPRIME MENU
*
* AUTOR: LEVY MARLON SOUZA SANTIAGO
*
* DATA DA CRIAÇÃO: 18/07/2016
* ÚLTIMA MODIFICAÇÃO: 18/07/2016
*
* DESCRIÇÃO: ESTA FUNÇÃO IRÁ IMPRIMIR UM MENU NA TELA E DEPOIS LER DO USUARIO A OPÇÃO DO MENU
*            QUE ELE ESCOLHEU
*
* PARÂMETROS: A FUNÇÃO NÃO RECEBE PARÂMETROS
*
* VALOR DE RETORNO: A FUNÇÃO RETORNA UM VALOR CHAR, QUE VAI SER A OPÇÃO ESCOLHIDA PELO USUARIO
*
****/

char Menu(void){
    char op;

    printf(" ************************ TORRE DE HANOI COM 4 HASTES ************************\n\n");
    printf(" Desenvolvedor: Levy Marlon Souza Santiago\n\n");
    printf(" Este programa ira lhe mostrar como resolver o problema da Torre de Hanoi com \n 4 hastes, "
           "que eh uma extensão proposta por Henry Dudeney do classico \n 'quebra-cabeca' "
           "original de 3 hastes inventado pelo matematico frances \n Edouard Lucas. "
           "Va em frente e experimente!\n\n");
    printf("________________________________________________________________________________\n\n");
    printf(" MENU DE OPCOES:\n\n");

    //OPÇÕES DO MENU
    printf(" [0] Iniciar");
    printf("\n [1] Instrucoes");
    printf("\n [2] Sobre a Torre de Hanoi com 4 hastes");
    printf("\n [3] Curiosidade");
    printf("\n [4] Sair");

    //LEITURA DA OPÇÃO
    printf("\n\n Digite a opcao: ");
    fflush(stdin);
    op=getchar();
    fflush(stdin);

    return op;
}
