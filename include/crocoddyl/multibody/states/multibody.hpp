///////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License
//
// Copyright (C) 2018-2019, LAAS-CNRS
// Copyright note valid unless otherwise stated in individual files.
// All rights reserved.
///////////////////////////////////////////////////////////////////////////////

#ifndef CROCODDYL_MULTIBODY_STATES_MULTIBODY_HPP_
#define CROCODDYL_MULTIBODY_STATES_MULTIBODY_HPP_

#include "crocoddyl/core/state-base.hpp"
#include <pinocchio/multibody/model.hpp>

namespace crocoddyl {

class StateMultibody : public StateAbstract {
 public:
  enum JointType { FreeFlyer = 0, Spherical, Simple };

  explicit StateMultibody(pinocchio::Model& model);
  ~StateMultibody();

  Eigen::VectorXd zero() const;
  Eigen::VectorXd rand() const;
  void diff(const Eigen::Ref<const Eigen::VectorXd>& x0, const Eigen::Ref<const Eigen::VectorXd>& x1,
            Eigen::Ref<Eigen::VectorXd> dxout) const;
  void integrate(const Eigen::Ref<const Eigen::VectorXd>& x, const Eigen::Ref<const Eigen::VectorXd>& dx,
                 Eigen::Ref<Eigen::VectorXd> xout) const;
  void Jdiff(const Eigen::Ref<const Eigen::VectorXd>&, const Eigen::Ref<const Eigen::VectorXd>&,
             Eigen::Ref<Eigen::MatrixXd> Jfirst, Eigen::Ref<Eigen::MatrixXd> Jsecond,
             Jcomponent firstsecond = both) const;
  void Jintegrate(const Eigen::Ref<const Eigen::VectorXd>&, const Eigen::Ref<const Eigen::VectorXd>&,
                  Eigen::Ref<Eigen::MatrixXd> Jfirst, Eigen::Ref<Eigen::MatrixXd> Jsecond,
                  Jcomponent firstsecond = both) const;

  pinocchio::Model& get_pinocchio() const;

 private:
  void updateJdiff(const Eigen::Ref<const Eigen::MatrixXd>& Jdq, Eigen::Ref<Eigen::MatrixXd> Jd_,
                   bool positive = true) const;

  pinocchio::Model& pinocchio_;
  Eigen::VectorXd x0_;
  JointType joint_type_;
};

}  // namespace crocoddyl

#endif  // CROCODDYL_MULTIBODY_STATES_MULTIBODY_HPP_
