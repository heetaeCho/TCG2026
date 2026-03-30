// File: ./TestProjects/yaml-cpp/test/emitterutils_writebinary_test_638.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>
#include <vector>

#include "yaml-cpp/binary.h"
#include "yaml-cpp/ostream_wrapper.h"

// The function under test lives in emitterutils.cpp:
// namespace YAML { namespace Utils { bool WriteBinary(ostream_wrapper& out, const Binary& binary); } }
namespace YAML {
namespace Utils {
bool WriteBinary(ostream_wrapper& out, const Binary& binary);
}  // namespace Utils
}  // namespace YAML

namespace {

std::string GetWrapperString(const YAML::ostream_wrapper& out) {
  const char* s = out.str();
  return s ? std::string(s) : std::string();
}

YAML::Binary MakeBinary(const std::vector<unsigned char>& bytes) {
  if (bytes.empty())
    return YAML::Binary();
  return YAML::Binary(bytes.data(), bytes.size());
}

}  // namespace

class WriteBinaryTest_638 : public ::testing::Test {};

TEST_F(WriteBinaryTest_638, ReturnsTrueAndWritesEmptyAsDoubleQuotes_638) {
  YAML::ostream_wrapper out;
  YAML::Binary bin;  // default: empty

  const bool ok = YAML::Utils::WriteBinary(out, bin);

  EXPECT_TRUE(ok);
  EXPECT_EQ(GetWrapperString(out), "\"\"");
}

TEST_F(WriteBinaryTest_638, WritesKnownBase64EncodingsInDoubleQuotes_638) {
  struct Case {
    std::vector<unsigned char> bytes;
    const char* expected;  // expected full output including surrounding quotes
  };

  // These expectations rely only on the observable output format:
  // a double-quoted Base64 string.
  const Case cases[] = {
      {{}, "\"\""},
      {{0x00}, "\"AA==\""},
      {{0xFF}, "\"/w==\""},
      {{0x01, 0x02, 0x03}, "\"AQID\""},
      {{0x4D, 0x61, 0x6E}, "\"TWFu\""},  // "Man"
  };

  for (const auto& tc : cases) {
    YAML::ostream_wrapper out;
    YAML::Binary bin = MakeBinary(tc.bytes);

    const bool ok = YAML::Utils::WriteBinary(out, bin);

    EXPECT_TRUE(ok);
    EXPECT_EQ(GetWrapperString(out), std::string(tc.expected));
  }
}

TEST_F(WriteBinaryTest_638, OutputIsAlwaysDoubleQuoted_638) {
  const std::vector<unsigned char> bytes = {0x00, 0x10, 0x20, 0x30, 0xFF};
  YAML::ostream_wrapper out;
  YAML::Binary bin = MakeBinary(bytes);

  ASSERT_TRUE(YAML::Utils::WriteBinary(out, bin));
  const std::string s = GetWrapperString(out);

  ASSERT_GE(s.size(), 2u);
  EXPECT_EQ(s.front(), '"');
  EXPECT_EQ(s.back(), '"');

  // Base64 payload should not contain quotes; this checks the function doesn't emit extra quotes.
  const std::string payload = s.substr(1, s.size() - 2);
  EXPECT_EQ(payload.find('"'), std::string::npos);
}

TEST_F(WriteBinaryTest_638, WritesToProvidedStdOstreamWhenWrapperIsStreamBacked_638) {
  std::stringstream ss;
  YAML::ostream_wrapper out(ss);

  const std::vector<unsigned char> bytes = {0x01, 0x02, 0x03};
  YAML::Binary bin = MakeBinary(bytes);

  const bool ok = YAML::Utils::WriteBinary(out, bin);

  EXPECT_TRUE(ok);
  EXPECT_EQ(ss.str(), "\"AQID\"");
}