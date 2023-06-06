#ifndef CCLIENTE_H
#define CCLIENTE_H
#include <iostream>


using namespace std;

class cCliente {
public:
    cCliente();
    cCliente(const cCliente& orig);
    virtual ~cCliente();
      
    struct Cliente{
        string nome;
        string endereco;
        unsigned long int codigo;
        struct Cliente* prox;
    };
    
    Cliente* primeiro = NULL;
    
    Cliente* inserir_cliente(Cliente* primeiro);
    void listar_cliente(Cliente* primeiro);
    Cliente* excluir_cliente(Cliente* primeiro);
    void alterar_cliente(Cliente* primeiro);
    void buscar_cliente(Cliente* primeiro);
    void menuCliente();
    
    //Métodos utilizados na Venda
    bool listar_cliente_venda();
    bool codigo_valido_cliente(int codigo_cliente);
    void mostrar_cliente(int codigo_cliente);
    
private:

};

#endif /* CCLIENTE_H */

