#include <stdio.h>
#include <stdlib.h>

typedef struct Domino {
    int top, bottom;
} Domino;

typedef enum {false, true} bool;

void findBestChain(int handSize);
void getDominos(Domino *start, Domino *list, int amount);
int getChain(Domino *start, Domino *list, int *map, int amount);
int _getChain(Domino *start, Domino *list, int *tempMap, int *chainMap, bool *visited, int amount, int index, int maxSize);
bool dominoMatch(Domino* d1, Domino* d2);
void reverseDomino(Domino *d);
void printChain(Domino *list, int *chainMap, int amount);

int main(int argc, char *argv[]) {
    int handSize;
	Domino *dominos;
    Domino start;
    int *chainMap;
    int chainSize;
	
	if(argc - 1 != 1) {
		fprintf(stderr, "Expected one command line argument!\n");
		return 1;
	}
	
	handSize = atoi(argv[1]);
	
	if(handSize <= 0) {
		fprintf(stderr, "Argument must be a positive integer!\n");
		return 1;
	}
	
	dominos = malloc(handSize * sizeof(Domino));
	chainMap = malloc(handSize * sizeof(int));
	
    getDominos(&start, dominos, handSize);
    chainSize = getChain(&start, dominos, chainMap, handSize);
    printChain(dominos, chainMap, chainSize);
	
	free(dominos);
	free(chainMap);
    
    return 0;
}

void getDominos(Domino *start, Domino *list, int amount) {
    int i;
    
    printf("Enter starting domino (%%top %%bottom): ");
    scanf(" %i %i", &start->top, &start->bottom);
    
    printf("From your hand...\n");
    
    for(i = 0; i < amount; i++) {
        printf("Enter domino %i (%%top %%bottom): ", i + 1);
        scanf(" %i %i", &list[i].top, &list[i].bottom);
    }
}

int getChain(Domino *start, Domino *list, int *chainMap, int amount) {
    bool visited[amount];
    int tempMap[amount];
    int i;
    
    for(i = 0; i < amount; i++) {
        visited[i] = false;
    }
    
    return _getChain(start, list, tempMap, chainMap, visited, amount, 0, 0);
}

int _getChain(Domino *start, Domino *list, int *tempMap, int *chainMap, bool *visited, int amount, int index, int maxSize) {
    int i, attempt, result;
    Domino *former;
    
    if(index > maxSize) {
        for(i = 0; i < index; i++) {
            chainMap[i] = tempMap[i];
        }
        maxSize = index;
    }
    
    if(index == amount) {
        return amount;
    }
    
    for(i = 0; i < amount; i++) {
        if(!visited[i]) {
            for(attempt = 1; attempt <= 2; attempt++) {
                former = index == 0 ? start : list + tempMap[index - 1];
                if(dominoMatch(former, list + i)) {
                    tempMap[index] = i;
                    visited[i] = true;
                    result = _getChain(start, list, tempMap, chainMap, visited, amount, index + 1, maxSize);
                    if(result > maxSize) {
                        maxSize = result;
                    }
                    visited[i] = false;
                }
                reverseDomino(list + i);
            }
        }
    }
    
    return maxSize;
}

bool dominoMatch(Domino* d1, Domino* d2) {
    return d1->bottom == d2->top ||
        d1->bottom == 0 ||
        d2->top == 0;
}

void reverseDomino(Domino *d) {
    int temp = d->top;
    d->top = d->bottom;
    d->bottom = temp;
}

void printChain(Domino *list, int *chainMap, int amount) {
    int i;
    
    printf("Best chain: ");
    for(i = 0; i < amount; i++) {
        if(i > 0) {
            printf(", ");
        }
        printf("[%i %i]", list[chainMap[i]].top, list[chainMap[i]].bottom);
    }
    printf(".\n");
}
