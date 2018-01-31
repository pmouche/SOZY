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

#include "Potential.h"


template<>
InputParameters validParams<Potential>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("PNPConc", "Concentration of the diffusing anion or canion.");
  params.addRequiredParam<Real>("permittivity", "The permittivity of the oxide ");
  params.addRequiredParam<Real>("charge", "The charge of the species");

  return params;
}


Potential::Potential(const InputParameters & parameters) :
    Kernel(parameters),

    _concentration_value(coupledValue("PNPConc")),
    _concentration_var(coupled("PNPConc")),
    _permittivity(getParam<Real>("permittivity")),
    _charge(getParam<Real>("charge"))
{
}

Real
Potential::computeQpResidual()
{
  
   return -_charge*_permittivity * _concentration_value[_qp]*_test[_i][_qp];
}

Real
Potential::computeQpJacobian()
{
  return 0.0;  
}

Real
Potential::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _concentration_var)
  {
    return -_charge*_permittivity * _phi[_j][_qp]*_test[_i][_qp];
  }
  return 0.0;
}
