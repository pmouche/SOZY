#ifndef SOZYTESTAPP_H
#define SOZYTESTAPP_H

#include "MooseApp.h"

class SOZYTestApp;

template <>
InputParameters validParams<SOZYTestApp>();

class SOZYTestApp : public MooseApp
{
public:
  SOZYTestApp(InputParameters parameters);
  virtual ~SOZYTestApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* SOZYTESTAPP_H */
