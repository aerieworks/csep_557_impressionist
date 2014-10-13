#include <random>
#include <time.h>
#include "Scattered.h"


Scattered::Scattered() {
  srand(time(0));
}

double Scattered::getRandomOffset(const double min, const double max) const {
  const double offsetPercentage = (double)rand() / (double)RAND_MAX;
  return min + (max - min) * offsetPercentage;
}
