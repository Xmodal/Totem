/*
 * GeneticWorld.cpp
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

#include "GeneticWorld.h"
#include "../common/PolytopesDefs.h"

GeneticWorld::GeneticWorld(int nNodes, float mutationRate_, float survivalRate_, int nTargets)
 	: info(N_GENES, GENE_SIZES), mutationRate(mutationRate_), survivalRate(survivalRate_)
{
	for (int i=0; i<nNodes; i++)
		population.push_back(new BinaryChromosome(&info));
	for (int i=0; i<nTargets; i++)
		targets.push_back(new BinaryChromosome(&info));
}

GeneticWorld::~GeneticWorld()
{
	// Free memory.
	_free(population);
	_free(targets);
}

void GeneticWorld::init()
{
	// Init pop.
	for (Population::iterator dna = population.begin(); dna != population.end(); ++dna)
		(*dna)->init();

	// Init targets.
	for (Population::iterator dna = targets.begin(); dna != targets.end(); ++dna)
		(*dna)->init();
}

void GeneticWorld::step()
{
	static int agentId = 0;

	// Do one step.
	_step(agentId, round(survivalRate * population.size()));

	// Go to next agent.
	agentId = (agentId + 1) % population.size();

  PolytopeOSC::instance().checkBang( POLYTOPES_BANG_TIMEOUT );
}

GeneticWorld::Population GeneticWorld::selectFittest(const Population& pop, int nFit)
{
	// Copy items in new vector.
	Population fittest(pop.begin(), pop.end());
	// fittest.reserve(pop.size());
	// std::copy(pop.begin(), pop.end(), std::back_inserter(fittest));

	// Sort.
	struct _GeneticWorldWrapper {
  	GeneticWorld *cmp;
  	_GeneticWorldWrapper(GeneticWorld *cmp) : cmp(cmp) {}
		bool operator()(BinaryChromosome* c1, BinaryChromosome* c2) {
      return cmp->moreFit(c1,c2);
    }
	};
	_GeneticWorldWrapper w(this);
	std::sort(fittest.begin(), fittest.end(), w);

	// Crop.
	return Population(fittest.begin(), fittest.begin() + nFit);
}

float GeneticWorld::fitness(const BinaryChromosome& dna)
{
	float fitness = -100000;
	for (Population::iterator target = targets.begin(); target != targets.end(); ++target)
	{
		fitness = max(fitness, -float(distanceDNA(dna, **target)));
	}
	return (1 + fitness/info.bitSize()); // normalize to [0,1]
}

bool GeneticWorld::moreFit(BinaryChromosome* c1, BinaryChromosome* c2)
{
	return fitness(*c1) > fitness(*c2);
}

void GeneticWorld::setTargetSoundParameters(int targetId, int *params)
{
	printf("Target id %d =====\n", targetId);
	for (int i=0; i<N_GENES; i++) {
		targets[targetId]->setGeneValue(i, params[i]);
		printf("%i = %i\n", i, params[i]);
	}
}

/// Bit distance between two chromosomes.
int GeneticWorld::distanceDNA(const BinaryChromosome& c1, const BinaryChromosome& c2)
{
  int diff = 0;
  unsigned int bit = info.bitSize();
  while (bit--)
    diff += (arrayBitRead(c1.code, bit) != arrayBitRead(c2.code, bit) ? 1 : 0);
  return diff;
}

void GeneticWorld::_sendDNA(int agentId)
{
	// Get chromosome.
	BinaryChromosome* dna = population[agentId];

	// Gather parameters.
	std::vector<int> params;
	for (int i=0; i<N_GENES; i++)
	{
		// Directly get the gene value.
		params.push_back( (int) dna->getGeneValue(i) );
	}

	// Send OSC message.
  PolytopeOSC::instance().sendOutputSound(agentId, &params);
}

void GeneticWorld::_step(int agentId, int nFit)
{
	Population offsprings;
	BinaryChromosome* parent = population[agentId];

	// Randomly select some members of population to mate with.
	Population fittest = selectFittest(population, nFit);

	// Mate with them.
	for (Population::iterator dna = fittest.begin(); dna != fittest.end(); ++dna)
	{
    // Generate offsprings.
		BinaryChromosome* offspring1 = new BinaryChromosome(&info);
		BinaryChromosome* offspring2 = new BinaryChromosome(&info);

		// Cross-over.
    BinaryChromosome::crossoverTwoPoint(*parent, **dna, offspring1, offspring2);

		// Mutate.
		offspring1->mutate(mutationRate);
		offspring2->mutate(mutationRate);

		offsprings.push_back(offspring1);
		offsprings.push_back(offspring2);
	}

	// Evaluate offsprings: find best.
	Population best = selectFittest(offsprings, 1);

	// Change DNA to that of fittest offspring.
	parent->copyFrom(*best[0]);

	printf("Fittness: %f\n", fitness(*parent));

	// Send phenotype.
	_sendDNA(agentId);

	_free(offsprings);
}

void GeneticWorld::_free(Population& pop)
{
	for (Population::iterator dna = pop.begin(); dna != pop.end(); ++dna)
		delete (*dna);
}
