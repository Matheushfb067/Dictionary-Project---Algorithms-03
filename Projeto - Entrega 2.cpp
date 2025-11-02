/*
    Cau� de Souza Flauzino, GES, 410    
    J�lia Pereira Garcia Caputo, GES, 687
    Luana Roland Severini, GES, 363
    Luis Ant�nio Ribeiro Teles, GEC, 2223
    Matheus Henrique Ferreira Braz, GES, 636
*/

#include <iostream>
#include <string>
#include <list>
#include <locale>
 
using namespace std;
 
struct Palavra
{
    string ficticia;
    string portugues; // Significado principal/primeiro
    float x, y, z;
};

struct treenode{
  Palavra info;
  struct treenode * left;
  struct treenode * right;
};

void tInsert(treenode* &p, Palavra novaPalavra){
    if(p == NULL){
        p = new treenode;
        p -> info = novaPalavra;
        p -> left = NULL;
        p -> right = NULL;
    }else if(novaPalavra.ficticia < p -> info.ficticia){
        tInsert(p -> left, novaPalavra);
    }else{ 
        tInsert(p -> right, novaPalavra);
    }
}

treenode* tSearch(treenode* p, Palavra palavra){
    if(p == NULL){
        return NULL;
    }else if(palavra.ficticia == p -> info.ficticia){
        return p;
    }else{
        if(palavra.ficticia < p-> info.ficticia)
            return tSearch(p -> left, palavra);
        else
            return tSearch(p -> right, palavra);
    }
}

// Variáveis globais
const int MAX_PALAVRAS = 1000; // Dicionário com, no máximo, 1000 palavras
const int MAX_ARESTAS = 10; // Máximo de 10 significados por palavra

Palavra dicionario[MAX_PALAVRAS];
string adj[MAX_PALAVRAS][MAX_ARESTAS];   // Lista de adjac�ncia (significados)
int qtdSignificados[MAX_ARESTAS] = {0}; // Contagem de significados para cada palavra
int totalPalavras = 0;

void cadastrarPalavra()
{
    cout << "\n--- Cadastro de Palavra ---\n";
    cout << "Digite a palavra fict�cia: ";
    string nomeFicticio;
    cin >> nomeFicticio;
 
    int indicePalavra = -1;
    
    // Busca se a palavra j� existe
    for (int i = 0; i < totalPalavras; i++)
    {
        if (dicionario[i].ficticia == nomeFicticio)
        {
            indicePalavra = i;
            break;
        }
    }
 
    // Se a palavra foi encontrada, adiciona um novo significado
    if (indicePalavra != -1)
    {
        if (qtdSignificados[indicePalavra] >= MAX_ARESTAS)
        {
            cout << "Limite de significados atingido para esta palavra!\n";
            return;
        }
        cout << "Palavra '" << nomeFicticio << "' j� existe. Digite um novo significado em portugu�s: ";
        string novoSignificado;
        cin >> novoSignificado;
 
        // Adiciona o novo significado (aresta)
        adj[indicePalavra][qtdSignificados[indicePalavra]] = novoSignificado;
        qtdSignificados[indicePalavra]++;
        cout << "Novo significado adicionado com sucesso!\n";
    }
    
	// Se n�o encontrou, cadastra uma nova palavra
    else
    {
        if (totalPalavras >= MAX_PALAVRAS)
        {
            cout << "Limite de palavras no dicion�rio atingido!\n";
            return;
        }
        dicionario[totalPalavras].ficticia = nomeFicticio;
        cout << "Digite o primeiro significado em portugu�s: ";
        cin >> dicionario[totalPalavras].portugues;
        cout << "Digite as coordenadas (x y z): ";
        cin >> dicionario[totalPalavras].x >> dicionario[totalPalavras].y >> dicionario[totalPalavras].z;
 
        // Adiciona o primeiro significado � lista de adjac�ncia
        adj[totalPalavras][0] = dicionario[totalPalavras].portugues;
        qtdSignificados[totalPalavras] = 1;
 
        totalPalavras++;
        cout << "Nova palavra cadastrada com sucesso!\n";
    }
}
 
void listarSignificados()
{
    if (totalPalavras == 0)
    {
        cout << "Nenhuma palavra cadastrada!\n";
        return;
    }
 
    string nome;
    cout << "\nDigite a palavra fict�cia: ";
    cin >> nome;
 
    bool encontrada = false;
 
    for (int i = 0; i < totalPalavras; i++)
    {
        if (dicionario[i].ficticia == nome)
        {
            encontrada = true;
            cout << "\nSignificados de " << nome << ":\n";
            for (int j = 0; j < qtdSignificados[i]; j++)
            {
                cout << "- " << adj[i][j] << endl;
            }
            break;
        }
    }
 
    if (!encontrada)
        cout << "Palavra n�o encontrada!\n";
}
 
void listarSinonimos()
{
    if (totalPalavras == 0)
    {
        cout << "Nenhuma palavra cadastrada!\n";
        return;
    }
 
    string nome;
    cout << "\nDigite a palavra fict�cia: ";
    cin >> nome;
 
    int indiceBusca = -1;
    for (int i = 0; i < totalPalavras; i++)
    {
        if (dicionario[i].ficticia == nome)
        {
            indiceBusca = i;
            break;
        }
    }
 
    if (indiceBusca == -1)
    {
        cout << "Palavra n�o encontrada!\n";
        return;
    }

    cout << "Significados da palavra buscada:\n";
    for (int i = 0; i < qtdSignificados[indiceBusca]; i++)
    {
        cout << "  - " << adj[indiceBusca][i] << endl;
    }
 
    bool achouSinonimo = false;
    bool jaImpresso[MAX_PALAVRAS] = {false}; // Vetor para n�o imprimir duplicados
 
    // Para cada significado da palavra original...
    for (int i = 0; i < qtdSignificados[indiceBusca]; i++)
    {
        string significadoAtual = adj[indiceBusca][i];
 
        // ...procure em todas as outras palavras do dicion�rio...
        for (int j = 0; j < totalPalavras; j++)
        {
            if (j == indiceBusca)
                continue; // Pula a pr�pria palavra
            cout << endl;
 
            // ...e em todos os significados dela.
            for (int k = 0; k < qtdSignificados[j]; k++)
            {
                // Se encontrar um significado em comum e ainda n�o foi impresso
                if (adj[j][k] == significadoAtual && !jaImpresso[j])
                {
                    cout << "  >>> Encontrou significado em comum! <<<\n";
                    cout << "- " << dicionario[j].ficticia << endl;
                    jaImpresso[j] = true; // Marca como impresso
                    achouSinonimo = true;
                    break; // Vai para a pr�xima palavra do dicion�rio
                }
            }
        }
    }
 
    if (!achouSinonimo)
        cout << "Nenhum sin�nimo encontrado.\n";
}
 
void listarOrdemAlfabetica()
{
    cout << "Funcionalidade em constru??o\n";
}
 
void listarPorTamanho()
{
    cout << "Funcionalidade em constru??o\n";
}
 
void removerPalavra()
{
    cout << "Funcionalidade em constru??o\n";
}
 
void calcularSimilaridade()
{
    cout << "Funcionalidade em constru��o...\n";
}
 
int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;
 
    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Cadastrar palavra\n";
        cout << "2. Listar significados de uma palavra\n";
        cout << "3. Listar sin�nimos de uma palavra\n";
        cout << "4. Listar palavras em ordem alfab�tica\n";
        cout << "5. Listar palavras por tamanho\n";
        cout << "6. Remover palavra\n";
        cout << "7. Calcular similaridade entre duas palavras\n";
        cout << "0. Sair\n";
        cout << "Escolha uma op��o: ";
        cin >> opcao;
 
        switch (opcao)
        {
        case 1:
            cadastrarPalavra();
            break;
        case 2:
            listarSignificados();
            break;
        case 3:
            listarSinonimos();
            break;
        case 4:
            listarOrdemAlfabetica();
            break;
        case 5:
            listarPorTamanho();
            break;
        case 6:
            removerPalavra();
            break;
        case 7:
            calcularSimilaridade();
            break;
        case 0:
            cout << "Encerrando o programa...\n";
            break;
        default:
            cout << "Op��o inv�lida!\n";
        }
    } while (opcao != 0);
 
    return 0;
}