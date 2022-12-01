#include "utils.hpp"

using namespace std;
using namespace arma;

int index(int i,int j,int rl){
    return i*rl+j;
}

void log(int n){
    cout << n << endl;
}

umat locations(int N){
    umat locations = umat(2, N*(5*N-4));
    for (int i=0; i<N*N; i++){
        locations.col(i).fill(i);
    }
    int count = N*N;
    for (int i=0; i<N*(N-1); i++){
        locations(0,count)=i;
        locations(1,count)=i+N;
        count++;
        locations(0,count)=i+N;
        locations(1,count)=i;
        count++;
    }
    for (int i=0; i<N*N; i++){
        if(i%N != 0){
            locations(0,count)=i;
            locations(1,count)=i-1;
            count++;
        }
        if(i%N != 0){
            locations(0,count)=i-1;
            locations(1,count)=i;
            count++;
        }
    }
    return locations;
}

sp_cx_mat aMatrix(int M, double r, cx_vec a){
    int N=M-2;
    // We have N*N + 4*N*(N-1) values
    cx_vec values = cx_vec(N*(5*N-4));
    umat Locations = locations(N);
    values.subvec(0,N*N-1) = a;
    values.subvec(N*N,N*(5*N-4)-1).fill(-r);

    sp_cx_mat A = sp_cx_mat(Locations, values);
    return A;
}

sp_cx_mat bMatrix(int M, double r, cx_vec b){
    int N=M-2;
    // We have N*N + 4*N*(N-1) values
    cx_vec values = cx_vec(N*(5*N-4));
    umat Locations = locations(N);
    values.subvec(0,N*N-1) = b;
    values.subvec(N*N,N*(5*N-4)-1).fill(r);

    sp_cx_mat B = sp_cx_mat(Locations, values);
    return B;
}

