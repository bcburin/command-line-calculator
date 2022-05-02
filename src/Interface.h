#ifndef INTERFACE_H
#define INTERFACE_H

#include "Statement.h"
#include "Helpers.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<Statement*> read_statemets(
  std::istream* is = &std::cin, std::ostream* os = &std::cout, bool run=true, bool re_throw=false);

#endif