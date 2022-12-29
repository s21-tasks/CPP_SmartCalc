#include "Controller.h"
    
bool s21::Controller::expression_input(char ** expr) {
  return model.inp(expr);
}

double s21::Controller::expression_output(double x) {
  return model.polish(x);
}
