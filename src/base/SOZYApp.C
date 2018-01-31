#include "SOZYApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

// Kernels
#include "Potential.h"
#include "PNPConc.h"

// AuxKernels
#include "Flux.h"


template <>
InputParameters
validParams<SOZYApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

SOZYApp::SOZYApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SOZYApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SOZYApp::associateSyntax(_syntax, _action_factory);
}

SOZYApp::~SOZYApp() {}

// External entry point for dynamic application loading
extern "C" void
SOZYApp__registerApps()
{
  SOZYApp::registerApps();
}
void
SOZYApp::registerApps()
{
  registerApp(SOZYApp);
}

// void
// SOZYApp::registerObjectDepends(Factory & /*factory*/)

// External entry point for dynamic object registration
extern "C" void
SOZYApp__registerObjects(Factory & factory)
{
  SOZYApp::registerObjects(factory);
}
void
SOZYApp::registerObjects(Factory & factory)
{
  registerKernel(Potential);
  registerKernel(PNPConc);
  
  registerAux(Flux);

}

// void
// SOZYApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
// {
// }

// External entry point for dynamic syntax association
extern "C" void
SOZYApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  SOZYApp::associateSyntax(syntax, action_factory);
}
void
SOZYApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
