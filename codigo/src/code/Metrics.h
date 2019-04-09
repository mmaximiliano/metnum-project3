#ifndef __METRICS_H__
#define __METRICS_H__

#include <vector>

double calculatePSNR(const std::vector<std::vector<unsigned int> > &image,
                     const std::vector<std::vector<unsigned int> > &generatedImage);

double calculateECM(const std::vector<std::vector<unsigned int> > &image,
                    const std::vector<std::vector<unsigned int> > &generatedImage);

double calculateRECMIQR(const std::vector<std::vector<unsigned int> > &image,
                        const std::vector<std::vector<unsigned int> > &generatedImage);

double calculateIQR(const std::vector<std::vector<unsigned int> > &A);

#endif

