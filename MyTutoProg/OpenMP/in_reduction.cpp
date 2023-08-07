/**
 * @author RookieHPC
 * @brief Original source code at https://rookiehpc.org/openmp/docs/in_reduction/index.html
 **/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

/**
 * @brief Illustrates how to use the in_reduction clause.
 * @details This example consists in calculating the sum of all elements of an
 * array.
 **/
int main(int argc, char* argv[])
{
	// Use 2 threads when creating OpenMP parallel regions
	omp_set_num_threads(2);

	int total = 0;
	const int ARRAY_SIZE = 100;
	
	int myArray[ARRAY_SIZE];

	// Initialise the array
	for(int i = 0; i < ARRAY_SIZE; i++)
	{
		myArray[i] = i;
	}

	// Calculate the sum of all elements

	// 1st method: a parallel loop via tasks
	#pragma omp parallel reduction(task, +: total)
	{
		#pragma omp single
		{
			for(int i = 0; i < ARRAY_SIZE; i++)
			{
				#pragma omp task in_reduction(+: total)
				{
					total += myArray[i];
				}
			}
		}
	}
	printf("The sum of all array elements with the 1st method is equal to %d.\n", total);

	// 2nd method: a taskgroup
	total = 0;
	#pragma omp parallel
	{
		#pragma omp single
		{
			#pragma omp taskgroup task_reduction(+: total)
			{
				for(int i = 0; i < ARRAY_SIZE; i++)
				{
					#pragma omp task in_reduction(+: total)
					total += myArray[i];
				}
			}
		}
	}
	printf("The sum of all array elements with the 2nd method is equal to %d.\n", total);

	

	return EXIT_SUCCESS;
}
