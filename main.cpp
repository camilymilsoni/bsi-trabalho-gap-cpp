#include <cstdlib>
#include <iostream>
#include "cCliente.h"
#include "cProduto.h"
#include "cVenda.h"

using namespace std;

void menuPrincipal();

int main(int argc, char** argv) {
    menuPrincipal();
    return 0;
}

void menuPrincipal() {
    cCliente* objCliente = new cCliente;
    cProduto* objProduto = new cProduto;
    cVenda* objVenda = new cVenda(objCliente, objProduto);
    
    int opcao = -1;
   
    while(opcao != 0){
        system("clear||cls");
        cout << "" << endl;
        cout << "    SISTEMA DE VENDAS     " << endl;
        cout << "" << endl;
        cout << "    1. Cliente" << endl;
        cout << "------------------------" << endl;
        cout << "    2. Produto" << endl;
        cout << "------------------------" << endl;
        cout << "    3. Venda" << endl;
        cout << "------------------------" << endl;
        cout << "    0. Sair" << endl;
        cout << "" << endl;
        cout << "INFORME A SUA OPÇÃO: ";
        cin >> opcao;
        
        switch (opcao){
        case 1:
            system("clear||cls");
            objCliente->menuCliente();
            break;

        case 2:
            system("clear||cls");
            objProduto->menuProduto();
            break;

        case 3:
            system("clear||cls");
            objVenda->menuVenda();
            break;

        case 0:
            system("clear||cls");
            opcao = 0;
            break;
            
        default:
            cout << "Opção inválida." << endl;
            cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU PRINCIPAL**";
            cin.get();
            cin.get();
        }
    }
}