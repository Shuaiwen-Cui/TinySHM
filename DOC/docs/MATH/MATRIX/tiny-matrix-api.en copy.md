# MATRIX OPERATIONS - TINY_MATRIX

!!! INFO "TINY_MATRIX Library"
    - This library is a lightweight matrix computation library implemented in C++, providing basic matrix operations and linear algebra functions.
    - The design goal of this library is to provide a simple and easy-to-use matrix operation interface, suitable for embedded systems and resource-constrained environments.

!!! TIP "Usage Scenario"
    Compared to the TINY_MAT library, the TINY_MATRIX library offers richer functionality and higher flexibility, suitable for applications that require complex matrix computations. However, please note that this library is written in C++.

## LIST OF FUNCTIONS

```c
TinyMath
    ├──Vector
    └──Matrix
        ├── tiny_mat (c)
        └── tiny_matrix (c++) <---
```

```cpp
namespace tiny
{
    class Mat
    {
    public:
        /* === Matrix Metadata === */
        int rows, cols, stride, padding, length;
        float *data;
        bool ext_buff, sub_matrix;

        /* === Rectangular ROI Structure === */
        struct Rect
        {
            int x, y, width, height;
            Rect(int x = 0, int y = 0, int width = 0, int height = 0);
            void resizeRect(int x, int y, int width, int height);
            int areaRect(void) const;
        };

        /* === Constructors & Destructor === */
        Mat();                                      // Default constructor
        Mat(int rows, int cols);                    // Internal allocation
        Mat(float *data, int rows, int cols);       // External buffer
        Mat(float *data, int rows, int cols, int stride); // External buffer with stride
        Mat(const Mat &src);                        // Copy constructor
        ~Mat();                                     // Destructor

        void allocate();                            // Allocate internal memory

        /* === Element Access === */
        inline float &operator()(int row, int col) { return data[row * stride + col]; }
        inline const float &operator()(int row, int col) const { return data[row * stride + col]; }


        /* === Data Manipulation === */
        void Copy(const Mat &src, int row_pos, int col_pos);
        void CopyHead(const Mat &src);
        Mat getROI(int startRow, int startCol, int roiRows, int roiCols, int stride);
        Mat getROI(int startRow, int startCol, int roiRows, int roiCols);
        Mat getROI(const Rect &rect);
        Mat Get(int row_start, int row_size, int col_start, int col_size);
        Mat Get(const Rect &rect);
        Mat block(int startRow, int startCol, int blockRows, int blockCols);
        void swapRows(int row1, int row2);
        void clear();

        /* === Print & Debug === */
        void PrintHead();
        void PrintMatrix(bool show_padding, const std::string &label);

        /* === Arithmetic Operators === */
        Mat &operator=(const Mat &src);             // Copy assignment
        Mat &operator+=(const Mat &A);
        Mat &operator+=(float C);
        Mat &operator-=(const Mat &A);
        Mat &operator-=(float C);
        Mat &operator*=(const Mat &A);
        Mat &operator*=(float C);
        Mat &operator/=(const Mat &B);
        Mat &operator/=(float C);
        Mat operator^(int C);

        /* === Linear Algebra === */
        void normalize();
        float norm();
        float det(int n);
        Mat t();
        Mat inverse();
        Mat pinv();
        Mat gaussianEliminate();
        Mat rowReduceFromGaussian();

        /* === Static Utility Functions === */
        static Mat eye(int size);
        static Mat ones(int size);
        static Mat ones(int rows, int cols);
        static Mat solve(Mat A, Mat b);
        static Mat bandSolve(Mat A, Mat b, int k);
        static Mat roots(Mat A, Mat y);
        static float dotProduct(Mat A, Mat B);
        static Mat augment(Mat A, Mat B);

    private:
        Mat cofactor(int row, int col, int n);
        Mat adjoint();
        Mat expHelper(const Mat &m, int num);
    };

    /* === Stream Operators === */
    std::ostream &operator<<(std::ostream &os, const Mat &m);
    std::ostream &operator<<(std::ostream &os, const Mat::Rect &rect);
    std::istream &operator>>(std::istream &is, Mat &m);

    /* === Global Arithmetic Operators === */
    Mat operator+(const Mat &A, const Mat &B);
    Mat operator+(const Mat &A, float C);
    Mat operator-(const Mat &A, const Mat &B);
    Mat operator-(const Mat &A, float C);
    Mat operator*(const Mat &A, const Mat &B);
    Mat operator*(const Mat &A, float C);
    Mat operator*(float C, const Mat &A);
    Mat operator/(const Mat &A, float C);
    Mat operator/(const Mat &A, const Mat &B);
    bool operator==(const Mat &A, const Mat &B);
}

```

## MATRIX METADATA

- `int rows`: Number of rows in the matrix.

- `int cols`: Number of columns in the matrix.

- `int stride`: Number of elements in each row (including padding).

- `int padding`: Number of padding elements in each row.

- `int length`: Total number of elements in the matrix.

- `float *data`: Pointer to the data buffer of the matrix.

- `bool ext_buff`: Indicates whether the matrix uses an external buffer.

- `bool sub_matrix`: Indicates whether the matrix is a sub-matrix of another matrix.

## ROI STRUCTURE

### ROI Metadata

- `int x`: X-coordinate of the top-left corner of the ROI.

- `int y`: Y-coordinate of the top-left corner of the ROI.

- `int width`: Width of the ROI.

- `int height`: Height of the ROI.

### ROI Constructor

```cpp
Mat::Rect::Rect(int x, int y, int width, int height);
```

- `x`: X-coordinate of the top-left corner of the ROI.

- `y`: Y-coordinate of the top-left corner of the ROI.

- `width`: Width of the ROI.

- `height`: Height of the ROI.

### Resize ROI

```cpp
void Mat::Rect::resizeRect(int x, int y, int width, int height);
```

- `x`: New X-coordinate of the top-left corner of the ROI.

- `y`: New Y-coordinate of the top-left corner of the ROI.

- `width`: New width of the ROI.

- `height`: New height of the ROI.

### Area of ROI

```cpp
int Mat::Rect::areaRect(void) const;
```

- Returns the area of the ROI.

## CONSTRUCTORS & DESTRUCTOR

### Default Constructor

```cpp
Mat::Mat();
```

**Description**: Default constructor, creates an empty matrix.

**Parameters**: None.

### Constructor with Rows and Columns

```cpp
Mat::Mat(int rows, int cols);
```

**Description**: Constructor that allocates internal memory for the matrix.

**Parameters**:

- `int rows`: Number of rows in the matrix.

- `int cols`: Number of columns in the matrix.

### Constructor with External Buffer

```cpp
Mat::Mat(float *data, int rows, int cols);
```
**Description**: Constructor that uses an external buffer for the matrix data.

**Parameters**:

- `float *data`: Pointer to the external buffer.

- `int rows`: Number of rows in the matrix.

- `int cols`: Number of columns in the matrix.

### Constructor with External Buffer and Stride

```cpp
Mat::Mat(float *data, int rows, int cols, int stride);
```

**Description**: Constructor that uses an external buffer and specifies the stride.

**Parameters**:

- `float *data`: Pointer to the external buffer.

- `int rows`: Number of rows in the matrix.

- `int cols`: Number of columns in the matrix.

- `int stride`: Number of elements in each row (including padding).

### Copy Constructor

```cpp
Mat::Mat(const Mat &src);
```

**Description**: Copy constructor that creates a new matrix as a copy of the source matrix.

**Parameters**:

- `const Mat &src`: Source matrix to copy from.

### Destructor

```cpp
Mat::~Mat();
```

**Description**: Destructor that releases the internal memory of the matrix.

**Parameters**: None.

### Allocate Internal Memory

```cpp
void Mat::allocate();
```

**Description**: Allocates internal memory for the matrix.

**Parameters**: None.

## ELEMENT ACCESS

### Element Access Operator

```cpp
inline float &Mat::operator()(int row, int col);
```

**Description**: Accesses the element at the specified row and column.

**Parameters**:

- `int row`: Row index of the element.

- `int col`: Column index of the element.

### Const Element Access Operator

```cpp
inline const float &Mat::operator()(int row, int col) const;
```

**Description**: Accesses the element at the specified row and column (const version).

**Parameters**:

- `int row`: Row index of the element.

- `int col`: Column index of the element.


## DATA MANIPULATION

### Copy Function

```cpp
void Mat::Copy(const Mat &src, int row_pos, int col_pos);
```

**Description**: Copies the source matrix to the current matrix at the specified position.

**Parameters**:

- `const Mat &src`: Source matrix to copy from.

- `int row_pos`: Row position to copy to.

- `int col_pos`: Column position to copy to.

### Copy Head Function

```cpp
void Mat::CopyHead(const Mat &src);
```

**Description**: Copies the header (metadata) of the source matrix to the current matrix.

**Parameters**:

- `const Mat &src`: Source matrix to copy from.

### Get ROI Function

```cpp
Mat Mat::getROI(int startRow, int startCol, int roiRows, int roiCols, int stride);
```

**Description**: Returns a sub-matrix (ROI) of the current matrix.

**Parameters**:

- `int startRow`: Starting row index of the ROI.

- `int startCol`: Starting column index of the ROI.

- `int roiRows`: Number of rows in the ROI.

- `int roiCols`: Number of columns in the ROI.

- `int stride`: Stride of the ROI.

### Get ROI Function (Without Stride)

```cpp
Mat Mat::getROI(int startRow, int startCol, int roiRows, int roiCols);
```

**Description**: Returns a sub-matrix (ROI) of the current matrix without specifying stride.

**Parameters**:

- `int startRow`: Starting row index of the ROI.

- `int startCol`: Starting column index of the ROI.

- `int roiRows`: Number of rows in the ROI.

- `int roiCols`: Number of columns in the ROI.

### Get ROI Function (With Rect)

```cpp
Mat Mat::getROI(const Rect &rect);
```

**Description**: Returns a sub-matrix (ROI) of the current matrix using a Rect structure.

**Parameters**:

- `const Rect &rect`: Rect structure defining the ROI.

### Get Function

```cpp
Mat Mat::Get(int row_start, int row_size, int col_start, int col_size);
```

**Description**: Returns a sub-matrix of the current matrix defined by the specified row and column ranges.

**Parameters**:

- `int row_start`: Starting row index of the sub-matrix.

- `int row_size`: Number of rows in the sub-matrix.

- `int col_start`: Starting column index of the sub-matrix.

- `int col_size`: Number of columns in the sub-matrix.

### Get Function (With Rect)

```cpp
Mat Mat::Get(const Rect &rect);
```
**Description**: Returns a sub-matrix of the current matrix defined by a Rect structure.

**Parameters**:

- `const Rect &rect`: Rect structure defining the sub-matrix.

### Block Function

```cpp
Mat Mat::block(int startRow, int startCol, int blockRows, int blockCols);
```

**Description**: Returns a block of the current matrix defined by the specified starting row and column indices.

**Parameters**:

- `int startRow`: Starting row index of the block.

- `int startCol`: Starting column index of the block.

- `int blockRows`: Number of rows in the block.

- `int blockCols`: Number of columns in the block.

### Swap Rows Function

```cpp
void Mat::swapRows(int row1, int row2);
```

**Description**: Swaps two rows in the current matrix.

**Parameters**:

- `int row1`: Index of the first row to swap.

- `int row2`: Index of the second row to swap.

### Clear Function

```cpp
void Mat::clear();
```

**Description**: Clears the current matrix, releasing its internal memory.

**Parameters**: None.

!!! tip "getROI | Get | block"
    - getROI: Get a sub-matrix (Region of Interest) from the current matrix.
    - Get: Get a sub-matrix defined by row and column ranges.
    - block: Get a block of the current matrix defined by starting row and column indices.

| Method   | Copy Data | New Memory | Affect Original Matrix | Performance | Usage Scenario              |
|----------|-----------|------------|------------------------|-------------|-----------------------------|
| `getROI` | No        | No         | Yes                    | ⭐⭐⭐⭐⭐      | Fast temporary sub-matrix   |
| `Get`    | Yes       | Yes        | No                     | ⭐⭐⭐⭐       | Safe & independent sub-matrix |
| `block`  | Yes       | Yes        | No                     | ⭐⭐⭐        | Flexible complex copy       |


## PRINT & DEBUG

### Print Head Function

```cpp
void Mat::PrintHead();
```

**Description**: Prints the header (metadata) of the current matrix.

**Parameters**: None.

### Print Matrix Function

```cpp
void Mat::PrintMatrix(bool show_padding, const std::string &label);
```

**Description**: Prints the contents of the current matrix.

**Parameters**:

- `bool show_padding`: Indicates whether to show padding.

- `const std::string &label`: Label to print with the matrix.


## ARITHMETIC OPERATORS

### Copy Assignment Operator

```cpp
Mat &Mat::operator=(const Mat &src);
```

**Description**: Copy assignment operator that assigns the source matrix to the current matrix.

**Parameters**:

- `const Mat &src`: Source matrix to assign from.

### Addition Assignment Operator

```cpp
Mat &Mat::operator+=(const Mat &A);
```

**Description**: Adds the source matrix to the current matrix.

**Parameters**:

- `const Mat &A`: Source matrix to add.

### Addition Assignment Operator (with constant)

```cpp
Mat &Mat::operator+=(float C);
```

**Description**: Adds a constant value to the current matrix.

**Parameters**:

- `float C`: Constant value to add.

### Subtraction Assignment Operator

```cpp
Mat &Mat::operator-=(const Mat &A);
```

**Description**: Subtracts the source matrix from the current matrix.

**Parameters**:

- `const Mat &A`: Source matrix to subtract.

### Subtraction Assignment Operator (with constant)

```cpp
Mat &Mat::operator-=(float C);
```

**Description**: Subtracts a constant value from the current matrix.

**Parameters**:

- `float C`: Constant value to subtract.

### Multiplication Assignment Operator

```cpp
Mat &Mat::operator*=(const Mat &A);
```

**Description**: Multiplies the current matrix by the source matrix.

**Parameters**:

- `const Mat &A`: Source matrix to multiply.

### Multiplication Assignment Operator (with constant)

```cpp
Mat &Mat::operator*=(float C);
```

**Description**: Multiplies the current matrix by a constant value.

**Parameters**:

- `float C`: Constant value to multiply.

### Division Assignment Operator

```cpp
Mat &Mat::operator/=(const Mat &B); // by element
```

**Description**: Divides the current matrix by the source matrix.

**Parameters**:

- `const Mat &B`: Source matrix to divide by.

### Division Assignment Operator (by constant)

```cpp
Mat &Mat::operator/=(float C);
```

**Description**: Divides the current matrix by a constant value.

**Parameters**:

- `float C`: Constant value to divide by.

### Power Operator

```cpp
Mat Mat::operator^(int C);
```

**Description**: Raises the current matrix to the power of a constant value.

**Parameters**:

- `int C`: Constant value to raise the matrix to.

## LINEAR ALGEBRA

### Normalize Function

```cpp
void Mat::normalize();
```

**Description**: Normalizes the current matrix.

**Parameters**: None.

### Norm Function

```cpp
float Mat::norm();
```

**Description**: Computes the norm of the current matrix.

**Parameters**: None.

### Determinant Function

```cpp
float Mat::det(int n);
```

**Description**: Computes the determinant of the current matrix.

**Parameters**:

- `int n`: Size of the matrix.
### Transpose Function

```cpp
Mat Mat::t();
```

**Description**: Computes the transpose of the current matrix.

**Parameters**: None.

### Inverse Function

```cpp
Mat Mat::inverse();
```

**Description**: Computes the inverse of the current matrix.

**Parameters**: None.

### Pseudo-Inverse Function

```cpp
Mat Mat::pinv();
```

**Description**: Computes the pseudo-inverse of the current matrix.

**Parameters**: None.

### Gaussian Elimination Function

```cpp
Mat Mat::gaussianEliminate();
```

**Description**: Performs Gaussian elimination on the current matrix.

**Parameters**: None.

### Row Reduce from Gaussian Function

```cpp
Mat Mat::rowReduceFromGaussian();
```

**Description**: Performs row reduction from Gaussian elimination on the current matrix.

**Parameters**: None.

## STATIC UTILITY FUNCTIONS

### Identity Matrix Function

```cpp
Mat Mat::eye(int size);
```

**Description**: Creates an identity matrix of the specified size.

**Parameters**:

- `int size`: Size of the identity matrix.

### Ones Square Matrix Function

```cpp
Mat Mat::ones(int size);
```

**Description**: Creates a square matrix filled with ones.

**Parameters**:

- `int size`: Size of the square matrix.

### Ones Rectangular Matrix Function

```cpp
Mat Mat::ones(int rows, int cols);
```

**Description**: Creates a rectangular matrix filled with ones.

**Parameters**:

- `int rows`: Number of rows in the matrix.

- `int cols`: Number of columns in the matrix.

### Solve Function

```cpp
Mat Mat::solve(Mat A, Mat b);
```

**Description**: Solves the linear equation Ax = b.

**Parameters**:

- `Mat A`: Coefficient matrix.

- `Mat b`: Right-hand side matrix.

### Band Solve Function

```cpp
Mat Mat::bandSolve(Mat A, Mat b, int k);
```

**Description**: Solves the banded linear equation Ax = b.

**Parameters**:

- `Mat A`: Coefficient matrix.

- `Mat b`: Right-hand side matrix.

- `int k`: Bandwidth of the matrix.

### Roots Function

```cpp
Mat Mat::roots(Mat A, Mat y);
```

**Description**: Computes the roots of the polynomial defined by the matrix A.

**Parameters**:

- `Mat A`: Coefficient matrix.

- `Mat y`: Right-hand side matrix.

### Dot Product Function

```cpp
float Mat::dotProduct(Mat A, Mat B);
```

**Description**: Computes the dot product of two matrices.

**Parameters**:

- `Mat A`: First matrix.

- `Mat B`: Second matrix.

### Augment Function

```cpp
Mat Mat::augment(Mat A, Mat B);
```

**Description**: Augments two matrices.

**Parameters**:

- `Mat A`: First matrix.

- `Mat B`: Second matrix.

### Cofactor Function

```cpp
Mat Mat::cofactor(int row, int col, int n);
```

**Description**: Computes the cofactor of the current matrix.

**Parameters**:

- `int row`: Row index of the element.

- `int col`: Column index of the element.

- `int n`: Size of the matrix.

### Adjoint Function

```cpp
Mat Mat::adjoint();
```

**Description**: Computes the adjoint of the current matrix.

**Parameters**: None.

### Exponential Helper Function

```cpp
Mat Mat::expHelper(const Mat &m, int num);
```

**Description**: Helper function for computing the matrix exponential.

**Parameters**:

- `const Mat &m`: Matrix to compute the exponential of.

- `int num`: Number of terms in the series expansion.


## STREAM OPERATORS

### Output Stream Operator

```cpp
std::ostream &operator<<(std::ostream &os, const Mat &m);
```

**Description**: Overloads the output stream operator to print the matrix.

**Parameters**:

- `std::ostream &os`: Output stream.

- `const Mat &m`: Matrix to print.

### Output Stream Operator (Rect)

```cpp
std::ostream &operator<<(std::ostream &os, const Mat::Rect &rect);
```

**Description**: Overloads the output stream operator to print the Rect structure.

**Parameters**:

- `std::ostream &os`: Output stream.

- `const Mat::Rect &rect`: Rect structure to print.

### Input Stream Operator

```cpp
std::istream &operator>>(std::istream &is, Mat &m);
```

**Description**: Overloads the input stream operator to read a matrix.

**Parameters**:

- `std::istream &is`: Input stream.

- `Mat &m`: Matrix to read into.

## GLOBAL ARITHMETIC OPERATORS

### Addition Operator

```cpp
Mat operator+(const Mat &A, const Mat &B);
```

**Description**: Adds two matrices.

**Parameters**:

- `const Mat &A`: First matrix.

- `const Mat &B`: Second matrix.

### Addition Operator (with constant)

```cpp
Mat operator+(const Mat &A, float C);
```

**Description**: Adds a constant value to a matrix.

**Parameters**:

- `const Mat &A`: Matrix to add to.

- `float C`: Constant value to add.

### Subtraction Operator

```cpp
Mat operator-(const Mat &A, const Mat &B);
```

**Description**: Subtracts one matrix from another.

**Parameters**:

- `const Mat &A`: First matrix.

- `const Mat &B`: Second matrix.

### Subtraction Operator (with constant)

```cpp
Mat operator-(const Mat &A, float C);
```

**Description**: Subtracts a constant value from a matrix.

**Parameters**:

- `const Mat &A`: Matrix to subtract from.

- `float C`: Constant value to subtract.

### Multiplication Operator

```cpp
Mat operator*(const Mat &A, const Mat &B);
```

**Description**: Multiplies two matrices.

**Parameters**:

- `const Mat &A`: First matrix.

- `const Mat &B`: Second matrix.

### Multiplication Operator (with constant)

```cpp
Mat operator*(const Mat &A, float C);
```

**Description**: Multiplies a matrix by a constant value.

**Parameters**:

- `const Mat &A`: Matrix to multiply.

- `float C`: Constant value to multiply by.

### Multiplication Operator (with constant on left)

```cpp
Mat operator*(float C, const Mat &A);
```

**Description**: Multiplies a constant value by a matrix.

**Parameters**:

- `float C`: Constant value to multiply by.

- `const Mat &A`: Matrix to multiply.

### Division Operator

```cpp
Mat operator/(const Mat &A, float C);
```

**Description**: Divides a matrix by a constant value.

**Parameters**:

- `const Mat &A`: Matrix to divide.

- `float C`: Constant value to divide by.

### Division Operator (by matrix)

```cpp
Mat operator/(const Mat &A, const Mat &B);
```

**Description**: Divides one matrix by another.

**Parameters**:

- `const Mat &A`: Matrix to divide.

- `const Mat &B`: Matrix to divide by.

### Equality Operator

```cpp
bool operator==(const Mat &A, const Mat &B);
```

**Description**: Compares two matrices for equality.

**Parameters**:

- `const Mat &A`: First matrix.

- `const Mat &B`: Second matrix.