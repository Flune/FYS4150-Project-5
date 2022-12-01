#include "utils.hpp"

using namespace std;
using namespace arma;

int index(int i,int j,int rl){
    return i*rl+j;
}

void log_(int n){
    cout << n << endl;
}

void log_(double d){
    cout << d << endl;
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

cx_vec potential_(double T, double x, double dy, double y, int n, int M){
    double c, w;
    int N = M-2;

    // Width of the center with the splits
    c = n*y + (n-1)*dy;
    // Width of each of the wall on either side of the center 
    w = (1.-c)/2.;

    cx_vec temp = cx_vec(N).fill(0);
    double u = 1;
    // log_(u);
    double v = w * (M-1);
    // log_(v);
    temp.subvec((int)(u-0.5), (int)(v-1.5)).fill(1);
    for (int i = 0; i<n-1; i++){
        u = (w + y + 0  + i*(y+dy))*(M-1);
    // log_(u);
        v = (w + y + dy + i*(y+dy))*(M-1);
    // log_(v);
        temp.subvec((int)(u-0.5), (int)(v-1.5)).fill(1);
    }
    u = (1-w) * (M-1);
    // log_(u);
    v = M-1;
    // log_(v);
    temp.subvec((int)(u-0.5), (int)(v-1.5)).fill(1);

    // temp.print();

    // Width of the empy space in the x-direction
    double x_1 = x-T/2, x_2 = x+T/2, x_;
    cx_vec potential = cx_vec(N*N).fill(0);
    // log_(x_1);
    // log_(x_2);
    for (int i=0; i<N; i++){
        x_ = (i+1.)/(M-1);
        // log_(x_);
        if (x_>x_1 and x_<x_2){
            // log_(x_);
            potential.subvec(i*N, (i+1)*N-1) = temp;
        }
    }

    potential.print();

    return potential;
}

cx_vec potential(int M,
                 int n_slits,
                 double thickness,
                 double x_pos,
                 double slit_seperation,
                 double slit_size){
    return potential_(thickness, x_pos, slit_seperation, slit_size, n_slits, M);
}