#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

typedef struct {
    char    titulo[101];
    char    autor[21];
    char    editora[21];
    int     quant;
    int     codigo;
    float   preco;
    char    dataCadastro[11];
}Livros;
typedef struct {
    int     codigo;
    char    titulo[101];
    float   preco;
    char    dataVenda[9];
    int     quant;
}Venda;
typedef struct{
    int codigo;
    char nome[50];
    char cpf[12];
    char data_nasc[11];
    char telefone[12];
    char endereco[50];

}Cliente;

char dataSistema[11]={"00/00/0000"};
//---------------------------------------------------------------------------

void mostraMenu()
{
    system("cls");
    printf("\n---------------------------------------------------------------------------");
    printf("\n SISTEMA VENDA DE LIVROS                                   Data: %s", dataSistema); //Alterado espaço da data para encaixar
    printf("\n---------------------------------------------------------------------------");
    printf("\n                         MENU DE OPÇÕES DO SISTEMA                         ");
    printf("\n---------------------------------------------------------------------------");
    printf("\n [ 1 ] OPÇÕES CLIENTES");
    printf("\n [ 2 ] OPÇÕES LIVROS");
    printf("\n [ 3 ] VENDA DE LIVROS");
    printf("\n [ 4 ] MOSTRAR ESTOQUE");
    printf("\n [ 5 ] RELATÓRIO ADMINISTRATIVO");
    printf("\n [ESC] FINALIZAR SISTEMA");
    printf("\n---------------------------------------------------------------------------");
    printf("\n INFORME UMA OPÇÃO >>");
    fflush(stdin);
}
//---------------------------------------------------------------------------
void OpcoesCliente(){
        int  codigo =0;
        int tecla = 0;
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                     OPÇÕES DO CLIENTES                    Data: %s", dataSistema); //Alterado espaço da data para encaixar
        printf("\n---------------------------------------------------------------------------\n");
        printf("\n[ 1 ] CADASTRAR NOVO CLIENTE");
        printf("\n[ 2 ] ALTERAR CADASTRO DE CLIENTE");
        printf("\n[ 3 ] CONSULTAR CLIENTE");
        printf("\n[ 4 ] MOSTRAR TODOS OS CLIENTES");
        printf("\n[ESC] VOLTAR AO MENU PRINCIPAL");
        printf("\n---------------------------------------------------------------------------");
        printf("\n INFORME UMA OPÇÃO >>");

        while (tecla != 27)
        {
        if (kbhit())
        {
            tecla = getch();
            printf("%d", tecla);
            switch(tecla){
            case 49 : CadastrarNovoCliente();break;
            case 50 : AlterarCadastro(); break;
            case 51 : ConsultarCliente(); break;
            case 52 : MostrarClientes(); break;
            case 27 : main(); break;
            }

        }
    }
}
//---------------------------------------------------------------------------
void CadastrarNovoCliente (){
    char c;
    int i,tam;
        setlocale(LC_ALL,"Portuguese");
        Cliente cli;
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                     CADASTRAR NOVO CLIENTE");
        printf("\n---------------------------------------------------------------------------");
        cli.codigo=CodigoCadastros("CLIENTES.DAT",1);

        printf("\nCÓDIGO.: %d",cli.codigo);
        fflush(stdin);
        printf("\nNOME.: ");
        scanf("%49[^\n]",cli.nome);
        scanf("");
        printf("\nCPF.: ");
        i=0;
        while(i < 11){
            c=getch();
            if (isdigit(c) != 0){
                cli.cpf[i]=c;
                i++;
                printf("%c",c);
                if(i == 3 || i == 6){
                    printf(".");
                }else if(i == 9){
                    printf("-");
                }
            }else if(c == 8 && i > 0){
                if (i == 3 || i== 6){
                    printf("\b \b");
                }else if (i == 9){
                    printf("\b \b");
                }
                i--;
                printf("\b \b");
            }
        }
        fflush(stdin);
        printf("\nDATA NASCIMENTO.: ");
        i=0;
        while(i < 8){
            c=getch();
            if (isdigit(c) != 0){
                cli.data_nasc[i]=c;
                i++;
                printf("%c",c);
                if(i==2 || i==4){
                    printf("/");
                }
            }else if(c == 8 && i > 0){
                if (i == 2 || i== 4){
                    printf("\b \b");
                }
                i--;
                printf("\b \b");
            }
        }
        fflush(stdin);
        printf("\nTELEFONE.: (");
        i=0;
        while(i < 11){
            c=getch();
            if (isdigit(c) != 0){
                cli.telefone[i]=c;
                i++;
                printf("%c",c);
                if(i==2){
                    printf(") ");
                }else if(i == 3){
                    printf(" ");
                }else if(i==7){
                    printf("-");
                }
            }else if(c == 8 && i > 0){
                if (i == 2){
                    printf("\b \b");
                    printf("\b \b");
                }else if (i == 3){
                    printf("\b \b");
                }else if (i == 7){
                    printf("\b \b");
                }
                i--;
                printf("\b \b");
            }
        }
        fflush(stdin);
        printf("\nENDEREÇO.: ");
        scanf("%49[^\n]",cli.endereco);

        char tecla;
        printf("DESEJA SALVAR OS DADOS DIGITADOS S-SIM N-NÃO >> ");
        scanf(" %c", &tecla);
        tecla = toupper(tecla);
        if (tecla == 'S') {
        FILE *ArqCli;
        ArqCli = fopen("CLIENTES.DAT", "ab");
        if (ArqCli) {
            fwrite(&cli, sizeof(Cliente), 1, ArqCli);
            fflush(ArqCli);
            fclose(ArqCli);
            fflush(stdin);
            printf("CLIENTE CADASTRADO COM SUCESSO!");
            Sleep(1500);
            main();
        } else {
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO CLIENTES.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
        }
    } else if (tecla == 'N') {
        fflush(stdin);
        main();
    }
}
//---------------------------------------------------------------------------
void AlterarCadastro(){

        Cliente cli,clitem;
        unsigned int codigo=0;
        char tecla;

        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                     ALTERAR CADASTRO DE CLIENTE");
        printf("\n---------------------------------------------------------------------------\n");
        printf("DIGITE O CÓDIGO DO CLIENTE PARA SER ALTERADO.: ");
        scanf("%d",&codigo);

        FILE*ArqCli;
        ArqCli=fopen("CLIENTES.DAT", "rb+");
        if (ArqCli){
        rewind(ArqCli);
        fseek(ArqCli,sizeof(Cliente)*(codigo-1),SEEK_SET);
        if (fread(&cli,sizeof(Cliente),1,ArqCli)!= 0){
            clitem=cli;
            printf("\nCÓDIGO.: %d",cli.codigo);
            printf("\nNOME.: %s",cli.nome);
            char p[4],s[4],t[4],f[3],d[2],pd[5],sd[5];
                    sscanf(cli.cpf,"%3s%3s%3s%2s",&p,&s,&t,&f);
                    printf("\nCPF.: %s.%s.%s-%s",p,s,t,f);
                    sscanf(cli.data_nasc,"%2s%2s%4s",&p,&d,&t);
                    printf("\nDATA NASCIMENTO.: %s/%s/%s",p,d,t);
                    sscanf(cli.telefone,"%2s%1s%4s%4s",&d,&f,&pd,&sd);
                    printf("\nTELEFONE.: (%.2s) %s %s-%s",d,f,pd,sd);
                    printf("\nENDEREÇO.: %s",cli.endereco);
            fflush(stdin);
            printf("\nDESEJA ALTERAR ESSE CADASTRO? S-SIM  N-NÃO >> ");
            scanf("%c",&tecla);
            tecla=toupper(tecla);
            fflush(stdin);
        if (tecla == 'S'){
            printf("\nCÓDIGO.: %d",cli.codigo);
            printf("\nNOME.: ");
            fgets(cli.nome,49,stdin);
            fflush(stdin);
            printf("\nCPF.: ");
            scanf("%11s",&cli.cpf);
            printf("\nDATA NASCIMENTO.: ");
            scanf("%8s",&cli.data_nasc);
            fflush(stdin);
            printf("\nTELEFONE.: ");
            fgets(cli.telefone,12,stdin);
            fflush(stdin);
            printf("\nENDEREÇO.: ");
            fgets(cli.endereco,49,stdin);
        //Escrevendo dados para confirmação
                system("cls");
                printf("\nCÓDIGO.: %d",cli.codigo);
                printf("\nNOME.: %s",cli.nome);
                    sscanf(cli.cpf,"%3s%3s%3s%2s",&p,&s,&t,&f);
                    printf("\nCPF.: %s.%s.%s-%s",p,s,t,f);
                    sscanf(cli.data_nasc,"%2s%2s%4s",&p,&d,&t);
                    printf("\nDATA NASCIMENTO.: %s/%s/%s",p,d,t);
                    sscanf(cli.telefone,"%2s%1s%4s%4s",&d,&f,&pd,&sd);
                    printf("\nTELEFONE.: (%.2s) %s %s-%s",d,f,pd,sd);
                    printf("\nENDEREÇO.: %s",cli.endereco);
                printf("\nDESEJA SALVAR ESSES DADOS? S-SIM  N-NÃO >> ");
                scanf("%c",&tecla);
                tecla=toupper(tecla);
                 if (tecla == 'S'){
                        rewind(ArqCli);
                        fseek(ArqCli,sizeof(Cliente)*(codigo-1),SEEK_SET);
                        fwrite(&cli, sizeof(Cliente), 1, ArqCli);
                        fflush(ArqCli);
                        fclose(ArqCli);
                 }else {
                    fflush(stdin);
                    fclose(ArqCli);
                    main();
                 }

        }else if (tecla == 'N'){
            fflush(stdin);
            fclose(ArqCli);
            main();
        }

        }else{
            printf("CÓDIGO DO CLIENTE NÃO ENCONTADO");
            Sleep(1000);
            AlterarCadastro();
            }
        }else{
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO CLIENTES.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
        }
        fflush(stdin);
        fclose(ArqCli);
        printf("CADASTRO ALTERADO COM SUCESSO");
        Sleep(1000);
        return;
}
//---------------------------------------------------------------------------
void ConsultarCliente(){

        setlocale(LC_ALL,"Portuguese");
        Cliente cli;
        char tecla;
        unsigned int codigo;

        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                     CONSULTAR CADASTRO DE CLIENTE");
        printf("\n---------------------------------------------------------------------------\n");
        printf("DIGITE O CÓDIGO DO CLIENTE PARA SER CONSULTADO.: ");

        if (tecla=getch() == 27){
        main();} //Voltar ao menu

        scanf("%d",&codigo);
        fflush(stdin);
        FILE*ArqCli;
        ArqCli=fopen("CLIENTES.DAT", "rb");
        if (ArqCli){
            rewind(ArqCli);
            fseek(ArqCli,sizeof(Cliente)*(codigo-1),SEEK_SET);
            if (fread(&cli,sizeof(Cliente),1,ArqCli) != 0){
                printf("\nCÓDIGO.: %d",cli.codigo);
                printf("\nNOME.: %s",cli.nome);
               char p[4],s[4],t[4],f[3],d[2],pd[5],sd[5];
                    sscanf(cli.cpf,"%3s%3s%3s%2s",&p,&s,&t,&f);
                    printf("\nCPF.: %s.%s.%s-%s",p,s,t,f);
                    sscanf(cli.data_nasc,"%2s%2s%4s",&p,&d,&t);
                    printf("\nDATA NASCIMENTO.: %s/%s/%s",p,d,t);
                    sscanf(cli.telefone,"%2s%1s%4s%4s",&d,&f,&pd,&sd);
                    printf("\nTELEFONE.: (%.2s) %s %s-%s",d,f,pd,sd);

                printf("\nENDEREÇO.: %s",cli.endereco);
                printf("DESEJA ALTERAR CADASTRO DO CLIENTE? S-SIM  N-NÃO >> ");
                scanf("%c",&tecla);

            tecla=toupper(tecla);
            if (tecla == 'S'){
                AlterarCadastro();
            }else {
                main();
            }
            }
                printf("CÓDIGO DO CLIENTE NÃO ENCONTADO");

        }else{
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO CLIENTES.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
        }
}
//---------------------------------------------------------------------------
void MostrarClientes(){

        Cliente cli;
        unsigned int codigo;

        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                     TODOS OS CLIENTES CADASTRADOS");
        printf("\n---------------------------------------------------------------------------\n");

        FILE*ArqCli;
        ArqCli=fopen("CLIENTES.DAT", "rb");
        if (ArqCli){
                while(!feof(ArqCli)){
                if (fread(&cli,sizeof(Cliente),1,ArqCli) != 0){
                    printf("\nCÓDIGO.: %d",cli.codigo);
                    printf("\nNOME.: %s",cli.nome);
                    char p[4],s[4],t[4],f[3],d[2],pd[5],sd[5];
                    sscanf(cli.cpf,"%3s%3s%3s%2s",&p,&s,&t,&f);
                    printf("\nCPF.: %s.%s.%s-%s",p,s,t,f);
                    sscanf(cli.data_nasc,"%2s%2s%4s",&p,&d,&t);
                    printf("\nDATA NASCIMENTO.: %s/%s/%s",p,d,t);
                    sscanf(cli.telefone,"%2s%1s%4s%4s",&d,&f,&pd,&sd);
                    printf("\nTELEFONE.: (%.2s) %s %s-%s",d,f,pd,sd);
                    printf("\nENDEREÇO.: %s",cli.endereco);
                    printf("\n---------------------------------------------------------------------------");
                    }
                }
                printf("\n[ESC] VOLTAR AO MENU PRINCIPAL\n");
                getch();
        }else{
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO CLIENTES.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
        }

}
//---------------------------------------------------------------------------
int CodigoCadastros(char arquivo[22], int ID){

    int qtd = 0;

    FILE *pArq;
    pArq = fopen(arquivo,"rb");

    if(pArq == NULL){
        return qtd+1;
    }

    if (pArq){
        if (ID = 0){
        Livros liv;
        read(&liv, sizeof(Livros), 1, pArq);
        while(!feof(pArq)){
            if (fread(&liv, sizeof(Livros), 1, pArq) != 0)
                qtd ++;
        }
        }else if (ID = 1){
            Cliente cli;
            read(&cli, sizeof(Cliente), 1, pArq);
            while(!feof(pArq)){
            if(fread(&cli, sizeof(Cliente), 1, pArq)!= 0)
                qtd ++;
        }
        }
    }else{
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO %s -----------------",arquivo);
        printf("\n---------------------------------------------------------------------------");
        getch();

        }

    fclose(pArq);

    return qtd+1;
}
//---------------------------------------------------------------------------
void OpcoesLivro(){
        int tecla = 0;
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                     OPÇÕES LIVROS                         Data: %s", dataSistema);//Alterado espaço da data para encaixar
        printf("\n---------------------------------------------------------------------------\n");
        printf("\n[ 1 ] CADASTRAR LIVROS");
        printf("\n[ 2 ] ALTERAR CADASTRO");
        printf("\n[ 3 ] CONSULTAR LIVROS");
        printf("\n[ 4 ] MOSTRAR TODOS OS LIVROS");
        printf("\n[ESC] VOLTAR AO MENU PRINCIPAL");
        printf("\n---------------------------------------------------------------------------");
        printf("\n INFORME UMA OPÇÃO >>");

        while (tecla != 27)
        {
        if (kbhit())
        {
            tecla = getch();
            printf("%d", tecla);
            switch(tecla){
            case 49 : CadastroLivros();break;
            case 50 : AlterarCadastroLivro(); break;
            case 51 : ConsultarLivro(); break;
            case 52 : MostrarEstoque(); break;
            case 27 : main(); break;
            }

        }
    }
}
//---------------------------------------------------------------------------
void CadastroLivros(){
    Livros livro;

        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                  CADASTRO DE LIVROS                          ");
        printf("\n---------------------------------------------------------------------------");
        livro.codigo = CodigoCadastros("LIVROS.DAT",0);
        printf("\nCÓDIGO.: %d",livro.codigo);
        printf("\nTÍTULO.: ");
        scanf("%100[^\n]",livro.titulo);
        fflush(stdin);
        printf("\nAUTOR.: ");
        scanf("%20[^\n]",livro.autor);
        fflush(stdin);
        printf("\nEDITORA.: ");
        scanf("%20[^\n]",livro.editora);
        fflush(stdin);
        printf("\nDigite o valor do livro.: ");
        scanf(" %f",&livro.preco);
        printf("\nQUANTIDADE.: ");
        scanf(" %d",&livro.quant);
        strcpy(livro.dataCadastro,dataSistema);
        printf("\nData de Cadastro: ");
        printf(" [%s]\n", livro.dataCadastro);

        char tecla;
        printf("DESEJA SALVAR OS DADOS DIGITADOS S-SIM N-NÃO >> ");
        scanf(" %c", &tecla);
        tecla = toupper(tecla);
        if (tecla == 'S') {
        FILE *ArqL;
        ArqL = fopen("LIVROS.DAT", "ab");
        if (ArqL) {
            fwrite(&livro, sizeof(Livros), 1, ArqL);
            fflush(ArqL);
            fclose(ArqL);
            fflush(stdin);
            printf("LIVROS CADASTRADOS COM SUCESSO!");
            Sleep(1500);
            main();
        } else {
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
            main();
        }
    } else if (tecla == 'N') {
        fflush(stdin);
        main();
    }
}
//---------------------------------------------------------------------------
void AlterarCadastroLivro(){

        Livros liv,livrotemp;
        char tecla;
        unsigned int codigo;

        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                     ALTERAR CADASTRO DE LIVRO");
        printf("\n---------------------------------------------------------------------------\n");
        printf("DIGITE O CÓDIGO DO LIVRO PARA SER ALTERADO.: ");
        scanf("%d",&codigo);
        fflush(stdin);
        FILE*ArqL;
        ArqL=fopen("LIVROS.DAT", "rb+");
        if (ArqL){
            rewind(ArqL);
            fseek(ArqL,sizeof(Livros)*(codigo-1),SEEK_SET);
            if (fread(&liv,sizeof(Livros),1,ArqL)!= 0){
            printf("\nCÓDIGO.: %d",liv.codigo);
            printf("\nTÍTULO.: %s",liv.titulo);
            printf("\nAUTOR.: %s",liv.autor);
            printf("\nEDITORA.: %s",liv.editora);
            printf("\nVALOR.: %.2f",liv.preco);
            printf("\nQUANTIDADE.: %d",liv.quant);
            printf("\nData de Cadastro: %s",liv.dataCadastro);
            printf("\nDESEJA ALTERAR ESTE LIVRO? S-SIM  N-NÃO >> ");
            scanf("%c",&tecla);
            tecla=toupper(tecla);
            fflush(stdin);
            if (tecla == 'S'){
                livrotemp=liv;
                int teclai;
                printf("\nCÓDIGO.: %d",livrotemp.codigo);
                printf("\nTÍTULO.: ");
                fgets(livrotemp.titulo,99,stdin);
                printf("\nAUTOR.: ");
                fgets(livrotemp.autor,20,stdin);
                printf("\nEDITORA.: ");
                fgets(livrotemp.editora,20,stdin);
                printf("\nDigite o valor do livro.: ");
                scanf("%f",&livrotemp.preco);
                printf("\nCONFIRA OS DADOS E CONFIRME? \n1-OK \n2-NÃO SALVAR DADOS \n3-ALTERAR DADOS NOVAMENTE >> ");
                scanf("%d",&teclai);
                if(teclai == 1){
                    rewind(ArqL);
                    fseek(ArqL,sizeof(Livros)*(codigo-1),SEEK_SET);
                    fwrite(&livrotemp,sizeof(Livros),1,ArqL);
                    printf("LIVRO ALTERADO COM SUCESSO!");
                    fflush(ArqL);
                    fclose(ArqL);
                    Sleep(1500);
                    main();

                    }else if (teclai == 2){
                        fclose(ArqL);
                        main();
                    }else if(teclai == 3){
                        fclose(ArqL);
                        AlterarCadastroLivro();
                    }else{
                        printf("OPÇÃO INVALIDA!");
                        fclose(ArqL);
                        Sleep(1500);
                        main();
                    }

            }else {
                fclose(ArqL);
                main();
            }
            }else{
                fclose(ArqL);
                printf("CÓDIGO DO LIVRO NÃO ENCONTRADO");
                Sleep(1500);
                AlterarCadastroLivro();
            }

        }else{
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
            main();
        }
}
//---------------------------------------------------------------------------
void ConsultarLivro(){

        Livros liv;
        char tecla;
        unsigned int codigo;

        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n                     CONSULTAR LIVROS CADASTRADOS");
        printf("\n---------------------------------------------------------------------------\n");
        printf("DIGITE O CÓDIGO DO LIVRO PARA SER CONSULTADO.: ");

        if (tecla=getch() == 27){
        main();} //Voltar ao menu

        scanf("%d",&codigo);
        fflush(stdin);
        FILE*ArqL;
        ArqL=fopen("LIVROS.DAT", "rb");
        if (ArqL){
            rewind(ArqL);
            fseek(ArqL,sizeof(Livros)*(codigo-1),SEEK_SET);
            if (fread(&liv,sizeof(Livros),1,ArqL)!= 0){
            printf("\nCÓDIGO.: %d",liv.codigo);
            printf("\nTÍTULO.: %s",liv.titulo);
            printf("\nAUTOR.: %s",liv.autor);
            printf("\nEDITORA.: %s",liv.editora);
            printf("\nVALOR.: %.2f",liv.preco);
            printf("\nQUANTIDADE.: %d",liv.quant);
            printf("\nData de Cadastro: %s",liv.dataCadastro);
            printf("\nDESEJA ALTERAR CADASTRO DO LIVRO? S-SIM  N-NÃO >> ");
            scanf("%c",&tecla);

            tecla=toupper(tecla);
                if (tecla == 'S'){
                    fclose(ArqL);
                    AlterarCadastroLivro();
                }else if(tecla == 'N'){
                    fclose(ArqL);
                    ConsultarLivro();
                }else{
                    fclose(ArqL);
                    main();
                }
            }else{
                fclose(ArqL);
                printf("CÓDIGO DO LIVRO NÃO ENCONTRADO");
                Sleep(1500);
                ConsultarLivro();
            }

        }else{
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -----------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
            main();
        }
}
//---------------------------------------------------------------------------
void VendaLivros(){

    Livros livro;
    char cpf[12],tecla;
    int codigo,retorno,quant,cont=2,i,j,RegisLivros[10] [2],livrosvendidos=0;
    float valorTotal=0;

    clientcpf:
    system("cls");
    printf("\n---------------------------------------------------------------------------");
    printf("\n                 VENDA DE LIVROS                           Data: %s", dataSistema);
    printf("\n---------------------------------------------------------------------------");
    printf("\n DIGITE O CPF DO CLIENTE>> ");
    if (tecla=getch() == 27){
        main();
    }
    scanf("%11[^\n]",cpf);
    system("cls");
    printf("\n---------------------------------------------------------------------------");
    printf("\n                 VENDA DE LIVROS                           Data: %s", dataSistema);
    printf("\n---------------------------------------------------------------------------");
    retorno=ConsultarCadastro(cpf);
    if (retorno == 0){
        goto clientcpf;
    }
        FILE*ArqL;
        ArqL=fopen("LIVROS.DAT", "rb+");
        if (ArqL){
            while (tecla != 'F'){

                codigolivro:
                printf("\nDIGITE O CÓDIGO DO LIVRO>> ");
                scanf("%d",&codigo);
                scanf("");
                rewind(ArqL);
                fseek(ArqL,sizeof(Livros)*(codigo-1),SEEK_SET);
                if (fread(&livro,sizeof(Livros),1,ArqL) == 0){
                        printf("LIVRO NÃO CADASTRADO!");
                        Sleep(1000);
                        for (i=0; i <= 2; i++) {
                    printf("\033[2K");  // Apaga a linha atual
                    printf("\033[A");   ////move cursor para linha de cima
                    }
                        goto codigolivro;
                    }
                    Quantvenda:
                printf("\n%s -> VALOR UNITÁRIO: %.2f -> QUANTIDADE DISPONÍVEL: %d",livro.titulo,livro.preco,livro.quant);
                if(livro.quant==0){
                    printf("\n\nLIVRO INDISPONÍVEL");
                    Sleep(1500);
                    for (i=0; i <= 3; i++) {
                    printf("\033[2K");  // Apaga a linha atual
                    printf("\033[A");   ////move cursor para linha de cima
                    }
                    goto codigolivro;

                }
                printf("\nQUANTIDADE DESSE EXEMPLAR>> ");
                scanf("%d",&quant);
                if (quant > livro.quant){
                    printf("\nQUANTIDADE DE LIVROS INDISPONÍVEL PARA VENDA");
                    Sleep(1000);
                    for (i=0; i <= 3; i++) {
                    printf("\033[2K");  // Apaga a linha atual
                    printf("\033[A");   ////move cursor para linha de cima
                    }
                    goto Quantvenda;
                }
                j=0;
                RegisLivros[livrosvendidos][j]=codigo;
                RegisLivros[livrosvendidos][j+1] = quant;

                fflush(stdin);
                valorTotal= valorTotal+(livro.preco*quant);
                for (i=0; i <= cont; i++) {
                    printf("\033[A");   ////move cursor para linha de cima
                    printf("\033[2K");  // Apaga a linha atual
               }
                if (cont <= 2)
                    printf("\nTÍTULO\t \t \t               VALOR UNITÁRIO \t     QUANTIDADE");
                printf("\n%s\t \t\t    %.2f \t          %d",livro.titulo,livro.preco,quant);
                printf("\n---------------------------------------------------------------------------");
                printf("\n                                          \t \tVALOR TOTAL: %.2f",valorTotal);
                printf("\n\n[ S ] PARA ADICIONAR MAIS LIVROS\n[ F ] PARA FINALIZAR COMPRA\n>> ");
                scanf("%c",&tecla);
                tecla = toupper(tecla);
                if (cont ==2)
                    cont= cont +8;
                livrosvendidos ++;
                if (livrosvendidos > 10){
                    printf("QUANTIDADE DE LIVROS VENDIDOS ACIMA DA CAPACIDADE DO PROGRAMA\nEFETUE UMA NOVA VENDA DOS LIVROS FALTANTES");
                    getch();
                    tecla='F';
                }
                }
        }
        fclose(ArqL);
    //Finaliza venda
    Opvenda:
    fflush(stdin);
    printf("\nCONFIRMAR VENDA\n[ 1 ] SIM\n[ 2 ]NÃO\n>> ");
    fflush(stdin);
    scanf("%c",&tecla);
    if (tecla == '1'){
        Venda venda;
        FILE*ArqR;
        ArqR=fopen("RELATORIOSADM.DAT","ab");
        FILE*ArqL;
        ArqL=fopen("LIVROS.DAT", "rb+");
        if (ArqL){
                i=0;
            while( i <= livrosvendidos-1){
                codigo=RegisLivros[i][0];
                rewind(ArqL);
                fseek(ArqL,sizeof(Livros)*(codigo-1),SEEK_SET);
                fread(&livro,sizeof(Livros),1,ArqL);
                quant=RegisLivros[i][1];
                livro.quant=livro.quant-quant;
                rewind(ArqL);
                fseek(ArqL,sizeof(Livros)*(codigo-1),SEEK_SET);
                fwrite(&livro, sizeof(Livros), 1, ArqL);
                i++;
            }
        if(ArqR){
            i=0;
            while( i <= livrosvendidos-1){
                codigo=RegisLivros[i][0];
                rewind(ArqL);
                fseek(ArqL,sizeof(Livros)*(codigo-1),SEEK_SET);
                fread(&livro,sizeof(Livros),1,ArqL);
                venda.codigo=livro.codigo;
                strcpy(venda.titulo,livro.titulo);
                venda.quant=RegisLivros[i][1];
                venda.preco=livro.preco;
                strcpy(venda.dataVenda,dataSistema);
                fwrite(&venda, sizeof(Venda), 1, ArqR);
                i++;
        }
        }else{
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n----------------ERRO NA ABERTURA DO ARQUIVO RELATORIOSADM.DAT -------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
            main();

        }
        fclose(ArqL);
        fclose(ArqR);
        }else{
            system("cls");
            printf("\n---------------------------------------------------------------------------");
            printf("\n----------------ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -------------");
            printf("\n---------------------------------------------------------------------------");
            getch();
            main();
        }

        printf("\nVENDA REALIZADA COM SUCESSO!");
        Sleep(1500);
    }else if(tecla == '2'){
        main();
    }else{
        printf("\nOPÇÃO INVÁLIDA!");
        goto Opvenda;
    }

}
//---------------------------------------------------------------------------
int ConsultarCadastro(char cpf[12]){
    Cliente cli;
    FILE *ArqC;
    ArqC=fopen("CLIENTES.DAT","rb");
    if (ArqC){
        while (fread(&cli,sizeof(Cliente),1,ArqC) ==1){
            if (strcmp(cpf, cli.cpf) == 0){
                char p[4],s[4],t[4],f[3];
                sscanf(cli.cpf,"%3s%3s%3s%2s",&p,&s,&t,&f);
                printf("\nNOME: %s\tCPF: %3s.%3s.%3s-%2s",cli.nome,p,s,t,f);
                fclose(ArqC);
                return 1;
            }
        }
            printf("\nCLIENTE NÃO CADASTRADO!");
            Sleep(1000);
            fclose(ArqC);
            return 0;

    }else{
        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO CLIENTES.DAT -----------------");
        printf("\n---------------------------------------------------------------------------");
        Sleep(1500);
        VendaLivros();
    }
}
//---------------------------------------------------------------------------
void MostrarEstoque(){

    Livros livro;
    int qtd = 0;

    FILE* ArqL;
    ArqL = fopen("LIVROS.DAT", "rb");

    if (ArqL) {
    system("cls");
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
    printf("LISTAGEM DE TODOS OS LIVROS CADASTRADOS\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
    printf("CÓDIGO  TÍTULO                                       AUTOR                EDITORA              QUANTIDADE  PREÇO       DATA\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------\n");
    printf("\n");

    fread(&livro, sizeof(Livros), 1, ArqL);

        while (!feof(ArqL)) {
            printf("%-8d", livro.codigo);
            printf("%-45s", livro.titulo);
            printf("%-21s", livro.autor);
            printf("%-21s", livro.editora);
            printf("%-12d", livro.quant);
            printf("%-12.2f", livro.preco);
            printf("%s\n", livro.dataCadastro);

            qtd += 1;
            fread(&livro, sizeof(Livros), 1, ArqL);
            }
            printf("\n---------------------------------------------------------------------------------------------------------------------------------");
            printf("\nQUANTIDADE DE LIVROS CADASTRADOS: %05d", qtd);
            printf("\n---------------------------------------------------------------------------------------------------------------------------------");
            getch();

    }
    else{

        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n------------------ ERRO NA ABERTURA DO ARQUIVO LIVROS.DAT -----------------");
        printf("\n---------------------------------------------------------------------------");
        getch();
    }

    fclose(ArqL);

}
//---------------------------------------------------------------------------
void RelatorioAdm(){
    Venda venda;
    int qtd;
    float ValorTotal;
        FILE*ArqR;
        ArqR=fopen("RELATORIOSADM.dat","rb");
        if(ArqR){
    system("cls");
    printf("\n-----------------------------------------------------------------------------------------------");
    printf("\n             RELATÓRIO ADMINISTRATIVO                      Data: %s", dataSistema);
    printf("\n-----------------------------------------------------------------------------------------------");
    printf("\n LISTAGEM DE TODAS AS VENDAS REALIZADAS");
    printf("\n-----------------------------------------------------------------------------------------------\n");
    printf("CÓDIGO  TÍTULO                                       PREÇO          QUANTIDADE        DATA\n");
    printf("-----------------------------------------------------------------------------------------------\n");

        while (!feof(ArqR)){
            if(fread(&venda, sizeof(Venda), 1, ArqR) !=0){
                printf("%-8d", venda.codigo);
                printf("%-45s", venda.titulo);
                printf("%-12.2f", venda.preco);
                printf("\t%-12d", venda.quant);
                printf("%s\n", venda.dataVenda);
                ValorTotal=ValorTotal+venda.preco;
                qtd += 1;
            }
            }
            printf("\n-----------------------------------------------------------------------------------------------");
            printf("\nQUANTIDADE DE LIVROS VENDIDOS: %d  \t      \t                     VALOR TOTAL VENDIDO: %.2f", qtd,ValorTotal);
            printf("\n-----------------------------------------------------------------------------------------------");
            getch();

    }
    else{

        system("cls");
        printf("\n---------------------------------------------------------------------------");
        printf("\n-------------- ERRO NA ABERTURA DO ARQUIVO RELATORIOSADM.DAT --------------");
        printf("\n---------------------------------------------------------------------------");
        getch();
    }

    fclose(ArqR);


}
//---------------------------------------------------------------------------
int main(){
    time_t mytime;
    mytime = time(NULL);
    struct tm tm = *localtime(&mytime);
    sprintf(dataSistema,"%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    setlocale(LC_ALL,"Portuguese");
    char tecla = 0;

    mostraMenu();

    while (tecla != 27)
    {
        if (kbhit())
        {
            tecla = getch();
            printf("%c", tecla);

            switch(tecla)
            {
                case 13 : mostraMenu(); break;
                case 49 : OpcoesCliente(); mostraMenu(); break;
                case 50 : OpcoesLivro(); break;  mostraMenu(); break;
                case 51 : VendaLivros();  mostraMenu(); break;
                case 52 : MostrarEstoque();  mostraMenu(); break;
                case 53 : RelatorioAdm(); mostraMenu(); break;
                case 27 : exit(0);
            }
        }
    }

    return 0;
}
