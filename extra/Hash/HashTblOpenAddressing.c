#define MAXTABLESIZE 100000 	/* Maximum hashtable size */
typedef int ElementType;
typedef int Index; 		/* The element type of hash table address */
typedef Index Position;
typedef enum { Legitimate, Empty, Deleted } EntryType; 	/* Hash ceil status type */

typedef struct HashEntry Cell;
struct HashEntry {
	ElementType Data;
	EntryType Info;
};

typedef struct TblNode *HashTable;
struct TblNode {
	int TableSize; 	/* The maximum size of table */
	Cell *Cells; 	/* The array to store hash ceil */
};

/* Return a prime that is great than N and less than MAXTABLESIZE */
int NextPrime(int N)
{
	int i, p = (N%2)? N+2 : N+1; 	/* Start from an odd great than N */

	while (p <= MAXTABLESIZE) {
		for (i = (int)sqrt(p); i > 2; i--)
			if (!(p%i)) break; 	/* If p is not a prime */
		if (i == 2) break; 	/* for loop ends normally, p is a prime */
		else  p += 2; /* If not, try next odd */
	}
	return p;
}

HashTable CreateTable(int TableSize)
{
	HashTable H;
	int i;

	H = (HashTable) malloc(sizeof(struct TblNode));
	/* To make sure that the tablesize if a prime */
	H->TableSize = NextPrime(TableSize);
	/* Declaration of a ceil array */
	H->Cells = (Cell *) malloc(H->TableSize * sizeof(Cell));
	/* Initialize ceils to empty status */
	for (i = 0; i < H->TableSize; i++)
		H->Cells[i].Info = Empty;

	return H;
}

