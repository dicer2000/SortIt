// SortIt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

/************************************************************************\
*                     PREPROCESSOR DECLARATIONS                          *
\************************************************************************/
#include <iostream>
#include <stdio.h>     /* for legacy I/O functions (printf, scanf)      */
#include <time.h>      /* for timing information                        */
using namespace std;


#define MAXLISTLENGTH 10000000 /* maximum length of list to be sorted */
#define NAMELENGTH         15  /* maximum length of a name            */
#define PRINTABLE_LENGTH  200  /* longest printed list                */
/************************************************************************\
*                              TYPEDEFS                                  *
\************************************************************************/

typedef char NAME_IN[NAMELENGTH];   /* name input                       */
typedef long int  ID_IN;            /* identifying number input         */
typedef int  BOOLEAN;               /* TRUE (1) or false (0)            */

typedef struct {               /* structure to hold name and id         */
	NAME_IN lastName;         /* the last name                         */
	NAME_IN firstName;        /* the first name                        */
	ID_IN  id;                 /* the identifying number                */
} NAMECELL;

/************************************************************************\
*                           GLOBAL VARIABLES                             *
\************************************************************************/

NAMECELL name_list[MAXLISTLENGTH];  /* list of names and numbers     */

/************************************************************************\
*                                                                        *
*                              MAIN PROGRAM                              *
*                                                                        *
*   This program builds a list of name cells containing names and        *
*   indentifying numbers.  It then sorts this list by name or id. as     *
*   requested by the user.                                               *
*                                                                        *
\************************************************************************/

int main()
{
	char choice;                    /*  to hold selection during entry    */
	bool quit = false;              /*  to indicate choice to quit        */
	int list_length = 0;            /*  current length of the list        */

									/* function declarations */
	void menu(void);
	void get_entry(int *length);
	void get_sort_choice(char *c);
	void fill_list(int *length);
	void isort_list_name(int *length);
	void isort_list_id(int *length);
	void print_list(int *length);

	system("cls"); // clear screen
	menu();
	while (!quit)
	{
		cout << ":) ";
		cin >> choice;
		switch (toupper(choice))
		{
		case 'A': get_entry(&list_length);        break;
		case 'E': list_length = 0; cout << "The list is now empty.\n"; break;
		case 'F': fill_list(&list_length);
			if (list_length <= PRINTABLE_LENGTH) print_list(&list_length); break;
		case 'I':  isort_list_id(&list_length);
			print_list(&list_length);       break;
		case 'N':  isort_list_name(&list_length);
			print_list(&list_length);       break;
		case 'P': print_list(&list_length);       break;
		case 'S':  isort_list_name(&list_length); break;
		case 'T':  isort_list_id(&list_length); break;
		case 'Q': quit = true;                    break;
		default: cout << choice << " is not a valid choice\n"; menu();
		}
	}
	cout << ("\nBye for now!\n");
}

/************************************************************************\
*                               FUNCTIONS                                *
\************************************************************************/

void menu(void) {
	printf("\nChoose:  A     Add another name to the list.");
	printf("\n         E     Empty the list.");
	printf("\n         F     Fill list randomly to a specific length.");
	printf("\n         P     Print the list.");
	printf("\n         N     Sort list by name and print.");
	printf("\n         I     Sort list by id. number and print.");
	printf("\n         S     Sort list by name without printing.");
	printf("\n         T     Sort list by id. without printing.");
	printf("\n         Q     Quit this program.\n");
}

/************************************************************************/
void get_entry(int *length)   /* get next student entry */
							  /* length: current length of list */
{
	if (*length < MAXLISTLENGTH - 1)
	{
		printf("\nPlease type in the last name: ");
		scanf_s("%s", name_list[*length].lastName, NAMELENGTH);
		printf("Now, type in the first name: ");
		scanf_s("%s", name_list[*length].firstName, NAMELENGTH);
		printf("And finally, the student identification: ");
		scanf_s("%d", &name_list[*length].id);
		(*length)++;
	}
	else
	{
		printf("\nSorry, the list is too long to add another name.\n");
	}
}

/************************************************************************/

/************************************************************************/
void fill_list(int *length)  /*  randomly fill list */
							 /*length: current length of list */
{
	char	name_tmp[NAMELENGTH];
	int 	n, new_length, name_length;

	printf("How long would you like the list to be?  ");
	scanf_s(" %d", &new_length);
	while (new_length > MAXLISTLENGTH) {
		printf("Sorry, we cannot build a list longer than %d.\n", MAXLISTLENGTH);
		printf("Try a smaller value for the length: ");
		scanf_s(" %d", &new_length);
	}
	for (; *length < new_length; ++*length) {
		name_length = 3 + rand() % (NAMELENGTH - 4);
		name_tmp[0] = rand() % 26 + 'A';
		for (n = 1; n < name_length; n++) name_tmp[n] = rand() % 26 + 'a';
		name_tmp[n] = '\0';
		strcpy_s(name_list[*length].lastName, name_tmp);
		strcpy_s(name_list[*length].firstName, name_tmp);
		name_list[*length].id = rand();
	}
}

/************************************************************************/
int nameCompareFcn(const void *vpFirst, const void *vpSecond) {
	const NAMECELL *pCell1 = (const NAMECELL *)vpFirst, *pCell2 = (const NAMECELL *)vpSecond;
	return strcmp(pCell1->lastName, pCell2->lastName);
} /* nameCompareFcn() */


/************************************************************************/

int idCompareFcn(const void *vpFirst, const void *vpSecond) {
	const NAMECELL *pCell1 = (const NAMECELL *)vpFirst, *pCell2 = (const NAMECELL *)vpSecond;

	if (pCell1->id < pCell2->id) return -1;
	if (pCell1->id > pCell2->id) return  1;
	return 0;
} /* idCompareFcn() */


/************************************************************************/
void isort_list_name(int *length) /* insertion sort of the list by name */
{
	NAMECELL temp;           /* store cell temporarily */
	int i, j, k;

	clock_t CPU_time;
	CPU_time = clock();

	for (i = 1; i <= *length - 1; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (strcmp(name_list[i].lastName, name_list[j].lastName) < 0)
				/* insert the ith member of the list here      */
			{
				temp = name_list[j];
				name_list[j] = name_list[i];
				for (k = i; k > j; --k)
				{
					name_list[k] = name_list[k - 1];
				}
				name_list[j + 1] = temp;
			}
		}
	}

	CPU_time = clock() - CPU_time;
	printf("CPU time to isort %d records by name: %1.3f seconds.\n",
		*length, (float)CPU_time / CLOCKS_PER_SEC);
}

/************************************************************************/
void isort_list_id(int *length) /* insertion sort of the list by id. number */
{
	NAMECELL temp;           /* store cell temporarily */
	int i, j, k;

	clock_t CPU_time;
	CPU_time = clock();

	for (i = 1; i <= *length - 1; i++)
	{
		for (j = 0; j < i; j++)
		{
			if (name_list[i].id < name_list[j].id)
				/* insert the ith member of the list here      */
			{
				temp = name_list[j];
				name_list[j] = name_list[i];
				for (k = i; k > j; --k)
				{
					name_list[k] = name_list[k - 1];
				}
				name_list[j + 1] = temp;
			}
		}
	}

	CPU_time = clock() - CPU_time;
	printf("CPU time to isort %d records by id: %1.3f seconds.\n",
		*length, (float)CPU_time / CLOCKS_PER_SEC);
}
/************************************************************************/
void print_list(int *length) /* print the whole list  */
{
	int i;
	int few = 7;

	if (*length > 20) {
		printf("This list is too long (%d records). Here's the first few and last few.\n", *length);
		printf("Last Name, First Name, Student Id.\n\n");
		for (i = 0; i < few; i++)
		{
			printf("%s, ", name_list[i].lastName);
			printf("%s, %-8d\n", name_list[i].firstName, name_list[i].id);
		}
		printf(". . . . . . .\n");
		for (i = *length - few; i < *length; i++)
		{
			printf("%s, ", name_list[i].lastName);
			printf("%s, %-8d\n", name_list[i].firstName, name_list[i].id);
		}
		return;
	}

	printf("Last Name, First Name, Student Id.\n\n");
	for (i = 0; i <= *length - 1; i++)
	{
		printf("%s, ", name_list[i].lastName);
		printf("%s, %-8d\n", name_list[i].firstName, name_list[i].id);
	}
}