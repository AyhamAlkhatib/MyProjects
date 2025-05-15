// Copyright Ayham Alkhatib 2023
#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
class Matrix {
 public:
    // Accessors
    char getData(int index) const { return data[index];}
    int getRows() const {return _rows;}
    int getColumns() const {return _columns;}
    int getSize () const {return _size;}
    // Mutators
    void setRows(int rows) {_rows = rows;}
    void setColumns(int columns) {_columns = columns;}
    void setData() { data = new char[_rows * _columns];}
    void setDataAt(int index, char ch) { data[index] = ch;}
    char& operator()(size_t y, size_t x);
    void setSize() {_size = _rows * _columns;}
    Matrix& operator=(const Matrix& obj);
        // friend ()'s
    friend std::ostream& operator<<(std::ostream& out, Matrix& mat);
    friend std::istream& operator>>(std::istream& in,  Matrix& obj);
    // Destructor
    //~Matrix();
 private:
    int _columns;
    int _rows;
    char* data;
    size_t indexAt(size_t y, size_t x) {
        return x + y * _columns;
    }
    int _size;
};
