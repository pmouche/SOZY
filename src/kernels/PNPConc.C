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

#include "PNPConc.h"

template<>
InputParameters validParams<PNPConc>()
{
  InputParameters params = validParams<Kernel>();

  params.addRequiredCoupledVar("potential", "The electric field.");
  params.addRequiredParam<Real>("mobility", "The mobility of the diffusion species");
  params.addRequiredParam<Real>("bulkconc", "The bulk concentration");
  params.addRequiredParam<RealVectorValue>("gradchem", "gradient of chemical potential");

  return params;
}

PNPConc::PNPConc(const InputParameters & parameters) :
    Kernel(parameters),

    // Couple to the gradient of the electic field
    _potential_gradient(coupledGradient("potential")),

    // Save off the coupled variable identifier for use in
    // computeQpOffDiagJacobian
    _potential_var(coupled("potential")),
  

    _mobility(getParam<Real>("mobility")),
    _bulkconc(getParam<Real>("bulkconc")),

    _gradchem(getParam<RealVectorValue>("gradchem"))

{
}

    
Real
PNPConc::computeQpResidual()
{
    return _mobility * (_u[_qp] * (_potential_gradient[_qp]+_gradchem) + (_potential_gradient[_qp]+_gradchem)) * _grad_test[_i][_qp];
}

Real
PNPConc::computeQpJacobian()
{
  return _mobility * _phi[_j][_qp] * (_potential_gradient[_qp] + _gradchem)* _grad_test[_i][_qp];
}

Real
PNPConc::computeQpOffDiagJacobian(unsigned int jvar)
{
  if (jvar == _potential_var)
  {
    return _mobility * (_u[_qp]) * _grad_phi[_j][_qp] * _grad_test[_i][_qp];
  }
    else
   return 0.0;
}
