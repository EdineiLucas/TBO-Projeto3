#include <iostream>
#include <fstream>
#include <string>

#include "Dicionario.hpp"

using namespace std;

void imprimirConteudoArquivo(const string& caminhoTexto) {
    ifstream arquivo(caminhoTexto);
    string linha;

    if (!arquivo.is_open()) {
        cerr << "Erro ao abrir o arquivo: " << caminhoTexto << endl;
        return;
    }
    
    cout << "\n=== CONTEUDO DO ARQUIVO: " << "===\n";
    while (getline(arquivo, linha)) {
        cout << linha << endl;
    }
    cout << "=================================\n";

    arquivo.close();
}

void verificarErrosOrtograficos(Dicionario& dict, const string& caminhoTexto) {
    ifstream arquivoTexto(caminhoTexto);
    string palavraNoTexto;

    if (!arquivoTexto.is_open()) {
        cerr << "Erro ao abrir o arquivo de texto: " << caminhoTexto << endl;
        return;
    }

    cout << "\n--- Verificando erros ortograficos ---\n";
    bool encontrouErro = false;
    
    while (arquivoTexto >> palavraNoTexto) {
        if (!dict.buscar(palavraNoTexto)) {
            // Imprimimos a palavra original do texto, mas destacando o erro
            cout << "[ERRO] Palavra nao encontrada: " << palavraNoTexto << endl;
            encontrouErro = true;
        }
    }
    
    if (!encontrouErro) {
        cout << "Nenhum erro encontrado! O texto esta correto.\n";
    }
    
    arquivoTexto.close();
}

int main() {
    Dicionario meuDicionario;

    // 1. Carregar o Dicionário
    string caminhoDict = "Base de dados/words.txt"; 
    ifstream arquivoDict(caminhoDict);
    string palavra;

    if (!arquivoDict.is_open()) {
        cerr << "Erro ao abrir o dicionario! " << caminhoDict << endl;
        return 1;
    }

    cout << "Carregando dicionario..." << endl;
    while (arquivoDict >> palavra) {
        meuDicionario.inserir(palavra);
    }

    arquivoDict.close();
    cout << "Dicionario carregado com sucesso!\n";

    // 2. Verificar os textos de teste
    cout << "\n========== TESTE 1 ==========";
    imprimirConteudoArquivo("Base de dados/texto_teste_correto.txt");
    verificarErrosOrtograficos(meuDicionario, "Base de dados/texto_teste_correto.txt");

    cout << "\n========== TESTE 2 ==========";
    imprimirConteudoArquivo("Base de dados/texto_teste_com_erro.txt");
    verificarErrosOrtograficos(meuDicionario, "Base de dados/texto_teste_com_erro.txt");

    cout << "\n========== TESTE 3 ==========";
    imprimirConteudoArquivo("Base de dados/texto_teste_3.txt");
    verificarErrosOrtograficos(meuDicionario, "Base de dados/texto_teste_3.txt");

    cout << "\n========== TESTE 4 ==========";
    imprimirConteudoArquivo("Base de dados/texto_teste_4.txt");
    verificarErrosOrtograficos(meuDicionario, "Base de dados/texto_teste_4.txt");

    return 0;
}