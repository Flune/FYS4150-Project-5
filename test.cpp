#include "utils.hpp"

using namespace std;
using namespace arma;

int main(){
    cx_vec a = cx_vec(9, fill::none); a.fill(1);
    // arma::vec b=arma::zeros(9);
    sp_cx_mat A = aMatrix(5,2,a);
    // arma::mat B = bMatrix(5,2,b);
    A.print();

    return 0;
}