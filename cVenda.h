#ifndef CVENDA_H
#define CVENDA_H
#include <iostream>

#include "cCliente.h"
#include "cProduto.h"

using namespace std;

class cVenda {
public:
    cVenda(cCliente* objClient, cProduto* objProdut);
    cVenda(const cVenda& orig);
    virtual ~cVenda();

    struct Produto {
        unsigned long int codigo_venda_produto, codigo_produto, quantidade;
        double valor_total_produto;
        struct Produto* prox = NULL;
    };
    
    struct Venda {
        double valor_total;
        unsigned long int codigo_venda, codigo_cliente;
        Produto* produto_compra = NULL;
        struct Venda* prox = NULL;
    };

    Venda* primeiro = NULL;
    
    void inserir_venda();
    void listar_venda();
    void excluir_venda(Venda* primeiro);
    void alterar_venda(Venda* primeiro);
    void buscar_venda(Venda* primeiro);
    void buscar_venda_produto(Venda* primeiro);
    void buscar_compra_cliente(Venda* primeiro);
    bool verifica_codigo_venda(int codigo_venda);
    bool codigo_valido_venda_produto (int codigo_venda_produto, Venda* venda);
    void menuVenda();
    void listar_produto(Produto* produto);
    void alterar_venda_produto(Venda* primeiro);
    
private:

};

#endif /* CVENDA_H */

