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

## 元数据

- `int row`: 行数

- `int col`: 列数

- `int pad`: 行间填充数

- `int stride`: 行内元素数 + 填充数

- `int element`: 元素数

- `int memory`: 数据缓冲区大小 = 行数 * 步幅

- `float *data`: 数据缓冲区指针

- `float *temp`: 临时数据缓冲区指针

- `bool ext_buff`: 标志矩阵是否使用外部缓冲区

- `bool sub_matrix`: 标志矩阵是否为另一个矩阵的子集

## ROI 结构

### 元数据

- `int pos_x`: 起始列索引

- `int pos_y`: 起始行索引

- `int width`: ROI 的宽度（列数）

- `int height`: ROI 的高度（行数）

### ROI 构造函数

```cpp
Mat::ROI::ROI(int pos_x = 0, int pos_y = 0, int width = 0, int height = 0);
```

**描述**: 构造一个 ROI 对象，默认值为 (0, 0, 0, 0)。

**参数**:

- `int pos_x`: 起始列索引

- `int pos_y`: 起始行索引

- `int width`: ROI 的宽度（列数）

- `int height`: ROI 的高度（行数）

### ROI 重置函数

```cpp
void Mat::ROI::resize_roi(int pos_x, int pos_y, int width, int height);
```

**描述**: 重置 ROI 的位置和大小。

**参数**:

- `int pos_x`: 起始列索引

- `int pos_y`: 起始行索引

- `int width`: ROI 的宽度（列数）

- `int height`: ROI 的高度（行数）

**返回值**: void

### ROI 面积函数

```cpp
int Mat::ROI::area_roi(void) const;
```

**描述**: 计算 ROI 的面积。

**参数**: void

**返回值**: 整数类型 ROI 的面积

## 打印函数

### 打印矩阵信息

```cpp
void Mat::print_info() const
```

**描述**: 打印矩阵的基本信息，包括行数、列数、元素数、填充数、步幅数、内存大小、数据缓冲区指针、临时数据缓冲区指针、外部缓冲区标志、子矩阵标志。

**参数**: void

**返回值**: void

### 打印矩阵元素

```cpp
void Mat::print_matrix(bool show_padding);
```

**描述**: 打印矩阵的元素。

**参数**:

- `bool show_padding`: 是否显示填充区元素， true 显示，false 不显示

**返回值**: void

## 构造与析构函数

### 默认构造函数

```cpp
Mat::Mat();
```

**描述**: 默认构造函数将使用默认值初始化一个矩阵对象。这个函数会创建一个一行一列的矩阵，唯一的元素是0。

**参数**: void

### 构造函数 - Mat(int rows, int cols)

```cpp
Mat::Mat(int rows, int cols);
```

**描述**: 构造一个指定行数和列数的矩阵对象。

**参数**:

- `int rows`: 行数

- `int cols`: 列数

### 构造函数 - Mat(int rows, int cols, int stride)

```cpp
Mat::Mat(int rows, int cols, int stride);
```

**描述**: 构造一个指定行数、列数和步幅的矩阵对象。

**参数**:

- `int rows`: 行数

- `int cols`: 列数

- `int stride`: 步幅

### 构造函数 - Mat(float *data, int rows, int cols)

```cpp
Mat::Mat(float *data, int rows, int cols);
```

**描述**: 构造一个指定行数和列数的矩阵对象，并使用给定的数据缓冲区。

**参数**:

- `float *data`: 数据缓冲区指针

- `int rows`: 行数

- `int cols`: 列数

### 构造函数 - Mat(float *data, int rows, int cols, int stride)

```cpp
Mat::Mat(float *data, int rows, int cols, int stride);
```

**描述**: 构造一个指定行数、列数和步幅的矩阵对象，并使用给定的数据缓冲区。

**参数**:

- `float *data`: 数据缓冲区指针

- `int rows`: 行数

- `int cols`: 列数

- `int stride`: 步幅

### 构造函数 - Mat(const Mat &src)

```cpp
Mat::Mat(const Mat &src);
```

**描述**: 构造一个矩阵对象，并使用给定的矩阵对象的头部信息。

**参数**:

- `const Mat &src`: 源矩阵对象

### 析构函数

```cpp
Mat::~Mat();
```

**描述**: 析构函数释放矩阵对象的内存。

**参数**: void


## 元素访问

## 数据操作

## 算术运算符

## 线性代数

## 流操作符

## 全局算数运算符
