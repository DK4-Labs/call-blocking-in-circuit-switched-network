#include "simparameters.h"
#include "on_hold_duration.h"

/*******************************************************************************/

double get_on_hold_duration(void)
{
  return exponential_generator((double) MEAN_ON_HOLD_DURATION);
}