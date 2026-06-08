#include <iostream>
#include <fstream>
#include <string>

#include "Dicionario.hpp"

using namespace std;

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

    // 2. Verificar dois textos de teste (correto e com erro)
    verificarErrosOrtograficos(meuDicionario, "Base de dados/texto_teste_correto.txt");
    verificarErrosOrtograficos(meuDicionario, "Base de dados/texto_teste_com_erro.txt");

    return 0;
}