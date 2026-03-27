// File: charclass_delete_test_377.cc

#include <gtest/gtest.h>
#include <cstdint>

namespace re2 {
// Forward declaration only for the callable interface we exercise.
// The definition/implementation is provided by ./TestProjects/re2/re2/regexp.cc
class CharClass {
public:
  void Delete();  // implemented in regexp.cc
};
}  // namespace re2

// NOTE:
// We cannot construct CharClass via public ctor or New() (they're private),
// and we cannot rely on internal state. The tested, observable behavior is
// that calling Delete() will free the underlying allocation. To create a
// valid 'this' pointer for Delete(), we allocate a raw byte array and
// reinterpret_cast it to CharClass*, matching the implementation that
// delete[]'s the underlying byte pointer.

// Normal operation: Delete on a reasonably sized byte allocation.
TEST(CharClassDeleteTest_377, DeleteOnByteArray_377) {
  uint8_t* raw = new uint8_t[32];
  re2::CharClass* cc = reinterpret_cast<re2::CharClass*>(raw);

  // Delete() should free without crashing or throwing.
  // (EXPECT_NO_THROW documents intent; delete[] is noexcept in practice.)
  EXPECT_NO_THROW(cc->Delete());
  // No further use of 'cc' — pointer is dangling post-Delete().
}

// Boundary condition: Delete on a minimal nonzero allocation (size = 1).
TEST(CharClassDeleteTest_377, DeleteOnSingleByteAllocation_377) {
  uint8_t* raw = new uint8_t[1];
  re2::CharClass* cc = reinterpret_cast<re2::CharClass*>(raw);

  EXPECT_NO_THROW(cc->Delete());
  // Do not access cc after Delete().
}

// Boundary-ish edge: Delete on a zero-length array allocation.
// new uint8_t[0] is permitted and returns a non-null pointer that must be
// deletable via delete[]. This validates Delete() handles that case as well.
TEST(CharClassDeleteTest_377, DeleteOnZeroLengthAllocation_377) {
  uint8_t* raw = new uint8_t[0];
  re2::CharClass* cc = reinterpret_cast<re2::CharClass*>(raw);

  EXPECT_NO_THROW(cc->Delete());
  // No further assertions possible without inspecting private state.
}
