#include "Glyph.h"
#include <iostream>

Glyph::Glyph(const GlyphBlockFactory& topFactory, const GlyphBlockFactory& subFactory, float subdivisionProbability)
{
	// Create top-level blocks.
	for (int i = 0; i < N_TOP_BLOCKS; i++)
		topBlocks[i] = topFactory.create();

	// Re-useable empty block.
	GlyphBlock emptyBlock;

	// Create sub-blocks.
	for (int i = 0; i < N_TOP_BLOCKS; i++)
	{
		// Preserve current, previous and next top-level blocks (to generate connections between top-blocks).
		GlyphBlock& currentTopBlock = topBlocks[i];
		GlyphBlock& prevTopBlock = (i == 0 ? emptyBlock : topBlocks[i - 1]);
		GlyphBlock& nextTopBlock = (i == N_TOP_BLOCKS - 1 ? emptyBlock : topBlocks[i + 1]);

		// For each column j inside top-block.
		for (int j = 0; j < BLOCK_SIDE; j++) {
			// For each row k inside top-block.
			for (int k = 0; k < BLOCK_SIDE; k++) {
				GlyphBlock newBlockOnTheBlock;
				// If top-block contains element: draw something there.
				if (topBlocks[i].get(j, k)) {
					float rnd = float(rand()) / RAND_MAX; // pick random number in [0, 1]
					
					// Subdivide using a generative block.
					if (rnd < subdivisionProbability)
					{
						newBlockOnTheBlock = subFactory.create();
					}

					// Do not subdivide: use basic connection block.
					else {
						newBlockOnTheBlock = GlyphBlock(
							currentTopBlock.getIfExists(j-1, k), // left
							currentTopBlock.getIfExists(j, k-1, prevTopBlock, nextTopBlock), // top
							currentTopBlock.getIfExists(j+1, k), // right
							currentTopBlock.getIfExists(j, k+1, prevTopBlock, nextTopBlock)); // bottom
						//newBlockOnTheBlock = GlyphBlock(
						//  currentTopBlock.getIfExists(j, k-1, prevTopBlock, nextTopBlock),
						//  i == 0 ? prevTopBlock.get(2, k) : currentTopBlock.getIfExists(j-1, k),
						//  currentTopBlock.getIfExists(j, k+1),
						//  i == (N_TOP_BLOCKS-1) ? nextTopBlock.get(0, k) : currentTopBlock.getIfExists(j+1, k));
					}
				}
				// Otherwise: empty block.
				else
					newBlockOnTheBlock = emptyBlock;
				blocks[i][j][k] = newBlockOnTheBlock;
			}
		}
	}

	// Each top block.
	for (int top = 0, yOffset = 0; top < N_TOP_BLOCKS; top++) {
		// Each row.
		for (int row = 0; row < BLOCK_SIDE; row++, yOffset += BLOCK_SIDE) {
			// Each column.
			for (int col = 0, xOffset = 0; col < BLOCK_SIDE; col++, xOffset += BLOCK_SIDE) {
				// Get current block.
				GlyphBlock currentBlock = blocks[top][col][row];
				// Copy it into the matrix in the right spot.
				for (int x = 0; x < BLOCK_SIDE; x++) {
					for (int y = 0; y < BLOCK_SIDE; y++) {
						matrix[xOffset + x][yOffset + y] = currentBlock.get(x, y);
					}
				}
			}
		}
	}
}
