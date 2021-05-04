#pragma once

template <typename G>
ref class Nodo {
public:
    G valor;
    Nodo<G>^ sig;
    Nodo<G>^ ant;
    //Nodo(G v, Nodo* s = nullptr) { valor = v; sig = s; }
    Nodo(G v, Nodo^ s, Nodo^ a) : valor(v), sig(s), ant(a) { }
    Nodo(G v) : valor(v), sig(nullptr), ant(nullptr) { }
};

template <class G>
ref class List {
    Nodo<G>^ inicio;
    Nodo<G>^ fin;
public:
    unsigned Count;

    List() {
        inicio = nullptr; // como lista vacia
        fin = nullptr;
        Count = 0;
    }

    G% operator[](int pos) {
        Nodo<G>^ aux = inicio;
        for (int i = 0; i < pos; ++i)
            aux = aux->sig;

        return aux->valor;
    }

    bool Contains(G valor) {
        Nodo<G>^ aux = inicio;
        for (int i = 0; i < Count; ++i) {
            if (Equals(valor, aux->valor)) return true;
            aux = inicio->sig;
        }
        return false;
    }

    void Add(G valor) {
        Nodo<G>^ nuevo = gcnew Nodo<G>(valor);
        if (Count == 0)
            inicio = nuevo;
        else {
            nuevo->ant = fin;
            fin->sig = nuevo;
        }

        fin = nuevo;
        ++Count;
    }

    void Remove(G valor) {
        Nodo<G>^ aux = inicio;
        if (Count == 0) return;
        else if (Count == 1) {
            delete aux;
            fin = nullptr;
            inicio = nullptr;
            Count = 0;
        }
        else {
            for (int i = 0; i < Count; ++i) {
                if (Equals(valor, aux->valor)) {

                    if (i > 0) {
                        if (i == 1) inicio = aux->ant;
                        aux->ant->sig = aux->sig;
                    }
                    else if (i <= Count - 1) {
                        if (i == Count - 2) fin = aux->sig;
                        aux->sig->ant = aux->ant;
                    }

                    delete aux;
                    --Count;
                    break;
                }
                aux = inicio->sig;
            }
            return;
        }
    }

    void RemoveAt(int pos) {

        if (pos < 0)
            return;
        else if (pos >= Count)
            return;
        else {
            Nodo<G>^ aux = inicio;
            for (long i = 0; i < pos + 1; ++i) {
                aux = aux->sig;
            }
            if (aux->ant != nullptr) aux->ant->sig = aux->sig;
            if (aux->sig != nullptr)aux->sig->ant = aux->ant;
            delete aux;
            --Count;
        }
    }

    void Clear() {
        if (Count > 0) {
            Nodo<G>^ aux = fin;
            for (int i = Count; i > 0; --i) {
                if (Count > 1 && aux->ant->sig != nullptr) aux->ant->sig = nullptr;
                fin = aux->ant;
                delete aux;
                aux = fin;
                Count--;
            }
        }
        return;
    }

    void Reverse() {
        if (Count > 1) {
            MyList^ auxList = gcnew MyList();
            Nodo<G>^ aux = fin;
            for (int i = 0; i < Count; ++i) {
                auxList->Add(aux->valor);
                aux = aux->ant;
            }

            Clear();
            for (int i = 0; i < auxList->Count; ++i) {
                Add(auxList[i]);
            }
        }
        return;
    }
};

