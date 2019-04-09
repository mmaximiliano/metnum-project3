#ifndef __SVD_H__
#define __SVD_H__

#include <vector>

// Devuelve Ut y Vt ya que es mas facil (evito transponer U) y es lo que necesito
void getSVD(const std::vector<std::vector<double> > &A,
            std::vector<std::vector<double> > &Ut,
            std::vector<double> &Sigma,
            std::vector<std::vector<double> > &Vt,
            unsigned int eigenvalueCount);

#endif
