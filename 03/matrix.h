#include <iostream>

using namespace std;

class Row
{
    int col_am;
    int* row;

public:
    Row(int* row_ptr, int col_am)
    {
        row = row_ptr;
        this->col_am = col_am;
    }    

    int& operator[](int col_ind)
    {
        if ((col_ind <= col_am) && (col_ind >= 0))
        {        
            int* tmp = row;
            delete this;
            return tmp[col_ind];
        }
        else
            throw out_of_range("");
    }
};

class Matrix
{
    int row_am, col_am;
    int *my_matrix;

public:
    Matrix(int rows_am=0, int cols_am=0)
    {
        this->row_am = rows_am;
        this->col_am = cols_am;
        
        if (rows_am && col_am)
        {
            my_matrix = new int[rows_am * cols_am];
            Init();
        }
        else
            my_matrix = nullptr;
    }

    ~Matrix() { if (my_matrix != nullptr) delete [] my_matrix; }
    
    int* getMatrPtr() { return my_matrix; }

    void Init()
    {
        for (int i=0; i<row_am; i++)
            for (int j=0; j<col_am; j++)
                my_matrix[j + i*col_am] = 0;
    }
    
    void Print()
    {
        for (int i=0; i<row_am; i++)
        {
            if (i != 0) cout << endl;
            for (int j=0; j<col_am; j++)
                cout << my_matrix[j + i*col_am] <<' ';
        }
        cout << endl;
    }

    int getRows() { return row_am; }

    int getColumns() { return col_am; }
    
    void operator*=(int num)
    {
        for (int i=0; i<row_am; i++)
            for (int j=0; j<col_am; j++)
                my_matrix[j + i*col_am] *= num;
    }
    
    bool operator==(Matrix &matr)
    {
        bool flag = true;
        
        if ((matr.getColumns() != getColumns()) ||
            (matr.getRows() != getRows()))
            return false;

        for (int i=0; i<row_am; i++)
            for (int j=0; j<col_am; j++)
                if (my_matrix[j + i*col_am] != matr.getMatrPtr()[j + i*col_am])
                {
                    flag = false;
                    break;
                }

        return flag;
    }
    
    bool operator!=(Matrix &matr) { return !(*this == matr); }

    Row& operator[](int row_ind)
    {
        if ((row_ind < row_am) && (row_ind >= 0))
            return *(new Row(my_matrix + col_am * row_ind, col_am));
        else 
            throw out_of_range("");
    }
};
