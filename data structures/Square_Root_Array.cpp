#include <bits/stdc++.h>

using namespace std;
typedef long long T;

int sqrtN = 200;

struct bucket {
    vector<T> elem;

    void insert(T e, int idx) {
        elem.insert(elem.begin() + idx, e);
    }
};

vector<bucket> s_array(1);

void split(bucket &target, int bucket_idx) {
    bucket temp;
    temp.elem.assign(target.elem.begin() + sqrtN, target.elem.end());
    target.elem.resize(sqrtN);
    s_array.insert(s_array.begin() + bucket_idx + 1, temp);
}

T at(int idx) {
    for(int i=0; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];

        if(idx < b.elem.size())
            return b.elem[idx];

        idx -= b.elem.size();
    }
}

void insert(T elem, int idx, int bucket_id = 0) {
    for(int i=bucket_id; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];

        if(idx <= b.elem.size()) {
            b.insert(elem, idx);
            if(b.elem.size() >= 2 * sqrtN) split(b, i);
            return;
        }

        idx -= b.elem.size();
    }
}

/**
 Under the premise that the array is sorted
 It is done in 2 * log(sqrt(N)), which is log(N)
 Returns (bucket_index, index_inside_bucket)
**/
pair<int, int> lower_bound(T elem) {
    int l = 0, r = s_array.size() - 1, m;
    while(l < r) {
        m = (l + r) / 2;
        if(s_array[m+1].elem[0] <= elem)
            l = m + 1;
        else
            r = m;
    }

    int bucket_id = l;
    l = 0, r = s_array[bucket_id].elem.size();
    while(l < r) {
        m = (l + r) / 2;
        if(s_array[bucket_id].elem[m] < elem)
            l = m + 1;
        else
            r = m;
    }

    return make_pair(bucket_id, l);
}

void ordered_insert(T elem) {
    pair<int, int> lbound = lower_bound(elem);
    insert(elem, lbound.second, lbound.first);
}

void print() {
    for(int i=0; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];
        if(i) cout

        for(int j=0; j<(int)b.elem.size(); j++)
            cout << b.elem[j] << " ";
    }

    puts("");
}
