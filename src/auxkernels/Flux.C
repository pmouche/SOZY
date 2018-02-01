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

#include "Flux.h"

template<>
InputParameters validParams<Flux>()
{
  InputParameters params = validParams<AuxKernel>();

  // Declare the options for a MooseEnum.
  // These options will be presented to the user in Peacock
  // and if something other than these options is in the input file
  // an error will be printed
  MooseEnum component("x y z");

  // Use the MooseEnum to add a parameter called "component"
  params.addRequiredParam<MooseEnum>("component", component, "The desired component of velocity.");

  // Add a "coupling paramater" to get a variable from the input file.
  params.addRequiredCoupledVar("potential", "The electric field.");
  params.addRequiredCoupledVar("PNPConc", "The concentration");
 
  params.addRequiredParam<Real>("mobility", "The mobiliy of the ions");
  params.addRequiredParam<RealVectorValue>("gradchem", "gradient of chemical potential");

  return params;
}

Flux::Flux(const InputParameters & parameters) :
    AuxKernel(parameters),

    // This will automatically convert the MooseEnum to an integer
    _component(getParam<MooseEnum>("component")),

    // Get the gradient of the variable
    _potential_gradient(coupledGradient("potential")),
    _conc_gradient(coupledGradient("PNPConc")),

    _conc(coupledValue("PNPConc")),

  
    _mobility(getParam<Real>("mobility")),
    _gradchem(getParam<RealVectorValue>("gradchem"))

{
}

Real
Flux::computeValue()
{
  // Get the gradient of the electric field at the quadrature point
  // Then pull out the "component" of it we are looking for (x, y or z)
  // Note that getting a particular component of a gradient is done using the
  // parenthesis operator
  // Diff=
  return (_conc_gradient[_qp](_component)+
          _mobility*_conc[_qp]*(_potential_gradient[_qp](_component)));
  
}
