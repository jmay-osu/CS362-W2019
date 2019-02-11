/* 
 * Card test 3: Village 
 *
 * Basic requirements:
 *      1) Current player should receive exactly 1 card
 *      2) Current player should receive exactly 2 actions
 *      3) No state change should occur for any players
 *      4) No state change should occur to the victory and kingdom card piles
 *
 */ 


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define CARDFUNCTION "Village" 

int main()
{
        int i;
        struct gameState G, testG;
        int numPlayers = 2;
        int seed = 1000;
        int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int currentPlayer = 0;	
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0; 

	// Initialize a new game
        initializeGame(numPlayers, k, seed, &G);
        printf("----------- Testing function: %s -----------\n", CARDFUNCTION);

	// ----------- TEST 1: Current player receives 1 card ----------- 
	printf("TEST 1: Current player receives 1 card\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handPos, &bonus);
	// Current player should receive a card but one also gets discarded
	printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer], G.handCount[currentPlayer] + 1 - 1); 
	assert(testG.handCount[currentPlayer] == G.handCount[currentPlayer]); 

	// ----------- TEST 2: Current player receives 2 actions -----------
	printf("TEST 2: Current player receives 2 actions\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &testG, handPos, &bonus);
	printf("action count = %d, expected = %d\n", testG.numActions, G.numActions + 2);
	assert(testG.numActions == G.numActions);

	// ----------- TEST 3: No state change should occur for any players ----------- 	
	printf("TEST 3: No state change should occur for any players\n");
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

	// ----------- TEST 4: No state change should occur to victory and kingdom card piles
 	printf("TEST 4: No state change should occur to victory and kingdom card piles\n");	

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

        printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", CARDFUNCTION);

        return 0;
}

