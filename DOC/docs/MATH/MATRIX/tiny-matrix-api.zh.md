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
        Mat t();
        void normalize();
        float norm();
        float det(int n);
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

## 矩阵元数据

- `int rows`：矩阵的行数

- `int cols`：矩阵的列数

- `int stride`：矩阵的步幅，表示每行的字节数

- `int padding`：矩阵的填充大小，表示每行的填充字节数

- `int length`：矩阵的总元素个数

- `float *data`：指向矩阵数据的指针

- `bool ext_buff`：是否使用外部缓冲区

- `bool sub_matrix`：是否为子矩阵

## 子矩阵结构

### 子矩阵元数据

- `int x`：子矩阵的起始行

- `int y`：子矩阵的起始列

- `int width`：子矩阵的宽度

- `int height`：子矩阵的高度

### 子矩阵构造函数

```cpp
Mat::Rect::Rect(int x, int y, int width, int height);
```
- `x`：子矩阵的起始行

- `y`：子矩阵的起始列

- `width`：子矩阵的宽度

- `height`：子矩阵的高度

### 子矩阵重新调整大小

```cpp
void Mat::Rect::resizeRect(int x, int y, int width, int height);
```

- `x`：子矩阵的起始行

- `y`：子矩阵的起始列

- `width`：子矩阵的宽度

- `height`：子矩阵的高度

### 子矩阵面积

```cpp
int Mat::Rect::areaRect(void) const；
```

- 返回子矩阵的面积 （覆盖的元素个数）

## 构造函数和析构函数

### 默认构造函数

```cpp
Mat::Mat()；
```

**功能描述：** 默认构造函数，创建一个空矩阵。

**参数：** 无

### 内部分配构造函数

```cpp
Mat::Mat(int rows, int cols)；
```
**功能描述：** 创建一个指定行数和列数的矩阵，并分配内存。

**参数：**

- `int rows`：矩阵的行数

- `int cols`：矩阵的列数

### 外部缓冲区构造函数

```cpp
Mat::Mat(float *data, int rows, int cols)；
```
**功能描述：** 创建一个指定行数和列数的矩阵，并使用外部缓冲区。

**参数：**

- `float *data`：指向外部缓冲区的指针

- `int rows`：矩阵的行数

- `int cols`：矩阵的列数

### 外部缓冲区和步幅构造函数

```cpp
Mat::Mat(float *data, int rows, int cols, int stride)；
```

**功能描述：** 创建一个指定行数、列数和步幅的矩阵，并使用外部缓冲区。

**参数：**

- `float *data`：指向外部缓冲区的指针

- `int rows`：矩阵的行数

- `int cols`：矩阵的列数

- `int stride`：矩阵的步幅

### 拷贝构造函数

```cpp
Mat::Mat(const Mat &src)；
```

**功能描述：** 创建一个矩阵的拷贝。

**参数：**

- `const Mat &src`：要拷贝的矩阵

### 析构函数

```cpp
Mat::~Mat()；
```

**功能描述：** 析构函数，释放矩阵的内存。

**参数：** 无

### 内存分配函数

```cpp
void Mat::allocate()；
```

**功能描述：** 分配矩阵的内存。

**参数：** 无

## 矩阵元素访问

### 元素访问运算符

```cpp
inline float &operator()(int row, int col) { return data[row * stride + col]; }
```
**功能描述：** 访问矩阵的元素。

**参数：**

- `int row`：要访问的行索引

- `int col`：要访问的列索引

### 常量元素访问运算符

```cpp
inline const float &operator()(int row, int col) const { return data[row * stride + col]; }
```

**功能描述：** 访问矩阵的元素（常量版本）。

**参数：**

- `int row`：要访问的行索引

- `int col`：要访问的列索引


## 数据操作

### 拷贝函数

```cpp
void Mat::Copy(const Mat &src, int row_pos, int col_pos)；
```

**功能描述：** 将源矩阵的内容拷贝到当前矩阵的指定位置。

**参数：**

- `const Mat &src`：源矩阵

- `int row_pos`：目标矩阵的起始行索引

- `int col_pos`：目标矩阵的起始列索引

### 拷贝头函数

```cpp
void Mat::CopyHead(const Mat &src)；
```

**功能描述：** 将源矩阵的头部信息拷贝到当前矩阵。

**参数：**

- `const Mat &src`：源矩阵

### 获取ROI函数

```cpp
Mat getROI(int startRow, int startCol, int roiRows, int roiCols, int stride)；
```

**功能描述：** 获取矩阵的感兴趣区域（ROI）。

**参数：**

- `int startRow`：ROI的起始行索引

- `int startCol`：ROI的起始列索引

- `int roiRows`：ROI的行数

- `int roiCols`：ROI的列数

- `int stride`：步幅 

### 获取ROI函数（重载-无步幅）

```cpp
Mat getROI(int startRow, int startCol, int roiRows, int roiCols)；
```

**功能描述：** 获取矩阵的感兴趣区域（ROI）。

**参数：**

- `int startRow`：ROI的起始行索引

- `int startCol`：ROI的起始列索引

- `int roiRows`：ROI的行数

- `int roiCols`：ROI的列数

### 获取ROI函数（重载-子矩阵）

```cpp
Mat getROI(const Rect &rect)；
```

**功能描述：** 获取矩阵的感兴趣区域（ROI）。

**参数：**

- `const Rect &rect`：子矩阵的矩形区域

### 获取子矩阵函数

```cpp
Mat Get(int row_start, int row_size, int col_start, int col_size)；
```

**功能描述：** 获取矩阵的子矩阵。

**参数：**

- `int row_start`：子矩阵的起始行索引

- `int row_size`：子矩阵的行数

- `int col_start`：子矩阵的起始列索引

- `int col_size`：子矩阵的列数
### 获取子矩阵函数（重载-矩形区域）

```cpp
Mat Get(const Rect &rect)；
```

**功能描述：** 获取矩阵的子矩阵。

**参数：**

- `const Rect &rect`：子矩阵的矩形区域

### 获取块函数

```cpp
Mat block(int startRow, int startCol, int blockRows, int blockCols)；
```

**功能描述：** 获取矩阵的块。

**参数：**

- `int startRow`：块的起始行索引

- `int startCol`：块的起始列索引

- `int blockRows`：块的行数

- `int blockCols`：块的列数

### 交换行函数

```cpp
void swapRows(int row1, int row2)；
```

**功能描述：** 交换矩阵的两行。

**参数：**

- `int row1`：要交换的第一行索引

- `int row2`：要交换的第二行索引

### 清空函数

```cpp
void clear()；
```

**功能描述：** 清空矩阵的内容。

**参数：** 无

!!! tip "getROI | Get | block"
    - getROI：获取矩阵的感兴趣区域（ROI）
    - Get：获取矩阵的子矩阵
    - block：获取矩阵的块

| 方法         | 是否拷贝数据 | 是否新建内存 | 修改后是否影响原矩阵 | 性能       | 适用场景            |
|--------------|--------------|--------------|----------------------|------------|---------------------|
| `getROI`     | 否           | 否           | 会影响               | ⭐⭐⭐⭐⭐     | 快速处理临时子矩阵  |
| `Get`        | 是           | 是           | 不影响               | ⭐⭐⭐⭐      | 安全独立的子矩阵    |
| `block`      | 是           | 是           | 不影响               | ⭐⭐⭐       | 灵活处理复杂拷贝    |


## 打印和调试

### 打印头函数

```cpp
void Mat::PrintHead()；
```

**功能描述：** 打印矩阵的元数据。

**参数：** 无

### 打印矩阵函数

```cpp
void Mat::PrintMatrix(bool show_padding, const std::string &label)；
```

**功能描述：** 打印矩阵的内容。

**参数：**

- `bool show_padding`：是否显示填充

- `const std::string &label`：打印的标签


## 算术运算符

### 赋值运算符

```cpp
Mat &operator=(const Mat &src)；
```

**功能描述：** 赋值运算符，将源矩阵的内容赋值给当前矩阵。

**参数：**

- `const Mat &src`：源矩阵

!!! warning "注意"
    该运算符会讲当前矩阵拷贝成为源矩阵的大小，且元素的值也会拷贝到当前矩阵中。两者并不共享内存，因为该操作会新分配内存。

### 加法运算符

```cpp
Mat &operator+=(const Mat &A)；
```

**功能描述：** 加法运算符，将当前矩阵与另一个矩阵相加。

**参数：**

- `const Mat &A`：要相加的矩阵

### 加法运算符（加常数）

```cpp
Mat &operator+=(float C)；
```

**功能描述：** 加法运算符，将当前矩阵与一个常数相加。

**参数：**

- `float C`：要相加的常数

### 减法运算符

```cpp
Mat &operator-=(const Mat &A)；
```

**功能描述：** 减法运算符，将当前矩阵与另一个矩阵相减。

**参数：**

- `const Mat &A`：要相减的矩阵

### 减法运算符（减常数）

```cpp
Mat &operator-=(float C)；
```

**功能描述：** 减法运算符，将当前矩阵与一个常数相减。

**参数：**

- `float C`：要相减的常数

### 乘法运算符

```cpp
Mat &operator*=(const Mat &A)；
```

**功能描述：** 乘法运算符，将当前矩阵与另一个矩阵相乘。

**参数：**

- `const Mat &A`：要相乘的矩阵

### 乘法运算符（乘常数）

```cpp
Mat &operator*=(float C)；
```

**功能描述：** 乘法运算符，将当前矩阵与一个常数相乘。

**参数：**

- `float C`：要相乘的常数

### 除法运算符 （按元素）

```cpp
Mat &operator/=(const Mat &B)；
```

**功能描述：** 除法运算符，将当前矩阵除以另一个矩阵。

**参数：**

- `const Mat &B`：要除以的矩阵

### 除法运算符（除常数）

```cpp
Mat &operator/=(float C)；
```

**功能描述：** 除法运算符，将当前矩阵除以一个常数。

**参数：**

- `float C`：要除以的常数

### 幂运算符

```cpp
Mat operator^(int C)；
```

**功能描述：** 幂运算符，将当前矩阵的每个元素都进行幂运算。

**参数：**

- `int C`：幂的指数


## 线性代数

### 归一化函数

```cpp
void Mat::normalize(void) // normalize the matrix
```

**功能描述：** 归一化矩阵。

**参数：** 无

### 范数函数

```cpp
float Mat::norm(void) // calculate matrix norm
```

**功能描述：** 计算矩阵的范数。

**参数：** 无

### 行列式函数

```cpp
float Mat::det(int n) // calculate determinant
```

**功能描述：** 计算矩阵的行列式。

**参数：**

- `int n`：矩阵的大小

### 转置函数

```cpp
Mat Mat::t()
```

**功能描述：** 转置矩阵。

**参数：** 无

### 逆矩阵函数

```cpp
Mat Mat::inverse()
```

**功能描述：** 计算矩阵的逆矩阵。

**参数：** 无

### 伪逆矩阵函数

```cpp
Mat Mat::pinv()
```

**功能描述：** 计算矩阵的伪逆矩阵。

**参数：** 无

### 高斯消元函数

```cpp
Mat Mat::gaussianEliminate()
```

**功能描述：** 进行高斯消元操作。

**参数：** 无

### 行简化函数

```cpp
Mat Mat::rowReduceFromGaussian()
```

**功能描述：** 进行行简化操作。

**参数：** 无


## 实用函数

### 单位矩阵函数

```cpp
Mat Mat::eye(int size)
```

**功能描述：** 创建一个单位矩阵。

**参数：**

- `int size`：矩阵的大小

### 全1矩阵函数

```cpp
Mat Mat::ones(int size)
```

**功能描述：** 创建一个全1方阵。

**参数：**  

- `int size`：矩阵的大小

### 全1矩阵函数（重载-指定行列）

```cpp
Mat Mat::ones(int rows, int cols)
```

**功能描述：** 创建一个全1矩阵。

**参数：**

- `int rows`：矩阵的行数

- `int cols`：矩阵的列数

### 解线性方程组函数

```cpp
Mat Mat::solve(Mat A, Mat b)
```

**功能描述：** 解线性方程组Ax = b。

**参数：**

- `Mat A`：系数矩阵

- `Mat b`：常数矩阵

### 带状矩阵求解函数

```cpp
Mat Mat::bandSolve(Mat A, Mat b, int k)
```

**功能描述：** 解带状矩阵方程Ax = b。

**参数：**

- `Mat A`：系数矩阵

- `Mat b`：常数矩阵

- `int k`：带宽

### 求根函数

```cpp
Mat Mat::roots(Mat A, Mat y)
```

**功能描述：** 求线性方程组的根。

**参数：**

- `Mat A`：系数矩阵
- `Mat y`：常数矩阵

### 点积函数

```cpp
Mat Mat::dotProduct(Mat A, Mat B)
```

**功能描述：** 计算两个矩阵的点积。

**参数：**

- `Mat A`：第一个矩阵

- `Mat B`：第二个矩阵

### 增广矩阵函数

```cpp
Mat Mat::augment(Mat A, Mat B)
```

**功能描述：** 创建增广矩阵。

**参数：**

- `Mat A`：第一个矩阵

- `Mat B`：第二个矩阵

### 代数余子式函数

```cpp
Mat Mat::cofactor(int row, int col, int n)
```

**功能描述：** 计算代数余子式。

**参数：**

- `int row`：行索引

- `int col`：列索引

- `int n`：矩阵的大小

### 伴随矩阵函数

```cpp
Mat Mat::adjoint()
```

**功能描述：** 计算伴随矩阵。

**参数：** 无

### 指数函数

```cpp
Mat Mat::expHelper(const Mat &m, int num)
```

**功能描述：** 计算矩阵的指数。

**参数：**

- `const Mat &m`：矩阵

- `int num`：指数的大小

## 流操作符

### 输出流操作符

```cpp
std::ostream &operator<<(std::ostream &os, const Mat &m)
```

**功能描述：** 输出矩阵到输出流。

**参数：**

- `std::ostream &os`：输出流

- `const Mat &m`：要输出的矩阵

### 输出流操作符（矩形区域）

```cpp
std::ostream &operator<<(std::ostream &os, const Mat::Rect &rect)
```

**功能描述：** 输出矩形区域到输出流。

**参数：**

- `std::ostream &os`：输出流

- `const Mat::Rect &rect`：要输出的矩形区域

### 输入流操作符

```cpp
std::istream &operator>>(std::istream &is, Mat &m)
```

**功能描述：** 从输入流读取矩阵。

**参数：**

- `std::istream &is`：输入流

- `Mat &m`：要读取的矩阵

## 全局算术运算符

### 加法运算符

```cpp
Mat operator+(const Mat &A, const Mat &B)
```

**功能描述：** 加法运算符，将两个矩阵相加。

**参数：**

- `const Mat &A`：第一个矩阵

- `const Mat &B`：第二个矩阵

### 加法运算符（加常数）

```cpp
Mat operator+(const Mat &A, float C)
```

**功能描述：** 加法运算符，将矩阵与一个常数相加。

**参数：**

- `const Mat &A`：矩阵

- `float C`：要相加的常数

### 减法运算符

```cpp
Mat operator-(const Mat &A, const Mat &B)
```

**功能描述：** 减法运算符，将两个矩阵相减。

**参数：**

- `const Mat &A`：第一个矩阵

- `const Mat &B`：第二个矩阵

### 减法运算符（减常数）

```cpp
Mat operator-(const Mat &A, float C)
```

**功能描述：** 减法运算符，将矩阵与一个常数相减。

**参数：**

- `const Mat &A`：矩阵

- `float C`：要相减的常数

### 乘法运算符

```cpp
Mat operator*(const Mat &A, const Mat &B)
```

**功能描述：** 乘法运算符，将两个矩阵相乘。

**参数：**

- `const Mat &A`：第一个矩阵

- `const Mat &B`：第二个矩阵

### 乘法运算符（乘常数）

```cpp
Mat operator*(const Mat &A, float C)
```

**功能描述：** 乘法运算符，将矩阵与一个常数相乘。

**参数：**

- `const Mat &A`：矩阵

- `float C`：要相乘的常数

### 乘法运算符（常数乘矩阵）

```cpp
Mat operator*(float C, const Mat &A)
```

**功能描述：** 乘法运算符，将一个常数与矩阵相乘。

**参数：**

- `float C`：要相乘的常数

- `const Mat &A`：矩阵

### 除法运算符 （除常数）

```cpp
Mat operator/(const Mat &A, float C)
```

**功能描述：** 除法运算符，将矩阵除以一个常数。

**参数：**

- `const Mat &A`：矩阵

- `float C`：要除以的常数

### 除法运算符 （按元素）

```cpp
Mat operator/(const Mat &A, const Mat &B)
```

**功能描述：** 除法运算符，将矩阵除以另一个矩阵。

**参数：**

- `const Mat &A`：第一个矩阵

- `const Mat &B`：第二个矩阵

### 等于运算符

```cpp
bool operator==(const Mat &A, const Mat &B)
```

**功能描述：** 等于运算符，判断两个矩阵是否相等。

**参数：**

- `const Mat &A`：第一个矩阵

- `const Mat &B`：第二个矩阵
