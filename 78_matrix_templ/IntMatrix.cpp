#include "IntMatrix.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(0) {
}

IntMatrix::IntMatrix(size_t r, size_t c) : numRows(r), numColumns(c) {
  for (size_t i = 0; i < r; i++) {
    std::vector<int> vec(c);
    rows.push_back(vec);
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(rhs.rows) {
}

IntMatrix::~IntMatrix() {
}

IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    rows.clear();
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = rhs.rows;
  }
  return *this;
}

size_t IntMatrix::getRows() const {
  return numRows;
}

size_t IntMatrix::getColumns() const {
  return numColumns;
}

const std::vector<int> & IntMatrix::operator[](size_t index) const {
  assert(index >= 0 && index < numRows);
  return rows[index];
}

std::vector<int> & IntMatrix::operator[](size_t index) {
  assert(index >= 0 && index < numRows);
  return rows[index];
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if (numRows != rhs.numRows || numColumns != rhs.numColumns || rows != rhs.rows) {
    return false;
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix matrix(numRows, numColumns);
  for (size_t i = 0; i < numRows; i++) {
    for (size_t j = 0; j < numColumns; j++) {
      matrix.rows[i][j] = rows[i][j] + rhs.rows[i][j];
    }
  }
  return matrix;
}

std::ostream & operator<<(std::ostream & s, const std::vector<int> & rhs) {
  s << "{";
  for (size_t i = 0; i < rhs.size(); i++) {
    s << rhs[i];
    if (i != rhs.size() - 1) {
      s << ", ";
    }
  }
  s << "}";
  return s;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if (rhs.getRows() == 0) {
    s << "[ ]";
    return s;
  }
  s << "[";
  for (size_t i = 0; i < rhs.getRows(); i++) {
    if (i != rhs.getRows() - 1) {
      s << rhs[i] << ",\n";
    }
  }
  s << rhs[rhs.getRows() - 1] << "]";
  return s;
}
