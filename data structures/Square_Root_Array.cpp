#include <bits/stdc++.h>

using namespace std;
typedef long long T;

int sqrtN = 200;

struct bucket {
    vector<T> elem;
};

vector<bucket> s_array(1);

void split(bucket &target, int bucket_idx) {
    bucket temp;
    temp.elem.assign(target.elem.begin() + sqrtN, target.elem.end());
    target.elem.resize(sqrtN);
    s_array.insert(s_array.begin() + bucket_idx + 1, temp);
}

 ///Returns pair(bucket_index, index_inside_bucket)
pair<int, int> at(int idx) {
    for(int i=0; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];

        if(idx < b.elem.size())
            return make_pair(i, idx);

        idx -= b.elem.size();
    }
}

void insert(T elem, int idx, int bucket_id = 0) {
    for(int i=bucket_id; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];

        if(idx <= b.elem.size()) {
            b.elem.insert(b.elem.begin() + idx, elem);
            if(b.elem.size() >= 2 * sqrtN) split(b, i);
            return;
        }

        idx -= b.elem.size();
    }
}

/**
 Under the premise that the array is sorted
 It is done in 2 * log(sqrt(N)), which is log(N)
 Returns pair(bucket_index, index_inside_bucket)
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

void erase(int idx) {
    pair<int, int> position = at(idx);
    bucket &b = s_array[position.first];

    b.elem.erase(b.elem.begin() + position.second);
    if(b.elem.size() == 0) s_array.erase(s_array.begin() + position.first);
}

void ordered_erase(T elem) {
    pair<int, int> position = lower_bound(elem);
    bucket &b = s_array[position.first];

    b.elem.erase(b.elem.begin() + position.second);
    if(b.elem.size() == 0) s_array.erase(s_array.begin() + position.first);
}

void print() {
    for(int i=0; i<(int)s_array.size(); i++) {
        bucket &b = s_array[i];
        if(i) cout << "| ";

        for(int j=0; j<(int)b.elem.size(); j++)
            cout << b.elem[j] << " ";
    }

    puts("");
}
