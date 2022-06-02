#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <queue>
#define INFINITO 10000000

using namespace std;

//Variaveis globais para uso durante a execucao do codigo, diminuindo a passagem de parametros entre as funcoes
vector<pair<int, int>> lista_adjacencia_g1[26];
vector<pair<int, int>> lista_adjacencia_g2[26];
vector<pair<int, int>> lista_adjacencia_g3[26];
vector<int> lista_largura_g1;
vector<int> lista_profundidade_g2;
vector<int> proximo_vertice_g1;
vector<int> proximo_vertice_g2;
int cont_vertice_g1 = 0;
int cont_vertice_g2 = 0;

//Funcao para obter o index do alfabeto de acordo com a letra ('a' a 'z')
int obter_index_alfabeto(string str)
{
    char letra = str[0];

    switch (letra)
    {
    case 'a': return 0;
    case 'b': return 1;
    case 'c': return 2;
    case 'd': return 3;
    case 'e': return 4;
    case 'f': return 5;
    case 'g': return 6;
    case 'h': return 7;
    case 'i': return 8;
    case 'j': return 9;
    case 'k': return 10;
    case 'l': return 11;
    case 'm': return 12;
    case 'n': return 13;
    case 'o': return 14;
    case 'p': return 15;
    case 'q': return 16;
    case 'r': return 17;
    case 's': return 18;
    case 't': return 19;
    case 'u': return 20;
    case 'v': return 21;
    case 'w': return 22;
    case 'x': return 23;
    case 'y': return 24;
    case 'z': return 25;
    }
}

//Funcao para obter a letra do alfabeto de acordo com o index (0 a 25)
char obter_letra_index(int i)
{
    switch (i)
    {
    case 0: return 'a';
    case 1: return 'b';
    case 2: return 'c';
    case 3: return 'd';
    case 4: return 'e';
    case 5: return 'f';
    case 6: return 'g';
    case 7: return 'h';
    case 8: return 'i';
    case 9: return 'j';
    case 10: return 'k';
    case 11: return 'l';
    case 12: return 'm';
    case 13: return 'n';
    case 14: return 'o';
    case 15: return 'p';
    case 16: return 'q';
    case 17: return 'r';
    case 18: return 's';
    case 19: return 't';
    case 20: return 'u';
    case 21: return 'v';
    case 22: return 'w';
    case 23: return 'x';
    case 24: return 'y';
    case 25: return 'z';
    }
}

//Funcao generica para imprimir na tela as listas de adjacencia
void printar_listas_adjacencia(vector<pair<int, int>> listaAdjacencia[])
{
    for (int i = 0; i < 26; i++)
    {
        //Como temos uma lista fixa em 26 (quantidade de letras no alfabeto) e nem todos os grafos iniciam em A e seguem a ordem
        //verificamos se existe informacao a ser exibida antes de imprimir
        if (listaAdjacencia[i].size() == 0)
        {
            continue;
        }

        cout << obter_letra_index(i);
        for (auto par : listaAdjacencia[i])
        {
            //No pair<int, int>, o segundo elemento seria o peso, no caso dos grafos 1 e 2 nao foi utilizado (padrao 0), entao nao serao impressos
            if (par.second == 0)
            {
                cout << " -> " << obter_letra_index(par.first);
            }
            else
            {
                cout << " -> [" << obter_letra_index(par.first) << "," << par.second << "]";
            }
        }
        cout << endl;
    }

    return;
}

//Funcao generica para adicionar um vertice na lista de adjacencia fornecida
void adicionar_vertice(vector<pair<int, int>> listaAdjacencia[], bool isOrientado, int x, int y, int peso = 0)
{
    listaAdjacencia[x].push_back(make_pair(y, peso));

    //Se o grafo nao for orientado, inserimos o caminho contrario, se x -> y entao y -> x
    if (!isOrientado)
    {
        listaAdjacencia[y].push_back(make_pair(x, peso));
    }
}

//Funcao recursiva para leitura do arquivo e criacao da lista de adjacencia, recebemos um identificador, conteudo completo do arquivo e
//realizamos a leitura linha a linha, o separador comum '\n' serve para inicialmente ler linha a linha
string ler_arquivo(int idArquivo, string texto, char separador = '\n')
{
    string str;
    stringstream ss(texto);

    //Definindo variaveis que vao receber os dados dos arquivos e
    //serao utilizadas como parametros para inclusao dos vertices
    string x = "", y = "", peso = "";

    //Laco para obter as linhas/conteudo, isso depende do separador
    while (getline(ss, str, separador))
    {
        //Verificacao para identificar se estamos lendo uma linha, ou se ja estamos lendo o conteudo da linha
        if (separador != ';')
        {
            //Se estamos com um separador diferente de ';', significa que ainda estamos lendo uma linha
            //assim realizamos a chamada recursiva, passando o separador como ';', porem dessa vez
            //o texto nao sera mais o texto do arquivo completo e sim a linha lida na chamada anterior
            ler_arquivo(idArquivo, str, ';');
            continue;
        }

        //Verificacao para identificar qual parametro precisamos preencher, dada a estrutura do arquivo,
        //a alocacao foi definida de forma sequencial
        if (x == "")
        {
            x = str;
        }
        else if (x != "" && y == "")
        {
            y = str;
        }
        else if (x != "" && y != "" && peso == "")
        {
            peso = str;
        }
    }

    //Se estamos lendo o conteudo da linha, ja temos as variaveis preenchidas nesse momento, assim podemos criar os vertices
    if (separador == ';')
    {
        //De acordo com o idArquivo, realiza a adicao do vertice a lista de adjacencia correspondente
        switch (idArquivo)
        {
        case 1:
            adicionar_vertice(lista_adjacencia_g1, false, obter_index_alfabeto(x), obter_index_alfabeto(y));
            break;
        case 2:
            adicionar_vertice(lista_adjacencia_g2, true, obter_index_alfabeto(x), obter_index_alfabeto(y));
            break;
        case 3:
            adicionar_vertice(lista_adjacencia_g3, false, obter_index_alfabeto(x), obter_index_alfabeto(y), stoi(peso));
            break;
        }
    }
    
    return "";
}

//Funcao para carregar o conteudo dos arquivos em variaveis que serao utilizadas na leitura
void carregar_arquivos()
{
    //Definindo o path dos arquivos a serem lidos
    string PATH_G1 = "C:\\Projetos\\Arquivos\\g1.txt";
    string PATH_G2 = "C:\\Projetos\\Arquivos\\g2.txt";
    string PATH_G3 = "C:\\Projetos\\Arquivos\\g3.txt";

    //Definindo strings que vao receber o conteudo dos arquivos para leitura
    string arquivoG1 = "";
    string arquivoG2 = "";
    string arquivoG3 = "";

    stringstream buffer;

    buffer.str("");

    buffer << ifstream(PATH_G1).rdbuf();
    arquivoG1 = buffer.str();

    buffer.str("");

    buffer << ifstream(PATH_G2).rdbuf();
    arquivoG2 = buffer.str();

    buffer.str("");

    buffer << ifstream(PATH_G3).rdbuf();
    arquivoG3 = buffer.str();

    ler_arquivo(1, arquivoG1);
    ler_arquivo(2, arquivoG2);
    ler_arquivo(3, arquivoG3);
}

//Funcao recursiva para realizar a busca em largura, definindo qual o vertice inicial
void faz_busca_largura(int ini)
{
    //contador para controle do índice do vértice
    cont_vertice_g1++;

    //verifica se o vértice já foi visitado
    if (find(lista_largura_g1.begin(), lista_largura_g1.end(), ini) == lista_largura_g1.end())
    {
        // se o vértice ainda nao foi visitado, adiciona-o à lista de largura e à lista de próximos vertices a serem lidos
        lista_largura_g1.push_back(ini);
        proximo_vertice_g1.push_back(ini);
    }

    //verifico todas as adjacencias daquela vértice
    for (auto par : lista_adjacencia_g1[ini])
    {
        if (find(lista_largura_g1.begin(), lista_largura_g1.end(), par.first) == lista_largura_g1.end())
        { 
            // se encontro algum vértice adjacente que ainda não foi visitado 
            // adiciona-o à lista de largura e à lista de próximos vertices a serem lidos
            lista_largura_g1.push_back(par.first);
            proximo_vertice_g1.push_back(par.first);
        }
    }

        //se há próximos vertices a serem lidos na sequencia que foram encontrados
    if (proximo_vertice_g1[cont_vertice_g1] != proximo_vertice_g1[proximo_vertice_g1.size()-1])
    { 
        //chamo recursão para visitar próximos vértices
        faz_busca_largura(proximo_vertice_g1[cont_vertice_g1]);
    }
}

//Funcao recursiva para realizar a busca em profundidade, definindo qual o vertice inicial
void faz_busca_profundidade(int ini)
{
    //contador para controle do índice dos próximos vértices a serem visitados
    cont_vertice_g2++;

    //verifica se o vértice atual já foi lido
    if (find(lista_profundidade_g2.begin(), lista_profundidade_g2.end(), ini) == lista_profundidade_g2.end())
    {
        // se o vértice ainda nao foi lido, adiciona-o à lista de vértices lidos
        lista_profundidade_g2.push_back(ini);
    }

    //percorro todos os vértices adjacentes ao vértice atual
    for (auto par : lista_adjacencia_g2[ini])
    {
        //se encontro algum vértice que ainda não foi lido
        if (find(lista_profundidade_g2.begin(), lista_profundidade_g2.end(), par.first) == lista_profundidade_g2.end())
        { 
            //entro na recursão para buscar o próximo vértice adjacente
            faz_busca_profundidade(par.first); //recursao pra ja buscar o proximo vertice antes de seguir
        }
    }
}

//Funcao generica para imprimir na tela as listas simples (largura e profundidade)
void printar_busca_simples(vector<int> lista)
{
    for (int i = 0; i < lista.size(); i++)
        cout << obter_letra_index(lista[i]) << " ";
}

//Funcao recursiva para imprimir na tela a sequencia do menor caminho entre origem e destino
void printa_menor_caminho(int pais[], int destino) {
    //Verificacao para identificar o vertice inicial e iniciar a impressao do caminho
    if (pais[destino] == -1) {
        cout << obter_letra_index(destino);
        return;
    }

    //Recursao para iniciar a impressao apenas quando chegarmos ao vertice inicial
    //pois a nossa estrutura funciona da seguinte forma:
    //Os vertices do caminho referenciam seu vertice pai, ou seja, o destino referencia seu vertice
    //antecessor no caminho, assim por diante, ate chegar no vertice inicial, que nao possui pai, sendo
    //padronizado como -1
    printa_menor_caminho(pais, pais[destino]);

    cout << " -> " << obter_letra_index(destino) ;
}

//Funcao para calcular o custo do menor caminho entre origem e distancia
//O metodo calcula o custo de todos os caminhos partindo da origem, porem imprime apenas
//o destino solicitado
void faz_busca_menor_caminho(int origem, int destino)
{
    //Array para guardar as distancias
    int distancias[26];
    //Array para guardar a referencia do vertice anterior 
    int pais[26];
    //Array para guardar os vertices que ja foram visitados
    int visitados[26];

    //Fila de prioridade de pares para alocar o peso e os vertices, aqui colocamos o peso antes do vertice
    //para possibilitar a ordenacao pelo custo do caminho
    priority_queue < pair<int, int>,
        vector<pair<int, int> >, greater<pair<int, int> > > pq;

    //Inicializar os arrays com um valor fixo predeterminado
    for (int i = 0; i < 26; i++)
    {
        pais[i] = -1;
        distancias[i] = INFINITO;
        visitados[i] = false;
    }

    //A distancia da origem para ela mesma sempre sera 0
    distancias[origem] = 0;

    //Insere a distancia da origem na fila
    pq.push(make_pair(distancias[origem], origem));

    //Laco para resolver a busca do menor caminho, enquanto houver vertices para serem 
    //iterados na fila de prioridades
    while (!pq.empty())
    {
        //Pegar o topo da fila, no caso o menor custo do caminho atual e seu vertice correspondente
        pair<int, int> p = pq.top();
        //Pegar o vertice do par acima
        int u = p.second;
        //Remover o par da fila
        pq.pop();

        //Verifica se o vertice atual ja foi visitado
        if (visitados[u] == false)
        {
            visitados[u] = true;

            // percorre os vértices "v" adjacentes de "u"
            //Laco para percorrer os vertices adjacentes v do vertice do topo u 
            for (auto it : lista_adjacencia_g3[u])
            {
                //Pegar o vertice adjacente e o seu custo
                int v = it.first;
                int custo_aresta = it.second;

                //Verificar se a distancia atual do vertice adjacente sera maior que soma da distancia de u + custo atual
                //Inicialmente, todas as distancias sao "infinitas", assim sempre que um caminho menos custoso for
                //descoberto, sera atualizado
                if (distancias[v] > (distancias[u] + custo_aresta))
                {
                    //Atualiza a distancia de v e insere na fila para seguir com as verificacoes
                    distancias[v] = distancias[u] + custo_aresta;
                    pais[v] = u;
                    pq.push(make_pair(distancias[v], v));
                }
            }
        }
    }

    cout << "O menor caminho entre os vertices " << obter_letra_index(origem) << " e " << obter_letra_index(destino) << " do Grafo 3 sera: ";
    printa_menor_caminho(pais, destino); 
    cout << endl <<  "Custo: " << distancias[destino];
    cout << endl << endl;

    return;
}

//Funcao que inicializa a resolucao dos exercicios da lista
void resolve_lista()
{
    //Limpa todos os elementos dos vetores
    lista_adjacencia_g1->clear();
    lista_adjacencia_g2->clear();
    lista_adjacencia_g3->clear();
    lista_largura_g1.clear();
    proximo_vertice_g1.clear();
    lista_profundidade_g2.clear();
    proximo_vertice_g2.clear();

    carregar_arquivos();

    cout << "Listas de adjacencia:" << endl;
    cout << "G1:" << endl;
    printar_listas_adjacencia(lista_adjacencia_g1);
    cout << endl << endl;

    cout << "G2:" << endl;
    printar_listas_adjacencia(lista_adjacencia_g2);
    cout << endl << endl;

    cout << "G3:" << endl;
    printar_listas_adjacencia(lista_adjacencia_g3);
    cout << endl << endl;

    faz_busca_largura(1); // B
    cout << "Busca em largura no Grafo 1:" << endl;
    printar_busca_simples(lista_largura_g1);
    cout << endl << endl;

    faz_busca_profundidade(0); // A
    cout << "Busca em profundidade no Grafo 2:" << endl;
    printar_busca_simples(lista_profundidade_g2);
    cout << endl << endl;

    faz_busca_menor_caminho(23, 19); // X e T
}

int main()
{
    resolve_lista();
    return 0;
}