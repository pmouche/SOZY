#ifndef SOZYAPP_H
#define SOZYAPP_H

#include "MooseApp.h"

class SOZYApp;

template <>
InputParameters validParams<SOZYApp>();

class SOZYApp : public MooseApp
{
public:
  SOZYApp(InputParameters parameters);
  virtual ~SOZYApp();

  static void registerApps();
  static void registerObjects(Factory & factory);
  static void registerObjectDepends(Factory & factory);
  static void associateSyntax(Syntax & syntax, ActionFactory & action_factory);
  static void associateSyntaxDepends(Syntax & syntax, ActionFactory & action_factory);
};

#endif /* SOZYAPP_H */
