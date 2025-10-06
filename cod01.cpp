#include <iostream>
#include <string>
#include <locale>

using namespace std;

struct Palavra
{
    string ficticia;
    string portugues; // Significado principal/primeiro
    float x, y, z;
};

// variaveis globais
const int MAX_PALAVRAS = 100;
const int MAX_ARESTAS = 10; // Máximo de 10 significados por palavra

Palavra dicionario[MAX_PALAVRAS];
string adj[MAX_PALAVRAS][MAX_ARESTAS];   // Lista de adjacência (significados)
int qtdSignificados[MAX_PALAVRAS] = {0}; // Contagem de significados para cada palavra
int totalPalavras = 0;

void cadastrarPalavra()
{
    cout << "\n--- Cadastro de Palavra ---\n";
    cout << "Digite a palavra fictícia: ";
    string nomeFicticio;
    cin >> nomeFicticio;

    int indicePalavra = -1;
    // 1. Busca se a palavra já existe
    for (int i = 0; i < totalPalavras; i++)
    {
        if (dicionario[i].ficticia == nomeFicticio)
        {
            indicePalavra = i;
            break;
        }
    }

    // 2. Se a palavra foi encontrada, adiciona um novo significado
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
    // 3. Se não encontrou, cadastra uma nova palavra
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

    cout << "\nSinônimos de " << nome << ":\n";
    cout << "Significados da palavra buscada:\n";
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
        cout << "\nProcurando sinônimos para o significado: " << significadoAtual << endl;

        // ...procure em todas as outras palavras do dicionário...
        for (int j = 0; j < totalPalavras; j++)
        {
            if (j == indiceBusca)
                continue; // Pula a própria palavra

            cout << "  Verificando palavra: " << dicionario[j].ficticia << endl;
            cout << "  Significados:";
            for (int k = 0; k < qtdSignificados[j]; k++)
            {
                cout << " " << adj[j][k];
            }
            cout << endl;

            // ...e em todos os significados dela.
            for (int k = 0; k < qtdSignificados[j]; k++)
            {
                // Se encontrar um significado em comum e ainda não foi impresso
                if (adj[j][k] == significadoAtual && !jaImpresso[j])
                {
                    cout << "  >>> Encontrou significado em comum! <<<\n";
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
    cout << "Funcionalidade em constru��o\n";
}

void listarPorTamanho()
{
    cout << "Funcionalidade em constru��o\n";
}

void removerPalavra()
{
    cout << "Funcionalidade em constru��o\n";
}

void calcularSimilaridade()
{
    cout << "Funcionalidade em construção...\n";
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int opcao;

    do
    {
        cout << "\n===== MENU =====\n";
        cout << "1. Cadastrar palavra ou significado\n"; // Texto do menu atualizado
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