#include "CML.h"

#include "tools/SVD.h"
#include "tools/Lineal.h"

#include "tools/Prints.h"
#include <iostream>
#include <fstream>

std::vector<std::vector<unsigned int> > reconstructImage(const std::vector<double> &times,
                                                         std::vector<std::vector<double> > &distances,
                                                         unsigned int eigenvalueCount, std::string svd_path,
                                                         Config config) {
    // Queremos buscar s tal que:
    // ||Ds - t||^2 sea minimo
    // D es de mx(n^2) (cantidad de rayos x tamaño de imagen)
    // Hay que tener cuidado con las dimensiones:
    // Si m < n^2 (hay menos rayos que pixeles), voy a tener infinitas soluciones
    // Si m > n^2, esta sobredeterminado y resuelvo normalmente
    // Asumo m > n^2 porque sino es un caos
    // Usamos SVD
    // Asumo que las columnas son li (TODO: ver teoricamente que onda esto)
    // Entonces, siendo D = U*Sigma*Vt
    // (Ut*t)i = ci para todo i entre 1 y m
    // yi = ci/Sigmaii para todo i entre 1 y m
    // Resta resolver Vt*s = y

    // Voy a asumir m > n^2 asi todo es mas feliz, hay que ver que pasaria sino
    std::vector<std::vector<unsigned int> > im;
    // std::cout << "D: ";
    // print(distances);
    // std::cout << std::endl;

    // Consigo factorizacion SVD
    std::vector<std::vector<double> > Ut, Vt;
    std::vector<double> Sigma;

    std::string path = svd_path + "/svd-" + getFileName(config, false) + ".out";
    std::ifstream smat_check(path);

    if (!smat_check.good()) {
        std::cout << "Consigo SVD" << std::endl;
        getSVD(distances, Ut, Sigma, Vt, eigenvalueCount);

        if (svd_path != "NULL") {
            std::ofstream smat;
            smat.open(path, std::ios::out | std::ios::trunc);
            smat << Ut.size() << " " << Ut[0].size() << std::endl;
            for (auto i = Ut.begin(); i != Ut.end(); i++) {
                for (auto j = i->begin(); j != i->end(); j++) {
                    smat << *j << " ";
                }
            }
            smat << std::endl;
            smat << Sigma.size() << std::endl;
            for (auto i = Sigma.begin(); i != Sigma.end(); i++) {
                smat << *i << " ";
            }
            smat << std::endl;
            smat << Vt.size() << " " << Vt[0].size() << std::endl;
            for (auto i = Vt.begin(); i != Vt.end(); i++) {
                for (auto j = i->begin(); j != i->end(); j++) {
                    smat << *j << " ";
                }
            }
            smat.close();
        }
    } else {
        std::cout << "Uso SVD guardada" << std::endl;
        std::ifstream smat;
        smat.open(path);
        int rows, cols;
        smat >> rows;
        smat >> cols;
        for (int i = 0; i < rows; i++) {
            Ut.push_back(std::vector<double>());
            for (int j = 0; j < cols; j++) {
                double e;
                smat >> e;
                Ut[i].push_back(e);
            }
        }

        smat >> rows;
        for (int i = 0; i < rows; i++) {
            double e;
            smat >> e;
            Sigma.push_back(e);
        }

        smat >> rows;
        smat >> cols;
        for (int i = 0; i < rows; i++) {
            Vt.push_back(std::vector<double>());
            for (int j = 0; j < cols; j++) {
                double e;
                smat >> e;
                Vt[i].push_back(e);
            }
        }
        smat.close();
    }

    // Calculo c e y
    // std::cout << "Calculo c e y" << std::endl;
    std::vector<double> c = Ut * times;
    std::vector<double> y;
    for (unsigned int i = 0; i < c.size(); i++) {
        y.push_back(c[i] / Sigma[i]);
    }

    // Resuelvo el sistema
    // std::cout << "Resuelvo el sistema" << std::endl;
    std::vector<double> s = transpose(Vt) * y;
    // std::cout << "S: " << std::endl;
    // print(s);
    // std::cout << std::endl;

    // Paso a imagen (matriz de naturales)
    // std::cout << "Paso a matriz" << std::endl;
    std::vector<unsigned int> row;
    for (unsigned int i = 0; i < s.size(); i++) {
        row.push_back((s[i] > 255) ? 255 : ((s[i] < 0) ? 0 : s[i]));

        if (row.size() * row.size() == s.size()) {
            im.push_back(row);
            row.clear();
        }
    }

    return im;
}
