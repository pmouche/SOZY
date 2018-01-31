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

#ifndef FLUX_H
#define FLUX_H

#include "AuxKernel.h"

//Forward Declarations
class Flux;

template<>
InputParameters validParams<Flux>();

/**
 * Constant auxiliary value
 */
class Flux : public AuxKernel
{
public:
  Flux(const InputParameters & parameters);

  //virtual ~Flux() {}

protected:
    virtual Real computeValue();

  /// 0,1,2 to stand for x,y,z
  int _component;

  /// The gradient of a coupled variable
  const VariableGradient & _potential_gradient;
  const VariableGradient & _conc_gradient;
  const VariableValue & _conc;

  Real _bulkconc;
  Real _mobility;
  RealVectorValue _gradchem;

  
  };

#endif //FLUX_H
