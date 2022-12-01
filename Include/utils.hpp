#include <armadillo>
#include <iostream>
#include <string>


arma::sp_cx_mat aMatrix(int M, double r, arma::cx_vec a);
    
arma::sp_cx_mat bMatrix(int M, double r, arma::cx_vec b);

arma::cx_vec potential(int M,
                       int n_slits = 2,
                       double thickness = 0.02,
                       double x_pos = 0.5,
                       double slit_seperation = 0.05,
                       double slit_size = 0.05);