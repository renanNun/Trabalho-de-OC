#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "binary.hpp"
#include "Leitor.hpp"
//#include "processador.hpp"

std::fstream outputFile;

using namespace std;

void Chamamenu();
void limparTela();
static vector<string> ListadeComandos;
void fazLeitura(string argv);
void lecomandoescrito(vector<string> command);
void escolheModo();

int main()
{

    cout << "\t\t\tTrabalho de Orrganização de computadores" << endl;
    cout << "Alunos: Luan Reis Ciribelli e Renan Nunes da Costa Gonçalves, João Pedro Lima" << endl;
    bool menu = true;
    int escolha;
    vector<string> argv;
    vector<string> command;
    string commando;
    string caminho;
    bool whi = true;
    while (menu)
    {
        Chamamenu();
        cin >> escolha;
        switch (escolha)
        {
        case 1:
            limparTela();
            cout << "Favor digitar o caminho Relativo ao arquivo de entrada : " << endl;
            cin >> caminho;
            argv.push_back(caminho);
            cout << "Agora o arquivo onde as informações serão salvas: " << endl;
            cin >> caminho;
            argv.push_back(caminho);

            outputFile.open(argv.at(1), ios::out); //Abre o Arquivo de Saida

            if (!outputFile)
            {
                cerr << "Erro ao Abrir o Arquivo de Saida! " << endl;
                exit(1);
            }

            fazLeitura(argv.at(0));
            
            int modo;
            escolheModo();
            cin >> modo;

            switch (modo)
            {
            case 1:
                /* code */
                break;
            case 2:
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
            escolheModo();
            switch (modo)
            {
            case 1:
                /* code */
                break;
            case 2:
                break;
            default:
                cout << "Opcao Invalida! Digite Novamente: ";
                cin >> modo;
            }
            
            break;

        case 3:
            limparTela();
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