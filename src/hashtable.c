#include <stdio.h>
#include <linkedlist.h>
#include "hashtable.h"

int hashtableNew(struct Hashtable* target, int (*hasher) (void*)) {
	// create the linkedlist on heap for buckets
	target->buckets = malloc(INITIAL_HASHTABLE * sizeof(struct LinkedList*));
	if (target->buckets == NULL) {
		return -1;
	}

	for (int i = 0; i < INITIAL_HASHTABLE; i++) {
		target->buckets[i] = NULL; // By setting the pointers as null explicily we
								   // make sure we can check bucket occupancy.
	}

	target->capacity = INITIAL_HASHTABLE;
	target->occupied = 0;
	target->hasher = hasher;
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
		// collect and redistribute the nodes from existing not null buckets that contain the linked list.
		struct LinkedList collection= { NULL, NULL };
	
		for (int i = 0; i < table->capacity; i++) {
			if (table->buckets[i] == NULL) {
				continue;
			}

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

			linkedListDestroy(list);
		}
		
		// increase size of our buckets to double
		struct LinkedList* newData = realloc(table->buckets, table->capacity *  2 * sizeof (struct LinkedList*));

		// at this point we have collected all our nodes and we want have enough buckets
		// now we begin redistribution
		struct LinkedListNode* rehashCandidate = linkedListPopLast(&collection);
		while (rehashCandidate != NULL) {
			int index = table->hasher((void*)element) % table->capacity;
			if (table->buckets[index] == NULL) {
				table->buckets[index] = malloc(sizeof(struct LinkedList));
			}
			int added = linkedListAddToTail(table->buckets[index], element);
			if (added != 0) {
				return -1;	
			}
			rehashCandidate = linkedListPopLast(&collection);
		}
	}

	int index = table->hasher((void*)element) % table->capacity;
	if (table->buckets[index] == NULL) {
		table->buckets[index] = malloc(sizeof(struct LinkedList));
	}
	int added = linkedListAddToTail(table->buckets[index], element);
	if (added != 0) {
		return -1;	
	}

	return 0;
}

int hashTableGet(struct Hashtable* table, void* key, struct LinkedListNode* target) {
	// hash key and get the linkedlist
	// find the linkedlist based on key
	// if it exists copy the data to target
	return 0;
}

int hashTableDelete(struct Hashtable* table, void* key) {
	// hash key and find the linkedlist
	// call delete
	return 0;
}
