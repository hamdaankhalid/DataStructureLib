# ifndef COMMONTYPES_H 
# define COMMONTYPES_H

# include <stdbool.h>
# include <stdio.h>

// Just a quick macro to handle malloc conditional error handling
# define EXIT_IF_MALLOC_FAIL(d) \
	if (d == NULL) { \
        fprintf(stderr, "Error allocating memory\n"); \
        return -1; \
	}


// Used by linked list and Hash tables
struct LinkedListNode {
	unsigned int sizeOfKey;
	unsigned int sizeOfValue;
	void* key;
	void* value;
	struct LinkedListNode* next;
};

// Used by linked list and Hash tables
// capture and variable should be of the type associated with the key of the linkedListNodes that are attached with each hashtable
struct DeleteFilterClosure {
	void* captured;
	void* variable;
	bool (*filter) (void* fixed, void* var);
};

# endif
