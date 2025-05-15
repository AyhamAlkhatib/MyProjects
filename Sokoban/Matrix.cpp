
// Copyright Ayham Alkhatib 2023
#include "Matrix.hpp"
std::ostream& operator<<(std::ostream& out, Matrix& mat) {
    for (int i = 0; i < (mat._rows * mat._columns); i++) {
        if ((i % mat._columns) == 0 && i != 0) {
                out << std::endl;
        }
    out << mat.data[i];
    }
    return out;
}

char& Matrix::operator()(size_t rows, size_t columns) {
     return data[indexAt(rows, columns)];
}

std::istream& operator>>(std::istream& in,  Matrix& obj) {
    for (int i = 0; i < obj._rows; i++) {
        for (int j = 0; j < obj._columns; j++) {
            in >> obj(i, j);
        }
    }
      return in;
}

Matrix& Matrix::operator=(const Matrix& obj) {
    if (this == &obj) return *this;
    this->_rows = obj.getRows();
    this->_columns = obj.getColumns();
    delete []this->data;
    this->data = new char[_rows * _columns];
    this->_size = _rows * _columns;
    for (int i = 0; i < this->getSize(); i++) {
        this->data[i] = obj.data[i];
    }
    return *this;
}
/*
Matrix::~Matrix() {
    delete[] data;
    data = nullptr;
    _rows = 0;
    _columns = 0;
}*/