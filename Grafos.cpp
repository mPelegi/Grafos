#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

enum Alfabeto {
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    F = 5,
    G = 6,
    H = 7,
    I = 8,
    J = 9,
    K = 10,
    L = 11,
    M = 12,
    N = 13,
    O = 14,
    P = 15,
    Q = 16,
    R = 17,
    S = 18,
    T = 19,
    U = 20,
    V = 21,
    W = 22,
    X = 23,
    Y = 24,
    Z = 25
};

int obter_index_alfabeto(string str) {
    char letra = str[0];

    switch (letra) {
        case 'a':
            return 0;
        case 'b':
            return 1;
        case 'c':
            return 2;
        case 'd':
            return 3;
        case 'e':
            return 4;
        case 'f':
            return 5;
        case 'g':
            return 6;
        case 'h':
            return 7;
        case 'i':
            return 8;
        case 'j':
            return 9;
        case 'k':
            return 10;
        case 'l':
            return 11;
        case 'm':
            return 12;
        case 'n':
            return 13;
        case 'o':
            return 14;
        case 'p':
            return 15;
        case 'q':
            return 16;
        case 'r':
            return 17; 
        case 's':
            return 18; 
        case 't':
            return 19; 
        case 'u':
            return 20;
        case 'v':
            return 21;
        case 'w':
            return 22;
        case 'x':
            return 23;
        case 'y':
            return 24;
        case 'z':
            return 25;
    }
}

char obter_letra_index(int i) {
    switch (i) {
    case 0:
        return 'a';
    case 1:
        return 'b';
    case 2:
        return 'c';
    case 3:
        return 'd';
    case 4:
        return 'e';
    case 5:
        return 'f';
    case 6:
        return 'g';
    case 7:
        return 'h';
    case 8:
        return 'i';
    case 9:
        return 'j';
    case 10:
        return 'k';
    case 11:
        return 'l';
    case 12:
        return 'm';
    case 13:
        return 'n';
    case 14:
        return 'o';
    case 15:
        return 'p';
    case 16:
        return 'q';
    case 17:
        return 'r';
    case 18:
        return 's';
    case 19:
        return 't';
    case 20:
        return 'u';
    case 21:
        return 'v';
    case 22:
        return 'w';
    case 23:
        return 'x';
    case 24:
        return 'y';
    case 25:
        return 'z';
    }
}

struct Aresta {
    char x;
    char y;
};

vector<pair<int, int>> lista_adjacencia_g1[26];
vector<pair<int, int>> lista_adjacencia_g2[26];
vector<pair<int, int>> lista_adjacencia_g3[26];

void printar_listas_adjacencia1() {
    for (int i = 0; i < 26; i++) {
        if (lista_adjacencia_g1[i].size() == 0) {
            continue;
        }

        cout << obter_letra_index(i);
        for (auto par : lista_adjacencia_g1[i]) {
            if (par.second == 0) {
                cout << " -> " << obter_letra_index(par.first);
            }
            else {
                cout << " -> [" << obter_letra_index(par.first) << "," << par.second << "]";
            }
        }
        cout << endl;
    }

    return;
}

void printar_listas_adjacencia2() {
    for (int i = 0; i < 26; i++) {
        if (lista_adjacencia_g2[i].size() == 0) {
            continue;
        }

        cout << obter_letra_index(i);
        for (auto par : lista_adjacencia_g2[i]) {
            if (par.second == 0) {
                cout << " -> " << obter_letra_index(par.first);
            }
            else {
                cout << " -> [" << obter_letra_index(par.first) << "," << par.second << "]";
            }
        }
        cout << endl;
    }

    return;
}

void printar_listas_adjacencia3() {
    for (int i = 0; i < 26; i++) {
        if (lista_adjacencia_g3[i].size() == 0) {
            continue;
        }

        cout << obter_letra_index(i);
        for (auto par : lista_adjacencia_g3[i]) {
            if (par.second == 0) {
                cout << " -> " << obter_letra_index(par.first);
            }
            else {
                cout << " -> [" << obter_letra_index(par.first) << "," << par.second << "]";
            }
        }
        cout << endl;
    }

    return;
}

void add_vertice(vector<pair<int, int>> listaAdjacencia[], bool isOrientado, int x, int y, int peso = 0) {
    listaAdjacencia[x].push_back(make_pair(y, peso));

    if (!isOrientado) {
        listaAdjacencia[y].push_back(make_pair(x, peso));
    }
}

string ler_arquivo1(string texto, char separador = '\n') {
    string str;
    stringstream ss(texto);

    string x = "", y = "", peso = "";

    //a;b;

    while (getline(ss, str, separador)) {
        if (separador != ';') {
            ler_arquivo1(str, ';');
            continue;
        }

        if (x == "") {
            x = str;
        }
        else if (x != "" && y == "") {
            y = str;
        }
        else if (x != "" && y != "" && peso == "")
        {
            peso = str;
        }
    }

    if (x != "" && y != "" && peso == "") {
        add_vertice(lista_adjacencia_g1, false, obter_index_alfabeto(x), obter_index_alfabeto(y));
    }
    else if (x != "" && y != "" && peso != "") {
        add_vertice(lista_adjacencia_g1, false, obter_index_alfabeto(x), obter_index_alfabeto(y), stoi(peso));
    }

    return "";
}

string ler_arquivo2(string texto, char separador = '\n') {
    string str;
    stringstream ss(texto);

    string x = "", y = "", peso = "";

    //a;b;

    while (getline(ss, str, separador)) {
        if (separador != ';') {
            ler_arquivo2(str, ';');
            continue;
        }

        if (x == "") {
            x = str;
        }
        else if (x != "" && y == "") {
            y = str;
        }
        else if (x != "" && y != "" && peso == "")
        {
            peso = str;
        }
    }

    if (x != "" && y != "" && peso == "") {
        add_vertice(lista_adjacencia_g2, true, obter_index_alfabeto(x), obter_index_alfabeto(y));
    }
    else if (x != "" && y != "" && peso != "") {
        add_vertice(lista_adjacencia_g2, true, obter_index_alfabeto(x), obter_index_alfabeto(y), stoi(peso));
    }

    return "";
}


string ler_arquivo3(string texto, char separador = '\n') {
    string str;
    stringstream ss(texto);

    string x = "", y = "", peso = "";

    //a;b;

    while (getline(ss, str, separador)) {
        if (separador != ';') {
            ler_arquivo3(str, ';');
            continue;
        }

        if (x == "") {
            x = str;
        }
        else if (x != "" && y == "") {
            y = str;
        }
        else if (x != "" && y != "" && peso == "")
        {
            peso = str;
        }
    }

    if (x != "" && y != "" && peso == "") {
        add_vertice(lista_adjacencia_g3, false, obter_index_alfabeto(x), obter_index_alfabeto(y));
    }
    else if (x != "" && y != "" && peso != "") {
        add_vertice(lista_adjacencia_g3, false, obter_index_alfabeto(x), obter_index_alfabeto(y), stoi(peso));
    }

    return "";
}


void carregar_arquivos() {
    string PATH_G1 = "C:\\Users\\Murilo\\Desktop\\g1.txt";
    string PATH_G2 = "C:\\Users\\Murilo\\Desktop\\g2.txt";
    string PATH_G3 = "C:\\Users\\Murilo\\Desktop\\g3.txt";

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

    ler_arquivo1(arquivoG1);
    ler_arquivo2(arquivoG2);
    ler_arquivo3(arquivoG3);

}

int main()
{
    lista_adjacencia_g1->clear();
    lista_adjacencia_g2->clear(); 
    lista_adjacencia_g3->clear();

    carregar_arquivos();
    printar_listas_adjacencia1();
    cout << endl << endl;
    printar_listas_adjacencia2();
    cout << endl << endl;
    printar_listas_adjacencia3();

    return 0;
}