#include<iostream>
#include<time.h>
#include<ctime>
#include<windows.h>
#include<cstdlib>
#include<conio.h>

using namespace std;

const int tam=100;

// ESPALHA BAMBAS NO CAMPO
int Sortearminas(int matriz2[][tam], int linha, int coluna, int minas)
{
     for(int i=0;i<linha;i++) // PREENCHE A MATRIZ DE INTEIROS COM ZERO
        for(int j=0;j<coluna;j++)
            matriz2[i][j]=0;

    int l,c,cont=0;
    srand(time(NULL));

    do
    {
        l = rand() % linha;
        c = rand() % coluna;
        if(matriz2[l][c] != -1)
        {
            matriz2[l][c] = -1;
            cont++;
        }
    }
    while(cont < minas);
}

// GERA MATRIZ DE CARACTERES
int GerarMatrizCaractere(char matriz[][tam], int linha, int coluna)
{
    for(int i=0; i<linha; i++)
    {
        for(int j=0; j<coluna; j++)
        {
            matriz[i][j]='.';
        }
    }
}

// VERIFICA MINAS AO REDOR E PREENCHE NA POSICAO
void VeriMinas( int matriz[][tam], int linha, int coluna)
{
    for(int i=0; i<linha; i++)
        for(int j=0; j<coluna; j++)
            if (matriz[i][j]!=-1)
                for (int x=i-1; x<=i+1; x++)
                    for (int y=j-1; y<=j+1; y++)
                        if (matriz[x][y]==-1)
                        {
                            matriz[i][j]+=1;
                        }
}

// VERIFICA A POSIÇOES AO REDOR E ABRE RECURSIVAMENTE CASO NECESSARIO
void Abrirmatriz(char matriz[][tam], int matriz2[][tam],int l, int c, int linha, int coluna,int & contar_posicoes)
{
        contar_posicoes++;

        if(matriz2[l][c]==0) // VERIFICA SE E 0 (VAZIO) OU NUMERO
        {
            matriz[l][c]='_';
            for (int x=l-1; x<=l+1; x++)
                for (int y=c-1; y<=c+1; y++)
                    if((x>=0 && x<linha) && (y>=0 && y<coluna) && matriz[x][y]!='_' && matriz[x][y]!='+')
                    {
                        Abrirmatriz(matriz, matriz2, x, y, linha, coluna,contar_posicoes);
                    }
        }
        else
        {
            matriz[l][c]='+';
        }
}

// IMPRIMIR TABULEIRO (CAMPO MINADO)
void ImprimirMatriz(char matriz[][tam], int matriz2[][tam], int linha, int coluna)
{
    cout<<"    ";
    for(int i=0;i<linha;i++)
    {
        cout<<"|";
        cout<<i;
        cout<<"|";
    }

    cout<<endl;
    for(int i=0; i<linha; i++)
    {
        cout<<"|"<<i<<"|";

        if(i<=9) // VERIFICACAO PARA NAO DEIXAR DEFORMADO O TABULEIRO
        {
            cout<<" ";
        }

        for(int j=0; j<coluna; j++)
        {
            if(j>=10) // VERIFICACAO PARA NAO DEIXAR DEFORMADO O TABULEIRO
            {
                cout<<" ";
            }

            if(matriz[i][j]=='-')
                cout<<" "<<matriz[i][j]<<" ";
            else if(matriz[i][j]=='+')
                cout<<" "<<matriz2[i][j]<<" ";
            else if(matriz[i][j]=='M')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // ADICIONAR A COR ESCOLHIDA
                cout<<" "<<matriz[i][j]<<" ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

            }
            else if(matriz[i][j]=='?')
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14); // ADICIONAR A COR ESCOLHIDA
                cout<<" "<<matriz[i][j]<<" ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

            }
            else
                cout<<" "<<matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}

// IMPRIMIR TABULEIRO NO FINAL CASO ACERTE A BOMBA
void ImprimirBombas(char matriz[][tam], int matriz2[][tam], int linha, int coluna)
{
    cout<<"    ";
    for(int i=0;i<linha;i++)
    {
        cout<<"|";
        cout<<i;
        cout<<"|";
    }

    cout<<endl;
    for(int i=0; i<linha; i++)
    {
        cout<<"|"<<i<<"|";

        if(i<=9)
        {
            cout<<" ";
        }

        for(int j=0; j<coluna; j++)
        {
            if(j>=10)
            {
                cout<<" ";
            }

            if(matriz2[i][j]== -1) // VERIFICA SE E BOMBA
             {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11); // ADICIONAR A COR ESCOLHIDA
                cout<<" "<<"*"<<" ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
             }
            else if(matriz[i][j]=='M' || matriz[i][j]=='?')// VERIFICA SE E SIMBOLO
             {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12); // ADICIONAR A COR ESCOLHIDA
                cout<<" "<<"X"<<" ";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
             }

            else if(matriz2[i][j] == 0) // VERIFICA SE E 0
                cout<<" "<<"_"<<" ";
            else
                cout<<" "<<matriz2[i][j]<<" "; // IMPRIMIR OS NUMEROS
        }
        cout<<endl;
    }
}

// PAINEL DO TEMPO
void paineltempo(int tempo)
{
    int minuto;
    int hora;
    int segundo;

    hora = tempo/3600;
    minuto =(tempo%3600) / 60;
    segundo = tempo % 60;
    cout<<"       ____ ____ ____"<<endl;
    cout<<"Time: | "<<hora<<"h : "<<minuto<<"m : "<<segundo<<"s"<<" |";
}

// CODIGO PARA FAZER AS JOGADAS
void JogarMatriz(char matriz[][tam], int matriz2[][tam], int linha, int coluna,int minas)
{
    time_t INICIAL = time(NULL); // DECLARACAO TEMPO INICIAL
    time_t FINAL = time(NULL); // DECLARACAO TEMPO FINAL
    float TEMPO = 0; // TEMPO TOTAL (FIINAL - INICIAL)

    int contar_posicoes = 0; // CONTADOR DE QUADRADOS DESCOBERTOS

    int Minas_Marcadas = minas;

    GerarMatrizCaractere(matriz, linha, coluna);

    Sortearminas(matriz2, linha, coluna, minas);

    VeriMinas(matriz2, linha, coluna);

    do
    {
        int l, c;
        int esc;

        ImprimirMatriz(matriz, matriz2, linha, coluna);

        cout<<endl;
        paineltempo(TEMPO); // PAINEL DO TEMPO
        cout<<" MM: "<<Minas_Marcadas; // CONTADOR DE MINAS MARCADAS
        cout<<" FD: "<<(linha*coluna - minas) - contar_posicoes<<endl; // TOTAL DE MINAS QUE FALTA DESCOBRIR
        cout<<endl;

        cout<<"[1] Descobrir Quadrado"<<endl;
        cout<<"[2] Marcar Mina"<<endl;
        cout<<"[3] Talvez Mina"<<endl;
        cout<<"[4] Limpar Marcacao"<<endl;
        cout<<"[5] Sair"<<endl<<endl;

        cout<<"Digite sua Escolha: ";
        cin>>esc;

        switch(esc)
        {
            case 1: // DESCOBRIR BOMBA

                system("cls");
                ImprimirMatriz(matriz, matriz2, linha, coluna); // IMPRIMIR CAMPO
                cout<<endl;

                FINAL = time(NULL);
                TEMPO = FINAL - INICIAL;
                paineltempo(TEMPO); // PAINEL DO TEMPO

                cout<<endl<<endl;
                cout<<"Linha e Coluna: ";
                cin>>l>>c;
                system("cls");

                if((l>=0 && l<linha) && (c>=0 && c<coluna)) // VERIFICA SE A POSICAO TA NOS LIMITES
                {
                    if(matriz2[l][c]!= -1) // VERIFICA SE E BOMBA
                    {
                        if(matriz[l][c]!='_' && matriz[l][c]!='+') // VERIFICA SE A POSIÇÃO JÁ SAIU
                        {
                            Abrirmatriz(matriz, matriz2, l, c, linha, coluna,contar_posicoes); // CHAMA A FUNCAO DE RECURSIVIDADE CASO NECESSARIO
                            if(contar_posicoes == linha*coluna-minas)// VERIFICA SE APÓS A JOGADA, O JOGADOR GANHOU
                            {
                                system("cls");

                                cout<<"*****************************************************"<<endl;
                                cout<<"*****************************************************"<<endl;
                                cout<<"********************* YOU * WIN! ********************"<<endl;
                                cout<<"*****************************************************"<<endl;
                                cout<<"******************* VOCE * VENCEU! ******************"<<endl;
                                cout<<"*****************************************************"<<endl;
                                cout<<"*****************************************************"<<endl<<endl;

                                ImprimirBombas(matriz, matriz2, linha, coluna);


                                FINAL = time(NULL);
                                TEMPO = FINAL - INICIAL;
                                paineltempo(TEMPO); // PAINEL DO TEMPO

                                int op;

                                cout<<endl<<endl;
                                cout<<"Deseja Jogar Novamente ?"<<endl;
                                cout<<"[1] Sim"<<endl;
                                cout<<"[2] Nao"<<endl<<endl;;
                                cout<<"Opcao: ";
                                cin>>op;

                                if(op==1) // VERIFICA SE DESEJA JOGAR NOVAMENTE OU NAO
                                {
                                    cout<<endl;
                                    system("cls");
                                    return ;
                                }
                                else
                                {
                                    exit(0);
                                }
                            }
                        }
                        else
                        {
                            system("cls");
                            cout<<"      Posicao ja Saiu!!"<<endl<<endl;
                        }
                    }
                    else
                    {
                        system("cls");

                        cout<<"*****************************************************"<<endl;
                        cout<<"*****************************************************"<<endl;
                        cout<<"******************** GAME * OVER! *******************"<<endl;
                        cout<<"*****************************************************"<<endl;
                        cout<<"******************* VOCE * PERDEU! ******************"<<endl;
                        cout<<"*****************************************************"<<endl;
                        cout<<"*****************************************************"<<endl<<endl;

                        ImprimirBombas(matriz, matriz2, linha, coluna);

                        FINAL = time(NULL);
                        TEMPO = FINAL - INICIAL;
                        paineltempo(TEMPO); // PAINEL DO TEMPO

                        int op;

                        cout<<endl<<endl;
                        cout<<"Deseja Jogar Novamente ?"<<endl;
                        cout<<"[1] Sim"<<endl;
                        cout<<"[2] Nao"<<endl<<endl;;
                        cout<<"Opcao: ";
                        cin>>op;

                        if(op==1) // VERIFICA SE DESEJA JOGAR NOVAMENTE OU NAO
                        {
                            cout<<endl;
                            system("cls");
                            return ;
                        }
                        else
                        {
                            exit(0);
                        }
                    }
                }
                else
                {
                    system("cls");
                    cout<<"Posicao Fora dos Limites!!! Escolha Sempre no limite do Campo!!"<<endl<<endl;
                }

                break;

            case 2:

                system("cls");
                ImprimirMatriz(matriz, matriz2, linha, coluna);
                cout<<endl;

                FINAL = time(NULL);
                TEMPO = FINAL - INICIAL;
                paineltempo(TEMPO); // PAINEL DO TEMPO

                cout<<endl<<endl;
                cout<<"Linha e Coluna: ";
                cin>>l>>c;
                system("cls");

                if(matriz[l][c]!='_' && matriz[l][c]!='+') // VERIFICA SE A POSICAO JA FOI EXIBIDA (ABERTA)
                {
                    matriz[l][c]='M';
                    Minas_Marcadas--;
                }else{
                    system("cls");
                    cout<<"Voce nao pode marcar essa posicao!!!"<<endl;
                    cout<<"Pois ja foi exibida!!!"<<endl<<endl;
                }

                break;

            case 3:

                system("cls");
                ImprimirMatriz(matriz, matriz2, linha, coluna);
                cout<<endl;

                FINAL = time(NULL);
                TEMPO = FINAL - INICIAL;
                paineltempo(TEMPO); // PAINEL DO TEMPO

                cout<<endl<<endl;
                cout<<"Linha e Coluna: ";
                cin>>l>>c;
                system("cls");

                if(matriz[l][c]!='_' && matriz[l][c]!='+') // VERIFICA SE A POSICAO JA FOI EXIBIDA (ABERTA)
                {
                    matriz[l][c]='?';
                }else{
                    system("cls");
                    cout<<"Voce nao pode marcar essa posicao!!!"<<endl;
                    cout<<"Pois ja foi exibida!!!"<<endl<<endl;
                }

                break;

            case 4:

                system("cls");
                ImprimirMatriz(matriz, matriz2, linha, coluna);
                cout<<endl;

                FINAL = time(NULL);
                TEMPO = FINAL - INICIAL;
                paineltempo(TEMPO); // PAINEL DO TEMPO

                cout<<endl<<endl;
                cout<<"Linha e Coluna: ";
                cin>>l>>c;
                system("cls");

                if(matriz[l][c]!='_' && matriz[l][c]!='+' && matriz[l][c]!='.') // VERIFICA SE A POSICAO AINDA NAO FOI EXIBIDA OU
                {
                    if(matriz[l][c]=='M')
                    {
                        Minas_Marcadas++;
                    }
                    matriz[l][c]='.';
                }else{
                    system("cls");
                    cout<<"Voce nao pode limpar essa posicao!!!"<<endl;
                    cout<<"Pois Nao foi Descoberta ou Marcada!!!"<<endl<<endl;
                }

                break;

            case 5:
                exit(0);

            default:
                system("cls");
                cout<<"Opcao Invalida!!!"<<endl<<endl;
                system("pause");
                system("cls");
                break;

        }

        FINAL = time(0);
        TEMPO = FINAL - INICIAL;

    }while(true);

}

// FUNCAO PRINCIPAL
int main()
{
    char matriz[tam][tam];
    int matriz2[tam][tam];

    int linha,coluna;
    int minas;
    int opcao,opcao2;

    cout<<"      ____________________________________________________________________"<<endl;
    cout<<"     |                                                                    | "<<endl;
    cout<<"     |  ****************************************************************  |"<<endl;
    cout<<"     |  ************************* CAMPO MINADO *************************  |"<<endl;
    cout<<"     |  ****************************************************************  |"<<endl;
    cout<<"     |                                                                    |"<<endl;
    cout<<"     |             UNIVERSIDADE FEDERAL DO RIO GRANDE DO NORTE            |"<<endl;
    cout<<"     |             -------------------------------------------            |"<<endl;
    cout<<"     |                 BACHARELADO EM CIENCIAS E TECNOLOGIA               |"<<endl;
    cout<<"     |                 ------------------------------------               |"<<endl;
    cout<<"     |                      LINGUAGEM DE PROGRAMACAO                      |"<<endl;
    cout<<"     |                      ------------------------                      |"<<endl;
    cout<<"     |                                                                    |"<<endl;
    cout<<"     |                          DESENVOLVEDORES:                          |"<<endl;
    cout<<"     |                                                                    |"<<endl;
    cout<<"     |                                                                    |"<<endl;
    cout<<"     |                                                                    |"<<endl;
    cout<<"     |                        JADERSON DE OLIVERA                         |"<<endl;
    cout<<"     |____________________________________________________________________|"<<endl;
    cout<<endl;
    system("pause");
    system("cls");

    do
    {
        cout<<"[1] Novo Jogo"<<endl;
        cout<<"[2] Melhores Tempo"<<endl;
        cout<<"[3] Sair"<<endl<<endl;

        cout<<"Digite sua escolha: ";
        cin>>opcao;

        cout<<endl;

        system("cls");

        switch(opcao)
        {
        case 1: // MENU DE TIPO DE JOGO
            cout<<"[1] Jogo Iniciante"<<endl;
            cout<<"[2] Jogo Intermediario"<<endl;
            cout<<"[3] Jogo Personalizado"<<endl;
            cout<<"[4] Voltar"<<endl<<endl;
            cout<<"Digite sua escolha: ";
            cin>>opcao2;

            system("cls");

            switch(opcao2)
            {
            case 1: // JOGO INICIANTE

                linha = 8;
                coluna = 8;
                minas = 10;

                JogarMatriz(matriz, matriz2, linha, coluna, minas);

                break;

            case 2: // JOGO INTERMEDIARIO

                linha = 16;
                coluna = 16;
                minas = 40;

                JogarMatriz(matriz, matriz2, linha, coluna, minas);

                break;

            case 3:  // JOGO PERSONALIZADO RESPEITANDO OS LIMITES DE NO MAXIMO 40 LINHAS, 40 COLUNA E MINAS ( (LINHAS * COLUNA)- 10 )

                cout<<"Respeito o Limite Maximo de : 40 Linhas , 40 Colunas e Minas ( (Linhas * Colunas)- 10 )"<<endl<<endl;
                cout<<"Total de Linhas: ";cin>>linha;
                cout<<"Total de Coluna: ";cin>>coluna;
                cout<<"Total de Minas: ";cin>>minas;

                system("cls");

                if(linha <= 40 && coluna <= 40 && ( minas <= (linha * coluna)- 10 ) )
                {
                    JogarMatriz(matriz, matriz2, linha, coluna, minas);
                }else
                {
                    cout<<"Voce Nao Respeitou os Limites!!!"<<endl<<endl;
                    system("pause");
                    system("cls");
                }

                break;

            case 4: // VOLTAR
                break;

            default:
                cout<<"Opcao Invalida!!!"<<endl<<endl;
                system("pause");
                system("cls");

            }

            break;

        case 2: // MELHORES TEMPOS
            cout<<"Melhores Tempos: "<<endl;
            break;

        case 3: // SAIR
            exit(0);

        default:
            cout<<"Opcao Invalida!!!"<<endl<<endl;
            system("pause");
            system("cls");

        }
    }while(true);

    return 0;
}


