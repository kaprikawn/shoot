#include <iostream>
#include "values.hpp"

Values* Values::s_pInstance = 0;

void Values::init() {
  Values::reset();
}

void Values::reset() {
  lives_ = 3;
  bombs_ = 3;
}
