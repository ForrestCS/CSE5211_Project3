/**
sortHelper.cpp
This class file contains various functions used for the implementation of the
select and quick sort algorithmns.

@author Charles Forrest
@version 1.0 03/02/2015
*/

#include "sortHelper.h"

/*
* This function is used to find the median of medians the given array
*
* @param arrayToSort input as reference array to sort
* @param startOfArray start of the array to sort
* @param endOfArray end of the array to sort
* @return int median value found
*/
int MedianOfMedians(int arrayToSort[], int startOfArray, int endOfArray)
{
 	int ii = 0;

	//get the number of groups.. this will ignore the last array of size < 5
	int numGroups = (int)floor(((endOfArray - startOfArray) - 1) / 5);
	int *medianArray = (int*)malloc((numGroups + 1) * sizeof(int));
	int *tempArray = (int*)malloc(5 * sizeof(int));

	memset(medianArray, 0, (numGroups + 1) * sizeof(int));
	memset(tempArray, 0, (5 * sizeof(int)));

	for (ii = 0; ii <= numGroups; ii++)
	{
		int kk = 0;

		for (int jj = startOfArray + (ii * 5); jj < (startOfArray + (ii * 5 + 5)); jj++)
		{
			tempArray[kk] = arrayToSort[jj];
			kk++;
		}

		//if our element total is less than 5, we cant sort the whole 5 elements
		//either way we get the middle element
		if ((endOfArray - startOfArray) < 5)
		{
			QuickSort(tempArray, 0, (endOfArray - startOfArray));
			int index = (int)floor((endOfArray - startOfArray) / 2);
			medianArray[ii] = tempArray[index];
		}
		else
		{
			QuickSort(tempArray, 0, 4);
			medianArray[ii] = tempArray[2];
		}
	}

	//sort of the median array generated from the sub groups
	QuickSort(medianArray, 0, numGroups - 1);

	//return middle element of sorted array
	int medianIndex = (int)floor(numGroups / 2);
	return medianArray[medianIndex];
}

/*
* This function calls a select search of the given array,
* based on the provided index
*
* @param arrayToSort input as reference array to sort
* @param startOfArray start of the array to sort
* @param endOfArray end of the array to sort
* @param index ith order element to find
* @return int the value of the ith order index
*/
int Select(int arrayToSort[], int startOfArray, int endOfArray, int index)
{
	int k = 0, q = 0;
	int medianValue = 0, pivot = 0;

 	if (startOfArray == endOfArray)
	{
		return arrayToSort[endOfArray];
	}

	medianValue = MedianOfMedians(arrayToSort, startOfArray, endOfArray);

	pivot = SelectPartition(arrayToSort, startOfArray, endOfArray, medianValue);

	if (pivot == (index - 1))
	{
		return arrayToSort[pivot];
	}
	else if (pivot > (index - 1))
	{
		return Select(arrayToSort, startOfArray, pivot - 1, index);
	}
	else
	{
		return Select(arrayToSort, pivot + 1, endOfArray, index);
	}
}

/*
* This function calls a quick sort of the given array
*
* @param arrayToSort input as reference array to sort
* @param startOfArray start of the array to sort
* @param endOfArray end of the array to sort
* @return N/A
*/
void QuickSort(int arrayToSort[], int startOfArray, int endOfArray)
{
	if (startOfArray < endOfArray)
	{
		//find the new pivot and recurse until we get to the base case
		int pivot = Parition(arrayToSort, startOfArray, endOfArray);
		QuickSort(arrayToSort, startOfArray, pivot - 1);
		QuickSort(arrayToSort, pivot + 1, endOfArray);
	}
}

/*
* This function paritions the array based on the end element
*
* @param arrayToSort input as reference array to sort
* @param startOfArray start of the array to sort
* @param endOfArray end of the array to sort
* @return parition element chosen
*/
int Parition(int arrayToSort[], int startOfArray, int endOfArray)
{
	int tempValue;
	int x = arrayToSort[endOfArray];
	int ii = startOfArray - 1;

	//go through the array
	for (int jj = startOfArray; jj < endOfArray; jj++)
	{
		//if the next index is less than x, put it on the left side of x
		if (arrayToSort[jj] <= x)
		{
			ii = ii + 1;
			tempValue = arrayToSort[ii];
			arrayToSort[ii] = arrayToSort[jj];
			arrayToSort[jj] = tempValue;
		}
	}

	tempValue = arrayToSort[ii + 1];
	arrayToSort[ii + 1] = arrayToSort[endOfArray];
	arrayToSort[endOfArray] = tempValue;

	return ii + 1;
}

/*
* This function paritions the array based on the index element
*
* @param arrayToSort input as reference array to sort
* @param startOfArray start of the array to sort
* @param endOfArray end of the array to sort
* @param pivot value of the element to pivot from
* @return int parition element index chosen
*/
int SelectPartition(int arrayToSort[], int startOfArray, int endOfArray, int pivot)
{
	int tempValue;
	int x = pivot;
	int ii = startOfArray - 1;

	//find your pivot and swap it with the last
	for (int jj = startOfArray; jj < endOfArray; jj++)
	{
		if (arrayToSort[jj] == pivot)
		{
			arrayToSort[jj] = arrayToSort[endOfArray];
			arrayToSort[endOfArray] = pivot;
		}
	}

	//go through the array
	for (int jj = startOfArray; jj < endOfArray; jj++)
	{
		//if the next index is less than x, put it on the left side of x
		if (arrayToSort[jj] <= x)
		{
			ii = ii + 1;
			tempValue = arrayToSort[ii];
			arrayToSort[ii] = arrayToSort[jj];
			arrayToSort[jj] = tempValue;
		}
	}

	tempValue = arrayToSort[ii + 1];
	arrayToSort[ii + 1] = arrayToSort[endOfArray];
	arrayToSort[endOfArray] = tempValue;

	return ii + 1;
}

/*
* This function prints the given array to the screen
*
* @param arrayToPrint array to print
* @param arraySize size of the array to print
* @return N/A
*/
void PrintArray(int arrayToPrint[], int arraySize)
{
	for (int ii = 0; ii < arraySize; ii++)
	{
		printf("%d ", arrayToPrint[ii]);
	}

	printf("\n");
	printf("\n");
}

/*
* This function prints the given array to the file specified
*
* @param outFile output file for array printing
* @param arrayToPrint array to print
* @param arraySize size of the array to print
* @return N/A
*/
void FilePrintArray(FILE *outFile, int arrayToPrint[], int arraySize)
{
	for (int ii = 0; ii < arraySize; ii++)
	{
		fprintf(outFile, "%d ", arrayToPrint[ii]);
	}

	fprintf(outFile, "\n");
}