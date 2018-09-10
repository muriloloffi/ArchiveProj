#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
const int MAX = 1024; 

/* inserts <value> into <sorted> containing <count> values */ 
void insert_sorted (long *sorted, int count, long value) { 
int i = 0; 

sorted[count] = value;
if (count == 0) return; 
	for (i = count;i >= 0; i--) { 
		if (value < sorted[i-1]) 
			sorted[i] = sorted[i-1]; 
		else break; 
	}
	sorted[i] = value; 
} 

int main (int argc, char *argv[]) { 
	FILE *fp = NULL; 
	long sorted[1024]; 
	long value; 
	int count = 0; 
	int i = 0; 
	
	if (argc < 2) { 
		fprintf (stderr, ""Usage : %s <file_name>\n"", argv[0]); 
	return 1; 
	} 
	
	fp = fopen (argv[1], ""r""); 
	
	if (NULL == fp) { 
		perror (""fopen""); 
	return -1; 
	} 
	
	
	while (!feof (fp)) { 
		fscanf (fp, ""%ld\n"", &value); /* pega valorese */ 
		insert_sorted (sorted, count, value); /* sort */ 
		++count; /* aumenta valor do sort */ 
	} 	

	
	printf (""Sorted values : ""); 
	for (i = 0; i < count; i++ ) { 
		printf (""%ld "", sorted[i]); 
	} 

	/* cleanup */ 
	if (fp) { 
		fclose (fp); 
		fp = NULL; 
	} 
	return 0; 
}


