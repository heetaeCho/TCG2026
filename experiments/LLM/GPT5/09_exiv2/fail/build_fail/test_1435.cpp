// File: test_mnheader_1435.cpp
#include <gtest/gtest.h>
#include <cstddef>
#include <limits>

// Try to include the real declaration if available in the codebase.
// (Different Exiv2 layouts may expose this header under different paths.)
#if __has_include("makernote_int.hpp")
#  include "makernote_int.hpp"
#elif __has_include("exiv2/makernote_int.hpp")
#  include "exiv2/makernote_int.hpp"
#elif __has_include("src/makernote_int.hpp")
#  include "src/makernote_int.hpp"
#else
// As a last resort, include the implementation unit directly (only if needed).
// Adjust the relative path to match your test build layout.
#  if __has_include("../src/makernote_int.cpp")
#    include "../src/makernote_int.cpp"
#  elif __has_include("TestProjects/exiv2/src/makernote_int.cpp")
#    include "TestProjects/exiv2/src/makernote_int.cpp"
#  else
#    error "Could not locate makernote_int.hpp or makernote_int.cpp for MnHeader."
#  endif
#endif

namespace {

class MnHeaderTest_1435 : public ::testing::Test {};

TEST_F(MnHeaderTest_1435, BaseOffsetReturnsSizeT_1435) {
  Exiv2::Internal::MnHeader header;
  const size_t result = header.baseOffset(0);
  (void)result;  // Type check: compiles as size_t.
  SUCCEED();
}

TEST_F(MnHeaderTest_1435, BaseOffsetWithTypicalOffsets_1435) {
  Exiv2::Internal::MnHeader header;

  EXPECT_EQ(0u, header.baseOffset(0));
  EXPECT_EQ(0u, header.baseOffset(1));
  EXPECT_EQ(0u, header.baseOffset(42));
  EXPECT_EQ(0u, header.baseOffset(1024));
}

TEST_F(MnHeaderTest_1435, BaseOffsetWithBoundaryOffsets_1435) {
  const Exiv2::Internal::MnHeader header;

  EXPECT_EQ(0u, header.baseOffset(std::numeric_limits<size_t>::min()));
  EXPECT_EQ(0u, header.baseOffset(std::numeric_limits<size_t>::max()));
}

}  // namespace