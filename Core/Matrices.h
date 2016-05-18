#pragma once

#include <iostream>
#include <vector>
#include <GL/glew.h>

namespace cagd
{
    // forward declaration of template class Matrix
    template <typename T>
    class Matrix;

    // forward declaration of template class RowMatrix
    template <typename T>
    class RowMatrix;

    // forward declaration of template class ColumnMatrix
    template <typename T>
    class ColumnMatrix;

    // forward declarations of overloaded and templated input/output from/to stream operators
    template <typename T>
    std::ostream& operator << (std::ostream& lhs, const Matrix<T>& rhs);

    template <typename T>
    std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs);

    //----------------------
    // template class Matrix
    //----------------------
    template <typename T>
    class Matrix
    {
        friend std::ostream& cagd::operator << <T>(std::ostream&, const Matrix<T>& rhs);
        friend std::istream& cagd::operator >> <T>(std::istream&, Matrix<T>& rhs);

    protected:
        unsigned int                    _row_count;
        unsigned int                    _column_count;
        std::vector< std::vector<T> >   _data;
    public:
        // special constructor (can also be used as a default constructor)
        Matrix(unsigned int row_count = 1, unsigned int column_count = 1);

        // copy constructor
        Matrix(const Matrix& m);

        // assignment operator
        Matrix& operator =(const Matrix& m);

        // get element by reference
        T& operator ()(unsigned int row, unsigned int column);

        // get copy of an element
        T operator ()(unsigned int row, unsigned int column) const;

        // get dimensions
        unsigned int GetRowCount() const;
        unsigned int GetColumnCount() const;

        // set dimensions
        virtual GLboolean ResizeRows(unsigned int row_count);
        virtual GLboolean ResizeColumns(unsigned int column_count);

        // update
        GLboolean SetRow(unsigned int index, const RowMatrix<T>& row);
        GLboolean SetColumn(unsigned int index, const ColumnMatrix<T>& column);

        // destructor
        virtual ~Matrix();
    };

    //-------------------------
    // template class RowMatrix
    //-------------------------
    template <typename T>
    class RowMatrix: public Matrix<T>
    {
    public:
        // special constructor (can also be used as a default constructor)
        RowMatrix(unsigned int column_count = 1);

        // get element by reference
        T& operator ()(unsigned int column);
        T& operator [](unsigned int column);

        // get copy of an element
        T operator ()(unsigned int column) const;
        T operator [](unsigned int column) const;

        // a row matrix consists of a single row
        GLboolean ResizeRows(unsigned int row_count);
    };

    //----------------------------
    // template class ColumnMatrix
    //----------------------------
    template <typename T>
    class ColumnMatrix: public Matrix<T>
    {
    public:
        // special constructor (can also be used as a default constructor)
        ColumnMatrix(unsigned int row_count = 1);

        // get element by reference
        T& operator ()(unsigned int row);
        T& operator [](unsigned int row);

        // get copy of an element
        T operator ()(unsigned int row) const;
        T operator [](unsigned int row) const;

        // a column matrix consists of a single column
        GLboolean ResizeColumns(unsigned int column_count);
    };

    //--------------------------------------------------
    // homework: implementation of template class Matrix
    //--------------------------------------------------
    // special constructor (can also be used as a default constructor)
    template <class T>
    Matrix<T>::Matrix(unsigned int row_count , unsigned int column_count )
    {
        _row_count = row_count;
        _column_count = column_count;
        _data.resize(_row_count);
        for (int i = 0; i < _row_count; i++)
        {
            _data.resize(_column_count);
        }
    }
    // copy constructor
    template<class T>
    Matrix<T>::Matrix(const Matrix<T>& m): _row_count(m._row_count), _column_count(m._column_count), _data(m._data)
    {
    }
    // assignment operator
    template<class T>
    Matrix<T>& Matrix<T>::operator =(const Matrix<T>& m)
    {
        if (this != &m)
        {
            _row_count = m._row_count;
            _column_count = m._column_count;
            _data = m._data;
        }
        return *this;
    }
    // get element by reference
    template<class T>
    T& Matrix<T>::operator ()(unsigned int row, unsigned int column)
    {
        return _data[row][column];
    }

    // get copy of an element
    template<class T>
    T Matrix<T>::operator ()(unsigned int row, unsigned int column) const
    {
        return _data[row][column];
    }

    // get dimensions
    template<class T>
    unsigned int Matrix<T>::GetRowCount() const
    {
        return _row_count;
    }

    template<class T>
    unsigned int Matrix<T>::GetColumnCount() const
    {
        return _column_count;
    }

    // set dimensions
    template<class T>
    GLboolean Matrix<T>::ResizeRows(unsigned int row_count) {
        _data.resize(row_count);
        for (GLuint i = _row_count; i < row_count; ++i)
        {
            _data[i].resize(_column_count);
        }
        _row_count = row_count;
        return GL_TRUE;
    }

    template<class T>
    GLboolean Matrix<T>::ResizeColumns(unsigned int column_count) {
         for (GLuint i = 0; i < _row_count; ++i)
         {
            _data[i].resize(column_count);
         }
          _column_count = column_count;
         return GL_TRUE;
    }
    // update
    template<class T>
    GLboolean Matrix<T>::SetRow(unsigned int index, const RowMatrix<T> &row)
    {
        if ( index >= _row_count || row._column_count != _column_count)
        {
            return GL_FALSE;
        }
        _data[index] = row._data[0];

        return GL_TRUE;
    }

    template<class T>
    GLboolean Matrix<T>::SetColumn(unsigned int index, const ColumnMatrix<T>& column) {
        if(column.GetRowCount() != _row_count) {
            return GL_FALSE;
        }

        for (int i = 0; i<_row_count; i++){
            _data[i][index] = column[i];
        }

        return GL_TRUE;
    }

    // destructor
    template<class T>
    Matrix<T>::~Matrix()
    {
        _data.clear();
    }

    //-----------------------------------------------------
    // homework: implementation of template class RowMatrix
    //-----------------------------------------------------
    template<class T>
    RowMatrix<T>::RowMatrix(unsigned int column_count) {
        this->_column_count = column_count;
        this->_row_count = 1;
        this->_data.resize(1);
        this->_data[0].resize(column_count);
    }

    // get element by reference
    template<class T>
    T& RowMatrix<T>::operator ()(unsigned int column) {
        return this->_data[0][column];
    }

    template<class T>
    T& RowMatrix<T>::operator [](unsigned int column) {
        return this->_data[0][column];
    }

    // get copy of an element
    template<class T>
    T RowMatrix<T>::operator ()(unsigned int column) const {
        return this->_data[0][column];
    }

    template<class T>
    T RowMatrix<T>::operator [](unsigned int column) const {
        return this->_data[0][column];
    }

    // a row matrix consists of a single row
    template<class T>
    GLboolean RowMatrix<T>::ResizeRows(unsigned int row_count) {
        if(row_count != 1) {
            return GL_FALSE;
        }

        return GL_TRUE;
    }

    //--------------------------------------------------------
    // homework: implementation of template class ColumnMatrix
    //--------------------------------------------------------
    template<class T>
    ColumnMatrix<T>::ColumnMatrix(unsigned int row_count) {
        this->_row_count = row_count;
        this->_column_count = 1;
        this->_data.resize(row_count);
        for(GLuint i = 0; i < this->_row_count; ++i) {
            this->_data[i].resize(1);
        }
    }

    // get element by reference
    template<class T>
    T& ColumnMatrix<T>::operator ()(unsigned int row) {
        return this->_data[row][0];
    }

    template<class T>
    T& ColumnMatrix<T>::operator [](unsigned int row) {
        return this->_data[row][0];
    }

    // get copy of an element
    template<class T>
    T ColumnMatrix<T>::operator ()(unsigned int row) const {
        return this->_data[row][0];
    }

    template<class T>
    T ColumnMatrix<T>::operator [](unsigned int row) const {
        return this->_data[row][0];
    }

    // a column matrix consists of a single column
    template<class T>
    GLboolean ColumnMatrix<T>::ResizeColumns(unsigned int column_count) {
        if(column_count != 1) {
            return GL_FALSE;
        }

        return GL_TRUE;
    }


    //------------------------------------------------------------------------------
    // definitions of overloaded and templated input/output from/to stream operators
    //------------------------------------------------------------------------------

    // output to stream
    template <class T>
    std::ostream& operator <<(std::ostream& lhs, const Matrix<T>& rhs)
    {
        lhs << rhs._row_count << " " << rhs._column_count << std::endl;
        for (typename std::vector< std::vector<T> >::const_iterator row = rhs._data.begin();
             row != rhs._data.end(); ++row)
        {
            for (typename std::vector<T>::const_iterator column = row->begin();
                 column != row->end(); ++column)
                    lhs << *column << " ";
            lhs << std::endl;
        }
        return lhs;
    }

    // input from stream
    template <class T>
    std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs)
    {
        // homework
        lhs >> rhs._row_count >> rhs._column_count;
        rhs._data.resize(rhs._row_count);
        for(int i = 0; i < rhs._row_count; i++) {
            rhs._data[i].resize(rhs._column_count);
            for(int j = 0; j < rhs._column_count; j++) {
                lhs >> rhs._data[i][j];
            }
        }
        return lhs;
    }
}
