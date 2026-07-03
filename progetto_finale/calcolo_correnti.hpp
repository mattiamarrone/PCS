#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <Eigen/Dense>
#include "matrice_resistori.hpp"
#include "matrice_incidenza.hpp"


//tensioni_generatori è il vettore dei termini noti

Eigen::VectorXd calcolo_correnti(const Eigen::MatrixXd& R, const Eigen::MatrixXd& B, const Eigen::VectorXd& tensioni_generatori, const Eigen::VectorXd& x0, int iter_max = 10000, double tol=1e-9) {    
    // calcolo la matrice B^t*R*B
    Eigen::MatrixXd A=B.transpose()*R*B;

    // inizializzazione di x0
    Eigen::VectorXd correnti=x0;

    // inizializzazione del residuo
    Eigen::VectorXd r=tensioni_generatori-A*correnti;

    // inizializzazione del passo
    Eigen::VectorXd p=r;

    // inzializzazione del contatore 
    int k=0;

    while (r.norm()>=tol && k<iter_max) {

        double alpha=r.dot(r)/(p.dot(A*p));

        // aggiornamento di x
        correnti=correnti+alpha*p;

        // aggiornamento del residuo
        r=r-alpha*A*p;

        // calcolo di beta
        double beta=(p.dot(A*r))/(p.dot(A*p));

        //aggiornamento del passo
        p=r-beta*p;

        // aggiornamento del contatore
        k=k+1;
    }
            

    return correnti;
};