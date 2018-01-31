/****************************************************************/
/*               DO NOT MODIFY THIS HEADER                      */
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*           (c) 2010 Battelle Energy Alliance, LLC             */
/*                   ALL RIGHTS RESERVED                        */
/*                                                              */
/*          Prepared by Battelle Energy Alliance, LLC           */
/*            Under Contract No. DE-AC07-05ID14517              */
/*            With the U. S. Department of Energy               */
/*                                                              */
/*            See COPYRIGHT for full restrictions               */
/****************************************************************/

#ifndef PNPCONC_H
#define PNPCONC_H

#include "Kernel.h"

// Forward Declaration
class PNPConc;

template<>
InputParameters validParams<PNPConc>();

/**
 * This Kernel Calculates the concentration from the Poisson Nernst Plank equation.
 */
class PNPConc : public Kernel
{
public:
  PNPConc(const InputParameters & parameters);

protected:
  virtual Real computeQpResidual();

  virtual Real computeQpJacobian();

  virtual Real computeQpOffDiagJacobian(unsigned int jvar);

  /// The gradient of electric field
  const VariableGradient & _potential_gradient;

  /// Coupling identifier for the electric field.  This is used to uniquely
  /// identify a coupled variable
  unsigned int _potential_var;

  Real _mobility;
  Real _bulkconc;

  RealVectorValue _gradchem;

 
};

#endif //PNPCONC_H
