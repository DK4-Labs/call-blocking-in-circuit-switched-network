
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

#ifndef _SIMPARAMETERS_H_
#define _SIMPARAMETERS_H_

/*******************************************************************************/

#define Call_ARRIVALRATE 3   /* calls/minute */
#define MEAN_CALL_DURATION 1 /* minutes */
#define RUNLENGTH 5e6        /* number of successful calls */
#define BLIPRATE 1e3
#define NUMBER_OF_CHANNELS 1
#define WAIT_THRESHOLD 3        /*minutes*/
#define MEAN_ON_HOLD_DURATION 3 /*minutes*/

#define OFFERED_LOAD (Call_ARRIVALRATE * MEAN_CALL_DURATION)

/* Comma separated list of random seeds to run. */
#define RANDOM_SEED_LIST 400191540, 400175089, 400186733

/*******************************************************************************/

#endif /* simparameters.h */
