#include <stdio.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
    struct RecordType* next;
};

struct HashType
{
    // create a pointer to a RecordType
    struct RecordType* head;
};

// Compute the hash function
int hash(int x, int tableSize)
{
    // hash function is x % tableSize
  return x % tableSize;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// insert record into the hash table
void insertRecord(struct HashType *hashTable, struct RecordType *record, int tableSize)
{
    // call the hash function to get the index
    // if the RecordType at that index is NULL
        // set 'record' equal to the HashType pointer in the table at index
    // else
        // traverse to the end of the linkedlist and add 'record' to the end of it
    // Call the hash function to get the index
     // Call the hash function to get the index
    // Call the hash function to get the index
    int index = hash(record->id, tableSize);

    // If the RecordType at that index is NULL, set 'record' equal to the HashType pointer in the table at index
    if (hashTable[index].head == NULL)
    {
        hashTable[index].head = record;
    }
    else
    {
        // Traverse to the end of the linkedlist and add 'record' to the end of it
        struct RecordType *current = hashTable[index].head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = record;
    }

}
void displayRecordsInHash(struct HashType *hashTable, int tableSize)
{
    // for each entry in the table
        // print the contents in that index
        // The output should look like this (for example): "Index 1 -> 21715, Q, 16 -> 28876, a, 26 -> NULL"
         printf("\nRecords in Hash Table:\n");
    for (int i = 0; i < tableSize; i++)
    {
        if (hashTable[i].head != NULL)
        {
            printf("Index %d -> ", i);
            struct RecordType *current = hashTable[i].head;
            while (current != NULL)
            {
                printf("%d, %c, %d -> ", current->id, current->name, current->order);
                current = current->next;
            }
            printf("NULL\n");
        }
    }
    printf("\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    int hashTableSize = 10;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize the hash table
    // create a variable hashTableSize and assign it a value
    // initialize a hashTable, use calloc (so everything is assigned to NULL)
    // for each record in pRecords, insert it into the hash table using the insertRecord function
    // call the display records function
    // free all the allocated memory
   // Initialize the hash table
     // Initialize the hash table
    struct HashType *hashTable = calloc(hashTableSize, sizeof(struct HashType));

    for (int i = 0; i < recordSz; i++) {
        insertRecord(hashTable, &pRecords[i], hashTableSize);
    }

    displayRecordsInHash(hashTable, hashTableSize);

  
    free(pRecords);

   for (int i = 0; i < hashTableSize; i++) {
        struct RecordType *current = hashTable[i].head;
        while (current != NULL) {
            struct RecordType *temp = current;
            current = current->next;
            free(temp);
        }
    }
    free(hashTable);

  

    return 0;
}
