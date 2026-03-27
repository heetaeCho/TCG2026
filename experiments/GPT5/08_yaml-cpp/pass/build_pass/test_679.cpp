// File: ./TestProjects/yaml-cpp/test/stream_test.cpp
#include <gtest/gtest.h>

#include <sstream>
#include <string>
#include <vector>

#include "stream.h"  // YAML::Stream

namespace {

static std::string Bytes(const std::vector<unsigned char>& v) {
  return std::string(reinterpret_cast<const char*>(v.data()), v.size());
}

static YAML::Stream MakeStreamFromBytes(const std::vector<unsigned char>& bytes) {
  // std::istringstream stores a copy of the string internally, so it's safe.
  auto s = Bytes(bytes);
  auto* iss = new std::istringstream(s, std::ios::in | std::ios::binary);
  // YAML::Stream stores a reference, so the stream must outlive YAML::Stream.
  // We'll manage lifetime in the test by deleting the istringstream after Stream is destroyed.
  // To keep things simple, we return the Stream by value is impossible (copy deleted),
  // so tests should construct YAML::Stream directly where the std::istringstream lives.
  //
  // This helper is intentionally unused (kept here as a reference pattern).
  (void)iss;
  // Unreachable, but required to satisfy the signature in case of accidental use.
  std::istringstream dummy;
  return YAML::Stream(dummy);
}

}  // namespace

class StreamTest_679 : public ::testing::Test {};

TEST_F(StreamTest_679, EmptyInput_PeekIsEofAndBoolFalse_679) {
  std::istringstream input(std::string{}, std::ios::in | std::ios::binary);
  YAML::Stream s(input);

  EXPECT_FALSE(static_cast<bool>(s));
  EXPECT_TRUE(!s);

  EXPECT_EQ(s.peek(), YAML::Stream::eof());
  EXPECT_EQ(s.get(), YAML::Stream::eof());
  EXPECT_EQ(s.get(0), std::string{});
  EXPECT_EQ(s.get(1), std::string{});
}

TEST_F(StreamTest_679, FailStreamOnConstruction_BoolFalseAndPeekEof_679) {
  std::istringstream input(std::string("abc"), std::ios::in | std::ios::binary);
  input.setstate(std::ios::failbit);  // make !input true before construction

  YAML::Stream s(input);

  EXPECT_FALSE(static_cast<bool>(s));
  EXPECT_TRUE(!s);
  EXPECT_EQ(s.peek(), YAML::Stream::eof());
  EXPECT_EQ(s.get(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, Utf8NoBom_ReadsAsciiNormally_679) {
  std::istringstream input(std::string("abc"), std::ios::in | std::ios::binary);
  YAML::Stream s(input);

  EXPECT_TRUE(static_cast<bool>(s));
  EXPECT_FALSE(!s);

  EXPECT_EQ(s.peek(), 'a');
  EXPECT_EQ(s.get(), 'a');
  EXPECT_EQ(s.peek(), 'b');
  EXPECT_EQ(s.get(2), "bc");
  EXPECT_EQ(s.peek(), YAML::Stream::eof());
  EXPECT_EQ(s.get(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, Utf8Bom_IsNotExposedAsData_679) {
  // UTF-8 BOM: EF BB BF
  const std::string payload = std::string("\xEF\xBB\xBF", 3) + "a";
  std::istringstream input(payload, std::ios::in | std::ios::binary);

  YAML::Stream s(input);

  // Observable behavior expectation: stream should present 'a' as the first character.
  EXPECT_EQ(s.peek(), 'a');
  EXPECT_EQ(s.get(), 'a');
  EXPECT_EQ(s.peek(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, EatZero_DoesNotAdvance_679) {
  std::istringstream input(std::string("xyz"), std::ios::in | std::ios::binary);
  YAML::Stream s(input);

  const char p0 = s.peek();
  s.eat(0);
  EXPECT_EQ(s.peek(), p0);

  EXPECT_EQ(s.get(), 'x');
  EXPECT_EQ(s.get(2), "yz");
  EXPECT_EQ(s.peek(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, GetZero_ReturnsEmptyAndDoesNotConsume_679) {
  std::istringstream input(std::string("q"), std::ios::in | std::ios::binary);
  YAML::Stream s(input);

  EXPECT_EQ(s.peek(), 'q');
  EXPECT_EQ(s.get(0), std::string{});
  EXPECT_EQ(s.peek(), 'q');  // should still be there
  EXPECT_EQ(s.get(), 'q');
  EXPECT_EQ(s.peek(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, EatMoreThanAvailable_ReachesEof_679) {
  std::istringstream input(std::string("hi"), std::ios::in | std::ios::binary);
  YAML::Stream s(input);

  EXPECT_TRUE(static_cast<bool>(s));
  s.eat(100);  // beyond available

  EXPECT_EQ(s.peek(), YAML::Stream::eof());
  EXPECT_EQ(s.get(), YAML::Stream::eof());
  EXPECT_FALSE(static_cast<bool>(s));
  EXPECT_TRUE(!s);
}

TEST_F(StreamTest_679, MixedOperations_ProduceConsistentSequence_679) {
  std::istringstream input(std::string("012345"), std::ios::in | std::ios::binary);
  YAML::Stream s(input);

  EXPECT_EQ(s.peek(), '0');
  EXPECT_EQ(s.get(2), "01");  // consume 0,1
  EXPECT_EQ(s.peek(), '2');

  s.eat(2);  // consume 2,3
  EXPECT_EQ(s.peek(), '4');

  EXPECT_EQ(s.get(), '4');
  EXPECT_EQ(s.get(), '5');
  EXPECT_EQ(s.peek(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, Utf16LeBom_DoesNotCrashAndEventuallyEof_679) {
  // UTF-16 LE BOM: FF FE
  // Followed by 'A' (0x0041) and 'B' (0x0042) in LE: 41 00 42 00
  const std::string bytes = std::string("\xFF\xFE\x41\x00\x42\x00", 6);
  std::istringstream input(bytes, std::ios::in | std::ios::binary);

  YAML::Stream s(input);

  // We avoid asserting exact transcoding details; we only assert observable safety and termination.
  // The stream should provide some non-EOF output before EOF (if it can decode).
  const char c1 = s.get();
  if (c1 != YAML::Stream::eof()) {
    (void)s.get();  // attempt more consumption
  }
  // Consume the rest aggressively; must not hang or crash.
  s.eat(1024);

  EXPECT_EQ(s.peek(), YAML::Stream::eof());
}

TEST_F(StreamTest_679, Utf32BeBom_DoesNotCrashAndEventuallyEof_679) {
  // UTF-32 BE BOM: 00 00 FE FF
  // Then 'Z' (U+005A) in UTF-32 BE: 00 00 00 5A
  const std::string bytes =
      std::string("\x00\x00\xFE\xFF\x00\x00\x00\x5A", 8);
  std::istringstream input(bytes, std::ios::in | std::ios::binary);

  YAML::Stream s(input);

  // Same philosophy: no internal assumptions, just observable progress + EOF.
  const char c1 = s.get();
  if (c1 != YAML::Stream::eof()) {
    (void)s.get();
  }
  s.eat(2048);

  EXPECT_EQ(s.peek(), YAML::Stream::eof());
}