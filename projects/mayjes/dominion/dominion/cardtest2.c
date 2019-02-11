/* 
 * Card test 2: Adventurer 
 *
 * Basic requirements:
 *      1) Exactly 3 treasure cards drawn for current player
 *      2) All drawn cards are discarded
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

#define CARDFUNCTION "Adventurer"

int main()
{
        int i;
        struct gameState G, testG;
        int numPlayers = 2;
        int seed = 1000;
        int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int currentPlayer = 0;

	// Initialize a new game
        initializeGame(numPlayers, k, seed, &G);
        printf("----------- Testing function: %s -----------\n", CARDFUNCTION);

	// ----------- TEST 1: Exactly two treasure cards drawn ----------- 
	printf("TEST 1: Exactly two treasure cards drawn\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	int drawnTreasure = 0;
	for (i = 0; i < testG.handCount[currentPlayer]; i++)
	{
		int drawnCard = testG.hand[currentPlayer][i];
		if (drawnCard == copper || drawnCard == silver || drawnCard == gold)
		{
			drawnTreasure++;
		}
	} 
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);
	printf("treasure count = %d, expected = %d\n", drawnTreasure, 2);
	if (drawnTreasure != 2)
	{
		printf("TEST 1: Exactly two treasure cards drawn FAILED\n");
	}
	
	// ----------- TEST 2: All drawn cards are discarded -----------
	printf("TEST 2: All drawn cards are discarded\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &testG, handPos, &bonus);
	printf("discard count = %d, expected = %d\n", testG.discardCount[currentPlayer], G.discardCount[currentPlayer]);
	if (testG.discardCount[currentPlayer] != G.discardCount[currentPlayer])
	{
		printf("TEST 2: All drawn cards are discarded FAILED\n");
	} 

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

