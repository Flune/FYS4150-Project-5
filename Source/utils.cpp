#include "utils.hpp"

using namespace std;
using namespace arma;

int index(int i,int j,int rl){
    return i*rl+j;
}

// void log_(int n){
//     cout << n << endl;
// }

// void log_(double d){
//     cout << d << endl;
// }

// void log_(complex<double> d){
//     cout << d << endl;
// }

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

sp_cx_mat aMatrix(int M, complex<double> r, cx_vec& a){
    int N=M-2;
    // We have N*N + 4*N*(N-1) values
    cx_vec values = cx_vec(N*(5*N-4));
    umat Locations = locations(N);
    values.subvec(0,N*N-1) = a;
    values.subvec(N*N,N*(5*N-4)-1).fill(-r);

    sp_cx_mat A = sp_cx_mat(Locations, values);
    return A;
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

    // potential.print();

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

sp_cx_mat AMatrix(int M, double h, double dt, cx_vec& V){
    complex<double> r = 1j*dt/(2*h*h);
    cx_vec a = 0.5j*dt*V + 1 + 4.*r;
    return aMatrix(M, r, a);
}

sp_cx_mat BMatrix(int M, double h, double dt, cx_vec& V){
    return AMatrix(M, h, -dt, V);
}

void time_step(cx_vec& u, sp_cx_mat& A, sp_cx_mat& B){
    cx_vec b = B*u;
    u = spsolve(A, b);
}

cx_vec u_init(int M, double xc, double xs, double xp,
              double yc, double ys, double yp, cx_vec& V){
    int N = M-2, ind;
    double x, y, h = 1./(M-1), sum;
    complex<double> temp;

    cx_vec u = cx_vec(N*N);

    for(int i = 1; i < M-1; i++){
        x = i*h-xc;
        for(int j = 1; j < M-1; j++){
            ind = index(i-1, j-1, N);
            if (norm(V(ind))<1){
                y = j*h-yc;
                temp = -x*x/(2*xs*xs) -y*y/(2*ys*ys) +1j*xp*x +1j*yp*y;
                u(ind) = exp(temp);
            }
            else{
                u(ind) = 0;
            }
        }
    }
    
    u = normalise(u,2);

    // u.print();

    return u;
}

