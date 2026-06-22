#include <iostream>

// Reminder: information about functions is on the specification PDF

void Print2DArray(const int matrix_local[][3], const int matrix_local_rows_total){

    // start of the function message to terminal
    
    // Body of the function. Do your magic!

    // function end message
}

void MatrixAddition(const int matrix_one[][3], const int matrix_one_rows_total,
                    const int matrix_two[][3], const int matrix_two_rows_total)
    {

    }

void TransposeMatrix(const int matrix_local[][3], const int matrix_local_rows_total){
    // beging of function print

    // body of the function

    // display resulting matrix
    // if the dimension of the resulting matrix doesn't match the print function, you could do it manually here
    // or modify the parameter of the print function so it doesn't cause errors

    // end of the function message 
}

void Determinant(const int matrix_local[][3], const int size){
    // start message 

    // check for valid dimensions

    // body of the function 

    // print the determinant value on the terminal

    // end message
}

void SearchValue(const int matrix_local[][3], const int rows, const int target){
    // start message 

    // body of the function
        // found  or not

    // end of the function message
}

void MatrixMultiplication(const int matrix_a[][3], const int matrix_b[][3], 
                    const int rows_a, const int cols_a, 
                    const int rows_b, const int cols_b){
    // start message 

    // check for valid arrays

    // body of the function

    //print resulting matrix

    // end message
}

int main(){
    // you could use these two matrices for basic testing

    int testing_matrix_one[3][3] = {
        {1,2,3},
        {4,5,6},
        {7,8,9},
    };

    int testing_matrix_two[3][3] = {
        {12,65,82},
        {83,2,8},
        {10,96,67}
    };


// not used in this class, but it is nice to know other ways to find the size of primitive array
// this method below is similar to how you will find the size of vectors (future material)
    // DO NOT USE IN THIS PROJECT FUNCTION, but you could test it yourselves.
    // int size_row_one = std::size(testing_matrix_one);
    // int size_col_one = std::size(testing_matrix_one[0]);




    // This is a way to find the dimensions of an array without hardcoding values.
    // It dynamically reflects the array's actual declared size, so if you change
    // the array dimensions, the calculation updates automatically.
    //
    // How it works:
    //
    // To find the number of ROWS:
    //   sizeof(testing_matrix_one)      = total bytes of the whole array = 3*9*4 = one08 bytes
    //   sizeof(testing_matrix_one[0])   = total bytes of one row         = 1*9*4 =  36 bytes
    //   108 / 36 = 3 rows
    int size_row_one = sizeof(testing_matrix_one)/sizeof(testing_matrix_one[0]);

    // To find the number of COLUMNS:
    //   sizeof(testing_matrix_one[0])      = total bytes of one row          = 1*9*4 = 36 bytes
    //   sizeof(testing_matrix_one[0][0])   = total bytes of one element(int) = 1*4   =  4 bytes
    //   36 / 4 = 9 cols
    int size_col_one = sizeof(testing_matrix_one[0])/sizeof(testing_matrix_one[0][0]);

    std::cout << "row: " << size_row_one<< " col: " << size_col_one<< std::endl << std::endl;


    
    Print2DArray(testing_matrix_one, size_row_one);

    return 0; 
}