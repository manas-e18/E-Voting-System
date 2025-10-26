#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_VOTERS 100
#define CANDIDATE_COUNT 5

int main(void) {
    int voterIDs[MAX_VOTERS];
    int votes[CANDIDATE_COUNT] = {0};
    const char *candidates[CANDIDATE_COUNT] = {
        "Ayush",
        "Aditya",
        "Sujata",
        "Pratham",
        "Emily"
    };
    int totalVoters = 0;
    char continueChoice = 'y';

    printf("\nWelcome to the E-Voting System\n");

    while ((continueChoice == 'y' || continueChoice == 'Y') && totalVoters < MAX_VOTERS) {
        int id;
        printf("\nPlease enter your voter ID (integer): ");
        if (scanf("%d", &id) != 1) {
            printf("Invalid input. Please enter numeric voter ID.\n");
            while (getchar() != '\n') {}
            continue;
        }

        bool alreadyVoted = false;
        for (int i = 0; i < totalVoters; i++) {
            if (voterIDs[i] == id) {
                alreadyVoted = true;
                break;
            }
        }

        if (alreadyVoted) {
            printf("You have already voted. Duplicate votes are not allowed.\n");
        } else {
            if (totalVoters < MAX_VOTERS) {
                voterIDs[totalVoters++] = id;
            } else {
                printf("Voter list full. Cannot accept more voters.\n");
                break;
            }

            printf("\nCandidates:\n");
            for (int i = 0; i < CANDIDATE_COUNT; i++) {
                printf(" %d. %s\n", i + 1, candidates[i]);
            }

            int choice;
            printf("Enter the number of your chosen candidate (1-%d): ", CANDIDATE_COUNT);
            if (scanf("%d", &choice) != 1) {
                printf("Invalid choice. Vote discarded.\n");
                while (getchar() != '\n') {}
            } else if (choice < 1 || choice > CANDIDATE_COUNT) {
                printf("Choice out of range. Vote discarded.\n");
            } else {
                votes[choice - 1]++;
                printf("Thank you. your vote for %s has been recorded.\n", candidates[choice - 1]);
            }
        }

        printf("\nWould you like to allow another voter? (y/n): ");
        while (getchar() != '\n') {}
        continueChoice = getchar();
        while (getchar() != '\n') {}
    }

    printf("\nElection results:\n");
    for (int i = 0; i < CANDIDATE_COUNT; i++) {
        printf(" %d. %-15s : %d\n", i + 1, candidates[i], votes[i]);
    }

    int maxVotes = votes[0];
    for (int i = 1; i < CANDIDATE_COUNT; i++) {
        if (votes[i] > maxVotes) maxVotes = votes[i];
    }

    int winners[CANDIDATE_COUNT];
    int winnerCount = 0;
    for (int i = 0; i < CANDIDATE_COUNT; i++) {
        if (votes[i] == maxVotes) {
            winners[winnerCount++] = i;
        }
    }

    if (maxVotes == 0) {
        printf("\nNo votes were cast.\n");
    } else if (winnerCount == 1) {
        printf("\nWinner: %s with %d votes\n", candidates[winners[0]], maxVotes);
    } else {
        printf("\nIt's a tie between:\n");
        for (int i = 0; i < winnerCount; i++) {
            printf(" - %s\n", candidates[winners[i]]);
        }
        printf("Each has %d votes\n", maxVotes);
    }

    printf("\nTotal voters who cast at least one vote: %d\n", totalVoters);
    printf("Thank you for using the E-Voting System.\n");
    return 0;
}
