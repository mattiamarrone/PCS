#pragma once
#include "Eigen/Dense"

double gradiente_coniugato(const Eigen::MatrixXd& A, Eigen::VectorXd& x, const Eigen::VectorXd& b, const double tol, const int it) {
    
    Eigen::VectorXd r = b - A * x;
    Eigen::VectorXd p = r;
    
    double res_tol = r.norm();
    int i = 0;
    
    while (i < it && res_tol > tol) {
		const double alpha_k = p.dot(r) / p.dot(A * p);        
		x = x + alpha_k * p;
		r = b - A * x;
		const double beta_k = p.dot(A * r) / p.dot(A * p);		
		p = r - beta_k * p;
		res_tol = r.norm();
		i++;
    }
    
    return res_tol;
}