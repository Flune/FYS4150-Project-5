#include "utils.hpp"

using namespace std;
using namespace arma;

int index(int i,int j,int rl){
    return i*rl+j;
}

void log(int n){
    cout << n << endl;
}

sp_cx_mat aMatrix(int M, double r, cx_vec a){
    int N=M-2;
    // We have N*N + 4*N*(N-1) values
    cx_vec values = cx_vec(N*(5*N-4));
    umat locations = umat(2, N*(5*N-4));
    // A.diag()=a;
    values.subvec(0,N*N-1) = a;
    for (int i=0; i<N*N; i++){
        locations.col(i).fill(i);
    }
    int count = N*N;
    values.subvec(N*N,N*(5*N-4)-1).fill(-r);
    // A.diag(-N)=arma::ones(A.diag(-N).n_elem)*(-r);
    for (int i=0; i<N*(N-1); i++){
        locations(0,count)=i;
        locations(1,count)=i+N;
        count++;
    }
    // A.diag(N)=arma::ones(A.diag(N).n_elem)*(-r);
    for (int i=0; i<N*(N-1); i++){
        locations(0,count)=i+N;
        locations(1,count)=i;
        count++;
    }
    // A.diag(-1)=arma::ones(A.diag(-1).n_elem)*(-r);
    for (int i=0; i<N*N; i++){
        if(i%N != 0){
            locations(0,count)=i;
            locations(1,count)=i-1;
            count++;
        }
    }
    // A.diag(1)=arma::ones(A.diag(-1).n_elem)*(-r);
    for (int i=0; i<N*N; i++){
        if(i%N != 0){
            locations(0,count)=i-1;
            locations(1,count)=i;
            count++;
        }
    }

    sp_cx_mat A = sp_cx_mat(locations, values);
    return A;
}

// arma::sp_cx_mat bMatrix(int M, double r, arma::cx_vec b){

//     int N=M-2;
//     arma::mat B = arma::zeros(N*N,N*N);
//     B.diag()=b;
//     B.diag(-N)=arma::ones(B.diag(-N).n_elem)*(r);
//     B.diag(N)=arma::ones(B.diag(N).n_elem)*(r);
//     B.diag(-1)=arma::ones(B.diag(-1).n_elem)*(r);
//     B.diag(1)=arma::ones(B.diag(-1).n_elem)*(r);


//     for (int i=1; i<(N*N); i++){
//         if (i%N==0){
//             B(i-1,i)=0;
//             B(i,i-1)=0;
//         }
//     }

//     return B;
// }

