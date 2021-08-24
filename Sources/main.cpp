#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "../Headers/Binary.hpp"
#include "../Headers/Leitor.hpp"
#include "../Headers/Processador.hpp"
#include "../Headers/Log.hpp"

std::fstream outputFile;

using namespace std;

void Chamamenu();
void limparTela();
static vector<string> ListadeComandos;
void fazLeitura(string argv);
void lecomandoescrito(vector<string> command);
void escolheModo();
Processador *processador;
int main()
{

    cout << "\t\t\tTrabalho de Organização de computadores" << endl;
    cout << "Alunos: Luan Reis Ciribelli e Renan Nunes da Costa Gonçalves, João Pedro Lima" << endl;
    bool menu = true;
    int escolha;
    vector<string> argv;
    vector<string> command;
    string commando;
    string caminho;
    bool whi = true;
    Processador *processador;
    int modo, modo2, p;

    while (menu)
    {
        Chamamenu();
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            limparTela();
            //cout << "Favor digitar o caminho Relativo ao arquivo de entrada : " << endl;
            //cin >> caminho;
            caminho = "Inputs/instrucoes.txt";
            argv.push_back(caminho);
            //cout << "Agora o arquivo onde as informações serão salvas: " << endl;
            //cin >> caminho;
            caminho = "Inputs/saida.txt";
            argv.push_back(caminho);

            Log::getInstance().getInstance().iniciaArquivoSaida(argv.at(1));
            outputFile.open(argv.at(1), ios::out); //Abre o Arquivo de Saida

            if (!outputFile)
            {
                cerr << "Erro ao Abrir o Arquivo de Saida! " << endl;
                exit(1);
            }

            fazLeitura(argv.at(0));

            for (int i = 0; i < ListadeComandos.size(); i++)
            {
                cout << ListadeComandos.at(i) << endl;
            }

            escolheModo();
            cin >> modo;
            processador = new Processador(ListadeComandos);

            switch (modo)
            {
            case 1:
                cout << "Modo Direto escolhido. Começando execução ..." << endl;
                p = 0;
                //cout << "Tamanho da lista de comandos " <<  ListadeComandos.size() << endl;
                while (p < ListadeComandos.size())
                {
                    cout << endl
                         << ListadeComandos.at(p) << endl;
                    processador->IF();
                    processador->ID();
                    processador->EX();
                    processador->MEM();
                    processador->WB();

                    p++;
                }
                cout << endl;
                break;
            case 2:
                cout << "Modo passo a passo escolhido. Começando execução ..." << endl;
                break;
            default:
                cout << "Opcao Invalida! Digite Novamente: ";
                cin >> modo;
            }

            break;
        case 2:
            limparTela();

            while (whi)
            {

                cout << endl;
                cout << "Escreva o comando em FORMATO MIPS ASSEMBLY" << endl;
                cout << "inicalmente todos os comandos serão aceitos, mas comandos invalidos serão ignorados" << endl;
                cout << "Separe os comandos utilizando ESPAÇO qualquer outra separação irá impedir a execução do programa" << endl;
                cout << "Para colocar o comando na lista de comandos aperte 'enter', para parar de digitar comandos pressione '0'" << endl;
                cout << "comando : " << endl;
                cin >> commando;
                if (commando == "0")
                {
                    whi = false;
                }
                else
                {
                    command.push_back(commando);
                }
            }
            lecomandoescrito(command);
            for (int i = 0; i < ListadeComandos.size(); i++)
            {
                cout << ListadeComandos.at(i) << endl;
            }
            escolheModo();
            cin >> modo2;
            switch (modo)
            {
            case 1:
                cout << "Modo Direto escolhido. Começando execução ..." << endl;
                p = 0;
                //cout << "Tamanho da lista de comandos " <<  ListadeComandos.size() << endl;
                while (p < ListadeComandos.size())
                {
                    cout << endl
                         << ListadeComandos.at(p) << endl;
                    processador->IF();
                    processador->ID();
                    processador->EX();
                    processador->MEM();
                    processador->WB();

                    p++;
                }

                cout << endl;
                break;
            case 2:
                cout << "Modo passo a passo escolhido. Começando execução ..." << endl;
                break;
            default:
                cout << "Opcao Invalida! Digite Novamente: ";
                cin >> modo;
            }

            break;

        case 3:
            limparTela();
            cout << "Limpando memoria" << endl;
            //sleep(5);
            ListadeComandos.clear();
            break;
        case 0:
            return 0;
        default:
            cout << "Opcao Invalida! Digite Novamente: ";
            cin >> escolha;
        }
    }

    return 0;
};

void Chamamenu()
{

    cout << "\t\tFuncionalidades:" << endl;
    cout << "[1] - Ler um arquivo com caminho passado pelo usuario " << endl;
    cout << "[2] - Escrever manualmente o comando " << endl;
    cout << "[3] - Resetar a memoria" << endl;
    cout << "[0] - Parar execução" << endl;
    cout << "Favor usar os numeros para selecionar a opção pretendida" << endl;
    cout << endl;
    cout << "Escolha: " << endl;
};

void limparTela()
{
#ifdef LINUX
    system("clear");
#endif // LINUX
#ifdef _WIN32
    system("cls");
#endif // WIN32
};

void fazLeitura(string argv)
{

    string caminho = argv;
    Leitor *leitor = new Leitor(caminho);
    ListadeComandos = leitor->getVector();
};

void lecomandoescrito(vector<string> command)
{

    for (int i = 0; i < command.size(); i++)
    {
        ListadeComandos.push_back(command.at(i));
    }
};

void escolheModo()
{

    cout << "Escolher modo de execução : " << endl;
    cout << "[1] - Direta " << endl;
    cout << "[2] - Passo a passo" << endl;
    cout << "Escolha : " << endl;
}
