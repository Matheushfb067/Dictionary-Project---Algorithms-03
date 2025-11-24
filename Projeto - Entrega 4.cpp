/*
    Cauã de Souza Flauzino, GES, 410
    Júlia Pereira Garcia Caputo, GES, 687
    Luana Roland Severini, GES, 363
    Luis Antonio Ribeiro Teles, GEC, 2223
    Matheus Henrique Ferreira Braz, GES, 636
*/
 
#include <iostream>
#include <string>
#include <list>
#include <locale>
#include <cmath>
 
using namespace std;
 
// Structs

struct Palavra
{
    string ficticia;
    string portugues; // Significado principal/primeiro
    float x, y, z;
};
 
struct treenode
{
    Palavra info;
    struct treenode *left;
    struct treenode *right;
};

// Variáveis globais

const int MAX_PALAVRAS = 1000; // Dicionário com, no máximo, 1000 palavras
const int MAX_ARESTAS = 10;    // Máximo de 10 significados por palavra
 
Palavra dicionario[MAX_PALAVRAS];
string adj[MAX_PALAVRAS][MAX_ARESTAS];  // Lista de adjacência (significados)
int qtdSignificados[MAX_ARESTAS] = {0}; // Contagem de significados para cada palavra
int totalPalavras = 0;
 
treenode *arvore = NULL;
 
// Funções para manipulação da árvore binária

void tInsert(treenode *&p, Palavra novaPalavra)
{
    if (p == NULL)
    {
        p = new treenode;
        p->info = novaPalavra;
        p->left = NULL;
        p->right = NULL;
    }
    else if (novaPalavra.ficticia < p->info.ficticia)
    {
        tInsert(p->left, novaPalavra);
    }
    else
    {
        tInsert(p->right, novaPalavra);
    }
}
 
treenode *tSearch(treenode *p, Palavra palavra)
{
    if (p == NULL)
    {
        return NULL;
    }
    else if (palavra.ficticia == p->info.ficticia)
    {
        return p;
    }
    else
    {
        if (palavra.ficticia < p->info.ficticia)
            return tSearch(p->left, palavra);
        else
            return tSearch(p->right, palavra);
    }
}

treenode *encontrarMinimo(treenode *t)
{
    if (t == NULL)
        return NULL;
    else if (t->left == NULL)
        return t;
    else
        return encontrarMinimo(t->left);
}
 
// Função recursiva para remover da Árvore
void tRemove(treenode *&p, string val)
{
    if (p == NULL)
        return;
 
    if (val < p->info.ficticia)
    {
        tRemove(p->left, val);
    }
    else if (val > p->info.ficticia)
    {
        tRemove(p->right, val);
    }
    else // Encontrou o nó a ser removido
    {
        // Caso 1: Sem filhos (folha) e Caso 2: Um filho
        if (p->left == NULL)
        {
            treenode *temp = p;
            p = p->right;
            delete temp;
        }
        else if (p->right == NULL)
        {
            treenode *temp = p;
            p = p->left;
            delete temp;
        }
        // Caso 3: Dois filhos
        else
        {
            treenode *temp = encontrarMinimo(p->right);
            p->info = temp->info;                   // Copia os dados do sucessor
            tRemove(p->right, temp->info.ficticia); // Remove o sucessor duplicado
        }
    }
}

// Função recursiva para percorrer a árvore Em-Ordem (Esquerda -> Raiz -> Direita)
void percorrerEmOrdem(treenode *p)
{
    if (p != NULL)
    {
        // 1. Visita o filho da esquerda (palavras "menores" alfabeticamente)
        percorrerEmOrdem(p->left);
 
        // 2. Processa o nó atual (Raiz da sub-árvore)
        cout << p->info.ficticia << endl;
 
        // 3. Visita o filho da direita (palavras "maiores" alfabeticamente)
        percorrerEmOrdem(p->right);
    }
}

// Algoritmo quick sort para ordenação das palavras por tamanho
void quickSort(Palavra vetor[], int i, int j)
{
    Palavra trab;
    int esq, dir, pivo;
    esq = i;
    dir = j;
    pivo = vetor[(int)round((esq + dir) / 2.0)].ficticia.size();
    do
    {
        while (vetor[esq].ficticia.size() < pivo)
            esq++;
        while (vetor[dir].ficticia.size() > pivo)
            dir--;
 
        if (esq <= dir)
        {
            trab = vetor[esq];
            vetor[esq] = vetor[dir];
            vetor[dir] = trab;
            esq++;
            dir--;
        }
    } while (esq <= dir);
    if (dir - i >= 0)
        quickSort(vetor, i, dir);
    if (j - esq >= 0)
        quickSort(vetor, esq, j);
}

// Funções para o cálculo da distância euclidiana

double distSq(Palavra p1, Palavra p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                     (p1.y - p2.y) * (p1.y - p2.y) +
                     (p1.z - p2.z) * (p1.z - p2.z));
}
 
int buscarIndice(const string &nome)
{
    for (int i = 0; i < totalPalavras; i++)
    {
        if (dicionario[i].ficticia == nome)
        {
            return i;
        }
    }
    return -1; // Palavra não encontrada
}
 
void cadastrarPalavra()
{
    cout << "\n--- Cadastro de Palavra ---\n";
    cout << "Digite a palavra fictícia: ";
    string nomeFicticio;
    cin >> nomeFicticio;
 
    int indicePalavra = -1;
 
    // Busca se a palavra já existe
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
        cout << "Palavra '" << nomeFicticio << "' já existe. Digite um novo significado em português: ";
        string novoSignificado;
        cin >> novoSignificado;
 
        // Adiciona o novo significado (aresta)
        adj[indicePalavra][qtdSignificados[indicePalavra]] = novoSignificado;
        qtdSignificados[indicePalavra]++;
        cout << "Novo significado adicionado com sucesso!\n";
    }
 
    // Se não encontrou, cadastra uma nova palavra
    else
    {
        if (totalPalavras >= MAX_PALAVRAS)
        {
            cout << "Limite de palavras no dicionário atingido!\n";
            return;
        }
        dicionario[totalPalavras].ficticia = nomeFicticio;
        cout << "Digite o primeiro significado em português: ";
        cin >> dicionario[totalPalavras].portugues;
        cout << "Digite as coordenadas (x y z): ";
        cin >> dicionario[totalPalavras].x >> dicionario[totalPalavras].y >> dicionario[totalPalavras].z;
 
        // Adiciona o primeiro significado à lista de adjacência
        adj[totalPalavras][0] = dicionario[totalPalavras].portugues;
        qtdSignificados[totalPalavras] = 1;
 
        tInsert(arvore, dicionario[totalPalavras]);
 
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
    
    cout << "\n--- Lista de significados ---\n";
    cout << "\nDigite a palavra fictícia: ";
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
        cout << "Palavra não encontrada!\n";
}

void listarSinonimos()
{
    if (totalPalavras == 0)
    {
        cout << "Nenhuma palavra cadastrada!\n";
        return;
    }
 
    string nome;
    
    cout << "\n--- Lista de sinônimos ---\n";
    cout << "\nDigite a palavra fictícia: ";
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
        cout << "Palavra não encontrada!\n";
        return;
    }
 
    cout << "Significados da palavra informada:\n";
    for (int i = 0; i < qtdSignificados[indiceBusca]; i++)
    {
        cout << "  - " << adj[indiceBusca][i] << endl;
    }
 
    bool achouSinonimo = false;
    bool jaImpresso[MAX_PALAVRAS] = {false}; // Vetor para não imprimir duplicados
 
    // Para cada significado da palavra original...
    for (int i = 0; i < qtdSignificados[indiceBusca]; i++)
    {
        string significadoAtual = adj[indiceBusca][i];
 
        // ...procure em todas as outras palavras do dicionário...
        for (int j = 0; j < totalPalavras; j++)
        {
            if (j == indiceBusca)
                continue; // Pula a própria palavra
            cout << endl;
 
            // ...e em todos os significados dela.
            for (int k = 0; k < qtdSignificados[j]; k++)
            {
                // Se encontrar um significado em comum e ainda não foi impresso
                if (adj[j][k] == significadoAtual && !jaImpresso[j])
                {
                    cout << "  >>> Encontrou-se sinônimo(s)! <<<\n";
                    cout << "- " << dicionario[j].ficticia << endl;
                    jaImpresso[j] = true; // Marca como impresso
                    achouSinonimo = true;
                    break; // Vai para a próxima palavra do dicionário
                }
            }
        }
    }
 
    if (!achouSinonimo)
        cout << "Nenhum sinônimo encontrado.\n";
}
 
void listarOrdemAlfabetica()
{
    if (arvore == NULL)
    {
        cout << "Dicionário vazio (nenhuma palavra na árvore).\n";
        return;
    }
 
    cout << "\n--- Palavras em Ordem Alfabética ---\n";
    // Chama a função recursiva passando a raiz da árvore
    percorrerEmOrdem(arvore);
}
 
void listarPorTamanho()
{
    if (totalPalavras == 0)
    {
        cout << "Nenhuma palavra cadastrada.\n"
             << endl;
        return;
    }
    quickSort(dicionario, 0, totalPalavras - 1);
    
    cout << "\n--- Listagem em ordem crescente de tamanho ---\n";
    for (int i = 0; i < totalPalavras; i++)
    {
        cout << "[" << dicionario[i].ficticia.size() << "] " << dicionario[i].ficticia << endl;
    }
}

void removerPalavra()
{
    if (totalPalavras == 0)
    {
        cout << "Dicionário vazio.\n";
        return;
    }
 
    string nome;
    cout << "--- Remoção de palavras ---\n";
    cout << "\nDigite a palavra fictícia a ser removida: ";
    cin >> nome;
 
    int indiceAlvo = -1;
 
    // 1. Encontrar o índice no Array
    for (int i = 0; i < totalPalavras; i++)
    {
        if (dicionario[i].ficticia == nome)
        {
            indiceAlvo = i;
            break;
        }
    }
 
    if (indiceAlvo == -1)
    {
        cout << "Palavra não encontrada no dicionário!\n";
        return;
    }
 
    // 2. Remover da Árvore Binária
    tRemove(arvore, nome);
 
    // 3. Remover do Array e reorganizar índices (Shift Left)
    // Precisamos mover tudo que está à direita do índice removido uma casa para a esquerda
    // Isso deve ser feito no Dicionário, na Matriz de Adjacência e no vetor de Quantidades
    for (int i = indiceAlvo; i < totalPalavras - 1; i++)
    {
        // Move a palavra principal
        dicionario[i] = dicionario[i + 1];
 
        // Move a contagem de significados
        qtdSignificados[i] = qtdSignificados[i + 1];
 
        // Move os significados (arestas) daquela palavra
        for (int j = 0; j < MAX_ARESTAS; j++)
        {
            adj[i][j] = adj[i + 1][j];
        }
    }
 
    // Limpa a última posição (opcional, apenas para organização)
    qtdSignificados[totalPalavras - 1] = 0;
    for (int j = 0; j < MAX_ARESTAS; j++)
    {
        adj[totalPalavras - 1][j] = "";
    }
 
    totalPalavras--; // Decrementa o contador total
    cout << "Palavra '" << nome << "' removida com sucesso!\n";
}
 
void calcularSimilaridade()
{
    if (totalPalavras < 2)
    {
        cout << "São necessárias pelo menos duas palavras cadastradas.\n";
        return;
    }
 
    string nome1, nome2;
    cout << "\n--- Calcular Similaridade (Distância Euclidiana) ---\n";
    cout << "Digite a primeira palavra fictícia: ";
    cin >> nome1;
    cout << "Digite a segunda palavra fictícia: ";
    cin >> nome2;
 
    int indice1 = buscarIndice(nome1);
    int indice2 = buscarIndice(nome2);
 
    if (indice1 == -1)
    {
        cout << "Erro: Primeira palavra '" << nome1 << "' não encontrada!\n";
        return;
    }
    if (indice2 == -1)
    {
        cout << "Erro: Segunda palavra '" << nome2 << "' não encontrada!\n";
        return;
    }
 
    // Acessa as estruturas Palavra nos índices encontrados
    Palavra p1 = dicionario[indice1];
    Palavra p2 = dicionario[indice2];
 
    // Calcula a distância usando a função 3D
    double distancia = distSq(p1, p2);
 
    cout << "\nResultado da Similaridade:\n";
    cout << "- Palavra 1: " << p1.ficticia << " (" << p1.x << ", " << p1.y << ", " << p1.z << ")\n";
    cout << "- Palavra 2: " << p2.ficticia << " (" << p2.x << ", " << p2.y << ", " << p2.z << ")\n";
    cout << "Distância Euclidiana: " << distancia << endl;
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
        cout << "3. Listar sinônimos de uma palavra\n";
        cout << "4. Listar palavras em ordem alfabética\n";
        cout << "5. Listar palavras por tamanho\n";
        cout << "6. Remover palavra\n";
        cout << "7. Calcular similaridade entre duas palavras\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
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
            cout << "Opção inválida!\n";
        }
    } while (opcao != 0);
 
    return 0;
}