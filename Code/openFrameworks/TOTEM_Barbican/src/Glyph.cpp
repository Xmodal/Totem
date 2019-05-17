#include "Glyph.h"
#include <iostream>

Glyph::Glyph(const GlyphBlockFactory& topFactory, const GlyphBlockFactory& subFactory)
{
	// Create top-level blocks.
	for (int i = 0; i < N_TOP_BLOCKS; i++) {
		topBlocks[i] = topFactory.create();

		// For each column j inside top-block.
		for (int j = 0; j < BLOCK_SIDE; j++) {
			// For each row k inside top-block.
			for (int k = 0; k < BLOCK_SIDE; k++) {
				// The latent block that exists there.
				blocks[i][j][k] = subFactory.create();
			}
		}
	}

	build();
}

void Glyph::build() {
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

				// Default block if sub-block is not activated.
				defaultBlocks[i][j][k] =
				  (topBlocks[i].get(j, k) ?
            GlyphBlock(
							currentTopBlock.getIfExists(j-1, k), // left
							currentTopBlock.getIfExists(j, k-1, prevTopBlock, nextTopBlock), // top
							currentTopBlock.getIfExists(j+1, k), // right
							currentTopBlock.getIfExists(j, k+1, prevTopBlock, nextTopBlock)) // bottom
							:
							emptyBlock);
			}
		}
	}
}

void Glyph::update(float activationThreshold) {
	// Each top block.
	for (int top = 0, yOffset = 0; top < N_TOP_BLOCKS; top++) {
		// Each row.
		for (int row = 0; row < BLOCK_SIDE; row++, yOffset += BLOCK_SIDE) {
			// Each column.
			for (int col = 0, xOffset = 0; col < BLOCK_SIDE; col++, xOffset += BLOCK_SIDE) {
				// Get current block.
				GlyphBlock& currentBlock = blocks[top][col][row];
				if (! currentBlock.isActivated(activationThreshold))
					currentBlock = defaultBlocks[top][col][row];
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

void Glyph::evolveTopBlock(const GlyphBlockFactory& topFactory, int topBlockIndex, float mutationRate) {
	if (GlyphBlockFactory::random01() < mutationRate) {
		topBlocks[topBlockIndex] = topFactory.create();
		build();
	}
}

void Glyph::evolveSubBlock(const GlyphBlockFactory& subFactory, int topBlockIndex, int x, int y, float mutationRate) {
	if (GlyphBlockFactory::random01() < mutationRate) {
		blocks[topBlockIndex][x][y] = subFactory.create();
		build();
	}
}
