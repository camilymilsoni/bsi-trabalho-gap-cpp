#ifndef CPRODUTO_H
#define CPRODUTO_H
#include <iostream>

using namespace std;

class cProduto {
public:
    cProduto();
    cProduto(const cProduto& orig);
    virtual ~cProduto();
    
    struct Produto{
        string nome;
        double valor;
        unsigned long int codigo;
        struct Produto* prox;
    };
    
    Produto* primeiro = NULL;
    
    Produto* inserir_produto(Produto* primeiro);
    void listar_produto(Produto* primeiro);
    Produto* excluir_produto(Produto* primeiro);
    void alterar_produto(Produto* primeiro);
    void buscar_produto(Produto* primeiro);
    void menuProduto();
       
private:

};

#endif /* CPRODUTO_H */

