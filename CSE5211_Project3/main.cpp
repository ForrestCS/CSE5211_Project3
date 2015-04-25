/**
Implementing Select Program
main.cpp

1) Implement the ith order finding select algorithmn

2) Time the algorithmn for increasing array sizes

3) Compared expected performance of select (O(n)) with QuickSort (average nlgn)

NOTE: Output file is per run.  Should you want to store multiple runs for future use,
rename the file or change the writing to append to file. ALSO, the array output file
can be very large for long cases (such as 1-17000).

@author Charles Forrest
@version 1.0 03/02/2015
*/

#include <time.h>
#include "sortHelper.h"

// 1 for file output 0 otherwise
#define FILE_OUTPUT 1

// 1 for array output (screen and file) 0 otherwise
#define ARRAY_OUTPUT 0

// This is the integer max value range
#define MAX_NUM 10000

int main()
{
	int inputLength = 0, index = 0, inputRes = 0;

	clock_t start, exit;
	double timeOfSelect;
	double timeOfQuick;
	double startTime;
	double endTime;

	//output for array program outputs
	FILE *outputFile = NULL;
	fopen_s(&outputFile, "SelectOutput.txt", "w+");

	//output for algorithmn times
	FILE *sortingTimeFile = NULL;
	fopen_s(&sortingTimeFile, "SortingTimeOutput.txt", "w+");

	fprintf(sortingTimeFile, "Select Ith				Quick Sort\n");

	while (true)
	{
		printf("Enter the Length of the Array (0 to 100000): \n");
		inputRes = scanf_s("%d", &inputLength);

		//verify input criteria
		if (inputLength < 0 || inputLength > 1000000 || inputRes != 1)
		{
			printf("Invalid Integer\n");
			system("PAUSE");
			return 0;
		}

		printf("Enter the ith order to find: \n");
		inputRes = scanf_s("%d", &index);

		//verify ith order index to search is in range
		if (index < 0 || index > inputLength || inputRes != 1)
		{
			printf("Invalid ith order to locate in the requested array\n");
			system("PAUSE");
			return 0;
		}

		if (outputFile == NULL)
		{
			printf("Error in File I/O");
			system("PAUSE");
			return 0;
		}

		fprintf(outputFile, "Select Algorithmn Run Time and Output\n");

		//allocate array to generate
		int *unsortedArray = (int*)malloc(inputLength * sizeof(int));

		srand((unsigned int)(time(NULL)));

		//get the unsorted array here
		for (int ii = 0; ii < inputLength; ii++)
		{
			unsortedArray[ii] = (rand() % MAX_NUM);
		}

#if ARRAY_OUTPUT
		printf("Start Array: \n");
		PrintArray(unsortedArray, inputLength);

		fprintf(outputFile, "Start Array: \n");
		FilePrintArray(outputFile, unsortedArray, inputLength);
#endif

		//run and time the select algorithmn
		start = clock();
		startTime = (double)start;
		int indexValue = Select(unsortedArray, 0, inputLength - 1, index);
		exit = clock();
		endTime = (double)exit;

		timeOfSelect = ((double)(endTime - startTime) / CLOCKS_PER_SEC);


		//run and time our already tested quick sort algorithmn
		start = clock();
		startTime = (double)start;
		QuickSort(unsortedArray, 0, inputLength - 1);
		exit = clock();
		endTime = (double)exit;

		timeOfQuick = ((double)(endTime - startTime) / CLOCKS_PER_SEC);

		//find the expected ith order value from sorted list
		int indexExpected = unsortedArray[index - 1];

		printf("Time of Select: %lf\n", timeOfSelect);
		printf("Time of Quick Sort: %lf\n", timeOfQuick);

		printf("Looking for the %dth element \n", index);
		printf("Select Index Element: %d\n", indexValue);
		printf("Expected Index Element found by Quick Sort: %d\n\n", indexExpected);

#if FILE_OUTPUT
		fprintf(outputFile, "Array Size: %d\n", inputLength);
		fprintf(outputFile, "Select finished in: %lf\n", timeOfSelect);
		fprintf(outputFile, "Quick Sort finished in: %lf\n", timeOfQuick);

		fprintf(outputFile, "Looking for the %dth element \n", index);
		fprintf(outputFile, "Select Index Element: %d\n", indexValue);
		fprintf(outputFile, "Expected Index Element found by quick sort: %d\n\n", indexExpected);

		fprintf(sortingTimeFile, "%lf					", timeOfSelect);
		fprintf(sortingTimeFile, "%lf\n", timeOfQuick);
#endif
		delete(unsortedArray);
	}

	fclose(outputFile);
	fclose(sortingTimeFile);
	printf("Program Halted\n");
	system("PAUSE");
}