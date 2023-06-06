#include "cCliente.h"
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>

using namespace std;

cCliente::cCliente() {
}

cCliente::cCliente(const cCliente& orig) {
}

cCliente::~cCliente() {
}

void cCliente::menuCliente() {

    int opcao;

    while (opcao != 0) {
        system("clear||cls");
        cout << "" << endl;
        cout << "     MENU DE CLIENTES     " << endl;
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
                primeiro = inserir_cliente(primeiro);
                cin.get();
                break;

            case 2:
                system("clear||cls");
                listar_cliente(primeiro);
                cin.get();
                break;

            case 3:
                system("clear||cls");
                primeiro = excluir_cliente(primeiro);
                cin.get();
                break;

            case 4:
                system("clear||cls");
                alterar_cliente(primeiro);
                cin.get();
                break;

            case 5:
                system("clear||cls");
                buscar_cliente(primeiro);
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

cCliente::Cliente* cCliente::inserir_cliente(Cliente* primeiro) {

    Cliente* atual = primeiro;
    char identificador = 'F';

    Cliente* cliente = new Cliente();

    cout << "NOME: ";
    getline(cin, cliente->nome);
    cout << "ENDEREÇO: ";
    getline(cin, cliente->endereco);
    cout << "CÓDIGO: ";
    cin >> cliente->codigo;
    cin.ignore();

    for (atual = primeiro; atual != NULL; atual = atual->prox) {
        if (atual->codigo == cliente->codigo) {
            identificador = 'V';
            break;
        }
    }

    if (identificador != 'V' && (!cliente->nome.empty() && !cliente->endereco.empty())) {
        cliente->prox = primeiro;
        cout << "Cadastro realizado com sucesso." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
        return cliente;
    } else {
        cout << "Cadastro inválido." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
        delete cliente;
        return primeiro;
    }
}

void cCliente::listar_cliente(Cliente* primeiro) {

    Cliente* atual = primeiro;

    while (atual != NULL) {
        cout << "NOME: " << atual->nome << endl;
        cout << "ENDEREÇO: " << atual->endereco << endl;
        cout << "CÓDIGO: " << atual->codigo << endl << endl;
        atual = atual->prox;
    }

    if (primeiro == NULL)
        cout << "Nenhum cliente cadastrado." << endl;

    
    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
}

cCliente::Cliente* cCliente::excluir_cliente(Cliente* primeiro) {

    Cliente* anterior = NULL;
    Cliente* atual = primeiro;
    unsigned long int codigo = 0;

    cout << "Código do cliente a ser excluído: ";
    cin >> codigo;
    cin.ignore();

    while (atual != NULL && atual->codigo != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        cout << endl << "Cliente não encontrado." << endl;
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

void cCliente::alterar_cliente(Cliente* primeiro) {

    string nome_substituto, endereco_substituto;
    unsigned long int codigo;
    Cliente* atual = primeiro;

    cout << "Código do cliente a ser alterado: ";
    cin >> codigo;
    cin.ignore();

    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        cout << endl << "NOVO NOME: ";
        getline(cin, nome_substituto);
        atual->nome = nome_substituto;

        cout << "NOVO ENDEREÇO: ";
        getline(cin, endereco_substituto);
        atual->endereco = endereco_substituto;

        cout << "Dados alterados com sucesso." << endl;
    } else {
        cout << endl << "Cliente não encontrado." << endl;
    }

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
}

void cCliente::buscar_cliente(Cliente* primeiro) {

    unsigned long int codigo;
    Cliente* atual = primeiro;

    cout << "Código do cliente a ser buscado: ";
    cin >> codigo;
    cin.ignore();

    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        cout << "NOME: " << atual->nome << endl;
        cout << "ENDEREÇO: " << atual->endereco << endl;
        cout << "CÓDIGO: " << atual->codigo << endl << endl;
    } else {
        cout << endl << "Cliente não encontrado." << endl;
    }

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
}
