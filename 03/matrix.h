#include <iostream>

class Row
{
    size_t col_am;
    int* row;

public:
    Row(int* row_ptr, size_t col_am)
    {
        row = row_ptr;
        this->col_am = col_am;
    }    

    int& operator[](size_t col_ind)
    {
        if ((col_ind <= col_am) && (col_ind >= 0))
        {        
            //int* tmp = row;
            //delete this;
            return row[col_ind];
        }
        else
            throw std::out_of_range("");
    }
};

class Matrix
{
    size_t row_am, col_am;
    int *my_matrix;

public:
    Matrix(size_t rows_am=0, size_t cols_am=0)
    {
        this->row_am = rows_am;
        this->col_am = cols_am;
        
        if (rows_am && col_am)
            my_matrix = new int[rows_am * cols_am]();
        else
            my_matrix = nullptr;
    }

    ~Matrix() { if (my_matrix != nullptr) delete [] my_matrix; }
    
    int* getMatrPtr() const { return my_matrix; }

    void Init()
    {
        for (size_t i=0; i<row_am; i++)
            for (size_t j=0; j<col_am; j++)
                my_matrix[j + i*col_am] = 0;
    }
    
    void Print() const
    {
        for (size_t i=0; i<row_am; i++)
        {
            if (i != 0) std::cout << std::endl;
            for (size_t j=0; j<col_am; j++)
                std::cout << my_matrix[j + i*col_am] <<' ';
        }
        std::cout << std::endl;
    }

    size_t getRows() const { return row_am; }

    size_t getColumns() const { return col_am; }
    
    Matrix& operator*=(int num)
    {
        for (size_t i=0; i<row_am; i++)
            for (size_t j=0; j<col_am; j++)
                my_matrix[j + i*col_am] *= num;
        return *this;
    }
    
    bool operator==(const Matrix &matr) const
    {
        if ((matr.getColumns() != getColumns()) ||
            (matr.getRows() != getRows()))
            return false;

        for (size_t i=0; i<row_am; i++)
            for (size_t j=0; j<col_am; j++)
                if (my_matrix[j + i*col_am] != matr.my_matrix[j + i*col_am])
                    return false;

        return true;
    }
    
    bool operator!=(const Matrix &matr) const { return !(*this == matr); }

    Row operator[](size_t row_ind)
    {
        if ((row_ind < row_am) && (row_ind >= 0))
            return Row(my_matrix + col_am * row_ind, col_am);
        else 
            throw std::out_of_range("");
    }
};
