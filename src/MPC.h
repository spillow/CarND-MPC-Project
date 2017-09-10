#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

struct Vars
{
    std::vector<double> xs;
    std::vector<double> ys;
    std::vector<double> psis;
    std::vector<double> vs;
    std::vector<double> ctes;
    std::vector<double> epsis;
    std::vector<double> deltas;
    std::vector<double> as;
};

class MPC {
 public:
  MPC() {};

  virtual ~MPC() {};

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuations.
  Vars Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
};

#endif /* MPC_H */
