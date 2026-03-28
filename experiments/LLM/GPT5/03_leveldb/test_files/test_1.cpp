// slice_data_test.cc
#include <gtest/gtest.h>
#include <cstring>
#include <string>

// Include the header under test
#include "leveldb/slice.h"

using leveldb::Slice;

// A tiny fixture to group the TEST_ID=1 cases (no special setup needed)
class SliceDataTest_1 : public ::testing::Test {};

// Normal operation: C-string ctor should expose the same content via data()
TEST_F(SliceDataTest_1, FromCString_ReturnsSameContent_1) {
  const char* src = "hello";
  Slice s(src);
  // Verify content equality (do not rely on pointer identity)
  EXPECT_STREQ(s.data(), src);
}

// Normal operation: std::string ctor should expose identical bytes via data()
TEST_F(SliceDataTest_1, FromStdString_ReturnsSameContent_1) {
  std::string src = "world";
  Slice s(src);
  // Compare content up to the source string size (no assumptions about null-termination)
  EXPECT_EQ(std::string(s.data(), src.size()), src);
}

// Boundary: default-constructed slice should present empty content via data()
TEST_F(SliceDataTest_1, DefaultConstructed_IsEmptyStringViaData_1) {
  Slice s;
  // Treat as a black box: verify that it reads as empty when interpreted as a C-string.
  // (This does not assume size(); it only checks observable behavior through data()).
  EXPECT_STREQ(s.data(), "");
}

// Copy construction: copied slice should expose the same data bytes
TEST_F(SliceDataTest_1, CopyConstructed_ExposesSameData_1) {
  std::string src = "abc123";
  Slice a(src);
  Slice b(a);

  // Content visible through data() should match the original bytes
  EXPECT_EQ(std::string(a.data(), src.size()), std::string(b.data(), src.size()));
}

// Assignment: assigned slice should expose the same data bytes
TEST_F(SliceDataTest_1, Assignment_ExposesSameData_1) {
  std::string src = "assign!";
  Slice a(src);
  Slice b;    // some other state
  b = a;

  EXPECT_EQ(std::string(a.data(), src.size()), std::string(b.data(), src.size()));
}

// Boundary: constructing from an empty std::string yields empty content via data()
TEST_F(SliceDataTest_1, FromEmptyStdString_DataLooksEmpty_1) {
  std::string empty;
  Slice s(empty);
  EXPECT_EQ(std::string(s.data(), empty.size()), empty);  // compares zero-length byte sequence
}
