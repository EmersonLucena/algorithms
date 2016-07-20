//Coordinate Compression- taught by Felipe Abella

vector<int> comp_coord(int y[], int N) {

    vector<int> ys;
    for(int i=0;i<N;i++) ys.push_back(y[i]);

    sort(ys.begin(),ys.end());
    ys.resize( unique( ys.begin(), ys.end()) - ys.begin());

    for(int i=0;i<N;i++)
        y[i] = lower_bound(ys.begin(), ys.end(), y[i]) - ys.begin();

    return ys;
}
