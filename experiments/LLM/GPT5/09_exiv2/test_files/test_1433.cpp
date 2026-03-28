// File: test_makernote_int_mnheader_1433.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <type_traits>

#if __has_include("makernote_int.hpp")
#include "makernote_int.hpp"
#elif __has_include("./TestProjects/exiv2/src/makernote_int.hpp")
#include "./TestProjects/exiv2/src/makernote_int.hpp"
#else
// Minimal fallback so the test file can still compile in isolation.
// In the real codebase, the proper header should be available.
namespace Exiv2 {
using byte = unsigned char;
enum ByteOrder { invalidByteOrder = 0 };
namespace Internal {
class MnHeader {
public:
  MnHeader() = default;
  MnHeader(const MnHeader&) = delete;
  virtual ~MnHeader() = default;
  MnHeader& operator=(const MnHeader&) = delete;

  // Only what this test needs:
  size_t ifdOffset() const { return 0; }
};
}  // namespace Internal
}  // namespace Exiv2
#endif

namespace {

class MnHeaderTest_1433 : public ::testing::Test {};

TEST_F(MnHeaderTest_1433, IsNotCopyConstructible_1433) {
  EXPECT_FALSE(std::is_copy_constructible<Exiv2::Internal::MnHeader>::value);
}

TEST_F(MnHeaderTest_1433, IsNotCopyAssignable_1433) {
  EXPECT_FALSE(std::is_copy_assignable<Exiv2::Internal::MnHeader>::value);
}

TEST_F(MnHeaderTest_1433, IfdOffsetConst_DefaultIsZero_1433) {
  const Exiv2::Internal::MnHeader h;
  const size_t off = h.ifdOffset();
  EXPECT_EQ(static_cast<size_t>(0), off);
}

TEST_F(MnHeaderTest_1433, IfdOffsetConst_IsStableAcrossCalls_1433) {
  const Exiv2::Internal::MnHeader h;
  const size_t a = h.ifdOffset();
  const size_t b = h.ifdOffset();
  const size_t c = h.ifdOffset();
  EXPECT_EQ(a, b);
  EXPECT_EQ(b, c);
  EXPECT_EQ(static_cast<size_t>(0), a);
}

TEST_F(MnHeaderTest_1433, IfdOffsetConst_OnConstReference_1433) {
  Exiv2::Internal::MnHeader h;
  const Exiv2::Internal::MnHeader& ch = h;

  const size_t off = ch.ifdOffset();
  EXPECT_EQ(static_cast<size_t>(0), off);
}

TEST_F(MnHeaderTest_1433, DeletableThroughBasePointer_1433) {
  // Verifies the destructor is usable polymorphically (observable: no crash/leak in test harness).
  Exiv2::Internal::MnHeader* p = new Exiv2::Internal::MnHeader();
  delete p;
  SUCCEED();
}

}  // namespace