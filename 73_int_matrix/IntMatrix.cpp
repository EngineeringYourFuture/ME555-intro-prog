#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < numRows; i++) {
    rows[i] = new IntArray(numColumns);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < rhs.numRows; i++) {
    rows[i] = new IntArray(rhs[i]);
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < numRows; i++) {
    delete rows[i];
  }
  delete[] rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    for (int i = 0; i < numRows; i++) {
      delete rows[i];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      rows[i] = new IntArray(rhs[i]);
    }
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index) {
  assert(index >= 0 && index < numRows);
  return *rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numColumns != rhs.numColumns || numRows != rhs.numRows) {
    return false;
  }
  for (int i = 0; i < numRows; i++) {
    if ((*this)[i] != rhs[i]) {
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numColumns == rhs.numColumns && numRows == rhs.numRows);
  IntMatrix m(numRows, numColumns);
  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j < numColumns; j++) {
      m[i][j] = rhs[i][j] + (*this)[i][j];
    }
  }
  return m;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0) {
    s << "[ ]";
    return s;
  }
  s << "[";
  for (int i = 0; i < rhs.getRows(); i++) {
    if (i != rhs.getRows() - 1) {
      s << rhs[i] << ",\n";
    }
  }
  s << rhs[rhs.getRows() - 1] << "]";
  return s;
}
