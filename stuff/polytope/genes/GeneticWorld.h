/*
 * GeneticWorld.h
 *
 * (c) 2017 Sofian Audry -- info(@)sofianaudry(.)com
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

#ifndef GENETIC_WORLD_H_
#define GENETIC_WORLD_H_

#include "../osc/PolytopesOSC.h"

#include <qualia/ga/BinaryChromosome.h>
#include <vector>
#include <algorithm>

class GeneticWorld {
public:
	typedef std::vector<BinaryChromosome*> Population;
	enum {
		OSC1_WAVEFORM,
		OSC1_OFFSETS,
		OSC1_FREQUENCY,
		OSC1_DURATIONS,
		OSC1_ENVELOPPE_USE,
		OSC1_ENVELOPPE_ATTACK,
		OSC1_ENVELOPPE_DECAY,
		OSC1_ENVELOPPE_SPEED,

		OSC2_WAVEFORM,
		OSC2_OFFSETS,
		OSC2_FREQUENCY,
		OSC2_DURATIONS,
		OSC2_ENVELOPPE_USE,
		OSC2_ENVELOPPE_ATTACK,
		OSC2_ENVELOPPE_DECAY,
		OSC2_ENVELOPPE_SPEED,

		OSC3_WAVEFORM,
		OSC3_OFFSETS,
		OSC3_FREQUENCY,
		OSC3_DURATIONS,
		OSC3_ENVELOPPE_USE,
		OSC3_ENVELOPPE_ATTACK,
		OSC3_ENVELOPPE_DECAY,
		OSC3_ENVELOPPE_SPEED,

		N_GENES
	};

	const uint8_t GENE_SIZES[N_GENES] = {
			3,  // WAVEFORM,
			8,  // OFFSETS,
			16, // FREQUENCY,
			16, // DURATIONS,
			1, // ENVELOPPE_USE,
			8, // ENVELOPPE_ATTACK,
			8, // ENVELOPPE_DECAY,
			8, // ENVELOPPE_SPEED,

			3,  // WAVEFORM,
			8,  // OFFSETS,
			16, // FREQUENCY,
			16, // DURATIONS,
			1, // ENVELOPPE_USE,
			8, // ENVELOPPE_ATTACK,
			8, // ENVELOPPE_DECAY,
			8, // ENVELOPPE_SPEED,

			3,  // WAVEFORM,
			8,  // OFFSETS,
			16, // FREQUENCY,
			16, // DURATIONS,
			1, // ENVELOPPE_USE,
			8, // ENVELOPPE_ATTACK,
			8, // ENVELOPPE_DECAY,
			8, // ENVELOPPE_SPEED,
	};

	/// Chromosome properties.
	BinaryChromosomeProperties info;

	Population targets;

	Population population;

	float mutationRate;
	float survivalRate;

	GeneticWorld(int nNodes, float mutationRate, float survivalRate, int nTargets=1);
	~GeneticWorld();

	void init();

	void step();

	Population selectFittest(const Population& pop, int nFit);
	float fitness(const BinaryChromosome& dna);
	int distanceDNA(const BinaryChromosome& c1, const BinaryChromosome& c2);

	void setMutationRate(float m) { mutationRate = m; }
	void setSurvivalRate(float s) { survivalRate = s; }

	/// Returns true iff c1 is more fit than c2.
	bool moreFit(BinaryChromosome* c1, BinaryChromosome* c2);

	void setTargetSoundParameters(int targetId, int *params);

	/// Send DNA to OSC.
	void _sendDNA(int agentId);

	void _step(int agentId, int nFit);

	void _free(Population& pop);
};

#endif
