#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "array_stack.h"  // Incluindo o arquivo da estrutura de pilha
#include "array_queue.h"  // Incluindo o arquivo da estrutura de fila

using namespace std;
using namespace structures;  // Permite acessar as classes e funções da pilha

class Cenario {
  public:
    Cenario(string& texto, size_t indice_inicial) {
        size_t pos = indice_inicial;
        nome = proxima_tag_conteudo(texto, pos, "nome");
        altura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "altura") ) );
        largura = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "largura") ) );
        x = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "x") ) );
        y = static_cast<size_t>( stoi( proxima_tag_conteudo(texto, pos, "y") ) );
        matriz = matriz_remove_espacos( proxima_tag_conteudo(texto, pos, "matriz") );
        indice_final = pos;
    }
    ~Cenario() {};
    string nome;
    size_t altura;
    size_t largura;
    size_t x;
    size_t y;
    string matriz;
    size_t indice_final;

  private:
    string proxima_tag(string& texto, size_t& pos) {
        string tag = "";
        for ( ; pos < texto.length(); pos++) {
            if (texto[pos] == '<') {
                pos++;
                while (texto[pos] != '>') {
                    tag += texto[pos];
                    pos++;
                }
                pos++;
                return tag;
            }
        }
        return tag;
    }
    string proximo_conteudo(string& texto, size_t& pos) {
        string txt = "";
        while (texto[pos] != '<') {
            txt += texto[pos];
            pos++;
        }
        while (texto[pos] != '>') {
            pos++;
        }
        pos++;
        return txt;
    }
    string proxima_tag_conteudo(string& texto, size_t& pos, string nome_tag) {
        string tag = "";
        while (tag != nome_tag) {
            tag = proxima_tag(texto, pos);
        }
        return proximo_conteudo(texto, pos);
    }
    string matriz_remove_espacos(string texto) {
        string saida;
        for (int i = 0; i < texto.length(); i++) {
            if (texto[i] == '0' || texto[i] == '1') {
                saida += texto[i];
            }
        }
        return saida;
    }
};

bool verificarAninhamentoXML(string& texto) {
    ArrayStack<string> pilha;
    size_t i = 0;

    while (i < texto.size()) {
        if (texto[i] == '<') {
            // Procura a tag de fechamento a partir da posição i
            size_t j = texto.find('>', i);
            // Verifica se a busca falhou (retornou npos)
            if (j == string::npos) {
                // Erro: Tag não fechada
                return false;
            }

            // Extrai o nome da tag
            string tag = texto.substr(i+1, j-i-1);

             // Verifica se a tag possui um '<' dentro dela
            if (tag.find('<', i) != string::npos) return false;

            if (!tag.empty() && tag[0] == '/') {
                // É uma tag de fechamento 
                if (pilha.empty() || pilha.top() != tag.substr(1)) {
                    // Se a pilha não conter a tag de abertura
                    // Ou se tentamos fechar uma tag que não é a esperada
                    return false; // Erro de aninhamento
                }
                pilha.pop();
            } else {
                // É uma tag de abertura
                pilha.push(tag);
            }
            i = j; // Move para depois de '>'
        }
        i++;
    }
    return pilha.empty();  // Se a pilha estiver vazia, o XML está bem aninhado
}

char** CriaMatriz(string& texto, int linhas, int colunas, bool zeros) {
    char** matriz = new char*[linhas];
    for (size_t i = 0; i < linhas; i++) {
        matriz[i] = new char[colunas];
        for (size_t j = 0; j < colunas; j++) {
            if (!zeros) {
                matriz[i][j] = texto[i*colunas + j];
            } else {
                matriz[i][j] = 0;
            }
        }
    }
    return matriz;
}

void DestroiMatriz(char** &matriz, int altura) {
    for (size_t i = 0; i < altura; i++) {
        delete[] matriz[i];
    }
    delete[] matriz;
    matriz = nullptr;  
}

int CalcularAreaLimpeza(string& matriz_texto, int x0, int y0, int altura, int largura) {
    char** matriz = CriaMatriz(matriz_texto, altura, largura, 0);

    if (matriz[x0][y0] == '0') return 0;

    // Matriz R para controlar os pontos visitados
    char** R = CriaMatriz(matriz_texto, altura, largura, 1);

    // Definir a fila que aceitará valores do tipo pares de inteiros (coordenadas)
    ArrayQueue<std::pair<int, int>> fila(altura*largura);  

    fila.enqueue({x0, y0});
    R[x0][y0] = 1;
    int area = 1;

    // Vetores de deslocamento para as 4 direções possíveis (vizinhança-4)
    int dx[] = {-1, 1, 0, 0}; // Movimentos Verticais 
    int dy[] = {0, 0, -1, 1}; // Movimentos Horizontais

    while (!fila.empty()) {
        pair<int, int> posicao_atual = fila.dequeue();

        int x = posicao_atual.first;
        int y = posicao_atual.second;

        for (int i = 0; i < 4; i++) {
            int novo_x = x + dx[i];
            int novo_y = y + dy[i];

            if (novo_x >= 0 && novo_x < altura &&   // Posições válidas
                novo_y >= 0 && novo_y < largura &&
                R[novo_x][novo_y] == 0 &&           
                matriz[novo_x][novo_y] == '1') {

                fila.enqueue({novo_x, novo_y});
                R[novo_x][novo_y] = 1; // Marca o lugar da nova matriz como visitado
                area++;
            }
        }
    }

    for (size_t i = 0; i < altura; i++) {
        delete[] matriz[i];
        delete[] R[i];
    }
    delete[] matriz;
    delete[] R;

    // DestroiMatriz(matriz, largura);
    // DestroiMatriz(R, largura);

    return area;
}

/**********************
    FUNÇÃO PRINCIPAL
***********************/
int main() {

    string filename;

    std::cin >> filename;  // nome do arquivo de entrada 
                           // (no 'executar': escrever pelo teclado;
                           //  no 'avaliar' : nome é passado pelos testes)

    // Abertura do arquivo
    ifstream filexml(filename);
    if (!filexml.is_open()) {
        cerr << "Erro ao abrir o arquivo " << filename << endl;
        throw runtime_error("Erro no arquivo XML");
    }

    // Leitura do XML completo para 'texto'
    string texto;
    char character;
    while (filexml.get(character)) {
        texto += character;
    }

    // Verificação de aninhamento de tags XML
    if (!verificarAninhamentoXML(texto)) {
        cerr << "erro" << endl;
        return 0;
    }

    size_t ultimo_indice = texto.find_last_of('0');
    size_t tmp = texto.find_last_of('1');
    if (tmp > ultimo_indice) {
        ultimo_indice = tmp;
    }

    size_t indice = 0;
    while (indice < ultimo_indice) {
        Cenario c(texto, indice);
        int area = CalcularAreaLimpeza(c.matriz, c.x, c.y, c.altura, c.largura);
        cout << c.nome << " " << area << endl;
        indice = c.indice_final;
    }

    return 0;
}
