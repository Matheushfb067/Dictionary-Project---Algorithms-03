/*
    Cauã de Souza Flauzino, GES, 410    
    Júlia Pereira Garcia Caputo, GES, 687
    Luana Roland Severini, GES, 363
    Luis Antônio Ribeiro Teles, GEC, 2223
    Matheus Henrique Ferreira Braz, GES, 636
*/

#include <iostream>
#include <string>
#include <locale>
using namespace std;

// Funções para cada funcionalidade
void cadastrarPalavra()
{
    cout << "Funcionalidade em construção\n";
}

void listarSignificados()
{
    cout << "Funcionalidade em construção\n";
}

void listarSinonimos()
{
    cout << "Funcionalidade em construção\n";
}

void listarOrdemAlfabetica()
{
    cout << "Funcionalidade em construção\n";
}

void listarPorTamanho()
{
    cout << "Funcionalidade em construção\n";
}

void removerPalavra()
{
    cout << "Funcionalidade em construção\n";
}

void calcularSimilaridade()
{
    cout << "Funcionalidade em construção\n";
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

        switch (opcao) {
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