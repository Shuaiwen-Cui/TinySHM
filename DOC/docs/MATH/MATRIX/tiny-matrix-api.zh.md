# 矩阵操作 - TINY_MATRIX

!!! INFO "TINY_MATRIX库"
    - 该库是一个轻量级的矩阵运算库，基于C++实现，提供了基本的矩阵操作和线性代数功能。
    - 该库的设计目标是提供简单易用的矩阵操作接口，适合于嵌入式系统和资源受限的环境。

!!! TIP "使用场景"
    相对于TINY_MAT库而言，TINY_MATRIX库提供了更丰富的功能和更高的灵活性，适合于需要进行复杂矩阵运算的应用场景。但是请注意，该库基于C++编写，

## 目录

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
        int row;         //< number of rows
        int col;         //< number of columns
        int pad;         //< number of paddings between 2 rows
        int stride;      //< stride = (number of elements in a row) + padding
        int element;     //< number of elements = rows * cols
        int memory;      //< size of the data buffer = rows * stride
        float *data;     //< pointer to the data buffer
        float *temp;     //< pointer to the temporary data buffer
        bool ext_buff;   //< flag indicates that matrix use external buffer
        bool sub_matrix; //< flag indicates that matrix is a subset of another matrix

        /* === Rectangular ROI Structure === */
        /**
         * @name Region of Interest (ROI) Structure
         * @brief This is the structure for ROI
         * 
         */
        struct ROI
        {
            int pos_x;  ///< starting column index
            int pos_y;  ///< starting row index
            int width;  ///< width of ROI (columns)
            int height; ///< height of ROI (rows)

            // ROI constructor
            ROI(int pos_x = 0, int pos_y = 0, int width = 0, int height = 0);

            // resize ROI
            void resize_roi(int pos_x, int pos_y, int width, int height);

            // calculate area of ROI
            int area_roi(void) const;
        };
        
        /* === Printing Functions === */
        // print matrix info
        void print_info() const;

        // print matrix elements, paddings optional
        void print_matrix(bool show_padding);

        /* === Constructors & Destructor === */
        // memory allocation
        void alloc_mem(); // Allocate internal memory

        // constructor
        Mat();
        Mat(int rows, int cols);
        Mat(int rows, int cols, int stride);
        Mat(float *data, int rows, int cols);
        Mat(float *data, int rows, int cols, int stride);
        Mat(const Mat &src);

        // destructor
        ~Mat();

        /* === Element Access === */
        // access matrix elements - non const
        inline float &operator()(int row, int col) { return data[row * stride + col]; }

        // access matrix elements - const             
        inline const float &operator()(int row, int col) const { return data[row * stride + col]; }

        /* === Data Manipulation === */
        // copy other matrix into this matrix as a sub-matrix
        tiny_error_t copy_paste(const Mat &src, int row_pos, int col_pos);

        // copy header of other matrix to this matrix
        tiny_error_t copy_head(const Mat &src);

        // get a view (shallow copy) of sub-matrix (ROI) from this matrix
        Mat view_roi(int start_row, int start_col, int roi_rows, int roi_cols) const;

        // get a view (shallow copy) of sub-matrix (ROI) from this matrix using ROI structure
        Mat view_roi(const Mat::ROI &roi) const;

        // get a replica (deep copy) of sub-matrix (ROI) 
        Mat copy_roi(int start_row, int start_col, int roi_rows, int roi_cols);

        // get a replica (deep copy) of sub-matrix (ROI) using ROI structure
        Mat copy_roi(const Mat::ROI &roi);

        // get a block of matrix
        Mat block(int start_row, int start_col, int block_rows, int block_cols);

        // swap rows
        void swap_rows(int row1, int row2);

        // clear matrix
        void clear(void);

        /* === Arithmetic Operators === */
        Mat &operator=(const Mat &src);    // Copy assignment
        Mat &operator+=(const Mat &A);     // Add matrix
        Mat &operator+=(float C);          // Add constant
        Mat &operator-=(const Mat &A);     // Subtract matrix
        Mat &operator-=(float C);          // Subtract constant 
        Mat &operator*=(const Mat &A);     // Multiply matrix
        Mat &operator*=(float C);          // Multiply constant
        Mat &operator/=(const Mat &B);     // Divide matrix
        Mat &operator/=(float C);          // Divide constant
        Mat operator^(int C);              // Exponentiation

        /* === Linear Algebra === */
        Mat transpose();                   // Transpose matrix
        Mat cofactor(int row, int col);    // cofactor matrix extraction
        float determinant();
        Mat adjoint(); 
        void normalize();
        float norm() const;
        Mat inverse_adjoint();
        static Mat eye(int size);
        static Mat augment(const Mat &A, const Mat &B);
        static Mat ones(int rows, int cols);
        static Mat ones(int size);
        Mat gaussian_eliminate() const;
        Mat row_reduce_from_gaussian();
        Mat inverse_gje(); // Inverse using Gaussian-Jordan elimination
        float dotprod(const Mat &A, const Mat &B);
        Mat solve(const Mat &A, const Mat &b);
        Mat band_solve(Mat A, Mat b, int k);
        Mat roots(Mat A, Mat y);
        
    protected:

    private:

    };

    /* === Stream Operators === */
    std::ostream &operator<<(std::ostream &os, const Mat &m);
    std::ostream &operator<<(std::ostream &os, const Mat::ROI &roi);
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

<!-- ## 元数据

## ROI 结构

## 打印函数

## 构造与析构函数

## 元素访问

## 数据操作

## 算术运算符

## 线性代数

## 流操作符

## 全局算数运算符 -->
