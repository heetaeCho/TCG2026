// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_stringvaluebase_806.cpp

#include <gtest/gtest.h>

#include <exiv2/value.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace {

// NOTE: We treat Exiv2::StringValueBase as a black box.
// These tests validate only *observable* relationships via the public interface.
// In particular, value.cpp provides: `size_t count() const { return size(); }`.
// So the only strict, interface-driven invariant we can assert is: count() == size().

class StringValueBaseTest_806 : public ::testing::Test {};

TEST_F(StringValueBaseTest_806, CountEqualsSize_EmptyBuffer_806) {
  Exiv2::StringValueBase v(Exiv2::asciiString, std::string{});
  EXPECT_EQ(v.count(), v.size());
}

TEST_F(StringValueBaseTest_806, CountEqualsSize_NonEmptyBuffer_806) {
  Exiv2::StringValueBase v(Exiv2::asciiString, std::string("hello"));
  EXPECT_EQ(v.count(), v.size());
}

TEST_F(StringValueBaseTest_806, CountEqualsSize_BufferWithEmbeddedNull_806) {
  const std::string buf("a\0b", 3);
  Exiv2::StringValueBase v(Exiv2::asciiString, buf);
  EXPECT_EQ(v.count(), v.size());
}

TEST_F(StringValueBaseTest_806, CountEqualsSize_AfterReadFromStdString_806) {
  Exiv2::StringValueBase v(Exiv2::asciiString, std::string("initial"));

  EXPECT_NO_THROW({
    const int rc = v.read(std::string("changed"));
    (void)rc;
  });

  EXPECT_EQ(v.count(), v.size());
}

TEST_F(StringValueBaseTest_806, CountEqualsSize_AfterReadFromBytes_ZeroLength_806) {
  Exiv2::StringValueBase v(Exiv2::asciiString, std::string("initial"));

  const Exiv2::byte* p = nullptr;
  EXPECT_NO_THROW({
    const int rc = v.read(p, static_cast<size_t>(0), Exiv2::littleEndian);
    (void)rc;
  });

  EXPECT_EQ(v.count(), v.size());
}

TEST_F(StringValueBaseTest_806, CountEqualsSize_AfterReadFromBytes_NonZeroLength_806) {
  Exiv2::StringValueBase v(Exiv2::asciiString, std::string("initial"));

  const std::vector<Exiv2::byte> bytes = {
      static_cast<Exiv2::byte>('A'),
      static_cast<Exiv2::byte>('B'),
      static_cast<Exiv2::byte>(0),
      static_cast<Exiv2::byte>('C'),
  };

  EXPECT_NO_THROW({
    const int rc = v.read(bytes.data(), bytes.size(), Exiv2::littleEndian);
    (void)rc;
  });

  EXPECT_EQ(v.count(), v.size());
}

TEST_F(StringValueBaseTest_806, CountEqualsSize_ForLargeInput_806) {
  const std::string big(4096, 'x');
  Exiv2::StringValueBase v(Exiv2::asciiString, big);
  EXPECT_EQ(v.count(), v.size());
}

TEST_F(StringValueBaseTest_806, CopyDoesNotBreakCountEqualsSize_806) {
  Exiv2::StringValueBase v(Exiv2::asciiString, std::string("payload"));

  const size_t n = v.size();
  std::vector<Exiv2::byte> out(n == 0 ? 1 : n);  // ensure non-empty allocation

  EXPECT_NO_THROW({
    const size_t copied = v.copy(out.data(), Exiv2::littleEndian);
    (void)copied;
  });

  EXPECT_EQ(v.count(), v.size());
}

}  // namespace