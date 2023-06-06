#include "cProduto.h"
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>

using namespace std;

cProduto::cProduto() {
}

cProduto::cProduto(const cProduto& orig) {
}

cProduto::~cProduto() {
}

void cProduto::menuProduto(){
    
    int opcao;

    while (opcao != 0) {
        system("clear||cls");
        cout << "" << endl;
        cout << "     MENU DE PRODUTOS     " << endl;
        cout << "" << endl;
        cout << "    1. Novo Cadastro" << endl;
        cout << "--------------------------" << endl;
        cout << "    2. Listar Cadastros" << endl;
        cout << "--------------------------" << endl;
        cout << "    3. Excluir Cadastro" << endl;
        cout << "--------------------------" << endl;
        cout << "    4. Alterar Cadastro" << endl;
        cout << "--------------------------" << endl;
        cout << "    5. Buscar Cadastro" << endl;
        cout << "--------------------------" << endl;
        cout << "    0. Voltar" << endl;
        cout << "" << endl;
        cout << "INFORME A SUA OPÇÃO: ";
        cin >> opcao;
        cin.ignore();
        cout << endl;

        switch (opcao) {
            case 1:
                system("clear||cls");
                primeiro = inserir_produto(primeiro);
                cin.get();
                break;

            case 2:
                system("clear||cls");
                listar_produto(primeiro);
                cin.get();
                break;

            case 3:
                system("clear||cls");
                primeiro = excluir_produto(primeiro);
                cin.get();
                break;

            case 4:
                system("clear||cls");
                alterar_produto(primeiro);
                cin.get();
                break;
                
            case 5:
                system("clear||cls");
                buscar_produto(primeiro);
                cin.get();
                break;

            case 0:
                system("clear||cls");
                opcao = 0;
                break;

            default:
                cout << "Opção inválida." << endl;
                cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                cin.get();
                break;
        }
    }
}

cProduto::Produto* cProduto::inserir_produto(Produto* primeiro){
    
    Produto* atual = primeiro;
    char identificador = 'F';

    Produto* produto = new Produto();

    cout << "NOME: ";
    getline(cin, produto->nome);
    cout << "VALOR: ";
    cin >> produto->valor;
    cout << "CÓDIGO: ";
    cin >> produto->codigo;
    cin.ignore();

    for(atual = primeiro; atual != NULL; atual = atual->prox) {
        if (atual->codigo == produto->codigo) {
            identificador = 'V';
            break;
        }
    }

    if(identificador != 'V' && (!produto->nome.empty() && produto->valor != 0)) {
        produto->prox = primeiro;
        cout << "Cadastro realizado com sucesso." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
        return produto;
    }else{
        cout << "Cadastro inválido." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
        delete produto;
        return primeiro;
    }
}

void cProduto::listar_produto(Produto* primeiro){
    
    Produto* atual = primeiro;

    while (atual != NULL) {
        cout << "NOME: " << atual->nome << endl;
        cout << "VALOR: " << atual->valor << endl;
        cout << "CÓDIGO: " << atual->codigo << endl << endl;
        atual = atual->prox;
    }

    if (primeiro == NULL)
        cout << "Nenhum produto cadastrado." << endl;

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
}

cProduto::Produto* cProduto::excluir_produto(Produto* primeiro) {
    
    Produto* anterior = NULL;
    Produto* atual = primeiro;
    unsigned long int codigo = 0;

    cout << "Código do produto a ser excluído: ";
    cin >> codigo;
    cin.ignore();

    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        cout << endl << "Produto não encontrado." << endl;
    } else {
        if (anterior == NULL) {
            primeiro = atual->prox;
        } else {
            anterior->prox = atual->prox;
        }

        cout << endl << "Conteúdo excluído com sucesso." << endl;
        delete atual;
    }

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
    return primeiro;
}

void cProduto::alterar_produto(Produto* primeiro){
    
    string nome_substituto;
    double valor_substituto;
    unsigned long int codigo;
    Produto* atual = primeiro;

    cout << "Código do produto a ser alterado: ";
    cin >> codigo;
    cin.ignore();

    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        cout << endl << "NOVO NOME: ";
        getline(cin, nome_substituto);
        atual->nome = nome_substituto;

        cout << "NOVO VALOR: ";
        cin >> valor_substituto;
        atual->valor = valor_substituto;

        cout << "Dados alterados com sucesso." << endl;
    } else {
        cout << endl << "Produto não encontrado." << endl;
    }

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
}

void cProduto::buscar_produto(Produto* primeiro){
    
    unsigned long int codigo;
    Produto* atual = primeiro;
    
    cout << "Código do produto a ser buscado: ";
    cin >> codigo;
    cin.ignore();
    
    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        cout << "NOME: " << atual->nome << endl;
        cout << "VALOR: " << atual->valor << endl;
        cout << "CÓDIGO: " << atual->codigo << endl << endl;
    } else {
        cout << endl << "Produto não encontrado." << endl;
    }

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
}