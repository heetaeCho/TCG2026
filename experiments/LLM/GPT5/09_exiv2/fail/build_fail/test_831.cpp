// ============================================================================
// filename: test_value_xmpvalue_copy_831.cpp
// ============================================================================

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <ostream>
#include <string>
#include <vector>

// Exiv2 headers (adjust include path if your project uses a different layout)
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>

namespace {

// A controllable XmpValue for black-box testing of XmpValue::copy().
class FixedXmpValue_831 : public Exiv2::XmpValue {
 public:
  explicit FixedXmpValue_831(std::string s) : s_(std::move(s)) {}

  void write(std::ostream& os) const override { os << s_; }

 private:
  std::string s_;
};

// Mock to verify external interaction: XmpValue::copy() must call write(os).
class MockXmpValue_831 : public Exiv2::XmpValue {
 public:
  MOCK_METHOD(void, write, (std::ostream& os), (const, override));
};

class XmpValueCopyTest_831 : public ::testing::Test {
 protected:
  static std::vector<Exiv2::byte> MakeBuffer(std::size_t n, Exiv2::byte fill = static_cast<Exiv2::byte>(0xCC)) {
    return std::vector<Exiv2::byte>(n, fill);
  }
};

}  // namespace

TEST_F(XmpValueCopyTest_831, CopiesNonEmptyStringIntoBufferAndReturnsSize_831) {
  const std::string payload = "Hello XMP";
  FixedXmpValue_831 v(payload);

  auto buf = MakeBuffer(payload.size() + 8);  // extra bytes should remain unchanged
  const auto written = v.copy(buf.data(), Exiv2::invalidByteOrder);

  ASSERT_EQ(written, payload.size());
  ASSERT_TRUE(std::equal(payload.begin(), payload.end(), buf.begin(),
                         [](char c, Exiv2::byte b) { return static_cast<unsigned char>(c) == b; }));

  // Verify it does not write past payload.size()
  for (std::size_t i = payload.size(); i < buf.size(); ++i) {
    EXPECT_EQ(buf[i], static_cast<Exiv2::byte>(0xCC));
  }
}

TEST_F(XmpValueCopyTest_831, EmptyStringReturnsZeroAndDoesNotTouchBuffer_831) {
  FixedXmpValue_831 v("");

  auto buf = MakeBuffer(16, static_cast<Exiv2::byte>(0x7A));
  const auto written = v.copy(buf.data(), Exiv2::invalidByteOrder);

  EXPECT_EQ(written, 0u);
  for (auto b : buf) {
    EXPECT_EQ(b, static_cast<Exiv2::byte>(0x7A));
  }
}

TEST_F(XmpValueCopyTest_831, EmptyStringAllowsNullBufferPointer_831) {
  FixedXmpValue_831 v("");

  // Boundary: buf may be null when there is nothing to copy.
  const auto written = v.copy(nullptr, Exiv2::invalidByteOrder);
  EXPECT_EQ(written, 0u);
}

TEST_F(XmpValueCopyTest_831, ByteOrderParameterDoesNotAffectCopiedBytesOrSize_831) {
  const std::string payload = "OrderIgnored";
  FixedXmpValue_831 v(payload);

  auto buf1 = MakeBuffer(payload.size());
  auto buf2 = MakeBuffer(payload.size());

  const auto n1 = v.copy(buf1.data(), Exiv2::littleEndian);
  const auto n2 = v.copy(buf2.data(), Exiv2::bigEndian);

  ASSERT_EQ(n1, payload.size());
  ASSERT_EQ(n2, payload.size());
  EXPECT_EQ(buf1, buf2);

  ASSERT_TRUE(std::equal(payload.begin(), payload.end(), buf1.begin(),
                         [](char c, Exiv2::byte b) { return static_cast<unsigned char>(c) == b; }));
}

TEST_F(XmpValueCopyTest_831, CopiesLargeString_831) {
  const std::size_t kLen = 4096;
  std::string payload(kLen, 'A');
  FixedXmpValue_831 v(payload);

  auto buf = MakeBuffer(kLen + 3);
  const auto written = v.copy(buf.data(), Exiv2::invalidByteOrder);

  ASSERT_EQ(written, kLen);
  for (std::size_t i = 0; i < kLen; ++i) {
    EXPECT_EQ(buf[i], static_cast<Exiv2::byte>('A'));
  }
  EXPECT_EQ(buf[kLen + 0], static_cast<Exiv2::byte>(0xCC));
  EXPECT_EQ(buf[kLen + 1], static_cast<Exiv2::byte>(0xCC));
  EXPECT_EQ(buf[kLen + 2], static_cast<Exiv2::byte>(0xCC));
}

TEST_F(XmpValueCopyTest_831, CallsWriteExactlyOnce_831) {
  using ::testing::_;
  using ::testing::Invoke;

  MockXmpValue_831 v;

  // Make write emit deterministic content into the provided stream.
  EXPECT_CALL(v, write(_))
      .Times(1)
      .WillOnce(Invoke([](std::ostream& os) { os << "abc"; }));

  auto buf = MakeBuffer(8);
  const auto written = v.copy(buf.data(), Exiv2::invalidByteOrder);

  EXPECT_EQ(written, 3u);
  EXPECT_EQ(buf[0], static_cast<Exiv2::byte>('a'));
  EXPECT_EQ(buf[1], static_cast<Exiv2::byte>('b'));
  EXPECT_EQ(buf[2], static_cast<Exiv2::byte>('c'));
}

// Note: A non-empty payload with nullptr buffer would be undefined behavior
// for this interface (it would attempt to copy). We intentionally do not
// include such a test.