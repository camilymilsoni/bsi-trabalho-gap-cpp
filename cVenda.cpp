#include "cVenda.h"
#include "cCliente.h"
#include "cProduto.h"
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <stdlib.h>
#include <cstdio>

using namespace std;

cCliente* objCliente = new cCliente();
cProduto* objProduto = new cProduto();

cVenda::cVenda(cCliente* objClient, cProduto* objProdut) {
    objCliente = objClient;
    objProduto = objProdut;
}

cVenda::cVenda(const cVenda& orig) {
}

cVenda::~cVenda() {
}

void cVenda::inserir_venda() {
    Venda* atual = primeiro;
    char identificador = 'F';

    Venda* venda = new Venda();

    if (primeiro == NULL) {
        cout << "CÓDIGO DA VENDA: ";
        cin >> venda->codigo_venda;
        cout << endl;
    } else {
        do {
            cout << "CÓDIGO DA VENDA: ";
            cin >> venda->codigo_venda;
            cout << endl;
        } while (verifica_codigo_venda(venda->codigo_venda));
    }

    do {
        cout << "CLIENTES: " << endl;
        if (objCliente->listar_cliente_venda()) {
            return;
        } else {
            cout << endl << endl << "CÓDIGO DO CLIENTE: ";
            cin >> venda->codigo_cliente;
            system("clear||cls");
        }
    } while (objCliente->codigo_valido_cliente(venda->codigo_cliente));
    int opc = -1;

    do {
        system("clear||cls");
        Produto* produto = new Produto();
        cout << "Adicionar um produto ao carrinho? ";
        cout << endl << "1. SIM";
        cout << endl << "2. NÃO";
        cout << endl << "Insira a opção desejada: ";
        cin >> opc;
        cin.ignore();
        system("clear||cls");
        switch (opc) {
            case 1:
                do {
                    system("clear||cls");
                    if (objProduto->listar_produto_venda()) {
                        return;
                    } else {
                        cout << endl << endl << "CÓDIGO DO PRODUTO: ";
                        cin >> produto->codigo_produto;
                        system("clear||cls");
                    }
                } while (objProduto->codigo_valido_produto(produto->codigo_produto));
                cout << "QUANTIDADE: ";
                cin >> produto->quantidade;
                system("clear||cls");
                produto->valor_total_produto = produto->quantidade * objProduto->valor_produto(produto->codigo_produto);
                venda->valor_total = venda->valor_total + produto->valor_total_produto;

                unsigned int codigo_venda_produto;

                cout << "CÓDIGO VENDA_PRODUTO: ";
                cin >> codigo_venda_produto;
                cin.ignore();

                if (codigo_valido_venda_produto(codigo_venda_produto, venda)) {
                    system("clear||cls");
                    venda->valor_total = venda->valor_total - produto->valor_total_produto;
                    delete produto;
                    cout << "Código Inválido.";
                    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                    cin.get();
                } else {

                    produto->codigo_venda_produto = codigo_venda_produto;

                    if (venda->produto_compra == NULL) {
                        venda->produto_compra = produto;
                    } else {
                        Produto* produtoAtual = venda->produto_compra;
                        produto->prox = produtoAtual;
                        venda->produto_compra = produto;
                    }
                }
                break;
            case 2:
                system("clear||cls");
                opc == 2;
                break;
            default:
                cout << "Opção inválida." << endl;
                cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                cin.get();
                system("clear||cls");
        }
    } while (opc != 2);

    for (atual = primeiro; atual != NULL; atual = atual->prox) {
        if (atual->codigo_venda == venda->codigo_venda) {
            identificador = 'V';
            break;
        }
    }

    if (identificador != 'V' && (venda->codigo_cliente != 0 && venda->produto_compra != nullptr) && venda->valor_total != 0) {
        venda->prox = primeiro;
        cout << "Cadastro realizado com sucesso." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
        primeiro = venda;
        return;
    }

}

void cVenda::listar_venda() {

    Venda* atual = primeiro;

    while (atual != NULL) {
        cout << "-------------------------------" << endl;
        cout << "CÓDIGO DA VENDA: " << atual->codigo_venda << endl;
        objCliente->mostrar_cliente(atual->codigo_cliente);
        cout << endl << endl << "**PRODUTOS VENDIDOS**" << endl;
        listar_produto(atual->produto_compra);
        cout << endl << "**VALOR TOTAL DA VENDA: " << atual->valor_total << endl;
        cout << "-------------------------------" << endl << endl;
        atual = atual->prox;
    }

    if (primeiro == NULL)
        cout << "Nenhuma venda cadastrada." << endl;

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";

}

void cVenda::excluir_venda(Venda* primeiro) {
    Venda* anterior = NULL;
    Venda* atual = primeiro;

    Produto* produto = new Produto();
    unsigned long int codigo = 0;

    cout << "Código da venda a ser excluída: ";
    cin >> codigo;
    cin.ignore();

    produto = atual->produto_compra;

    while (produto != NULL) {
        Produto* aux = new Produto();
        aux = produto->prox;
        produto = produto->prox;
        delete aux;
    }

    while (atual != NULL && atual->codigo_venda != codigo) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        cout << endl << "Venda não encontrada." << endl;
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
    this->primeiro = primeiro;
}

void cVenda::alterar_venda(Venda* primeiro) {
    Venda* atual = primeiro;
    unsigned int codigo_venda;


    cout << "Código da venda a ser alterada: ";
    cin >> codigo_venda;
    cin.ignore();

    while (atual != NULL && atual->codigo_venda != codigo_venda) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        int opc1;
        alterar_venda_produto(atual);
        do {
            system("clear||cls");
            cout << "Deseja alterar o cliente? ";
            cout << endl << "1. SIM";
            cout << endl << "2. NÃO";
            cout << endl << "Insira a opção desejada: ";
            cin >> opc1;
            switch (opc1) {
                case 1:
                    do {
                        system("clear||cls");
                        cout << "CLIENTES: " << endl;
                        if (objCliente->listar_cliente_venda()) {
                            return;
                        } else {
                            cout << endl << endl << "CÓDIGO DO CLIENTE: ";
                            cin >> atual->codigo_cliente;
                            system("clear||cls");
                        }
                    } while (objCliente->codigo_valido_cliente(atual->codigo_cliente));
                    break;
                case 2:
                    opc1 = 2;
                    system("clear||cls");
                    break;
                default:
                    system("clear||cls");
                    cout << "Opção inválida." << endl;
                    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                    cin.get();
                    cin.get();
                    system("clear||cls");
                    break;
            }
        } while (opc1 != 2 );

        cout << "Dados alterados com sucesso." << endl;
    } else {
        cout << endl << "Venda não encontrada." << endl;
    }

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
    cin.get();
}

void cVenda::buscar_venda(Venda* primeiro) {
    unsigned long int codigo;
    Venda* atual = primeiro;

    cout << "Código da venda a ser buscada: ";
    cin >> codigo;
    cin.ignore();

    while (atual != NULL && atual->codigo_venda != codigo) {
        atual = atual->prox;
    }

    if (atual != NULL) {
        cout << endl << "-------------------------------" << endl;
        cout << "CÓDIGO DA VENDA: " << atual->codigo_venda << endl;
        objCliente->mostrar_cliente(atual->codigo_cliente);
        cout << endl << endl << "**PRODUTOS VENDIDOS**" << endl;
        listar_produto(atual->produto_compra);
        cout << endl << "**VALOR TOTAL DA VENDA: " << atual->valor_total << endl;
        cout << "-------------------------------" << endl << endl;
    } else {
        cout << endl << "Venda não encontrada." << endl;
    }

    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
}

bool cVenda::verifica_codigo_venda(int codigo_venda) {
    unsigned long int codigo = codigo_venda;
    Venda* atual = this->primeiro;
    while (atual != NULL) {
        if (atual->codigo_venda == codigo_venda) {
            cout << "Código inválido." << endl;
            cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR**";
            cin.get();
            cin.get();
            system("clear||cls");
            return true;
        }
        atual = atual->prox;
    }
    return false;
}

bool cVenda::codigo_valido_venda_produto(int codigo_venda_produto, Venda* venda) {
    unsigned long int codigo = codigo_venda_produto;
    Produto* atual = venda->produto_compra;
    while (atual != NULL) {
        if (atual->codigo_venda_produto == codigo) {
            system("clear||cls");
            return true;
        }
        atual = atual->prox;
    }
    return false;
}

void cVenda::listar_produto(Produto* produto) {
    Produto* atual = produto;

    while (atual != NULL) {
        cout << "CÓDIGO VENDA_PRODUTO: " << atual->codigo_venda_produto << endl;
        cout << "CÓDIGO DO PRODUTO: " << atual->codigo_produto << endl;
        objProduto->mostrar_nome_valor_produto(atual->codigo_produto);
        cout << endl << "QUANTIDADE: " << atual->quantidade << endl << endl;
        atual = atual->prox;
    }

}

void cVenda::alterar_venda_produto(Venda* primeiro) {
    int opcao = -1;
    int opc = -1;
    Venda* atual = primeiro;
    Produto* produtoatual = primeiro->produto_compra;
    Produto* anterior = NULL;

    do {
        system("clear||cls");
        cout << endl << "1. ADICIONAR NOVO PRODUTO À VENDA" << endl;
        cout << "2. REMOVER PRODUTO DA VENDA " << endl;
        cout << "3. ALTERAR PRODUTO DA VENDA " << endl;
        cout << "0. SAIR " << endl;
        cout << endl << "Insira a opção desejada: ";
        cin >> opcao;
        system("clear||cls");
        cin.ignore();
        switch (opcao) {
            case 1:
                do {
                    system("clear||cls");
                    Produto* produto = new Produto();
                    cout << "Adicionar um produto ao carrinho? ";
                    cout << endl << "1. SIM";
                    cout << endl << "2. NÃO";
                    cout << endl << "Insira a opção desejada: ";
                    cin >> opc;
                    system("clear||cls");
                    cin.ignore();
                    switch (opc) {
                        case 1:
                            do {
                                system("clear||cls");
                                if (objProduto->listar_produto_venda()) {
                                    return;
                                } else {
                                    cout << endl << endl << "CÓDIGO DO PRODUTO: ";
                                    cin >> produto->codigo_produto;
                                    system("clear||cls");
                                }
                            } while (objProduto->codigo_valido_produto(produto->codigo_produto));
                            cout << "QUANTIDADE: ";
                            cin >> produto->quantidade;
                            system("clear||cls");
                            produto->valor_total_produto = produto->quantidade * objProduto->valor_produto(produto->codigo_produto);
                            atual->valor_total = atual->valor_total + produto->valor_total_produto;
                            unsigned int codigo_venda_produto;

                            cout << "CÓDIGO VENDA_PRODUTO: ";
                            cin >> codigo_venda_produto;
                            cin.ignore();

                            if (codigo_valido_venda_produto(codigo_venda_produto, atual)) {
                                system("clear||cls");
                                atual->valor_total = atual->valor_total - produto->valor_total_produto;
                                delete produto;
                                cout << "Código Inválido.";
                                cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                                cin.get();
                            } else {

                                produto->codigo_venda_produto = codigo_venda_produto;

                                if (atual->produto_compra == NULL) {
                                    atual->produto_compra = produto;
                                } else {
                                    Produto* produtoAtual = atual->produto_compra;
                                    produto->prox = produtoAtual;
                                    atual->produto_compra = produto;
                                }
                            }
                            break;
                        case 2:
                            system("clear||cls");
                            opc == 2;
                            break;
                        default:
                            cout << "Opção inválida." << endl;
                            cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                            cin.get();
                            system("clear||cls");
                    }
                } while (opc != 2);
                break;
            case 2:
                unsigned int codigo;
                cout << endl << endl << "**PRODUTOS VENDIDOS**" << endl;
                listar_produto(atual->produto_compra);
                cout << endl << "INSIRA O CÓDIDO DO VENDA_PRODUTO: ";
                cin >> codigo;

                produtoatual = primeiro->produto_compra;

                while (produtoatual != NULL && produtoatual->codigo_venda_produto != codigo) {
                    anterior = produtoatual;
                    produtoatual = produtoatual->prox;
                }

                if (produtoatual == NULL) {
                    cout << endl << "Produto não encontrado." << endl;
                } else {
                    if (anterior == NULL) {
                        primeiro->produto_compra = produtoatual->prox;
                    } else {
                        anterior->prox = produtoatual->prox;
                    }

                    cout << endl << "Conteúdo excluído com sucesso." << endl;
                    cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                    cin.get();
                    cin.get();
                    primeiro->valor_total = primeiro->valor_total - produtoatual->valor_total_produto;
                    delete produtoatual;
                }

                cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                break;
            case 3:
                unsigned int codigo_produto;
                cout << endl << endl << "**PRODUTOS VENDIDOS**" << endl;
                listar_produto(atual->produto_compra);
                cout << endl << "INSIRA O CÓDIDO DO VENDA_PRODUTO: ";
                cin >> codigo_produto;

                produtoatual = primeiro->produto_compra;

                while (produtoatual != NULL && produtoatual->codigo_venda_produto != codigo_produto) {
                    produtoatual = produtoatual->prox;
                }

                if (produtoatual == NULL) {
                    cout << endl << "Produto não encontrado." << endl;
                } else {
                    system("clear||cls");
                    if (objProduto->listar_produto_venda()) {
                        return;
                    } else {
                        Produto* produto = new Produto();
                        cout << endl << endl << "CÓDIGO DO PRODUTO: ";
                        cin >> produto->codigo_produto;
                        system("clear||cls");
                        cout << "QUANTIDADE: ";
                        cin >> produto->quantidade;
                        system("clear||cls");
                        produto->valor_total_produto = produto->quantidade * objProduto->valor_produto(produto->codigo_produto);
                        atual->valor_total = atual->valor_total + produto->valor_total_produto;
                        atual->valor_total = atual->valor_total - produtoatual->valor_total_produto;
                        produto->codigo_venda_produto = produtoatual->codigo_venda_produto;
                        primeiro->produto_compra = produto;
                        system("clear||cls");
                        cout << "Produto alterado com sucesso." << endl;
                        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                        cin.get();
                        cin.get();
                    }
                }

                break;
            case 0:
                opcao = 0;
                break;
            default:
                cout << "Opção inválida." << endl;
                cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR AO MENU**";
                cin.get();
                system("clear||cls");
                break;

        }
    } while (opcao != 0);
}

void cVenda::menuVenda() {
    int opcao;

    while (opcao != 0) {
        system("clear||cls");
        cout << "" << endl;
        cout << "      MENU DE VENDAS     " << endl;
        cout << "" << endl;
        cout << "    1. Novo Cadastro" << endl;
        cout << "---------------------------" << endl;
        cout << "    2. Listar Cadastros" << endl;
        cout << "---------------------------" << endl;
        cout << "    3. Excluir Cadastro" << endl;
        cout << "---------------------------" << endl;
        cout << "    4. Alterar Cadastro" << endl;
        cout << "---------------------------" << endl;
        cout << "    5. Buscar Cadastro" << endl;
        cout << "---------------------------" << endl;
        cout << "    0. Voltar" << endl;
        cout << "" << endl;
        cout << "INFORME A SUA OPÇÃO: ";
        cin >> opcao;
        cin.ignore();
        cout << endl;

        switch (opcao) {
            case 1:
                system("clear||cls");
                inserir_venda();
                cin.get();
                break;

            case 2:
                system("clear||cls");
                listar_venda();
                cin.get();
                break;

            case 3:
                system("clear||cls");
                excluir_venda(primeiro);
                cin.get();
                break;

            case 4:
                system("clear||cls");
                alterar_venda(primeiro);
                cin.get();
                break;

            case 5:
                system("clear||cls");
                buscar_venda(primeiro);
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

bool cCliente::listar_cliente_venda() {

    Cliente* atual = this->primeiro;

    while (atual != NULL) {
        cout << atual->codigo;
        cout << "- " << atual->nome << ", ";
        atual = atual->prox;
    }

    if (primeiro == NULL) {
        cout << "Nenhum produto cadastrado." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR**";
        cin.get();
        system("clear||cls");
        return true;
    }
    return false;
}

bool cCliente::codigo_valido_cliente(int codigo_cliente) {
    unsigned long int codigo = codigo_cliente;
    Cliente* atual = this->primeiro;

    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->prox;
    }

    if (atual != NULL) {

    } else {
        cout << endl << "Cliente não encontrado." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR**";
        cin.get();
        cin.get();
        system("clear||cls");
        return true;
    }
    return false;
}

bool cProduto::listar_produto_venda() {

    Produto* atual = this->primeiro;

    while (atual != NULL) {
        cout << atual->codigo;
        cout << "- " << atual->nome << ", ";
        atual = atual->prox;
    }

    if (primeiro == NULL) {
        cout << "Nenhum cliente cadastrado." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR**";
        cin.get();
        cin.get();
        system("clear||cls");
        return true;
    }
    return false;
}

bool cProduto::codigo_valido_produto(int codigo_produto) {
    unsigned long int codigo = codigo_produto;
    Produto* atual = this->primeiro;

    cin.ignore();

    while (atual != NULL && atual->codigo != codigo) {
        atual = atual->prox;
    }

    if (atual != NULL) {

    } else {
        cout << endl << "Produto não encontrado." << endl;
        cout << endl << "**PRESSIONE QUALQUER TECLA PARA VOLTAR**";
        cin.get();
        system("clear||cls");
        return true;
    }
    return false;
}

double cProduto::valor_produto(int codigo_produto) {
    Produto* atual = this->primeiro;

    while (atual->codigo != codigo_produto) {
        atual = atual->prox;
    }
    return atual->valor;
}

void cCliente::mostrar_cliente(int codigo_cliente) {
    Cliente* atual = this->primeiro;

    while (atual != NULL) {
        if (atual->codigo == codigo_cliente) {
            cout << "CÓDIGO DO CLIENTE: " << atual->codigo << endl;
            cout << "NOME DO CLIENTE: " << atual->nome;
        }
        atual = atual->prox;
    }
}

void cProduto::mostrar_nome_valor_produto(int codigo_produto) {
    Produto* atual = this->primeiro;

    while (atual != nullptr) {
        if (atual->codigo == codigo_produto) {
            cout << "NOME DO PRODUTO: " << atual->nome << endl;
            cout << "VALOR DO PRODUTO: " << atual->valor;
        }
        atual = atual->prox;
    }
}