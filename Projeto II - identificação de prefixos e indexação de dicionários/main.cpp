// Alunos: Juliana Miranda Bosio e Lucas Furlanetto Pascoali

#include <iostream>
#include <fstream>

class NoTrie {
public:
    char word;
    NoTrie *child[26];
    unsigned long position;
    unsigned long length;
    unsigned long counter;

    NoTrie(char c) {
        word = c;
        position = 0;
        length = 0;
        counter = 0;
        for (int i = 0; i < 26; i++) child[i] = nullptr;
    }

    ~NoTrie() {
        for (int i = 0; i < 26; i++) delete child[i];
    }
};

class Trie {
public:
    NoTrie *root;

    Trie() {
        root = new NoTrie('\0'); // Empty Node
    }

    ~Trie() {
        delete root;
    }

    void add(std::string word, unsigned long position, unsigned long length) {
        NoTrie *current = root;
        for (char c : word) {
            int index = c - 'a'; 
            if (current->child[index] == nullptr) {
                current->child[index] = new NoTrie(c);
            } 
            current->child[index]->counter++;
            current = current->child[index];
        }
        current->position = position;
        current->length = length;
    }

    NoTrie *find_prefix(std::string prefix) {
        NoTrie *current = root;
        for (char c: prefix) {
            int index = c - 'a';
            if (current->child[index] == nullptr) return nullptr; // Char not found

            current = current->child[index];
        }

        return current;
    }
};

void populate_trie(const std::string& filename, Trie *trie) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    unsigned long position_counter = 0;
    std::string line;
    while (std::getline(file, line)) {
        std::string word = line.substr(1, line.find_first_of(']') - 1);

        trie->add(word, position_counter, line.size());
        position_counter += line.size() + 1;
    }
}

int main() {
    using namespace std;

    string filename;
    string word;
    Trie trie = Trie();

    cin >> filename;  // entrada

    populate_trie(filename, &trie);
    
    while (1) {  // leitura das palavras ate' encontrar "0"
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        
        NoTrie *result = trie.find_prefix(word);
        if (result == nullptr) {
            cout << word << " is not prefix" << endl;
            continue;
        }

        cout << word << " is prefix of " << result->counter << " words" << endl;

        // Is a word
        if (result->length > 0) {
            cout << word << " is at (" << result->position << "," << result->length << ")" << endl;
        }
    }

    return 0;
}
