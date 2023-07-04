#include <stdio.h>
#include <linkedlist.h>
#include "hashtable.h"
#include <string.h>
#include <stdbool.h>
#include <commontypes.h>

int hashTableNew(struct Hashtable* target, int (*hasher) (void*), bool (*keyComparer) (void*, void*), void (*printNode) (struct LinkedListNode*)) {
	// create the linkedlist on heap for buckets
	target->buckets = malloc(INITIAL_HASHTABLE * sizeof(struct LinkedList*));
	EXIT_IF_MALLOC_FAIL(target->buckets);

	for (int i = 0; i < INITIAL_HASHTABLE; i++) {
		target->buckets[i] = NULL; // By setting the pointers as null explicily we
								   // make sure we can check bucket occupancy.
	}

	target->capacity = INITIAL_HASHTABLE;
	target->occupied = 0;
	target->hasher = hasher;
	target->comparer = keyComparer;

	target->deleteClosure = malloc(sizeof (struct DeleteFilterClosure));
	EXIT_IF_MALLOC_FAIL(target->deleteClosure);

	target->deleteClosure->filter = target->comparer;
	
	target->printNode = printNode;

	return 0;
}

int hashTableDestroy(struct Hashtable *table) {
	for (int i = 0; i < table->capacity; i++) {
		if (table->buckets[i] != NULL) {
			// destroy the linkedlist and explicitly free its memory.
			linkedListDestroy(table->buckets[i]);
			free(table->buckets[i]);
		}
	}
	free(table->buckets);
	table->capacity = 0;
	table->occupied = 0;
}

int hashTableSet(struct Hashtable* table, struct LinkedListNode* element) {
	double occupancyLoad = table->occupied/table->capacity;
	// rehash all existing key value pairs after resizing the underlying array
	if (occupancyLoad >= OCCUPANCY_THRESHOLD) {
		printf("Scale up internal data struture \n");

		// collect and redistribute the nodes from existing not null buckets that contain the linked list.
		struct LinkedList collection= { NULL, NULL };
		
		printf("Current internal array is of size %d \n", table->capacity);
		for (int i = 0; i < table->capacity ; i++) {
			if (table->buckets[i] == NULL) {
				printf("Bucket at %d is empty \n", i);
				continue;
			}
			
			printf("Bucket at %d is occupied \n", i);
			struct LinkedList* list = table->buckets[i];

			while (!linkedListIsEmpty(list)) {
				struct LinkedListNode* dataNode = linkedListPopLast(list);
				int added = linkedListAddToTail(&collection, dataNode); 
				if (added != 0) {
					return -1;
				}
				// linkedlist node can be destroyed, it has already been popped off and the data is copied into our dynamic array
				linkedListDestroyNode(dataNode);
			}
			
			printf("all node popped, destroying initial internal array \n");
			linkedListDestroy(list);
			printf("internal array destroyed \n");
		}
		
		printf("redistribution stage in scale up started \n");
	
		// increase size of our buckets to double
		struct LinkedList** newData = realloc(table->buckets, table->capacity *  2 * sizeof (struct LinkedList*));
		for (int i = table->capacity; i < table->capacity*2; i++) {
			newData[i] = NULL;
		}
		table->buckets = newData;

		EXIT_IF_MALLOC_FAIL(newData);
		table->capacity *= 2;
	
		printf("Internal array doubled in size to be %d \n", table->capacity);
		// at this point we have collected all our nodes and we want have enough buckets
		// now we begin redistribution
		struct LinkedListNode* rehashCandidate = linkedListPopLast(&collection);
		while (rehashCandidate != NULL) {
			int index = table->hasher((void*)rehashCandidate->key) % table->capacity;
			printf("node ");
			table->printNode(rehashCandidate);
			printf(" placed into %d \n", index);
	
			if (table->buckets[index] == NULL) {
				table->buckets[index] = malloc(sizeof(struct LinkedList));
			}

			int added = linkedListAddToTail(table->buckets[index], rehashCandidate);
			if (added != 0) {
				return -1;	
			}
			rehashCandidate = linkedListPopLast(&collection);
		}
	}

	int index = table->hasher((void*)element->key) % table->capacity;
	printf("Node ");
	table->printNode(element);
	printf(" being added at index %d \n", index);

	if (table->buckets[index] == NULL) {
		table->buckets[index] = malloc(sizeof(struct LinkedList));
	}
	int added = linkedListAddToTail(table->buckets[index], element);
	if (added != 0) {
		return -1;	
	}
	table->occupied++;
	return 0;
}

int hashTableGet(struct Hashtable* table, void* key, struct LinkedListNode* target) {
	// hash key and get the linkedlist
	int index = table->hasher(key) % table->capacity;
	printf("Get Node: Checking if node is present at %d \n", index);

	struct LinkedList* chain = table->buckets[index];
	// find the linkedlist based on key
	struct LinkedListNode* current = chain->head;
	while (current != NULL) {
		table->printNode(current);
		if (table->comparer(current->key, key)) {
			memcpy(target, current, sizeof(struct LinkedListNode));
			return 0;
		}
		current = current->next;
	}

	return -1;
}

int hashTableDelete(struct Hashtable* table, void* key) {
	// hash key and find the linkedlist
	int index = table->hasher(key) % table->capacity;

	struct LinkedList* chain = table->buckets[index];
	
	table->deleteClosure->captured = key;

	// use linkedListRemove function with filter to match keys here
	int removed = linkedListRemove(chain, table->deleteClosure);	
	if (removed > 0) {
		table->occupied -= removed;
		
		double occupancyLoad = table->occupied/table->capacity;
		// rehash all existing key value pairs after resizing the underlying array
		if (occupancyLoad < OCCUPANCY_THRESHOLD) {
			// TODO: DOWNSIZE

		}
	}

	return removed;
}
