/*
 * PolytopesDefs.h
 *
 * (c) 2012 Sofian Audry -- info(@)sofianaudry(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

// Standard definitions/configuration options for the Polytopes project

#ifndef POLYTOPESDEFS_H_
#define POLYTOPESDEFS_H_

#define POLYTOPES_DRUNK_MAX_LED_INC 0.2f

/// Mutation rate.
#define POLYTOPE_GENE_MUTATE_RATE 0.01f
#define POLYTOPE_GENE_SURVIVAL_RATE 0.1f
#define POLYTOPE_GENE_N_TARGETS 5

#define N_LEDS_PER_NODE   3

// just defaults - but relevant for FireFly: N_NODES
#define N_LINES          12
#define N_NODES_PER_LINE  4

// Datanetwork configuration.
#define POLYTOPES_TARGET_IP "10.42.0.1"
#define POLYTOPES_TARGET_PORT  "57121"
#define POLYTOPES_LISTEN_PORT "7000"

#define POLYTOPES_BANG_TIMEOUT 10000UL

/// ------ calculated -------

// Number of lines/nodes/leds.
const int N_NODES         = N_LINES * N_NODES_PER_LINE;
const int N_LEDS_PER_LINE = N_NODES_PER_LINE * N_LEDS_PER_NODE;
const int N_LEDS          = N_LINES * N_LEDS_PER_LINE;

// Constants for lasers/mirrors controls.
#define NO_CHANGE     (-1)
#define UNINITIALIZED (-2)

// Observations:
// [0 .. N_NODES-1]              -> incoming light reading
// [N_NODES .. N_NODES+N_LEDS-1] -> LED value [0..1]
const int OBSERVATION_DIM = N_NODES + N_LEDS;
const int ACTION_DIM      = N_LEDS;
#define N_ACTIONS_PER_DIM 256
const int ACTION_MAX = N_ACTIONS_PER_DIM-1;

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)

#endif /* POLYTOPESDEFS_H_ */
