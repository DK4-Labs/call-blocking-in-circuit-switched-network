
/*
 *
 * Call Blocking in Circuit Switched Networks
 *
 * Copyright (C) 2014 Terence D. Todd
 * Hamilton, Ontario, CANADA
 * todd@mcmaster.ca
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

/*******************************************************************************/

#include <stdio.h>
#include "simparameters.h"
#include "main.h"
#include "output.h"
#include "math.h"

/*******************************************************************************/

void output_progress_msg_to_screen(Simulation_Run_Ptr this_simulation_run)
{
  double percentagedone;
  Simulation_Run_Data_Ptr sim_data;

  sim_data = (Simulation_Run_Data_Ptr)simulation_run_data(this_simulation_run);

  sim_data->blip_counter++;

  if ((sim_data->blip_counter >= BLIPRATE) ||
      (sim_data->number_of_calls_processed >= RUNLENGTH))
  {
    sim_data->blip_counter = 0;

    percentagedone =
        100 * (double)sim_data->number_of_calls_processed / RUNLENGTH;

    printf("%3.0f%% ", percentagedone);

    printf("Call Count = %ld \r", sim_data->number_of_calls_processed);

    fflush(stdout);
  }
}

/*******************************************************************************/

void output_results(Simulation_Run_Ptr this_simulation_run, FILE **writeFile)
{
  double xmtted_fraction, wait_fraction;
  double average_wait_time, hang_up_probability;
  Simulation_Run_Data_Ptr sim_data;

  sim_data = (Simulation_Run_Data_Ptr)simulation_run_data(this_simulation_run);

  printf("\n");

  printf("random seed = %d \n", sim_data->random_seed);
  printf("call arrival count = %ld \n", sim_data->call_arrival_count);
  printf("calls that have to wait count = %ld \n", sim_data->wait_call_count);
  printf("hung up calls = %ld \n", sim_data->hang_up_call_count);

  // hang up probability
  hang_up_probability = ((double)sim_data->hang_up_call_count) / (sim_data->call_arrival_count);

  // actual value
  average_wait_time = (60.0 * (double)sim_data->accumulated_wait_time) / (sim_data->call_arrival_count);

  xmtted_fraction = (double)(sim_data->call_arrival_count -
                             sim_data->wait_call_count) /
                    sim_data->call_arrival_count;

  printf("Blocking probability = %.50f (Service fraction = %.5f)\n",
         1 - xmtted_fraction, xmtted_fraction);

  printf("Hang Up Probability = %.50f Average wait time= %.50f", hang_up_probability, average_wait_time);

  /* output order: w, N, Hang up Probability, average wait time */

  printf("\n");

  fprintf(*writeFile, "%d, %.50f, %.50f, %d, %d \n", sim_data->random_seed, hang_up_probability, average_wait_time, OFFERED_LOAD, NUMBER_OF_CHANNELS);
}
