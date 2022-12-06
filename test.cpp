#include "utils.hpp"
#include <iomanip>

using namespace std;
using namespace arma;

int main(){
    int M = 3;
    double x = 1./M;
    // A.print();
    // B.print();
    // cx_vec V = potential(M);
    // u_init(M, 0.25, 0.05 ,200, 0.5, 0.05, 0, V);

    // potential(61);
    cout << setw(20) << setprecision(16)
            << scientific << x << endl;

    return 0;
}