#include "SOZYTestApp.h"
#include "SOZYApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<SOZYTestApp>()
{
  InputParameters params = validParams<SOZYApp>();
  return params;
}

SOZYTestApp::SOZYTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  SOZYApp::registerObjectDepends(_factory);
  SOZYApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  SOZYApp::associateSyntaxDepends(_syntax, _action_factory);
  SOZYApp::associateSyntax(_syntax, _action_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    SOZYTestApp::registerObjects(_factory);
    SOZYTestApp::associateSyntax(_syntax, _action_factory);
  }
}

SOZYTestApp::~SOZYTestApp() {}

// External entry point for dynamic application loading
extern "C" void
SOZYTestApp__registerApps()
{
  SOZYTestApp::registerApps();
}
void
SOZYTestApp::registerApps()
{
  registerApp(SOZYApp);
  registerApp(SOZYTestApp);
}

// External entry point for dynamic object registration
extern "C" void
SOZYTestApp__registerObjects(Factory & factory)
{
  SOZYTestApp::registerObjects(factory);
}
void
SOZYTestApp::registerObjects(Factory & /*factory*/)
{
}

// External entry point for dynamic syntax association
extern "C" void
SOZYTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  SOZYTestApp::associateSyntax(syntax, action_factory);
}
void
SOZYTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}
