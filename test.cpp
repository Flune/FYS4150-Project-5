#include "utils.hpp"

using namespace std;
using namespace arma;

int main(){
    arma::vec a=arma::ones(9);
    arma::vec b=arma::zeros(9);
    arma::mat A = aMatrix(5,2,a);
    arma::mat B = bMatrix(5,2,b);
    //A.print();

    return 0;
}