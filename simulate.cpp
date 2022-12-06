#include "utils.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <tuple>

using namespace std;
using namespace arma;

void log_(int n){
    cout << n << endl;
}

void log_(double d){
    cout << d << endl;
}

void log_(complex<double> d){
    cout << d << endl;
}


tuple<int, double, double, double, double, double,
    double, double, double, double> read_params(string filename){
    cout << "reading form: " << filename << endl;
    ifstream file(filename);
    string temp;
    getline(file, temp);
    int M = stoi(temp);
    getline(file, temp);
    double dt = stod(temp);
    getline(file, temp);
    double T = stod(temp);
    getline(file, temp);
    double xc = stod(temp);
    getline(file, temp);
    double xs = stod(temp);
    getline(file, temp);
    double xp = stod(temp);
    getline(file, temp);
    double yc = stod(temp);
    getline(file, temp);
    double ys = stod(temp);
    getline(file, temp);
    double yp = stod(temp);
    getline(file, temp);
    double V = stod(temp);

    cout << "done" << endl;

    return make_tuple(M, dt, T, xc, xs, xp, yc, ys, yp, V);
}

int main(int argc, char *argv[]){

    for (int i = 1; i<argc; i++){
        read_params(argv[i]);
    }


    #pragma omp parallel for
    for (int i = 1; i<argc; i++){
        int M;
        double dt, T, xc, xs, xp, yc, ys, yp, v0, h;
        tie(M, dt, T, xc, xs, xp, yc, ys, yp, v0) = read_params(argv[i]);
        h = 1./M;

        // log_(0);
        cx_vec V = potential(M) * v0;
        // log_(1);
        cx_vec u = u_init(M, xc, xs, xp, yc, ys, yp, V);
        // log_(2);
        sp_cx_mat A = AMatrix(M, h, dt, V);
        // log_(3);
        sp_cx_mat B = BMatrix(M, h, dt, V);
        // log_(4);

        double t = 0;
        int n = (int)(T/dt+0.5);
        double prob[n];
        cx_mat log = cx_mat((M-2)*(M-2), n);

        for (int j = 0; j<n; j++){
            // log_(5);
            time_step(u, A, B);
            // log_(6);
            log.col(j) = u;
            // log_(7);
            prob[j] = norm(u);
            // log_(8);
            cout << j+1 << "/" << n << "    norm = " << prob[j] << endl;
        }
        string filename = argv[i];
        filename = filename.substr(0, filename.length()-4);
        cout << filename << endl;
        bool success = log.save(filename + "/" + filename + ".bin");
        if (not success){cout << "Problem with saving of " << filename << endl;}

        ofstream file(filename + "/" + filename + "_meta.dat");
        file << "# time and total probability for each time step" << endl;
        for (int j = 0; j<n; j++){
            file << (j+1)*dt << "\t" << setw(20) << setprecision(16)
            << scientific << prob[j] << endl;
        }
    }

    return 0;
}