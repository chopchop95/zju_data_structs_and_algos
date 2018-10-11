/* Radix sort - least significant digit first */

/* Assume that there are MaxDigit key and the radix is same */
#define MaxDigit 4
#define Radix 10

/* Bucket element node */
typedef struct Node *PtrToNode;
struct Node {
	int key;
	PtrToNode next;
};

/* Bucket head node */
struct HeadNode {
	PtrToNode head, tail;
};
typedef struct HeadNode Bucket[Radix];

/* LSD=1 by default, MSD <= MaxDigit */
int GetDigit(int X, int D)
{
	int d, i;

	for (i = 1; i <= D; i++) {
		d = X % Radix;
		X /= Radix;
	}
	return d;
}

/* Radix sort - LSD first */
void LSDRadixSort(ElementType A[], int N)
{
	int D, Di, i;
	Bucket B;
	PtrToNode tmp, p, List = NULL; 

	for (i = 0; i < Radix; i++)		/* Initialize every bucket as a empty list */
		B[i].head = B[i].tail = NULL;
	for (i = 0; i < N; i++) {	/* Store the original sequence into the initilized List in reversed order */
		tmp = (PtrToNode) malloc(sizeof(struct Node));
		tmp->key = A[i];
		tmp->next = List;
		List = tmp;
	}
	/* Start to sort */ 
	for (D = 1; D <= MaxDigit; D++) {	/* Process every digit of data in a loop */
		/* Distribution process */
		p = List;
		while (p) {
			Di = GetDigit(p->key, D);	/* Get the current digit of the current element */
			/* Remove from List */
			tmp = p; p = p->next;
			/* Insert into the tail of B[Di] bucket */
			tmp->next = NULL;
			if (B[Di].head == NULL)
				B[Di].head = B[Di].tail = tmp;
			else {
				B[Di].tail->next = tmp;
				B[Di].tail = tmp;
			}
		}
		/* Collecting process */
		List = NULL; 
		for (Di = Radix-1; Di >= 0; Di--)	/* Collect elements in every bucket into List in order */
			if (B[Di].head) {	/* If the bucket is not empty */
				/* Insert the whole bucket into the head of List */
				B[Di].tail->next = List;
				List = B[Di].head;
				B[Di].head = B[Di].tail = NULL;		/* Empty the bucket */
			}
	}
	/* Move elements from List to A[] and free memory */
	for (i = 0; i < N; i++) {
		tmp = List;
		List = List->next;
		A[i] = tmp->key;
		free(tmp);
	} 
}

