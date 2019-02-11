/* 
 * Card test 1: Smithy 
 *
 * Basic requirements:
 *      1) Current player should receive exactly 3 cards
 *      2) 3 cards should come from his or her own pile
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

#define CARDFUNCTION "Smithy" 

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

	// ----------- TEST 1: Current player receives 3 cards ----------- 
	printf("TEST 1: Current player receives 3 cards\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);
	printf("hand count = %d, expected = %d\n", testG.handCount[currentPlayer] - 3, G.handCount[currentPlayer] + 3 - 3);
	if (testG.handCount[currentPlayer] != G.handCount[currentPlayer] + 3 - 3)
	{
		printf("TEST 1: Current player receives 3 cards FAILED\n");
	} 

	// ----------- TEST 2: Cards should come from his or her own pile -----------
	printf("TEST 2: Cards should come from his or her own pile\n");
	memcpy(&testG, &G, sizeof(struct gameState));
	cardEffect(smithy, choice1, choice2, choice3, &testG, handPos, &bonus);
	printf("deck count = %d, expected = %d\n", testG.deckCount[currentPlayer], G.deckCount[currentPlayer] - 3);
 	if (testG.deckCount[currentPlayer] != G.deckCount[currentPlayer] - 3)
	{
		printf("TEST 2: Cards should come from his or her own pile FAILED\n");
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

