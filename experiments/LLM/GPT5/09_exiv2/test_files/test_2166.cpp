// -------------------------------------------------------------------------------------------------
// UNIT TESTS for Exiv2::StringValueBase (TEST_ID = 2166)
// File under test: ./TestProjects/exiv2/src/value.cpp
//
// Constraints:
//  - Treat implementation as a black box.
//  - Assert only observable behavior through public interface.
//  - Do not access private/internal state (public members are part of interface, but we avoid relying
//    on them to keep tests robust).
// -------------------------------------------------------------------------------------------------

#include <gtest/gtest.h>

#include <exiv2/value.hpp>
#include <exiv2/types.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

namespace {

class StringValueBaseTest_2166 : public ::testing::Test {};

TEST_F(StringValueBaseTest_2166, ConstructDoesNotThrowAndTypeIdMatches_2166) {
  const std::string input = "hello";
  const Exiv2::TypeId tid = Exiv2::asciiString;

  EXPECT_NO_THROW({
    Exiv2::StringValueBase v(tid, input);
    EXPECT_EQ(v.typeId(), tid);
  });
}

TEST_F(StringValueBaseTest_2166, ConstructSetsOkObservableAsTrueForSimpleInput_2166) {
  const std::string input = "simple";
  Exiv2::StringValueBase v(Exiv2::asciiString, input);

  // Observable state via public API
  EXPECT_TRUE(v.ok());
}

TEST_F(StringValueBaseTest_2166, WriteIsStableAndProducesSomeOutput_2166) {
  const std::string input = "abc";
  Exiv2::StringValueBase v(Exiv2::asciiString, input);

  std::ostringstream os1;
  std::ostringstream os2;

  v.write(os1);
  v.write(os2);

  // Black-box friendly: same object should write deterministically.
  EXPECT_EQ(os1.str(), os2.str());

  // For a non-empty input, writing should typically produce something.
  // (We only require non-emptiness here; no assumptions about exact formatting.)
  EXPECT_FALSE(os1.str().empty());
}

TEST_F(StringValueBaseTest_2166, CopyReturnsNoMoreThanSizeAndIsDeterministic_2166) {
  const std::string input = "copy-me";
  Exiv2::StringValueBase v(Exiv2::asciiString, input);

  const size_t sz = v.size();
  std::vector<Exiv2::byte> buf1(sz + 8, static_cast<Exiv2::byte>(0xA5));
  std::vector<Exiv2::byte> buf2(sz + 8, static_cast<Exiv2::byte>(0x5A));

  const size_t n1 = v.copy(buf1.data(), Exiv2::invalidByteOrder);
  const size_t n2 = v.copy(buf2.data(), Exiv2::invalidByteOrder);

  EXPECT_LE(n1, sz);
  EXPECT_LE(n2, sz);
  EXPECT_EQ(n1, n2);

  // Only compare the bytes that the function reported as written.
  EXPECT_TRUE(std::equal(buf1.begin(), buf1.begin() + static_cast<std::ptrdiff_t>(n1), buf2.begin()));

  // Sentinel bytes beyond reported written size should remain unchanged.
  // (We do not assume copy writes exactly size(); only that it doesn't write beyond n.)
  for (size_t i = n1; i < buf1.size(); ++i) {
    EXPECT_EQ(buf1[i], static_cast<Exiv2::byte>(0xA5));
  }
  for (size_t i = n2; i < buf2.size(); ++i) {
    EXPECT_EQ(buf2[i], static_cast<Exiv2::byte>(0x5A));
  }
}

TEST_F(StringValueBaseTest_2166, HandlesEmptyStringInput_2166) {
  const std::string input;
  Exiv2::StringValueBase v(Exiv2::asciiString, input);

  EXPECT_TRUE(v.ok());
  EXPECT_EQ(v.typeId(), Exiv2::asciiString);

  // Self-consistency expectations that avoid assuming exact encoding:
  // - size() should be >= copy() result
  const size_t sz = v.size();
  std::vector<Exiv2::byte> buf(sz + 4, static_cast<Exiv2::byte>(0xCC));
  const size_t n = v.copy(buf.data(), Exiv2::invalidByteOrder);
  EXPECT_LE(n, sz);
}

TEST_F(StringValueBaseTest_2166, HandlesEmbeddedNullBytesInInput_2166) {
  // Input with embedded '\0' is a good boundary for string handling.
  const std::string input = std::string("A\0B\0C", 5);
  Exiv2::StringValueBase v(Exiv2::asciiString, input);

  EXPECT_TRUE(v.ok());

  // Ensure operations are safe / non-throwing for this boundary.
  std::ostringstream os;
  EXPECT_NO_THROW({ v.write(os); });

  const size_t sz = v.size();
  std::vector<Exiv2::byte> buf(sz + 8, static_cast<Exiv2::byte>(0x11));
  EXPECT_NO_THROW({
    const size_t n = v.copy(buf.data(), Exiv2::invalidByteOrder);
    EXPECT_LE(n, sz);
  });
}

TEST_F(StringValueBaseTest_2166, HandlesLargeStringInput_2166) {
  // Large-but-reasonable input to exercise boundary behavior.
  const std::string input(1u << 16, 'x');  // 65536 chars
  Exiv2::StringValueBase v(Exiv2::asciiString, input);

  EXPECT_TRUE(v.ok());

  // Copy should remain bounded by size() and be callable.
  const size_t sz = v.size();
  std::vector<Exiv2::byte> buf(sz + 16, static_cast<Exiv2::byte>(0x77));
  const size_t n = v.copy(buf.data(), Exiv2::invalidByteOrder);
  EXPECT_LE(n, sz);

  // Writing should also be safe.
  std::ostringstream os;
  EXPECT_NO_THROW({ v.write(os); });
  EXPECT_FALSE(os.str().empty());
}

}  // namespace