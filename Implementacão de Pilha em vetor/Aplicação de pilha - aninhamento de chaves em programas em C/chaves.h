// Copyright [2022] <Juliana Miranda Bosio>
#include "./array_stack.h"

bool verificaChaves(std::string trecho_programa) {
    bool resposta = true;
    int  tamanho  = trecho_programa.length();
    structures::ArrayStack<char> pilha(500);
    
    for (int i = 0; i < tamanho; i++) {
        if (trecho_programa[i] == '{') {
            pilha.push('{');
        }
        if (trecho_programa[i] == '}') {
            if (pilha.empty()) {
                resposta = false;
                break;
            }
            pilha.pop();
        }

    }
    if (!pilha.empty()) {
        resposta = false;
    }
    return resposta;
}
