#include "gradiente_coniugato.hpp"
#include "Eigen/Dense"
#include <iostream>


int main() {
    const int N = 20;
    const double tol_cg = 1.0e-12;
    const int it_max = 10000;
    
    const double tol_test = 1.0e-7; 

    for (int i = 2; i <= N; i++) {
        
        // Costruzione matrice simmetrica definita positiva
        Eigen::MatrixXd B = Eigen::MatrixXd::Random(i, i);
        Eigen::MatrixXd A = B.transpose() * B;
        
		// sol esatta: vettori di tutti 1
        Eigen::VectorXd x_ex = Eigen::VectorXd::Ones(i);
        
        // costruisco b
        Eigen::VectorXd b = A * x_ex;
        
        // x_0 casuale
        Eigen::VectorXd x = Eigen::VectorXd::Zero(i);
        
        // Risoluzione
        const double res = gradiente_coniugato(A, x, b, tol_cg, it_max);
        
        // controllo se raggiunge la tol
        if (res >= tol_cg) {
            std::cerr << "Errore (N = " << i << "): Convergenza non raggiunta. Residuo: " << res << std::endl;
            return EXIT_FAILURE;
        }
        
        // controllo se err_rel  supera la mia tol_test
        const double err_rel = (x - x_ex).norm() / x_ex.norm();
        
        if (err_rel >= tol_test) {
            std::cerr << "Errore (N = " << i << "): Errore relativo troppo grande. Err: " << err_rel << std::endl;
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}