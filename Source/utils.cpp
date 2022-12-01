#include "utils.hpp"

using namespace std;
using namespace arma;

int index(int i,int j,int rl){
    return i*rl+j;
}

arma::mat aMatrix(int M, double r, arma::vec a){
    int N=M-2;
    arma::mat A = arma::zeros(N*N,N*N);
    A.diag()=a;
    A.diag(-N)=arma::ones(A.diag(-N).n_elem)*(-r);
    A.diag(N)=arma::ones(A.diag(N).n_elem)*(-r);
    A.diag(-1)=arma::ones(A.diag(-1).n_elem)*(-r);
    A.diag(1)=arma::ones(A.diag(-1).n_elem)*(-r);

    for (int i=1; i<(N*N); i++){
        if (i%N==0){
            A(i-1,i)=0;
            A(i,i-1)=0;
        }
    }
    return A;
}

arma::mat bMatrix(int M, double r, arma::vec b){

    int N=M-2;
    arma::mat B = arma::zeros(N*N,N*N);
    B.diag()=b;
    B.diag(-N)=arma::ones(B.diag(-N).n_elem)*(r);
    B.diag(N)=arma::ones(B.diag(N).n_elem)*(r);
    B.diag(-1)=arma::ones(B.diag(-1).n_elem)*(r);
    B.diag(1)=arma::ones(B.diag(-1).n_elem)*(r);


    for (int i=1; i<(N*N); i++){
        if (i%N==0){
            B(i-1,i)=0;
            B(i,i-1)=0;
        }
    }

    return B;
}

