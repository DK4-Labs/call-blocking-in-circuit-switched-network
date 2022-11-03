
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

#include <math.h>
#include <stdio.h>
#include "main.h"
#include "call_duration.h"
#include "simparameters.h"
#include "call_departure.h"
#include "call_arrival.h"

/*******************************************************************************/

/*
 * Function to schedule a call arrival event. 
 */

long int
schedule_call_arrival_event(Simulation_Run_Ptr simulation_run, 
			    double event_time)
{
  Event new_event;

  new_event.description = "Call Arrival";
  new_event.function = call_arrival_event;
  new_event.attachment = NULL;

  return simulation_run_schedule_event(simulation_run, new_event, event_time);
}

/*******************************************************************************/

/*
 * Call arrival event function.
 */

void
call_arrival_event(Simulation_Run_Ptr simulation_run, void * ptr)
{
  Call_Ptr new_call;
  Channel_Ptr free_channel;
  Simulation_Run_Data_Ptr sim_data;
  double now;

  now = simulation_run_get_time(simulation_run);

  sim_data = simulation_run_data(simulation_run);
  sim_data->call_arrival_count++;

  /* Allocate some memory for the call. If we can't service it immediately, put it in the FIFO */
  new_call = (Call_Ptr) xmalloc(sizeof(Call));
  new_call->arrive_time = now;
  new_call->call_duration = get_call_duration();
  new_call->waiting_time = exponential_generator(CALL_MEAN_WAITING_TIME);
  new_call->channel = NULL;
  new_call->hang_up_event_id = 0;

  /* See if there is a free channel.*/
  if((free_channel = get_free_channel(simulation_run)) != NULL) {

    // No waiting time for this call
    sim_data->total_call_waiting_time += 0;

    /* Place the call in the free channel and schedule its
       departure. */
    server_put(free_channel, (void*) new_call);
    new_call->channel = free_channel;

    schedule_end_call_on_channel_event(simulation_run,
				       now + new_call->call_duration,
				       (void *) free_channel);
  } else {
    /* No free channel was found. The call is added to FIFO queue */
    //sim_data->blocked_call_count++;

    new_call->hang_up_event_id = schedule_call_hang_up_event(simulation_run, new_call->arrive_time + new_call->waiting_time, (void *) new_call);
    fifoqueue_put(sim_data->fifo, (void *) new_call);
  }

  /* Schedule the next call arrival. */
  schedule_call_arrival_event(simulation_run,
	      now + exponential_generator((double) 1/Call_ARRIVALRATE));
}

/*******************************************************************************/

/*
 * Function to schedule call hang up
 */

long int
schedule_call_hang_up_event(Simulation_Run_Ptr simulation_run, 
			    double event_time, void * call_ptr)
{
  Event new_event;

  new_event.description = "Call Dropped";
  new_event.function = call_hang_up_event;
  new_event.attachment = call_ptr;

  return simulation_run_schedule_event(simulation_run, new_event, event_time);
}

/*******************************************************************************/

/*
 * Hang up handler function
 */

void
call_hang_up_event(Simulation_Run_Ptr simulation_run, void * call_ptr)
{
  Simulation_Run_Data_Ptr sim_data;
  double now;
  Call_Ptr fifo_dropped_call = (Call_Ptr) call_ptr;

  sim_data = simulation_run_data(simulation_run);

  now = simulation_run_get_time(simulation_run);

  // dequeue from fifo
  fifoqueue_remove(sim_data->fifo, (void *) fifo_dropped_call);

  // check that dequeued call is not null
  if (fifo_dropped_call == NULL)
  {
    printf("\nERROR: attempt to dequeue empty queue\n");
    exit(1);
  }

  sim_data->total_call_waiting_time += now - fifo_dropped_call->arrive_time;
  sim_data->blocked_call_count++;

  // free memory
  xfree((void*) fifo_dropped_call);
}
/*******************************************************************************/

/*
 * Scan through the channels and return a free one, if possible. Otherwise
 * return NULL.
 */

Channel_Ptr get_free_channel(Simulation_Run_Ptr simulation_run)
{
  Channel_Ptr *channels;
  int i;
  Simulation_Run_Data_Ptr sim_data;

  sim_data = simulation_run_data(simulation_run);
  channels = sim_data->channels;

  for (i=0; i<NUMBER_OF_CHANNELS; i++) {
    if (server_state(*(channels+i)) == FREE)
      return *(channels+i);
  }
  return (Channel_Ptr) NULL;
}


