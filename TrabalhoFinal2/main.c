#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*============= STRUCTS =================*/

struct Data
{
    int dia;
    int mes;
    int ano;
    int hora;
};

struct Paciente
{
    int ID;
    char nome[100];
    char condicaoMedica[100];
};

struct Medico
{
    int crm;
    char nome[100];
    char especializacao[100];
};

struct Consulta
{
    int CodConsulta;
    struct Medico medico;
    struct Paciente paciente;
    struct Data data;
};

/*Lista dupamente encadeada*/
struct No
{
    struct Consulta consulta;
    struct No *proximo;
    struct No *anterior;
};

struct Lista
{
    struct No *inicio;
    struct No *fim;
};

/*============= FUNÇÕES =================*/

void inicializarLista(struct Lista *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
}

/*Paciente*/

void inserirPaciente(struct Lista *lista, struct Paciente paciente)
{
    struct No *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->consulta.paciente.ID == paciente.ID)
        {
            printf("Erro: Paciente com ID %d ja cadastrado.\n", paciente.ID);
            return;
        }

        atual = atual->proximo;
    }

    // Cria um novo nó para o paciente
    struct No *novoNo = (struct No *)malloc(sizeof(struct No));
    if (novoNo == NULL)
    {
        printf("Erro: Falha ao alocar memoria para o novo paciente.\n");
        return;
    }

    // Copia os dados do paciente para o nó
    novoNo->consulta.paciente = paciente;

    // Configura os ponteiros para a lista duplamente encadeada
    novoNo->proximo = NULL;
    novoNo->anterior = lista->fim;

    // Atualiza o ponteiro do último elemento da lista, se a lista não estiver vazia
    if (lista->fim != NULL)
    {
        lista->fim->proximo = novoNo;
    }

    // Atualiza o ponteiro do início da lista, se a lista estiver vazia
    if (lista->inicio == NULL)
    {
        lista->inicio = novoNo;
    }

    // Atualiza o ponteiro do último elemento da lista
    lista->fim = novoNo;

    FILE *arquivo = fopen("pacientes.txt", "a");
    if (arquivo == NULL)
    {
        printf("Erro: Falha ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve os dados do paciente no arquivo
    fprintf(arquivo, "%d %s %s\n", paciente.ID, paciente.nome, paciente.condicaoMedica);

    // Fecha o arquivo
    fclose(arquivo);
}

void removerPaciente(struct Lista *lista, int ID)
{
    struct No *atual = lista->inicio;

    while (atual != NULL)
    {
        // Verifica se o ID do paciente corresponde ao ID fornecido
        if (atual->consulta.paciente.ID == ID)
        {
            struct No *anterior = atual->anterior;
            struct No *proximo = atual->proximo;

            // Atualiza os ponteiros dos nós adjacentes
            if (anterior != NULL)
            {
                anterior->proximo = proximo;
            }
            else
            {
                lista->inicio = proximo;
            }

            if (proximo != NULL)
            {
                proximo->anterior = anterior;
            }
            else
            {
                lista->fim = anterior;
            }

            // Libera a memória do nó atual
            free(atual);

            printf("Paciente com ID %d removido com sucesso.\n", ID);
            return;
        }

        atual = atual->proximo;
    }

    printf("Paciente com ID %d não encontrado na lista.\n", ID);
}

void imprimirPaciente(struct Lista lista)
{
    struct No *atual = lista.inicio;

    if (atual == NULL)
    {
        printf("Nenhum paciente cadastrado.\n");
        return;
    }

    printf("Lista de Pacientes:\n");

    while (atual != NULL)
    {
        struct Paciente paciente = atual->consulta.paciente;
        printf("Nome: %s\n", paciente.nome);
        printf("ID: %d\n", paciente.ID);
        printf("Condicao Medica: %s\n\n", paciente.condicaoMedica);
        atual = atual->proximo;
    }
}

void buscarPaciente(struct Lista lista, int ID)
{
    struct No *atual = lista.inicio;

    while (atual != NULL)
    {
        // Verifica se o ID do paciente corresponde ao ID fornecido
        if (atual->consulta.paciente.ID == ID)
        {
            printf("Paciente Encontrado:\n");
            printf("Nome: %s\n", atual->consulta.paciente.nome);
            printf("ID: %d\n", atual->consulta.paciente.ID);
            printf("Condicao Medica: %s\n", atual->consulta.paciente.condicaoMedica);
            return;
        }

        atual = atual->proximo;
    }

    printf("Paciente com ID %d nao encontrado na lista.\n", ID);
}

void alterarPaciente(struct Lista *lista, int ID)
{
    struct No *atual = lista->inicio;

    while (atual != NULL)
    {
        // Verifica se o ID do paciente corresponde ao ID fornecido
        if (atual->consulta.paciente.ID == ID)
        {
            printf("Dados atuais do paciente:\n");
            printf("Nome: %s\n", atual->consulta.paciente.nome);
            printf("ID: %d\n", atual->consulta.paciente.ID);
            printf("Condicao Medica: %s\n", atual->consulta.paciente.condicaoMedica);

            // Solicita novos dados para o paciente
            printf("\nDigite os novos dados do paciente:\n");
            printf("Novo Nome: ");
            scanf("%s", atual->consulta.paciente.nome);
            printf("Novo ID: ");
            scanf("%d", &atual->consulta.paciente.ID);
            printf("Nova Condicao Medica: ");
            scanf("%s", atual->consulta.paciente.condicaoMedica);

            printf("Paciente alterado com sucesso.\n");
            return;
        }

        atual = atual->proximo;
    }

    printf("Paciente com ID %d nao encontrado na lista.\n", ID);
}

/*Médico*/

void inserirMedico(struct Lista *lista, struct Medico medico)
{
    struct No *atual = lista->inicio;

    while (atual != NULL)
    {
        if (atual->consulta.medico.crm == medico.crm)
        {
            printf("Erro: Médico CRM %d já cadastrado.\n", medico.crm);
            return;
        }

        atual = atual->proximo;
    }

    // Cria um novo nó para o médico
    struct No *novoNo = (struct No *)malloc(sizeof(struct No));
    if (novoNo == NULL)
    {
        printf("Erro: Falha ao alocar memória para o novo medico.\n");
        return;
    }

    // Copia os dados do médico para o nó
    novoNo->consulta.medico = medico;

    // Configura os ponteiros para a lista duplamente encadeada
    novoNo->proximo = NULL;
    novoNo->anterior = lista->fim;

    // Atualiza o ponteiro do último elemento da lista, se a lista não estiver vazia
    if (lista->fim != NULL)
    {
        lista->fim->proximo = novoNo;
    }

    // Atualiza o ponteiro do início da lista, se a lista estiver vazia
    if (lista->inicio == NULL)
    {
        lista->inicio = novoNo;
    }

    // Atualiza o ponteiro do último elemento da lista
    lista->fim = novoNo;

    FILE *arquivo = fopen("medicos.txt", "a");
    if (arquivo == NULL)
    {
        printf("Erro: Falha ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escreve os dados do médico no arquivo
    fprintf(arquivo, "%d %s %s\n", medico.crm, medico.nome, medico.especializacao);

    // Fecha o arquivo
    fclose(arquivo);
}

void removerMedico(struct Lista *lista, int crm)
{
    struct No *atual = lista->inicio;

    while (atual != NULL)
    {
        // Verifica se o CRM do médico corresponde ao CRM fornecido
        if (atual->consulta.medico.crm == crm)
        {
            struct No *anterior = atual->anterior;
            struct No *proximo = atual->proximo;

            // Atualiza os ponteiros dos nós adjacentes
            if (anterior != NULL)
            {
                anterior->proximo = proximo;
            }
            else
            {
                lista->inicio = proximo;
            }

            if (proximo != NULL)
            {
                proximo->anterior = anterior;
            }
            else
            {
                lista->fim = anterior;
            }

            // Libera a memória do nó atual
            free(atual);

            printf("Medico CRM %d removido com sucesso.\n", crm);
            return;
        }

        atual = atual->proximo;
    }

    printf("Medico CRM %d não encontrado na lista.\n", crm);
}

void imprimirMedico(struct Lista lista)
{
    struct No *atual = lista.inicio;

    if (atual == NULL)
    {
        printf("Nenhum medico cadastrado.\n");
        return;
    }

    printf("Lista de Medicos:\n");

    while (atual != NULL)
    {
        struct Medico medico = atual->consulta.medico;
        printf("CRM: %d\n", medico.crm);
        printf("Nome: %s\n", medico.nome);
        printf("Especializacao: %s\n\n", medico.especializacao);
        atual = atual->proximo;
    }
}

void buscarMedico(struct Lista lista, int crm)
{
    struct No *atual = lista.inicio;

    while (atual != NULL)
    {
        // Verifica se o CRM do médico corresponde ao CRM fornecido
        if (atual->consulta.medico.crm == crm)
        {
            printf("Médico Encontrado:\n");
            printf("CRM: %d\n", atual->consulta.medico.crm);
            printf("Nome: %s\n", atual->consulta.medico.nome);
            printf("Especialização: %s\n", atual->consulta.medico.especializacao);
            return;
        }

        atual = atual->proximo;
    }

    printf("Medico CRM %d não encontrado na lista.\n", crm);
}

void alterarMedico(struct Lista *lista, int crm)
{
    struct No *atual = lista->inicio;

    while (atual != NULL)
    {
        // Verifica se o CRM do médico corresponde ao CRM fornecido
        if (atual->consulta.medico.crm == crm)
        {
            printf("Dados atuais do medico:\n");
            printf("CRM: %d\n", atual->consulta.medico.crm);
            printf("Nome: %s\n", atual->consulta.medico.nome);
            printf("Especialização: %s\n", atual->consulta.medico.especializacao);

            // Solicita novos dados para o médico
            printf("\nDigite os novos dados do medico:\n");
            printf("Novo Nome: ");
            scanf("%s", atual->consulta.medico.nome);
            printf("Nova Especialização: ");
            scanf("%s", atual->consulta.medico.especializacao);

            printf("Medico CRM %d alterado com sucesso.\n", crm);
            return;
        }

        atual = atual->proximo;
    }

    printf("Medico CRM %d não encontrado na lista.\n", crm);
}

/*Consulta*/

void inserirConsulta(struct Lista *lista, struct Consulta consulta)
{
    // Cria um novo nó para a consulta
    struct No *novoNo = (struct No *)malloc(sizeof(struct No));

    if (novoNo == NULL)
    {
        printf("Erro: Falha ao alocar memória para a nova consulta.\n");
        return;
    }

    // Copia os dados da consulta para o nó
    novoNo->consulta = consulta;
    novoNo->proximo = NULL;
    novoNo->anterior = NULL;

    if (lista->inicio == NULL)
    {
        // Se a lista está vazia, o novo nó se torna o primeiro e o último
        lista->inicio = novoNo;
        lista->fim = novoNo;
    }
    else
    {
        struct No *atual = lista->inicio;

        // Verifica se já existe uma consulta com o mesmo código
        while (atual != NULL)
        {
            if (atual->consulta.CodConsulta == consulta.CodConsulta)
            {
                printf("Erro: Consulta com codigo %d ja cadastrada.\n", consulta.CodConsulta);
                free(novoNo); // Libera a memória alocada para o novo nó
                return;
            }

            atual = atual->proximo;
        }

        // Adiciona o novo nó no final da lista
        novoNo->anterior = lista->fim;
        lista->fim->proximo = novoNo;
        lista->fim = novoNo;
    }
}

void removerConsulta(struct Lista *lista, int ID)
{
    struct No *atual = lista->inicio;

    while (atual != NULL)
    {
        // Verifica se o ID da consulta corresponde ao ID fornecido
            if (atual->consulta.paciente.ID == ID)
            {
            if (atual->anterior == NULL && atual->proximo)
            {
                lista->inicio = atual->proximo;
                lista->inicio->anterior = NULL;
                free(atual);
                printf("Consulta com ID %d removida com sucesso.\n", ID);
                return;
            }
            else if (atual->anterior && atual->proximo == NULL)
            {
                lista->fim = atual->anterior;
                lista->fim->proximo = NULL;
                free(atual);
                printf("Consulta com ID %d removida com sucesso.\n", ID);
                return;
            }
            else if (atual->anterior == NULL && atual->proximo == NULL)
            {
                lista->inicio = NULL;
                lista->fim = NULL;
                free(atual);

                printf("Consulta com ID %d removida com sucesso.\n", ID);
                return;
            }
            else if (atual->anterior && atual->proximo)
            {
                atual->anterior->proximo = atual->proximo;
                atual->proximo->anterior = atual->anterior;
                free(atual);
                printf("Consulta com ID %d removida com sucesso.\n", ID);
                return;
            }
        }

        atual = atual->proximo;
    }

    printf("Consulta com ID %d não encontrada na lista.\n", ID);
}

void imprimirConsulta(struct Lista lista)
{
    struct No *atual = lista.inicio;

    if (atual == NULL)
    {
        printf("Nenhuma consulta cadastrada.\n");
        return;
    }

    printf("Lista de Consultas:\n");

    while (atual != NULL)
    {
        printf("CodConsulta: %d\n", atual->consulta.CodConsulta);
        printf("Medico: %s (CRM: %d)\n", atual->consulta.medico.nome, atual->consulta.medico.crm);
        printf("Paciente: %s (ID: %d)\n", atual->consulta.paciente.nome, atual->consulta.paciente.ID);
        printf("Data/Hora: %d/%d/%d %d:00\n\n", atual->consulta.data.dia, atual->consulta.data.mes,
               atual->consulta.data.ano, atual->consulta.data.hora);
        atual = atual->proximo;
    }
}

void buscarConsulta(struct Lista lista, int ID)
{
    struct No *atual = lista.inicio;

    while (atual != NULL)
    {
        // Verifica se o ID da consulta corresponde ao ID fornecido
        if (atual->consulta.CodConsulta == ID)
        {
            printf("Consulta Encontrada:\n");
            printf("Medico: %s\n", atual->consulta.medico.nome);
            printf("Paciente: %s\n", atual->consulta.paciente.nome);
            printf("Data/Hora: %d/%d/%d %d:00\n", atual->consulta.data.dia,
                   atual->consulta.data.mes, atual->consulta.data.ano,
                   atual->consulta.data.hora);
            return;
        }

        atual = atual->proximo;
    }

    printf("Consulta com ID %d não encontrada na lista.\n", ID);
}

void alterarConsulta(struct Lista *lista, int CodConsulta)
{
    struct No *atual = lista->inicio;

    while (atual != NULL)
    {
        // Verifica se o CodConsulta da consulta corresponde ao fornecido
        if (atual->consulta.CodConsulta == CodConsulta)
        {
            printf("Dados atuais da consulta:\n");
            printf("Medico: %s\n", atual->consulta.medico.nome);
            printf("Paciente: %s\n", atual->consulta.paciente.nome);
            printf("Data/Hora: %d/%d/%d %d:00\n", atual->consulta.data.dia,
                   atual->consulta.data.mes, atual->consulta.data.ano,
                   atual->consulta.data.hora);

            // Solicita novos dados para a consulta
            printf("\nDigite os novos dados da consulta:\n");
            printf("Novo Medico: ");
            scanf("%s", atual->consulta.medico.nome);
            printf("Novo Paciente: ");
            scanf("%s", atual->consulta.paciente.nome);
            printf("Nova Data (dia mes ano hora): ");
            scanf("%d %d %d %d", &atual->consulta.data.dia, &atual->consulta.data.mes,
                  &atual->consulta.data.ano, &atual->consulta.data.hora);

            printf("Consulta alterada com sucesso.\n");
            return;
        }

        atual = atual->proximo;
    }

    printf("Consulta com CodConsulta %d nao encontrada na lista.\n", CodConsulta);
}

/*Relatórios Especiais*/
void relatorios_especiais(struct Lista listaMedicos,
                          const char especializacao_desejada[100])
{
    struct No *atual = listaMedicos.inicio;
    int encontrado = 0;

    printf("Lista de Medicos com a especializacao %s:\n",
           especializacao_desejada);

    while (atual != NULL)
    {
        if (strcmp(atual->consulta.medico.especializacao,
                   especializacao_desejada) == 0)
        {
            printf("Médico: %s\n", atual->consulta.medico.nome);
            encontrado = 1;
        }
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Nenhum medico encontrado com a especializacao %s.\n",
               especializacao_desejada);
    }
}

void consulta_data_especifica(struct Lista lista, int dia, int mes, int ano)
{
    struct No *atual = lista.inicio;
    int encontrado = 0;

    printf("Consultas agendadas para a data %d/%d/%d:\n", dia, mes, ano);

    while (atual != NULL)
    {
        if (atual->consulta.data.dia == dia && atual->consulta.data.mes == mes &&
            atual->consulta.data.ano == ano)
        {
            printf("Médico: %s\n", atual->consulta.medico.nome);
            printf("Paciente: %s\n", atual->consulta.paciente.nome);
            printf("Data/Hora: %d/%d/%d %d:%d\n", atual->consulta.data.dia,
                   atual->consulta.data.mes, atual->consulta.data.ano,
                   atual->consulta.data.hora);
            encontrado = 1;
        }
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Nenhuma consulta encontrada para a data %d/%d/%d.\n", dia, mes, ano);
    }
}

int main()
{
    struct Consulta consulta;
    struct Lista listaPacientes;
    struct Lista listaMedicos;
    struct Lista listaConsultas;

    inicializarLista(&listaPacientes);
    inicializarLista(&listaMedicos);
    inicializarLista(&listaConsultas);

    int opc;

    do
    {

        printf("===== MENU =====\n");
        printf(" 1 - Inserir Paciente\n 2 - Remover Paciente\n 3 - Imprimir "
               "Paciente\n 4 - Buscar Paciente\n 5 - Alterar Paciente ");
        printf("\n 6 - Inserir Medico\n 7 - Remover Medico\n 8 - Imprimir Medico\n "
               "9 - Buscar Medico\n10 - Alterar Medico");
        printf("\n11 - Inserir Consulta\n12 - Remover Consulta\n13 - Imprimir "
               "Consulta\n14 - Buscar Consulta\n15 - Alterar Consulta");
        printf("\n16 - Listar medicos que tem uma especializacao especifica\n17 - "
               "Consulta agendada em uma data especifica\n");
        printf("\n 0 - Sair\n");
        printf("================\n");
        printf("\nDigite a opcao desejada: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            printf("Digite o ID do paciente: ");
            scanf("%d", &consulta.paciente.ID);
            printf("Digite o nome do paciente: ");
            setbuf(stdin, NULL);
            gets(consulta.paciente.nome);
            printf("Digite a condicao medica do paciente: ");
            setbuf(stdin, NULL);
            gets(consulta.paciente.condicaoMedica);
            inserirPaciente(&listaPacientes, consulta.paciente);
            break;
        case 2:
            printf("Digite o ID do paciente: ");
            scanf("%d", &consulta.paciente.ID);
            removerPaciente(&listaPacientes, consulta.paciente.ID);
            break;
        case 3:
            imprimirPaciente(listaPacientes);
            break;
        case 4:
            printf("Digite o ID do paciente: ");
            scanf("%d", &consulta.paciente.ID);
            buscarPaciente(listaPacientes, consulta.paciente.ID);
            break;
        case 5:
            printf("Digite o ID do paciente: ");
            scanf("%d", &consulta.paciente.ID);
            alterarPaciente(&listaPacientes, consulta.paciente.ID);
            break;
        case 6:
            printf("Informe o CRM do medico: ");
            scanf("%d", &consulta.medico.crm);
            printf("Digite o nome do medico: ");
            setbuf(stdin, NULL);
            gets(consulta.medico.nome);
            printf("Digite a especializacao do medico: ");
            setbuf(stdin, NULL);
            gets(consulta.medico.especializacao);
            inserirMedico(&listaMedicos, consulta.medico);
            break;
        case 7:
            printf("Informe o CRM do medico: ");
            scanf("%d", &consulta.medico.crm);
            removerMedico(&listaMedicos, consulta.medico.crm);
            break;
        case 8:
            imprimirMedico(listaMedicos);
            break;
        case 9:
            printf("Digite o CRM do medico");
            scanf("%d", &consulta.medico.crm);
            buscarMedico(listaMedicos, consulta.medico.crm);
            break;
        case 10:
            printf("Digite o CRM do medico");
            scanf("%d", &consulta.medico.crm);
            alterarMedico(&listaMedicos, consulta.medico.crm);
            break;
        case 11:
            printf("Digite o codigo da consulta: ");
            scanf("%d", &consulta.CodConsulta);
            printf("Digite o CPF do paciente: ");
            scanf("%d", &consulta.paciente.ID);
            printf("Digite o CRM do médico: ");
            scanf("%d", &consulta.medico.crm);
            printf("Digite o dia da consulta: ");
            scanf("%d", &consulta.data.dia);
            printf("Digite o mês da consulta: ");
            scanf("%d", &consulta.data.mes);
            printf("Digite o ano da consulta: ");
            scanf("%d", &consulta.data.ano);
            printf("Digite a hora da consulta: ");
            scanf("%d", &consulta.data.hora);
            inserirConsulta(&listaConsultas, consulta);
            break;
        case 12:
            printf("Digite o codigo da consulta: ");
            scanf("%d", &consulta.CodConsulta);
            removerConsulta(&listaConsultas, consulta.CodConsulta);
            break;
        case 13:
            imprimirConsulta(listaConsultas);
            break;
        case 14:
            printf("Digite o codigo da consulta: ");
            scanf("%d", &consulta.CodConsulta);
            buscarConsulta(listaConsultas, consulta.CodConsulta);
            break;
        case 15:
            printf("Digite o codigo da consulta: ");
            scanf("%d", &consulta.CodConsulta);
            alterarConsulta(&listaConsultas, consulta.CodConsulta);
            break;
        case 16:
            printf("===== Listar medicos por especializacao =====\n");
            char especializacao_desejada[100];
            printf("Digite a especializacao desejada: ");
            scanf("%s", especializacao_desejada);
            relatorios_especiais(listaMedicos, especializacao_desejada);
            break;
        case 17:
            printf("Digite uma data dd/mm/aaaa: ");
            scanf("%d/%d/%d", &consulta.data.dia, &consulta.data.mes,
                  &consulta.data.ano);
            consulta_data_especifica(listaConsultas, consulta.data.dia,
                                     consulta.data.mes, consulta.data.ano);
            break;
        case 0:
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (opc != 0);

    return 0;
}