/* 
 * Unit test 4: isGameOver 
 *
 * Basic requirements:
 *      1) Game state changes if stack of province cards is empty
 *      2) Game state changes if three supply piles are empty
 *      3) No state change should occur to the victory and kingdom card piles
 *
 */ 


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTFUNCTION "isGameOver"

int main()
{
        int i;
        struct gameState G, testG;
        int numPlayers = 2;
        int seed = 1000;
        int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	
	// Initialize a new game
        initializeGame(numPlayers, k, seed, &G);
        printf("----------- Testing function: %s -----------\n", TESTFUNCTION);

	// ----------- TEST 1: Game state changes if stack of province cards is empty ----------- 
	printf("TEST 1: Game state changes if stack of province cards is empty\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	for (i = 0; i < 9; i++)
	{
		memset(&G, 23, sizeof(struct gameState));
		initializeGame(numPlayers, k, seed, &G);
		memcpy(&testG, &G, sizeof(struct gameState));
		printf("province count = %d\n", i);
		testG.supplyCount[province]--;
		G.supplyCount[province]--;
	}

	// ----------- TEST 2: No state change should occur for any players ----------- 	
	printf("TEST 2: No state change should occur for any players\n");
	for (i = 0; i < numPlayers; i++)
	{
		printf("Test player %d\n", i);
		// Clear the game state
                memset(&G, 23, sizeof(struct gameState));
                initializeGame(numPlayers, k, seed, &G);
                memcpy(&testG, &G, sizeof(struct gameState));
                printf("hand count = %d, expected = %d\n", testG.handCount[i], G.handCount[i]);
                assert(testG.handCount[i] == G.handCount[i]);
	}

	// ----------- TEST 3: No state change should occur to victory and kingdom card piles
 	printf("TEST 3: No state change should occur to victory and kingdom card piles\n");	

	// Check victory card piles
        printf("province count = %d, expected = %d\n", testG.supplyCount[province], G.supplyCount[province]);
        printf("duchy count = %d, expected = %d\n", testG.supplyCount[duchy], G.supplyCount[duchy]);
        printf("estate count = %d, expected = %d\n", testG.supplyCount[estate], G.supplyCount[estate]);
        assert(testG.supplyCount[estate] == G.supplyCount[estate]);
        assert(testG.supplyCount[duchy] == G.supplyCount[duchy]);
        assert(testG.supplyCount[province] == G.supplyCount[province]);

	// Checking kingdom card piles
  	for (int i = 0; i < 10; i++)
        {
                printf("Checking card %i = ", i);
                printf("card count = %d, expected = %d\n", testG.supplyCount[k[i]], G.supplyCount[k[i]]);
                assert(testG.supplyCount[k[i]] == G.supplyCount[k[i]]);
        }

        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNCTION);

        return 0;
}

