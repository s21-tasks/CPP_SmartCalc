#ifndef SMARTCALC_CONTROLLER_H
#define SMARTCALC_CONTROLLER_H

#include "../Model/Model.h"
#include <string>
namespace s21
{

  class Controller
  {
  private:
    Notation model;

  public:
    Controller(Notation n) : model(n){};
    bool expression_input(char **expr);
    double expression_output(double x);
  };

} // namespace s21

#endif // SMARTCALC_CONTROLLER_H
