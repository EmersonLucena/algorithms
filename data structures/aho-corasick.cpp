#include <bits/stdc++.h>

using namespace std;

#define N 100100
#define ALP_SIZ 52

int get(char c) {
    if(c >= 'a' && c <= 'z') return c - 'a';
    return c - 'A' + 26;
}

struct Automaton {
    struct AC_node {
        int fail, wid, endLink, child[ALP_SIZ];
        bool leaf;
    };
    queue<int> q;
    AC_node* no[N];
    int nodes;

    int newnode() {
        no[nodes] = new AC_node();
        no[nodes]->fail = no[nodes]->wid = no[nodes]->endLink = no[nodes]->leaf = 0;
        memset(no[nodes]->child, 0, sizeof(no[nodes]->child));
        return nodes++;
    }

    void clear() {
        nodes = 0;
        newnode();
    }

    void insert(string s, int id) {
        int atual = 0;
        for(int i = 0; i < s.size(); i++) {
            int c = get(s[i]);
            if(!no[atual]->child[c])
                no[atual]->child[c] = newnode();
            atual = no[atual]->child[c];
        }
        no[atual]->leaf = true;
        no[atual]->wid = id;
    }

    void getFails() {
        for(int i = 0; i < ALP_SIZ; i++)
            if(no[0]->child[i]) {
                no[ no[0]->child[i] ]->fail = 0, q.push(no[0]->child[i]);
                if(no[ no[0]->child[i] ]->leaf) no[ no[0]->child[i] ]->endLink = no[0]->child[i];
            }

        while(!q.empty()) {
            int u = q.front(); q.pop();

            for(int i = 0; i < ALP_SIZ; i++) {
                int v = no[u]->child[i];
                if(!v) { no[u]->child[i] = no[no[u]->fail]->child[i]; continue; }

                q.push(v);
                int j = no[u]->fail;
                while(j && !no[j]->child[i]) j = no[j]->fail;
                no[v]->fail = no[j]->child[i];

                if(no[v]->leaf) no[v]->endLink = v;
                else no[v]->endLink = no[no[v]->fail]->endLink;
            }
        }
    }
} AC;

void findOccurs(Automaton &AC, string s) {
    int atual = 0;

    for(int i = 0; i < s.size(); i++) {
        while(!(AC.no[atual])->child[get(s[i])] && atual != 0) atual = AC.no[atual]->fail;
        atual = (AC.no[atual])->child[get(s[i])];

        int aux = atual;
        while(true) {
            aux = (AC.no[aux])->endLink;
            if(aux == 0) break;
            aux = (AC.no[aux])->fail;
        }
    }
}

