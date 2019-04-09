#include "SVD.h"

#include "Lineal.h"
#include "Eigenvectors.h"
#include <cmath>

#include <iostream>
#include <stdexcept>

// TODO: meter threads?
std::vector<std::vector<double> > getAtA(const std::vector<std::vector<double> > &A) {
    std::vector<std::vector<double> > AtA;

    std::vector<std::vector<double> > At = transpose(A);

    // (AtA)ij = filai(At) * colj(A) = coli(A) * colj(A)
    for (unsigned int i = 0; i < At.size(); i++) {
        AtA.push_back(At * At[i]);
    }

    return AtA;
}

// std::vector<std::vector<double> > getAAt(const std::vector<std::vector<double> >& A) {
// 	std::vector<std::vector<double> > AAt;
//
// 	// (AAt)ij = filai(A) * colj(At) = filai(A) * filaj(A)
// 	for (unsigned int i = 0; i < A.size(); i++) {
// 		std::vector<double> row;
// 		for (unsigned int j = 0; j < A.size(); j++) {
// 			row.push_back(A[i] * A[j]);
// 		}
// 		AAt.push_back(row);
// 	}
//
// 	return AAt;
// }

void getSVD(const std::vector<std::vector<double> > &A,
            std::vector<std::vector<double> > &Ut,
            std::vector<double> &Sigma,
            std::vector<std::vector<double> > &Vt,
            unsigned int eigenvalueCount) {
    // Asumo que si A esta en R mxn, m > n (ver detalles en CML.cpp)

    std::vector<std::vector<double> > AtA = getAtA(A);

    std::vector<double> v(AtA.size());
    for (unsigned int i = 0; i < eigenvalueCount; i++) {
        std::cout << "Calculando valor singular " << (i + 1) << "/" << eigenvalueCount << " (Acotados de: "
                  << AtA.size() << ")...\r" << std::flush;
        double eigenvalue = powerMethod(AtA, v);
        if (eigenvalue < 0.0) {
            std::cout << std::endl << "Valor singular negativo";
            break;
            // eigenvalue = - eigenvalue;
            // throw std::runtime_error("No se pudo calcular un valor singular");;
        };
        Vt.push_back(v);
        // Pusheo aca ya que m > n
        Sigma.push_back(sqrt(eigenvalue));
        reduceEigenvalues(AtA, v, eigenvalue);
    }
    std::cout << std::endl << "Se van a usar " << Sigma.size() << " valores singulares" << std::endl;

    // Solo me va a interesar tener n columnas de U (el resto se multiplica por 0)
    // Calcular AAt es caro. Es mejor hacer A*vi / sigmai
    for (unsigned int i = 0; i < Sigma.size(); i++) {
        Ut.push_back((1 / Sigma[i]) * (A * Vt[i]));
    }
}
