// TEST_ID 602
// Unit tests for Exiv2::RemoteIo (basicio.cpp)
// Interface under test (given):
//   namespace Exiv2 { class RemoteIo { public: size_t write(const byte*, size_t) { return 0; } }; }

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <limits>
#include <vector>

// Forward declare the minimal type(s) needed to compile tests.
// In Exiv2, `byte` is typically an unsigned 8-bit type.
// We avoid inferring any behavior beyond what is required to pass pointers.
namespace Exiv2 {
using byte = unsigned char;

// The class is implemented in the real codebase; tests should include it via the
// real header in your project. If the build already provides the declaration,
// you can delete this forward declaration block and include the proper header.
// Keeping it here makes the test file self-contained w.r.t. the provided snippet.
class RemoteIo {
public:
  size_t write(const byte* /* unused data */, size_t /* unused wcount */);
};
}  // namespace Exiv2

class RemoteIoTest_602 : public ::testing::Test {
protected:
  Exiv2::RemoteIo io_;
};

TEST_F(RemoteIoTest_602, WriteWithNonNullPointerAndNonZeroCountReturnsZero_602) {
  std::vector<Exiv2::byte> buf(16, static_cast<Exiv2::byte>(0xAB));
  const size_t rc = io_.write(buf.data(), buf.size());
  EXPECT_EQ(0u, rc);
}

TEST_F(RemoteIoTest_602, WriteWithNonNullPointerAndZeroCountReturnsZero_602) {
  std::vector<Exiv2::byte> buf(1, static_cast<Exiv2::byte>(0x01));
  const size_t rc = io_.write(buf.data(), 0);
  EXPECT_EQ(0u, rc);
}

TEST_F(RemoteIoTest_602, WriteWithNullPointerAndZeroCountReturnsZero_602) {
  const Exiv2::byte* nullp = nullptr;
  const size_t rc = io_.write(nullp, 0);
  EXPECT_EQ(0u, rc);
}

TEST_F(RemoteIoTest_602, WriteWithNullPointerAndNonZeroCountReturnsZero_602) {
  // Even with a null data pointer, the observable behavior via the interface is
  // the return value; this ensures it does not report success.
  const Exiv2::byte* nullp = nullptr;
  const size_t rc = io_.write(nullp, 1);
  EXPECT_EQ(0u, rc);
}

TEST_F(RemoteIoTest_602, WriteWithVeryLargeCountReturnsZero_602) {
  std::vector<Exiv2::byte> buf(4, static_cast<Exiv2::byte>(0x7F));
  const size_t huge = std::numeric_limits<size_t>::max();
  const size_t rc = io_.write(buf.data(), huge);
  EXPECT_EQ(0u, rc);
}

TEST_F(RemoteIoTest_602, MultipleWritesAllReturnZero_602) {
  std::vector<Exiv2::byte> bufA(8, static_cast<Exiv2::byte>(0x10));
  std::vector<Exiv2::byte> bufB(8, static_cast<Exiv2::byte>(0x20));

  EXPECT_EQ(0u, io_.write(bufA.data(), bufA.size()));
  EXPECT_EQ(0u, io_.write(bufB.data(), bufB.size()));
  EXPECT_EQ(0u, io_.write(nullptr, 0));
}