/**
sortHelper.h
This class file contains various declarations of functions used for the implementation
of the select and quick sort algorithmns.

@author Charles Forrest
@version 1.0 03/03/2015
*/

#ifndef SORTHELPER_H
#define SORTHELPER_H

#include <iostream>
#include <stdio.h>
#include "Windows.h"

/* @brief Function to perform median of median findings */
void MedianOfMedians(int arrayToSort[], int medianArr[], int endOfArray);

/* @brief Function to perform the select algorithmn to find ith order index */
int Select(int arrayToSort[], int startOfArray, int endOfArray, int index);

/* @brief Function to perform quick sort */
void QuickSort(int arrayToSort[], int startOfArray, int endOfArray);

/* @brief Function to perform partitioning for quick sort */
int Parition(int arrayToSort[], int startOfArray, int endOfArray);

/* @brief Function to perform modified partitioning for select sort */
int SelectPartition(int arrayToSort[], int startOfArray, int endOfArray, int pivot);

/* @brief Function to print out the given array to the screen */
void PrintArray(int arrayToPrint[], int arraySize);

/* @brief Function to print out the given array to a file */
void FilePrintArray(FILE *outFile, int arrayToPrint[], int arraySize);

#endif