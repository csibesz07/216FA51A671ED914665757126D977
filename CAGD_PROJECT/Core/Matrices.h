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


    // forward declaration of template class TriangularMatrix
        template <typename T>
        class TriangularMatrix;

    //----------------------
    // template class Matrix
    //----------------------
    template <typename T>
            class Matrix
    {
        template<typename U>
        friend std::ostream& operator << (std::ostream&, const Matrix<U>& rhs);
        template<typename U>
        friend std::istream& operator >> (std::istream&, Matrix<U>& rhs);

        template <typename U>
        friend std::istream& operator >>(std::istream& lhs, TriangularMatrix<U>& rhs);

        template <typename U>
        friend std::ostream& operator << (std::ostream& lhs, const TriangularMatrix<U>& rhs);

    protected:
        unsigned int                    _row_count;
        unsigned int                    _column_count;
        std::vector< std::vector<T> >   _data;
    public:
        // special constructor (can also be used as a default constructor)
        Matrix(unsigned int row_count = 1,
               unsigned int column_count = 1);

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
        virtual ~Matrix(){
                delete &_data;
        }
    };

    //-------------------------
    // template class RowMatrix
    //-------------------------
    template <typename T>
            class RowMatrix : public Matrix<T>
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
            class ColumnMatrix : public Matrix<T>
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

    //--------------------------------
    // template class TriangularMatrix
    //--------------------------------
    template <typename T>
    class TriangularMatrix
    {
    protected:
        GLuint                        _row_count;
        std::vector<T> _data;

    public:
        // special constructor (can also be used as a default constructor)
        TriangularMatrix(GLuint row_count = 1);

        // get element by reference
        T& operator ()(GLuint row, GLuint column);

        // get copy of an element
        T operator ()(GLuint row, GLuint column) const;

        // get dimension
        GLuint GetRowCount() const;

        // set dimension
        GLboolean ResizeRows(GLuint row_count);
    };

    //--------------------------------------------------
    // homework: implementation of template class Matrix
    //--------------------------------------------------

    template<class T>
    Matrix<T>::Matrix(unsigned int row_count,unsigned int column_count):
            _row_count(row_count),
            _column_count(column_count),
            _data(row_count, std::vector<T>(column_count))
    {
    }


    template<class T>
    Matrix<T>::Matrix(const Matrix& m):
            _row_count(m._row_count),
            _column_count(m._column_count),
            _data(m._data)
    {
    }

    template<class T>
    Matrix<T>& Matrix<T>::operator =(const Matrix& m) {

        if (this != &m)
        {
            _row_count = m._row_count;
            _column_count = m._column_count;
            _data = m._data;
        }

        return *this;
    }

    template<class T>
    T& Matrix<T>::operator()(unsigned int row, unsigned int column) {
        return _data[row][column];
    }

    template<class T>
    T Matrix<T>::operator()(unsigned int row, unsigned int column) const {
        return _data[row][column];
    }

    template<class T>
    inline unsigned int Matrix<T>::GetRowCount() const {
        return _row_count;
    }

    template<class T>
    inline unsigned int Matrix<T>::GetColumnCount() const {
        return _column_count;
    }

    template<class T>
    inline GLboolean Matrix<T>::ResizeRows(unsigned int row_count) {
        _data.resize(row_count);
        for (GLuint i = _row_count; i < row_count; i++) {
            _data[i].resize(_column_count);
        }
        _row_count = row_count;
        return GL_TRUE;
    }

    template<class T>
    inline GLboolean Matrix<T>::ResizeColumns(unsigned int column_count) {
        _column_count = column_count;
        for (GLuint i = 0; i < _row_count; i++) {
            _data[i].resize(_column_count);
        }
        return GL_TRUE;
    }

    template<class T>
    GLboolean Matrix<T>::SetRow(unsigned int index, const RowMatrix<T>& row) {
        if (index >= _row_count || _column_count != row._column_count)
            return GL_FALSE;

        _data[index] = row._data[0];

        return GL_TRUE;
    }

    template<class T>
    GLboolean Matrix<T>::SetColumn(unsigned int index, const ColumnMatrix<T>& column) {

        if (index >= _column_count || _row_count != column._row_count)
            return GL_FALSE;

        for (GLuint i = 0; i < _row_count; i++) {
            _data[i][index] = column._data[i][0];
        }

        return GL_TRUE;
    }

    //-----------------------------------------------------
    // homework: implementation of template class RowMatrix
    //-----------------------------------------------------

    template<class T>
    RowMatrix<T>::RowMatrix(unsigned int column_count): Matrix<T>(1, column_count) {
    }

    template<class T>
    T& RowMatrix<T>::operator ()(unsigned int column) {
        return this->_data[0][column];
    }

    template<class T>
    T& RowMatrix<T>::operator [](unsigned int column) {
        return this->_data[0][column];
    }

    template<class T>
    T RowMatrix<T>::operator ()(unsigned int column) const {
        return this->_data[0][column];
    }

    template<class T>
    T RowMatrix<T>::operator [](unsigned int column) const {
        return this->_data[0][column];
    }

    template<class T>
    GLboolean RowMatrix<T>::ResizeRows(unsigned int row_count) {
        return (row_count == 1 ? GL_TRUE : GL_FALSE);
    }

    //template<class T>
    //RowMatrix<T>::~RowMatrix(){};

    //--------------------------------------------------------
    // homework: implementation of template class ColumnMatrix
    //--------------------------------------------------------

    template<class T>
    ColumnMatrix<T>::ColumnMatrix(unsigned int row_count): Matrix<T>(row_count, 1) {
    }

    template<class T>
    T& ColumnMatrix<T>::operator ()(unsigned int row) {
        return this->_data[row][0];
    }

    template<class T>
    T& ColumnMatrix<T>::operator [](unsigned int row) {
        return this->_data[row][0];
    }

    template<class T>
    T ColumnMatrix<T>::operator ()(unsigned int row) const {
        return this->_data[row][0];
    }

    template<class T>
    T ColumnMatrix<T>::operator [](unsigned int row) const {
        return this->_data[row][0];
    }

    template<class T>
    GLboolean ColumnMatrix<T>::ResizeColumns(unsigned int column_count) {
        return (column_count == 1 ? GL_TRUE : GL_FALSE);
    }

    //template<class T>
    //ColumnMatrix<T>::~ColumnMatrix() {};

    //--------------------------------------------------------
    // homework: implementation of template class ColumnMatrix
    //--------------------------------------------------------

    template<class T>
    TriangularMatrix<T>::TriangularMatrix(GLuint row_count):
            _row_count(row_count),
            _data((row_count+2)*(row_count+1)/2)
    {
    }

    template<class T>
    T& TriangularMatrix<T>::operator ()(GLuint row, GLuint column) {
        return _data[(row+1)*row/2+column];
    }

    template<class T>
    T TriangularMatrix<T>::operator ()(GLuint row, GLuint column) const {
        return _data[(row+1)*row/2+column];
    }

    template<class T>
    GLuint TriangularMatrix<T>::GetRowCount() const {
        return _row_count;
    }

    template<class T>
    GLboolean TriangularMatrix<T>::ResizeRows(unsigned int row_count) {
        return (row_count == _row_count ? GL_TRUE : GL_FALSE);
    }


    //------------------------------------------------------------------------------
    // definitions of overloaded and templated input/output from/to stream operators
    //------------------------------------------------------------------------------


    // output to stream
    template <typename T>
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
    template <typename T>
            std::istream& operator >>(std::istream& lhs, Matrix<T>& rhs)
    {
        // homework
        lhs >> rhs._row_count >> rhs._column_count;
        rhs.ResizeRows(rhs._row_count);
        for (typename std::vector< std::vector<T> >::iterator row = rhs._data.begin();
                                                              row != rhs._data.end(); ++row)
        {
            row->resize(rhs._column_count);
            for (typename std::vector<T>::iterator column = row->begin();
                                                   column != row->end(); ++column)
                lhs >> *column;
        }
        return lhs;
    }
};

