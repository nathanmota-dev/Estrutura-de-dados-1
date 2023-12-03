#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

typedef struct datanascimento
{
    int dia;
    int mes;
    int ano;

} datanascimento;

typedef struct enderecocliente
{
    char rua[40];
    int numero;
    char cidade[40];
    char estado[40];

} enderecocliente;

typedef struct cliente
{
    char cpf[12];
    char nome[100];
    char telefone[12];
    int idade;
    struct enderecocliente endereco;
    struct datanascimento data;
    struct cliente *anterior;
    struct cliente *proximo;

} cliente;

typedef struct produto
{
    int codigo;
    char descricao[100];
    int quantidade;
    float preco_unitario;
    struct produto *anterior;
    struct produto *proximo;
} produto;

typedef struct venda
{
    int codVenda;
    char cpfCliente[12];
    int codProduto;
    int qtdeComprada;
    struct venda *anterior;
    struct venda *proximo;
} venda;
void insere(cliente **inicio, char cpf[12], char nome[100], char telefone[12], char rua[40], int numero, char cidade[40], char estado[40], int dia, int mes, int ano)
{
    cliente *p, *aa;
    aa = *inicio;
    p = (struct cliente *)malloc(sizeof(cliente));
    if (!p)
    {

        printf("\nSem memoria!\n\n");
        getch();
    }
    else
    {
        strcpy(p->nome, nome);
        strcpy(p->endereco.rua, rua);
        strcpy(p->endereco.cidade, cidade);
        strcpy(p->endereco.estado, estado);
        strcpy(p->cpf, cpf);
        strcpy(p->telefone, telefone);
        p->endereco.numero = numero;
        p->data.dia = dia;
        p->data.mes = mes;
        p->data.ano = ano;

        if (p->data.mes > 10)
        {
            p->idade = 2023 - p->data.ano - 1;
        }
        else
        {
            p->idade = 2023 - p->data.ano;
        }

        if (aa == NULL)
        {
            p->proximo = NULL;
            p->anterior = NULL;
            *inicio = p;
        }
        else
        {
            while (strcmp(cpf, aa->cpf) > 0 && aa->proximo != NULL)//ordena a posi��o do cpf
            {
                aa = aa->proximo;
            }
            if (strcmp(cpf, aa->cpf) == 0)//compara se na ordem, j� n�o tem um cpf de mesmo valor
            {

                printf("\nNao foi possivel cadastrar o cliente. CPF ja cadastrado anteriormente.\n\n");
                getch();
            }
            else if (strcmp(cpf, aa->cpf) < 0)
            {
                if (aa->anterior == NULL)//coloca no inicio
                {
                    p->proximo = aa;
                    p->anterior = NULL;
                    aa->anterior = p;
                    *inicio = p;
                }
                else//coloca no meio
                {
                    p->proximo = aa;
                    p->anterior = aa->anterior;
                    aa->anterior->proximo = p;
                    aa->anterior = p;
                }
            }
            else
            {
                if (aa->proximo == NULL)//coloca no fim
                {
                    p->proximo = NULL;
                    p->anterior = aa;
                    aa->proximo = p;
                }
            }
        }
    }
}

    void consulta(cliente *inicio, char cpf[])
    {
        if (inicio == NULL)
        {

            printf("\nNenhum cliente foi cadastrado!\n\n");
            getch();
            return;
        }
        else
        {
            cliente *p;
            p = inicio;
            while (p && strcmp(cpf, p->cpf) != 0)
            {
                p = p->proximo;
                if (p == NULL)
                {

                    printf("\nNao ha esse cliente\n\n");
                    getch();
                    break;
                }
            }
            if (p != NULL)
            {

                printf("\ncliente pesquisado:\n\ncpf: %s\nnome: %s\ntelefone: %s\nendereco:\nrua: %s\nnumero: %d\ncidade: %s\nestado: %s\ndata de nascimento: %d/%d/%d\n\n", p->cpf, p->nome, p->telefone, p->endereco.rua, p->endereco.numero, p->endereco.cidade, p->endereco.estado, p->data.dia, p->data.mes, p->data.ano);
                getch();
            }
        }
    }

    void alterar(cliente **inicio, char cpf[])
    {
        if (inicio == NULL)
        {

            printf("\nNenhum cliente foi cadastrado!\n\n");
            getch();
            return;
        }
        else
        {
            cliente *p;
            p = *inicio;
            while (p && strcmp(cpf, p->cpf) != 0)
            {
                p = p->proximo;
                if (p == NULL)
                {

                    printf("\nNao ha esse cliente\n\n");
                    getch();
                    break;
                }
            }
            if (p != NULL)
            {
                int a, numero;
                char rua[40], cidade[40], estado[40], nome[100], telefone[12];

                printf("\nDigite o numero de acordo com o dado a ser alterado:\n\n");
                printf("1 - nome\n");
                printf("2 - telefone\n");
                printf("3 - endereco\n");
                scanf("%d", &a);
                switch (a)
                {
                case 1:

                    printf("Digite o novo nome do cliente:\n");
                    setbuf(stdin, NULL);
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = '\0'; // Remove o caractere de nova linha, se presente
                    strcpy(p->nome, nome);
                    break;
                case 2:

                    printf("Digite o novo telefone do cliente:\n");
                    setbuf(stdin, NULL);
                    fgets(telefone, sizeof(telefone), stdin);
                    telefone[strcspn(telefone, "\n")] = '\0'; // Remove o caractere de nova linha, se presente
                    strcpy(p->telefone, telefone);
                    break;
                case 3:

                    printf("Digite o novo endereco do cliente:\n");
                    printf("Rua:\n");
                    setbuf(stdin, NULL);
                    fgets(rua, sizeof(rua), stdin);
                    rua[strcspn(rua, "\n")] = '\0'; // Remove o caractere de nova linha, se presente
                    strcpy(p->endereco.rua, rua);
                    printf("Numero:\n");
                    scanf("%d", &numero);
                    p->endereco.numero = numero;
                    printf("Cidade:\n");
                    setbuf(stdin, NULL);
                    fgets(cidade, sizeof(cidade), stdin);
                    cidade[strcspn(cidade, "\n")] = '\0'; // Remove o caractere de nova linha, se presente
                    strcpy(p->endereco.cidade, cidade);
                    printf("Estado:\n");
                    setbuf(stdin, NULL);
                    fgets(estado, sizeof(estado), stdin);
                    estado[strcspn(estado, "\n")] = '\0'; // Remove o caractere de nova linha, se presente
                    strcpy(p->endereco.estado, estado);
                    break;
                default:

                    printf("Opcao invalida\n");
                    getch();
                }
            }
        }
    }

    void deletar(cliente **listaClientes, venda *listaVendas, const char *cpf)
    {
        // Verificar se o cliente est� cadastrado em alguma venda
        venda *atualVenda = listaVendas;
        while (atualVenda != NULL)
        {
            if (strcmp(atualVenda->cpfCliente, cpf) == 0)
            {
                printf("O cliente nao pode ser excluido porque esta cadastrado em uma venda.\n");
                return;
            }
            atualVenda = atualVenda->proximo;
        }

        // Excluir o cliente
        if (*listaClientes == NULL)
        {
            printf("Nenhum cliente cadastrado.\n");
            return;
        }
        else
        {
            cliente *p;
            p = *listaClientes;
            while (p && strcmp(cpf, p->cpf) != 0)
            {
                p = p->proximo;
                if (p == NULL)
                {
                    printf("Nao ha esse cliente.\n");
                    break;
                }
            }
            if (p != NULL)
            {
                //se to tiver 1 cliente cadastrado
                if (p->anterior == NULL && p->proximo == NULL)
                {
                    *listaClientes = NULL;
                }//primeiro
                else if (p->anterior == NULL)
                {
                    p->proximo->anterior = NULL;
                    *listaClientes = p->proximo;
                }//ultimo
                else if (p->proximo == NULL)
                {
                    p->anterior->proximo = NULL;
                }
                //meio
                else
                {
                    p->proximo->anterior = p->anterior;
                    p->anterior->proximo = p->proximo;
                }
                printf("O cliente foi deletado.\n");
                free(p);
            }
        }
    }

    void insere_produto(produto **inicio, int codigo, char descricao[100], int quantidade, float preco_unitario)
    {
        produto *p, *aa;
        aa = *inicio;
        p = (struct produto *)malloc(sizeof(produto));
        if (!p)
        {

            printf("\nSem memoria!\n\n");
            getch();
        }
        else
        {
            p->codigo = codigo;
            strcpy(p->descricao, descricao);
            p->quantidade = quantidade;
            p->preco_unitario = preco_unitario;

            if (aa == NULL)
            {
                p->proximo = NULL;
                p->anterior = NULL;
                *inicio = p;
            }
            else
            {
                while (codigo > aa->codigo && aa->proximo != NULL)
                {
                    aa = aa->proximo;
                }
                if (codigo == aa->codigo)
                {

                    printf("\nNao foi possivel cadastrar o produto. Codigo ja cadastrado anteriormente.\n\n");
                    getch();
                }
                else if (codigo < aa->codigo)
                {
                    if (aa->anterior == NULL)
                    {
                        p->proximo = aa;
                        p->anterior = NULL;
                        aa->anterior = p;
                        *inicio = p;
                    }
                    else
                    {
                        p->proximo = aa;
                        p->anterior = aa->anterior;
                        aa->anterior->proximo = p;
                        aa->anterior = p;
                    }
                }
                else
                {
                    if (aa->proximo == NULL)
                    {
                        p->proximo = NULL;
                        p->anterior = aa;
                        aa->proximo = p;
                    }
                }
            }
        }
    }

    void consulta_produto(produto *inicio, int codigo)
    {
        if (inicio == NULL)
        {

            printf("\nNenhum produto foi cadastrado!\n\n");
            getch();
            return;
        }
        else
        {
            produto *p;
            p = inicio;
            while (p && codigo != p->codigo)
            {
                p = p->proximo;
                if (p == NULL)
                {

                    printf("\nNao ha esse produto\n\n");
                    getch();
                    break;
                }
            }
            if (p != NULL)
            {

                printf("\nProduto pesquisado:\n\ncodigo: %d\ndescricao: %s\nquantidade: %d\npreco unitario: %.2f\n\n", p->codigo, p->descricao, p->quantidade, p->preco_unitario);
                getch();
            }
        }
    }

    void alterar_produto(produto **inicio, int codigo)
    {
        if (inicio == NULL)
        {

            printf("\nNenhum produto foi cadastrado!\n\n");
            getch();
            return;
        }
        else
        {
            produto *p;
            p = *inicio;
            while (p && codigo != p->codigo)
            {
                p = p->proximo;
                if (p == NULL)
                {

                    printf("\nNao ha esse produto\n\n");
                    getch();
                    break;
                }
            }
            if (p != NULL)
            {
                int a, quantidade;
                float preco_unitario;
                char descricao[100];

                printf("\nDigite o numero de acordo com o dado a ser alterado:\n\n");
                printf("1 - descricao\n");
                printf("2 - quantidade\n");
                printf("3 - preco unitario\n");
                scanf("%d", &a);
                switch (a)
                {
                case 1:

                    printf("Digite a nova descricao do produto:\n");
                    setbuf(stdin, NULL);
                    fgets(descricao, sizeof(descricao), stdin);
                    descricao[strcspn(descricao, "\n")] = '\0'; // Remove o caractere de nova linha, se presente
                    strcpy(p->descricao, descricao);
                    break;
                case 2:

                    printf("Digite a nova quantidade do produto:\n");
                    scanf("%d", &quantidade);
                    p->quantidade = quantidade;
                    break;
                case 3:

                    printf("Digite o novo preco unitario do produto:\n");
                    scanf("%f", &preco_unitario);
                    p->preco_unitario = preco_unitario;
                    break;
                default:

                    printf("Opcao invalida\n");
                    getch();
                }
            }
        }
    }

    void deletar_produto(produto **listaProdutos, venda *listaVendas, int codigo)
    {
        // Verificar se o produto est� cadastrado em alguma venda
        venda *atualVenda = listaVendas;
        while (atualVenda != NULL)
        {
            if (atualVenda->codProduto == codigo)
            {
                printf("O produto nao pode ser excluido porque esta cadastrado em uma venda.\n");
                return;
            }
            atualVenda = atualVenda->proximo;
        }

        // Excluir o produto
        if (*listaProdutos == NULL)
        {
            printf("Nenhum produto cadastrado.\n");
            return;
        }
        else
        {
            produto *p;
            p = *listaProdutos;
            while (p && codigo != p->codigo)
            {
                p = p->proximo;
                if (p == NULL)
                {
                    printf("Nao ha esse produto.\n");
                    break;
                }
            }
            if (p != NULL)
            {

                if (p->anterior == NULL && p->proximo == NULL)
                {
                    *listaProdutos = NULL;
                }
                else if (p->anterior == NULL)
                {
                    p->proximo->anterior = NULL;
                    *listaProdutos = p->proximo;
                }
                else if (p->proximo == NULL)
                {
                    p->anterior->proximo = NULL;
                }

                else
                {
                    p->proximo->anterior = p->anterior;
                    p->anterior->proximo = p->proximo;
                }
                printf("O produto foi deletado.\n");
                free(p);
            }
        }
    }

    void incluirVenda(venda **listaVendas, produto **listaProdutos, int codVenda, const char *cpfCliente, int codProduto, int qtdeComprada)
    {

        // Verificar se o produto j� est� cadastrado
        produto *atualProduto  = *listaProdutos;
        printf("codProduto %d AtualProduto %d",codProduto,atualProduto->codigo);
        while (atualProduto != NULL && atualProduto->codigo != codProduto)
        {

            atualProduto = atualProduto->proximo;

        }

        if (atualProduto == NULL)
        {
            printf("O produto nao esta cadastrado.\n");
            return;
        }

        // Verificar se a quantidade em estoque � suficiente
        if (atualProduto->quantidade < qtdeComprada)
        {
            printf("Quantidade em estoque insuficiente.\n");
            return;
        }

        // Incluir a venda
        venda *novaVenda = (venda *)malloc(sizeof(venda));
        novaVenda->codVenda = codVenda;
        strcpy(novaVenda->cpfCliente, cpfCliente);
        novaVenda->codProduto = codProduto;
        novaVenda->qtdeComprada = qtdeComprada;
        novaVenda->anterior = NULL;
        novaVenda->proximo = NULL;

        if (*listaVendas == NULL)
        {
            *listaVendas = novaVenda;
        }
        else
        {
            venda *atual = *listaVendas;
            while (atual->proximo != NULL)
            {
                atual = atual->proximo;
            }
            atual->proximo = novaVenda;
            novaVenda->anterior = atual;
        }

        // Atualiza a quantidade em estoque do produto
        atualProduto->quantidade -= qtdeComprada;

        printf("Venda incluida com sucesso.\n");
    }

    void alterarVenda(venda **listaVendas, int codVenda, int novoCodProduto, int novaQtdeComprada)
    {
        venda *atual = *listaVendas;
        while (atual != NULL)
        {
            if (atual->codVenda == codVenda)
            {
                atual->codProduto = novoCodProduto;
                atual->qtdeComprada = novaQtdeComprada;
                printf("Venda alterada com sucesso.\n");
                return;
            }
            atual = atual->proximo;
        }

        printf("Venda nao encontrada.\n");
    }

    void consultarVenda(venda **listaVendas, int codVenda)
    {
        venda *atual = *listaVendas;
        while (atual != NULL)
        {
            if (atual->codVenda == codVenda)
            {
                printf("Codigo da Venda: %d\n", atual->codVenda);
                printf("CPF do Cliente: %s\n", atual->cpfCliente);
                printf("Codigo do Produto: %d\n", atual->codProduto);
                printf("Quantidade Comprada: %d\n", atual->qtdeComprada);
                return;
            }
            atual = atual->proximo;
        }
        printf("Venda nao encontrada.\n");
    }

    void excluirVenda(venda **listaVendas, int codVenda)
    {
        venda *atual = *listaVendas;
        while (atual != NULL)
        {
            if (atual->codVenda == codVenda)
            {
                if (atual->anterior != NULL)
                {
                    atual->anterior->proximo = atual->proximo;
                }
                else
                {
                    *listaVendas = atual->proximo;
                }
                if (atual->proximo != NULL)
                {
                    atual->proximo->anterior = atual->anterior;
                }
                free(atual);
                printf("Venda excluida com sucesso.\n");
                return;
            }
            atual = atual->proximo;
        }

        printf("Venda nao encontrada.\n");
    }

    void mostrar(cliente *inicio)
    {
        if (inicio == NULL)
        {

            printf("\nNenhum cliente foi cadastrado!\n\n");
            getch();
            return;
        }
        else
        {
            cliente *p;
            p = inicio;

            printf("\nLista de todos os clientes:\n\n");
            while (p)
            {
                printf("cpf: %s\nnome: %s\n\n", p->cpf, p->nome);
                p = p->proximo;
            }
            printf("\n");
            getch();
        }
    }

    void listarProdutos(produto *listaProdutos)
    {
        if (listaProdutos == NULL)
        {
            printf("Nenhum produto cadastrado.\n");
            return;
        }

        printf("Produtos cadastrados:\n");
        printf("------------------------------\n");
        produto *atual = listaProdutos;
        while (atual != NULL)
        {
            printf("C�digo: %d\n", atual->codigo);
            printf("Descri��o: %s", atual->descricao);
            printf("Quantidade: %d\n", atual->quantidade);
            printf("Pre�o unit�rio: %.2f\n", atual->preco_unitario);
            printf("------------------------------\n");
            atual = atual->proximo;
        }
    }

    void listarVendasEfetivadas(venda *listaVendas)
    {
        if (listaVendas == NULL)
        {
            printf("Nenhuma venda efetivada.\n");
            return;
        }

        printf("Vendas efetivadas:\n");
        printf("-----------------------------\n");
        venda *atual = listaVendas;
        while (atual != NULL)
        {
            printf("C�digo da venda: %d\n", atual->codVenda);
            printf("CPF do cliente: %s\n", atual->cpfCliente);
            printf("C�digo do produto: %d\n", atual->codProduto);
            printf("Quantidade comprada: %d\n", atual->qtdeComprada);
            printf("-----------------------------\n");
            atual = atual->proximo;
        }
    }

    void listarClientesAcimaDeValor(venda *listaVendas, cliente *listaClientes, produto *listaProdutos, float valor)
    {
        if (listaVendas == NULL)
        {
            printf("Nenhuma venda efetivada.\n");
            return;
        }

        if (listaClientes == NULL)
        {
            printf("Nenhum cliente cadastrado.\n");
            return;
        }

        if (listaProdutos == NULL)
        {
            printf("Nenhum produto cadastrado.\n");
            return;
        }

        printf("Clientes que compraram acima de %.2f:\n", valor);
        printf("-----------------------------\n");

        cliente *atualCliente = listaClientes;
        while (atualCliente != NULL)
        {
            float totalCompras = 0;
            venda *atualVenda = listaVendas;
            while (atualVenda != NULL)
            {
                if (strcmp(atualVenda->cpfCliente, atualCliente->cpf) == 0)
                {
                    produto *atualProduto = listaProdutos;
                    while (atualProduto != NULL)
                    {
                        if (atualProduto->codigo == atualVenda->codProduto)
                        {
                            totalCompras += atualVenda->qtdeComprada * atualProduto->preco_unitario;
                            break;
                        }
                        atualProduto = atualProduto->proximo;
                    }
                }
                atualVenda = atualVenda->proximo;
            }
            if (totalCompras > valor)
            {
                printf("CPF: %s\n", atualCliente->cpf);
                printf("Nome: %s", atualCliente->nome);
                printf("Total de compras: %.2f\n", totalCompras);
                printf("-----------------------------\n");
            }
            atualCliente = atualCliente->proximo;
        }
    }

    void listarProdutosAbaixoDeValor(produto *listaProdutos, int valor)
    {
        if (listaProdutos == NULL)
        {
            printf("Nenhum produto cadastrado.\n");
            return;
        }

        printf("Produtos com quantidade em estoque abaixo de %d:\n", valor);
        printf("-----------------------------\n");

        produto *atual = listaProdutos;
        while (atual != NULL)
        {
            if (atual->quantidade < valor)
            {
                printf("C�digo: %d\n", atual->codigo);
                printf("Descri��o: %s", atual->descricao);
                printf("Quantidade: %d\n", atual->quantidade);
                printf("Pre�o unit�rio: %.2f\n", atual->preco_unitario);
                printf("-----------------------------\n");
            }
            atual = atual->proximo;
        }
    }

    int main()
    {

        FILE *file;        
        //char *filePath = "C:\\Users\\noceg\\OneDrive\\Documentos\\Docs\\ssss\\teste1.txt";
        char *filePath = "F:\\ssss\\teste1.txt";
        int arquivoVazio = 0;

        file = fopen(filePath, "r");

        if (file == NULL)
        {
            printf("Arquivo vazio.\n");
            arquivoVazio = 1;
        }

        if (arquivoVazio)
        {
            file = fopen(filePath, "w");
            if (file == NULL)
            {
                printf("Erro ao abrir o arquivo para escrita.\n");
                return 1;
            }

            int a, dia, mes, ano, numero, idade;
            char rua[40], cidade[40], estado[40], nome[100], cpf[12], telefone[12];
            cliente *pessoa;
            pessoa = NULL;
            char cpfCliente[12];
            int codigo, quantidade;
            float preco_unitario;
            char descricao[100];
            produto *prod;
            prod = NULL;

            int codVenda, novoCodProduto, novaQtdeComprada, codProduto, qtdeComprada;

            venda *listaVendas = NULL;
            do
            {

                printf("\nDigite o numero de acordo com a opcao desejada:\n\n");
                printf(" 1 - incluir cliente\n");
                printf(" 2 - alterar cliente\n");
                printf(" 3 - consultar cliente\n");
                printf(" 4 - deletar cliente\n");
                printf(" 5 - incluir produto\n");
                printf(" 6 - alterar produto\n");
                printf(" 7 - consultar produto\n");
                printf(" 8 - deletar produto\n");
                printf(" 9 - incluir venda\n");
                printf("10 - alterar venda\n");
                printf("11 - consultar venda\n");
                printf("12 - deletar venda\n");
                printf("13 - listar todos os clientes cadastrados\n");
                printf("14 - listar todos os produtos cadastrados\n");
                printf("15 - listar todas as vendas efetivadas\n");
                printf("16 - listar clientes que compraram acima de x\n");
                printf("17 - listar produtos com quantidade em estoque abaixo de x\n");

                printf(" 0 - Sair\n\n");
                scanf("%d", &a);

                switch (a)
                {
                case 1:

                    printf("Digite o cpf do cliente:\n");
                    setbuf(stdin, NULL);
                    fgets(cpf, sizeof(cpf), stdin);
                    printf("Digite o nome do cliente:\n");
                    setbuf(stdin, NULL);
                    fgets(nome, sizeof(nome), stdin);
                    printf("Digite o telefone:\n");
                    setbuf(stdin, NULL);
                    fgets(telefone, sizeof(telefone), stdin);
                    printf("Digite o endereco:\n");
                    printf("Rua:\n");
                    setbuf(stdin, NULL);
                    fgets(rua, sizeof(rua), stdin);
                    printf("Numero:\n");
                    scanf("%d", &numero);
                    printf("Cidade:\n");
                    setbuf(stdin, NULL);
                    fgets(cidade, sizeof(cidade), stdin);
                    printf("Estado:\n");
                    setbuf(stdin, NULL);
                    fgets(estado, sizeof(estado), stdin);
                    printf("Digite a data de nascimento:\n");
                    printf("Dia:\n");
                    scanf("%d", &dia);
                    printf("Mes(numero):\n");
                    scanf("%d", &mes);
                    printf("Ano:\n");
                    scanf("%d", &ano);
                    fprintf(file, "%s", cpf);
                    fprintf(file, "%s", nome);
                    fprintf(file, "%s", telefone);
                    fprintf(file, "%s", rua);
                    fprintf(file, "%d\n", numero);
                    fprintf(file, "%s", cidade);
                    fprintf(file, "%s", estado);
                    fprintf(file, "%d/%d/%d\n", dia, mes, ano);

                    insere(&pessoa, cpf, nome, telefone, rua, numero, cidade, estado, dia, mes, ano);
                    break;
                case 2:

                    printf("Digite o cpf do cliente:\n");
                    setbuf(stdin, NULL);
                    fgets(cpf, sizeof(cpf), stdin);
                    alterar(&pessoa, cpf);
                    break;
                case 3:

                    printf("Digite o cpf do cliente:\n");
                    setbuf(stdin, NULL);
                    fgets(cpf, sizeof(cpf), stdin);
                    consulta(pessoa, cpf);
                    break;
                case 4:
                    printf("Digite o cpf do cliente: ");
                    setbuf(stdin, NULL);
                    fgets(cpf, sizeof(cpf), stdin);
                    cpf[strcspn(cpf, "\n")] = '\0'; // Remove o caractere de nova linha, se presente
                    deletar(&pessoa, listaVendas, cpf);
                    break;
                case 5:

                    printf("Digite o codigo do produto:\n");
                    scanf("%d", &codigo);
                    printf("Digite a descricao do produto:\n");
                    setbuf(stdin, NULL);
                    fgets(descricao, sizeof(descricao), stdin);
                    printf("Digite a quantidade:\n");
                    scanf("%d", &quantidade);
                    printf("Digite o preco unitario:\n");
                    scanf("%f", &preco_unitario);
                    fprintf(file, "%d\n", codigo);
                    fprintf(file, "%s", descricao);
                    fprintf(file, "%d\n", quantidade);
                    fprintf(file, "%f\n", preco_unitario);
                    insere_produto(&prod, codigo, descricao, quantidade, preco_unitario);
                    break;
                case 6:

                    printf("Digite o codigo do produto:\n");
                    scanf("%d", &codigo);
                    alterar_produto(&prod, codigo);
                    break;
                case 7:

                    printf("Digite o codigo do produto:\n");
                    scanf("%d", &codigo);
                    consulta_produto(prod, codigo);
                    break;
                case 8:
                    printf("Digite o codigo do produto: ");
                    scanf("%d", &codigo);
                    deletar_produto(&prod, listaVendas, codigo);
                    break;
                case 9:
                    printf("Digite o codigo da venda: ");
                    scanf("%d", &codVenda);
                    printf("Digite o CPF do cliente: ");
                    setbuf(stdin, NULL);
                    fgets(cpfCliente, sizeof(cpfCliente), stdin);
                    cpfCliente[strcspn(cpfCliente, "\n")] = '\0'; // Remover o caractere de nova linha
                    printf("Digite o codigo do produto: ");
                    scanf("%d", &codProduto);
                    printf("Digite a quantidade comprada: ");
                    scanf("%d", &qtdeComprada);
                    fprintf(file, "%d\n", codVenda);
                    fprintf(file, "%s", cpfCliente);
                    fprintf(file, "%d\n", codProduto);
                    fprintf(file, "%d\n", qtdeComprada);
                    incluirVenda(&listaVendas, &prod, codVenda, cpfCliente, codProduto, qtdeComprada);
                    break;

                case 10:
                    printf("Digite o codigo da venda: ");
                    scanf("%d", &codVenda);
                    printf("Digite o novo codigo do produto: ");
                    scanf("%d", &novoCodProduto);
                    printf("Digite a nova quantidade comprada: ");
                    scanf("%d", &novaQtdeComprada);
                    alterarVenda(&listaVendas, codVenda, novoCodProduto, novaQtdeComprada);
                    break;
                case 11:
                    printf("Digite o codigo da venda: ");
                    scanf("%d", &codVenda);
                    consultarVenda(&listaVendas, codVenda);
                    break;
                case 12:
                    printf("Digite o codigo da venda: ");
                    scanf("%d", &codVenda);
                    excluirVenda(&listaVendas, codVenda);
                    break;
                case 13:
                    mostrar(pessoa);
                    break;
                case 14:
                    listarProdutos(prod);
                    break;
                case 15:
                    listarVendasEfetivadas(listaVendas);
                    break;
                case 16:
                    printf("Digite o valor: ");
                    float valor;
                    scanf("%f", &valor);
                    listarClientesAcimaDeValor(listaVendas, pessoa, prod, valor);
                    break;
                case 17:
                    printf("Digite o valor: ");
                    int valor2;
                    scanf("%d", &valor2);
                    listarProdutosAbaixoDeValor(prod, valor2);
                    break;

                case 0:
                    break;
                default:
                    printf("Opcao invalida\n");
                    break;
                }



            }
            while (a != 0);
        }

        file = fopen(filePath, "w");
        if (file == NULL)
        {
            printf("Erro ao abrir o arquivo para escrita.\n");
            return 1;
        }

        fclose(file);
        return 0;
    }







