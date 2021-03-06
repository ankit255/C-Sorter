#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "readlines.h"

#define MAXLINES 5000
char *lineptr[MAXLINES];

void Qsort(void *lineptr[], int left, int right,
	int (*comp)(void *, void *));

void rev(void *lineptr[], int nlines);

int numcmp(char *, char *);

main(int argc, char *argv[])
{
	int nlines;
	int numeric = 0, reverse = 0;
	int c;

	
	//if (argc > 1 && strcmp(argv[1], "-n"))
		//numeric=1;

	while (--argc>0 && (*++argv)[0]=='-') {
		while (c = *++argv[0]) {
			switch (c)
			{
				case 'n': numeric=1;
				break;
				case 'r': reverse=1;
				break;
				default:
				argc=0;
				break;
			}
		}
	}
	if (argc!=0) {
		printf("%s\n", "Usage: Sorter -r -n");
		return -1;
	}
	if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
		Qsort((void **)lineptr, 0, nlines-1, 
			(int (*)(void *, void *))(numeric ? numcmp : strcmp));
		if (reverse)
			rev(lineptr, nlines);
		writelines(lineptr, nlines);
		return 0;
	}
	else {
		printf("Input too big to sort\n");
		return 1;
	}
}

void rev(void *lineptr[], int nlines)
{
	int i = nlines -1;
	int j =0;

	while (i>j)
	{
		char *tmp = lineptr[i];
		lineptr[i] = lineptr[j];
		lineptr[j] = tmp;
		i--;
		j++;
	}
	// void *arr[nlines];
	// while(nlines-- >= 0) {
	// 	*arr[i] = *lineptr[nlines];
	// }
	// lineptr = arr;
}

void Qsort(void *v[], int left, int right, 
	int (*comp)(void *, void *)) {


	int i, last;
	void swap(void *v[], int, int);
	if(left>=right)
		return;

	swap(v, left, (left+right)/2);
	last = left;

	for (i = left+1; i<=right; i++) {
		if ((*comp)(v[i], v[left])< 0)
			swap(v, ++last, i);
	}

	swap(v, left, last);
	Qsort(v, left, last-1, comp);
	Qsort(v, last+1, right, comp);

}

int numcmp(char *s1, char *s2)
{
	double v1, v2;

	v1 = atof(s1);
	v2 = atof(s2);

	if (v1<v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

void swap(void *v[], int i, int j)
{
	void *temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}