#include "utils.hpp"

using namespace std;
using namespace arma;

int main(){
    cx_vec a = cx_vec(9, fill::none); a.fill(1);
    cx_vec b = cx_vec(9, fill::none); b.fill(0);

    sp_cx_mat A = aMatrix(5,2,a);
    sp_cx_mat B = bMatrix(5,2,b);
    // A.print();
    // B.print();

    potential(61);

    return 0;
}