// Copyright [2024] <Juliana Miranda Bosio>

/*
    *** Importante ***

    O código de fila em vetor está disponível internamente (não precisa de implementação aqui)

*/

void retira_veiculo(structures::ArrayQueue<int> *f, int k) {
    for (int i = 0; i < k-1; i++) {
        int primeiro = f->dequeue();
        f->enqueue(primeiro);
    }
    f->dequeue();
}


void mantenha_veiculo(structures::ArrayQueue<int> *f, int k) {
    int size = f->size();  // convertemos o retorno da função size() do
                           // tipo size_t para tipo int
    int carro;
    for (int i = 0; i < size; i++) {
        if (i == k-1) {
            carro = f->dequeue();
        } else {
            f->dequeue();
        }
    }
    f->enqueue(carro);
}



/*
    *** Importante ***

    A função 'main()' não deve ser escrita aqui, pois é parte do código dos testes e já está implementada

*/
