/* 
 * Unit test 3: updateCoins
 *
 * Basic requirements:
 *      1) Adds one coin for each copper card in the current player's hand
 *      2) Adds two coins for each silver card in the current player's hand
 *      3) Adds three coins for each gold card in the current player's hand
 *      4) No state change should occur for any other players
 *      5) No state change should occur to the victory or kingdom card piles
 *
 */ 


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define TESTFUNCTION "updateCoins" 

int main()
{
        int i;
        struct gameState G, testG;
        int numPlayers = 2;
        int seed = 1000;
        int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
	int bonus;	
	int coppers[MAX_HAND], silvers[MAX_HAND], golds[MAX_HAND];

	for (i = 0; i < MAX_HAND; i++)
	{
		coppers[i] = copper;	
		silvers[i] = silver;
		golds[i] = gold;
	}

	// Initialize a new game
        initializeGame(numPlayers, k, seed, &G);
        printf("----------- Testing function: %s -----------\n", TESTFUNCTION);

	// ----------- TEST 1: Adds one coin for each copper card in current player's hand ----------- 
	printf("TEST 1: Adds one coin for each copper\n");
	for (i = 0; i < 5; i++)
	{
		for (bonus = 0; bonus < 10; bonus++)
		{
			memset(&G, 23, sizeof(struct gameState));
			initializeGame(numPlayers, k, seed, &G);
			G.handCount[0] = i;
			memcpy(G.hand[0], coppers, sizeof(int) * i);
			updateCoins(0, &G, bonus); 
			printf("Coin count = %d, expected = %d\n", G.coins, i + bonus);
			assert(G.coins == i + bonus);

			memcpy(G.hand[0], silvers, sizeof(int) * i);
			updateCoins(0, &G, bonus);
			printf("Coin count = %d, expected = %d\n", G.coins, i * 2 + bonus);
			assert(G.coins == i * 2 + bonus);
		}		
 	}	

	// ----------- TEST 2: Adds two coins for each silver card in current player's hand -----------
	printf("TEST 2: Adds two coins for each silver\n");
        for (i = 0; i < 5; i++)
        {
                for (bonus = 0; bonus < 10; bonus++)
                {
                        memset(&G, 23, sizeof(struct gameState));
                        initializeGame(numPlayers, k, seed, &G);
                        G.handCount[0] = i;
                        memcpy(G.hand[0], silvers, sizeof(int) * i);
                        updateCoins(0, &G, bonus);
                        printf("Coin count = %d, expected = %d\n", G.coins, i * 2 + bonus);
                        assert(G.coins == i * 2 + bonus);
                }
        }

	// ----------- TEST 3: Adds three coins for each gold card in current player's hand -----------
	printf("TEST 3: Adds three coins for each gold\n");
	        for (i = 0; i < 5; i++)
        {
                for (bonus = 0; bonus < 10; bonus++)
                {
                        memset(&G, 23, sizeof(struct gameState));
                        initializeGame(numPlayers, k, seed, &G);
                        G.handCount[0] = i;
                        memcpy(G.hand[0], golds, sizeof(int) * i);
                        updateCoins(0, &G, bonus);
                        printf("Coin count = %d, expected = %d\n", G.coins, i * 3 + bonus);
                        assert(G.coins == i * 3 + bonus);
                }
        }	

	// ----------- TEST 4: No state change should occur for any players ----------- 	
	printf("TEST 4: No state change should occur for any players\n");
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

	// ----------- TEST 5: No state change should occur to victory and kingdom card piles
 	printf("TEST 5: No state change should occur to victory and kingdom card piles\n");	

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

