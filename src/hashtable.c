#include<stdio.h>
#include <linkedlist.h>
#include <hashtable.h>

int hashtableNew(struct Hashtable* target, int (*hasher) (void*)) {
	// create the linkedlist on heap for buckets
	target->buckets = malloc(INITIAL_HASHTABLE * sizeof(struct LinkedList));
	if (target->buckets == NULL) {
		return -1;
	}

	for (int i = 0; i < INITIAL_HASHTABLE; i++) {
		target->buckets[i] = NULL;
	}

	target->capacity = INITIAL_HASHTABLE;
	target->occupied = 0;
	target->hasher = hasher;
}

int hashTableDestroy(struct Hashtable *table) {
	for (int i = 0; i < table->capacity; i++) {
		free(table->buckets[i]);
	}
}

int hashTableSet(struct Hashtable* table, struct LinkedListNode* element) {
	// check occupancy load
	// if load at 80% rehash all existing keys.
	// then, hash the element by key and insert at that index.
}

int hashTableGet(struct Hashtable* table, void* key, struct LinkedListNode* target) {
	// hash key and get the linkedlist
	// find the linkedlist based on key
	// if it exists copy the data to target
}

int hashTableDelete(struct Hashtable* table, void* key) {
	// hash key and find the linkedlist
	// call delete
}
