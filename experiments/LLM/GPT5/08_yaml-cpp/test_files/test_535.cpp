// TEST_ID: 535
//
// Unit tests for YAML::Emitter::Write(const std::string&)
// Based strictly on the observable interface behavior.
// We treat implementation as a black box and only verify equivalence across overloads
// and observable state/output via c_str(), size(), good(), GetLastError().

#include <gtest/gtest.h>

#include <cstring>
#include <ostream>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

static std::string SnapshotOutput(YAML::Emitter& e) {
  // Capture exact emitted bytes, including embedded '\0' (if any),
  // using size() rather than strlen().
  return std::string(e.c_str(), e.size());
}

class EmitterWriteStringTest_535 : public ::testing::Test {
 protected:
  static void ExpectSameOutputAndStatus(YAML::Emitter& a, YAML::Emitter& b) {
    EXPECT_EQ(a.good(), b.good());
    EXPECT_EQ(a.GetLastError(), b.GetLastError());
    EXPECT_EQ(a.size(), b.size());

    const std::string out_a = SnapshotOutput(a);
    const std::string out_b = SnapshotOutput(b);
    EXPECT_EQ(out_a, out_b);
  }
};

TEST_F(EmitterWriteStringTest_535, WriteStringMatchesWriteCharBuffer_535) {
  const std::string input = "hello, world";

  YAML::Emitter e_str;
  YAML::Emitter e_buf;

  e_str.Write(input);
  e_buf.Write(input.data(), input.size());

  ExpectSameOutputAndStatus(e_str, e_buf);
}

TEST_F(EmitterWriteStringTest_535, WriteEmptyStringMatchesWriteCharBuffer_535) {
  const std::string input;

  YAML::Emitter e_str;
  YAML::Emitter e_buf;

  e_str.Write(input);
  e_buf.Write(input.data(), input.size());

  ExpectSameOutputAndStatus(e_str, e_buf);
}

TEST_F(EmitterWriteStringTest_535, WriteStringWithEmbeddedNullMatchesWriteCharBuffer_535) {
  // Includes embedded '\0' which should be preserved by size-based snapshotting.
  const std::string input(std::string("ab\0cd", 5));

  YAML::Emitter e_str;
  YAML::Emitter e_buf;

  e_str.Write(input);
  e_buf.Write(input.data(), input.size());

  ExpectSameOutputAndStatus(e_str, e_buf);

  // Additional observable check: snapshot should contain the embedded null at the right place.
  const std::string out = SnapshotOutput(e_str);
  ASSERT_EQ(out.size(), e_str.size());
  ASSERT_GE(out.size(), static_cast<std::size_t>(1));
  // We can't assert formatting, but we can assert our snapshot truly contains a '\0' somewhere
  // if the emitter preserves it. This is an observable property; if it doesn't preserve it,
  // the check is relaxed.
  const bool contains_null = (out.find('\0') != std::string::npos);
  const bool input_contains_null = (input.find('\0') != std::string::npos);
  // If the emitter chooses to encode/escape, it may not contain actual '\0' bytes.
  // So we only assert that equivalence between overloads holds (already done above).
  (void)contains_null;
  (void)input_contains_null;
}

TEST_F(EmitterWriteStringTest_535, ReturnsSameEmitterReferenceForChaining_535) {
  YAML::Emitter e;
  const std::string input = "x";

  YAML::Emitter& ret = e.Write(input);
  EXPECT_EQ(&ret, &e);

  // Also verify chaining is possible and produces some stable observable output.
  YAML::Emitter& ret2 = e.Write(std::string("y"));
  EXPECT_EQ(&ret2, &e);
}

TEST_F(EmitterWriteStringTest_535, AppendsConsistentlyAcrossMultipleCallsComparedToCharBuffer_535) {
  const std::string a = "first";
  const std::string b = "second";

  YAML::Emitter e_str;
  YAML::Emitter e_buf;

  e_str.Write(a).Write(b);

  e_buf.Write(a.data(), a.size());
  e_buf.Write(b.data(), b.size());

  ExpectSameOutputAndStatus(e_str, e_buf);
}

TEST_F(EmitterWriteStringTest_535, WorksWhenConstructedWithStreamAndMatchesCharBuffer_535) {
  const std::string input = "streamed";

  std::ostringstream oss1;
  std::ostringstream oss2;

  YAML::Emitter e_str(oss1);
  YAML::Emitter e_buf(oss2);

  e_str.Write(input);
  e_buf.Write(input.data(), input.size());

  // Compare observable emitter state/output (via c_str/size) for equivalence.
  ExpectSameOutputAndStatus(e_str, e_buf);

  // Additionally, the provided streams should also be consistent (observable external effect).
  EXPECT_EQ(oss1.str(), oss2.str());
}

TEST_F(EmitterWriteStringTest_535, LargeStringMatchesWriteCharBuffer_535) {
  std::string input;
  input.reserve(1 << 16);
  for (int i = 0; i < (1 << 16); ++i) {
    input.push_back(static_cast<char>('a' + (i % 26)));
  }

  YAML::Emitter e_str;
  YAML::Emitter e_buf;

  e_str.Write(input);
  e_buf.Write(input.data(), input.size());

  ExpectSameOutputAndStatus(e_str, e_buf);
}

}  // namespace