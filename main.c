#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/time.h>


///=========================================Performs Matrix Arithmetic==================================================

void matrixSubtraction();

void matrixMultiplication();

void matrixAddition();

void scalarMultiplication();

int main(int argc, char *argv[]) {
	setvbuf(stdout, NULL, _IONBF, 0);
	int operator;
	do {
		printf("Welcome to Matric Arithmetic. Which matrix operator would you like to use? (Enter 1-5)\n"
		       "1. Addition\n"
		       "2. Subtraction\n"
		       "3. Multiplication\n"
		       "4. Scalar Multiplication\n"
		       "5. Quit ");
		scanf("%d", &operator);
		
		switch (operator) {
			case 1:
				matrixAddition();
				break;
			case 2:
				matrixSubtraction();
				break;
			case 3:
				matrixMultiplication();
				break;
			case 4:
				scalarMultiplication();
				break;
			case 5:
				return 0;
			default:
				printf("\nERROR: You entered an invalid character. Please enter 1-5\n");
				break;
		}
	} while (operator != 5);
	
	return 0;
}

///	Matrix Multiplication (A * B) - aka MM
void matrixMultiplication() {
	///	Declaration of matrix dimensions
	int MATRIX_A_ROWS, MATRIX_A_COLUMNS, MATRIX_B_ROWS, MATRIX_B_COLUMNS;
	int count = 0;
	
	printf("\n\t\t\t---Matrix Multiplication\n");
	do {
		/**
	 	* The number of columns in Matrix A must equal the number of rows in Matrix B for MM
	 	*
	 	* Example 1: (2x2 matrix) * (2x6 matrix) is valid
	 	* Example 2: (5x1 matrix) * (3x5 matrix) is invalid
	 	*
	 	*/
		
		if (count++ > 0) printf("\nERROR: Matrix A columns and Matrix B rows must be the same.\n");
		
		///	Prompts user to enter the matrix dimensions of matrix A and B
		printf("How many rows will matrix A have? ");
		scanf("%d", &MATRIX_A_ROWS);
		printf("How many columns will matrix A have? ");
		scanf("%d", &MATRIX_A_COLUMNS);
		printf("How many rows will matrix B have? ");
		scanf("%d", &MATRIX_B_ROWS);
		printf("How many columns will matrix B have? ");
		scanf("%d", &MATRIX_B_COLUMNS);
	} while (MATRIX_A_COLUMNS != MATRIX_B_ROWS); /// Verifies it is a valid operation
	
	printf("(%dx%d) * (%dx%d) = %dx%d\n", MATRIX_A_ROWS, MATRIX_A_COLUMNS,
	       MATRIX_B_ROWS, MATRIX_B_COLUMNS, MATRIX_A_ROWS, MATRIX_B_COLUMNS);
	
	///	Declares matrix A
	double matrix_A[MATRIX_A_ROWS][MATRIX_A_COLUMNS];
	
	///	Gets the values from user for each index in matrix A
	for (int i = 0; i < MATRIX_A_ROWS; ++i) {
		for (int j = 0; j < MATRIX_A_COLUMNS; ++j) {
			printf("Matrix A - Enter the element at %dx%d: ", i + 1, j + 1);
			scanf("%lf", &matrix_A[i][j]);
		}
	}
	
	///	Prints Matrix A
	printf("\n\t\t\t---Matrix A---\n");
	for (int i = 0; i < MATRIX_A_ROWS; ++i) {
		printf("\t\t");
		for (int j = 0; j < MATRIX_A_COLUMNS; ++j) {
			printf("%10.2lf", matrix_A[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	
	
	///	Declares Matrix B
	double matrix_B[MATRIX_B_ROWS][MATRIX_B_COLUMNS];
	
	///	Gets the values from user for each index in matrix B
	for (int i = 0; i < MATRIX_B_ROWS; ++i) {
		for (int j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("Matrix B - Enter the element at %dx%d: ", i + 1, j + 1);
			scanf("%lf", &matrix_B[i][j]);
		}
	}
	///	Prints Matrix B
	printf("\n\t\t\t---Matrix B---\n");
	for (int i = 0; i < MATRIX_B_ROWS; ++i) {
		printf("\t\t");
		for (int j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("%10.2lf", matrix_B[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	
	///	Declares the resultant matrix (which always has dimensions of Matrix A Rows by Matrix B Columns in MM)
	double resultMatrix[MATRIX_A_ROWS][MATRIX_B_COLUMNS];
	
	int i, j, k;
	double result = 0, *firstTerm = NULL, *secondTerm = NULL;
	/**
	 * Since the resultant matrix has the same amount of rows as Matrix A, the outside loop will iterate
	 * the same number of times as there are rows in Matrix A
	 */
	for (i = 0; i < MATRIX_A_ROWS; ++i) {
		
		/**
		 * MM utilizes the Dot Product. Thus, each element in each row in Matrix A (outside loop) will
		 * be multiplied by its corresponding element in each column of Matrix B.
		 * Hence, the inside loop iterates through each column of Matrix B
		 */
		for (j = 0; j < MATRIX_B_COLUMNS; ++j) {
			result = 0; // reset result to 0 every iteration
			printf("\n");                ///	Iterates through each element in the current row of Matrix A
			for (k = 0; k < MATRIX_A_COLUMNS; ++k) {
				firstTerm = &matrix_A[i][k]; // i = current row of matrix A (outside loop), k = current element in that row
				secondTerm = &matrix_B[k][j];// since # of Matrix B rows equals # of Matrix A columns, we can use k for matrix b rows to iterate through each element in the current Matrix B column. j is current column of Matrix B
				result += ((*firstTerm) * (*secondTerm)); // adds to itself because of dot product
				printf("%c%.2lf %c %.2lf%c%s", '(', *firstTerm, '*', *secondTerm, ')',
				       ((k + 1) < MATRIX_A_COLUMNS) ? " + "
				                                    : "\0");//	Prints each operation to give clear explanation as to what is actually happening
			}
			printf(" = %.2lf\n", result);
			resultMatrix[i][j] = result; //sets current spot in matrix equal to result
			
			printf("Element %dx%d of the resultant A * B matrix: %.2lf\n", i + 1, j + 1, result);
			printf("\n=======================================\n");
		}
	}
	
	/// Prints resultant matrix
	printf("\n\t\t\t---A * B Matrix---\n");
	for (i = 0; i < MATRIX_A_ROWS; ++i) {
		printf("\t\t");
		for (j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("%10.2f", resultMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

///	Matrix Addition (A + B)
void matrixAddition() {
	int MATRIX_A_ROWS, MATRIX_A_COLUMNS, MATRIX_B_ROWS, MATRIX_B_COLUMNS;
	int count = 0;
	printf("\n\t\t-----Matrix Addition-----\n");
	
	do {
		if (count++ > 0) printf("\nError: The Dimensions of the two matrices must match.\n");
		
		///	Prompts user to enter the matrix dimensions of matrix A and B
		printf("How many rows will matrix A have? ");
		scanf("%d", &MATRIX_A_ROWS);
		printf("How many columns will matrix A have? ");
		scanf("%d", &MATRIX_A_COLUMNS);
		printf("How many rows will matrix B have? ");
		scanf("%d", &MATRIX_B_ROWS);
		printf("How many columns will matrix B have? ");
		scanf("%d", &MATRIX_B_COLUMNS);
	} while (MATRIX_A_ROWS != MATRIX_B_ROWS || MATRIX_A_COLUMNS != MATRIX_B_COLUMNS);
	
	printf("(%dx%d) + (%dx%d) = %dx%d\n", MATRIX_A_ROWS, MATRIX_A_COLUMNS,
	       MATRIX_B_ROWS, MATRIX_B_COLUMNS, MATRIX_A_ROWS, MATRIX_B_COLUMNS);
	
	///	Declares matrix A
	double matrix_A[MATRIX_A_ROWS][MATRIX_A_COLUMNS];
	
	///	Gets the values from user for each index in matrix A
	for (int i = 0; i < MATRIX_A_ROWS; ++i) {
		for (int j = 0; j < MATRIX_A_COLUMNS; ++j) {
			printf("Matrix A - Enter the element at %dx%d: ", i + 1, j + 1);
			scanf("%lf", &matrix_A[i][j]);
		}
	}
	
	///	Prints Matrix A
	printf("\n\t\t\t---Matrix A---\n");
	for (int i = 0; i < MATRIX_A_ROWS; ++i) {
		printf("\t\t");
		for (int j = 0; j < MATRIX_A_COLUMNS; ++j) {
			printf("%10.2f", matrix_A[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	
	
	///	Declares Matrix B
	double matrix_B[MATRIX_B_ROWS][MATRIX_B_COLUMNS];
	
	///	Gets the values from user for each index in matrix B
	for (int i = 0; i < MATRIX_B_ROWS; ++i) {
		for (int j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("Matrix B - Enter the element at %dx%d: ", i + 1, j + 1);
			scanf("%lf", &matrix_B[i][j]);
		}
	}
	///	Prints Matrix B
	printf("\n\t\t\t---Matrix B---\n");
	for (int i = 0; i < MATRIX_B_ROWS; ++i) {
		printf("\t\t");
		for (int j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("%10.2f", matrix_B[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
///	Matrix Addition (A + B)
	
	int i, j;
	double *termOne = NULL, *termTwo = NULL, sum;
	double additionMatrix[MATRIX_A_ROWS][MATRIX_A_COLUMNS];
	for (i = 0; i < MATRIX_A_ROWS; ++i) {
		for (j = 0; j < MATRIX_A_COLUMNS; ++j) {
			termOne = &matrix_A[i][j];
			termTwo = &matrix_B[i][j];
			sum = *termOne + *termTwo;
			additionMatrix[i][j] = sum;
			
			printf("\nA[%d][%d] + B[%d][%d] == %c%.2f %c %.2f%c == %.2f\n", i + 1, j + 1, i + 1, j + 1,
			       '(', *termOne, '+', *termTwo, ')', sum);
			printf("Element %dx%d of the resultant A + B matrix: %.2f\n", i + 1, j + 1, sum);
			printf("\n=======================================\n");
		}
	}
	
	printf("\n\t\t\t---A + B Matrix---\n");
	for (i = 0; i < MATRIX_A_ROWS; ++i) {
		for (j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("%10.2f", additionMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

///	Matrix Subtraction (A - B)
void matrixSubtraction() {
	int MATRIX_A_ROWS, MATRIX_A_COLUMNS, MATRIX_B_ROWS, MATRIX_B_COLUMNS;
	int count = 0;
	printf("\n\t\t-----Matrix Subtraction-----\n");
	
	do {
		if (count++ > 0) printf("\nError: The Dimensions of the two matrices must match.\n");
		
		///	Prompts user to enter the matrix dimensions of matrix A and B
		printf("How many rows will matrix A have? ");
		scanf("%d", &MATRIX_A_ROWS);
		printf("How many columns will matrix A have? ");
		scanf("%d", &MATRIX_A_COLUMNS);
		printf("How many rows will matrix B have? ");
		scanf("%d", &MATRIX_B_ROWS);
		printf("How many columns will matrix B have? ");
		scanf("%d", &MATRIX_B_COLUMNS);
	} while (MATRIX_A_ROWS != MATRIX_B_ROWS || MATRIX_A_COLUMNS != MATRIX_B_COLUMNS);
	
	printf("(%dx%d) - (%dx%d) = %dx%d\n", MATRIX_A_ROWS, MATRIX_A_COLUMNS,
	       MATRIX_B_ROWS, MATRIX_B_COLUMNS, MATRIX_A_ROWS, MATRIX_B_COLUMNS);
	
	///	Declares matrix A
	double matrix_A[MATRIX_A_ROWS][MATRIX_A_COLUMNS];
	
	///	Gets the values from user for each index in matrix A
	for (int i = 0; i < MATRIX_A_ROWS; ++i) {
		for (int j = 0; j < MATRIX_A_COLUMNS; ++j) {
			printf("Matrix A - Enter the element at %dx%d: ", i + 1, j + 1);
			scanf("%lf", &matrix_A[i][j]);
		}
	}
	
	///	Prints Matrix A
	printf("\n\t\t\t---Matrix A---\n");
	for (int i = 0; i < MATRIX_A_ROWS; ++i) {
		printf("\t\t");
		for (int j = 0; j < MATRIX_A_COLUMNS; ++j) {
			printf("%10.2lf", matrix_A[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\n");
	
	
	///	Declares Matrix B
	double matrix_B[MATRIX_B_ROWS][MATRIX_B_COLUMNS];
	
	///	Gets the values from user for each index in matrix B
	for (int i = 0; i < MATRIX_B_ROWS; ++i) {
		for (int j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("Matrix B - Enter the element at %dx%d: ", i + 1, j + 1);
			scanf("%lf", &matrix_B[i][j]);
		}
	}
	///	Prints Matrix B
	printf("\n\t\t\t---Matrix B---\n");
	for (int i = 0; i < MATRIX_B_ROWS; ++i) {
		printf("\t\t");
		for (int j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("%10.2f", matrix_B[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
	int i, j;
	double *termOne = NULL, *termTwo = NULL, difference = 0;
	double subtractionMatrix[MATRIX_A_ROWS][MATRIX_A_COLUMNS];
	for (i = 0; i < MATRIX_A_ROWS; ++i) {
		for (j = 0; j < MATRIX_A_COLUMNS; ++j) {
			termOne = &matrix_A[i][j];
			termTwo = &matrix_B[i][j];
			difference = *termOne - *termTwo;
			subtractionMatrix[i][j] = difference;
			
			printf("\nA[%d][%d] - B[%d][%d] == %c%.2f %c %.2f%c == %.2f\n", i + 1, j + 1, i + 1, j + 1,
			       '(', *termOne, '-', *termTwo, ')', difference);
			printf("Element %dx%d of the resultant A - B matrix: %.2f\n", i + 1, j + 1, difference);
			printf("\n=======================================\n");
		}
	}
	
	printf("\n\t\t\t---A - B Matrix---\n");
	for (i = 0; i < MATRIX_A_ROWS; ++i) {
		for (j = 0; j < MATRIX_B_COLUMNS; ++j) {
			printf("%10.2f", subtractionMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}

/// Scalar Multiplication (n * A) where n is a number and A is a matrix
void scalarMultiplication() {
	int MATRIX_ROWS, MATRIX_COLUMNS;
	int i, j;
	double scalar, result;
	
	printf("\n---Scalar Multiplication---\n");

///	Prompts user to enter the matrix dimensions of matrix A and B
	printf("How many rows will the matrix have? ");
	scanf("%d", &MATRIX_ROWS);
	printf("How many columns will the matrix have? ");
	scanf("%d", (int *) &MATRIX_COLUMNS);
	///Prompts user to enter a scalar
	double scalarMatrix[MATRIX_ROWS][MATRIX_COLUMNS];
	
	///	Gets the values from user for each index in matrix A
	for (i = 0; i < MATRIX_ROWS; ++i) {
		for (j = 0; j < MATRIX_COLUMNS; ++j) {
			printf("Matrix - Enter the element at %dx%d: ", i + 1, j + 1);
			scanf("%lf", &scalarMatrix[i][j]);
		}
	}
	
	///	Prints Matrix
	printf("\n\t\t\t---Matrix---\n");
	for (i = 0; i < MATRIX_ROWS; ++i) {
		printf("\t\t");
		for (j = 0; j < MATRIX_COLUMNS; ++j) {
			printf("%10.2f", scalarMatrix[i][j]);
		}
		printf("\n");
	}
	
	printf("\n\nEnter a scalar: ");
	scanf("%lf", &scalar);
	
	
	for (i = 0; i < MATRIX_ROWS; ++i) {
		for (j = 0; j < MATRIX_COLUMNS; ++j) {
			result = scalarMatrix[i][j] * scalar;
			scalarMatrix[i][j] = result;
		}
	}
	printf("\n\t\t\t---Scalar Matrix---\n");
	
	for (i = 0; i < MATRIX_ROWS; ++i) {
		for (j = 0; j < MATRIX_COLUMNS; ++j) {
			printf("%10.2f", scalarMatrix[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
	
}

