#include <armadillo>
#include <iostream>
#include <string>
#include <complex>


arma::sp_cx_mat abMatrix(int M, std::complex<double> r, arma::cx_vec& a);

arma::cx_vec potential(int M,
                       int n_slits = 2,
                       double thickness = 0.02,
                       double x_pos = 0.5,
                       double slit_seperation = 0.05,
                       double slit_size = 0.05);

arma::sp_cx_mat AMatrix(int M, double h, double dt, arma::cx_vec& V);

arma::sp_cx_mat BMatrix(int M, double h, double dt, arma::cx_vec& V);

void time_step(arma::cx_vec& u, arma::sp_cx_mat& A, arma::sp_cx_mat& B);

// xc = x position of the center
// xs = width in the x direction
// xp = velocitiy in the x direction
arma::cx_vec u_init(int M, double xc, double xs, double xp,
                    double yc, double ys, double yp, arma::cx_vec& V);