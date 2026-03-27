// File: yaml-cpp/test/operator_long_long_test_54.cpp

#include <gtest/gtest.h>

#include <climits>
#include <cstdint>
#include <ios>
#include <limits>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class OperatorLongLongTest_54 : public ::testing::Test {
 protected:
  static std::string EmitToString(long long v) {
    std::ostringstream oss;
    YAML::Emitter out(oss);
    out << v;
    // Prefer the stream output (most observable), but also sanity-check c_str().
    const std::string stream_str = oss.str();
    const char* cstr = out.c_str();
    if (cstr) {
      // They should generally agree; if not, still return stream output as canonical.
      // (Don't ASSERT equality here to avoid assuming emitter internals.)
      (void)cstr;
    }
    return stream_str;
  }

  static void ExpectContainsInOrder(const std::string& s,
                                   const std::string& a,
                                   const std::string& b) {
    const auto posa = s.find(a);
    ASSERT_NE(posa, std::string::npos) << "Missing first token: " << a << " in: " << s;
    const auto posb = s.find(b, posa + a.size());
    ASSERT_NE(posb, std::string::npos) << "Missing second token after first: " << b
                                       << " in: " << s;
  }
};

}  // namespace

TEST_F(OperatorLongLongTest_54, ReturnsSameEmitterReference_54) {
  std::ostringstream oss;
  YAML::Emitter out(oss);

  YAML::Emitter& ret = (out << 123LL);
  EXPECT_EQ(&ret, &out);
}

TEST_F(OperatorLongLongTest_54, EmitsZero_54) {
  const std::string s = OperatorLongLongTest_54::EmitToString(0LL);
  EXPECT_NE(s.find("0"), std::string::npos) << "Output did not contain '0': " << s;
}

TEST_F(OperatorLongLongTest_54, EmitsPositiveValue_54) {
  const long long v = 42LL;
  const std::string s = OperatorLongLongTest_54::EmitToString(v);

  const std::string token = std::to_string(v);
  EXPECT_NE(s.find(token), std::string::npos) << "Output did not contain '" << token
                                              << "': " << s;
}

TEST_F(OperatorLongLongTest_54, EmitsNegativeValue_54) {
  const long long v = -42LL;
  const std::string s = OperatorLongLongTest_54::EmitToString(v);

  const std::string token = std::to_string(v);
  EXPECT_NE(s.find(token), std::string::npos) << "Output did not contain '" << token
                                              << "': " << s;
}

TEST_F(OperatorLongLongTest_54, EmitsMaxLongLong_54) {
  const long long v = std::numeric_limits<long long>::max();
  const std::string s = OperatorLongLongTest_54::EmitToString(v);

  const std::string token = std::to_string(v);
  EXPECT_NE(s.find(token), std::string::npos) << "Output did not contain max token: " << s;
}

TEST_F(OperatorLongLongTest_54, EmitsMinLongLong_54) {
  const long long v = std::numeric_limits<long long>::min();
  const std::string s = OperatorLongLongTest_54::EmitToString(v);

  const std::string token = std::to_string(v);
  EXPECT_NE(s.find(token), std::string::npos) << "Output did not contain min token: " << s;
}

TEST_F(OperatorLongLongTest_54, CanChainMultipleInsertions_54) {
  std::ostringstream oss;
  YAML::Emitter out(oss);

  out << 1LL << 2LL << -3LL;

  const std::string s = oss.str();
  // Don't assume delimiters/spaces/newlines; just verify the values appear in order.
  OperatorLongLongTest_54::ExpectContainsInOrder(s, "1", "2");
  EXPECT_NE(s.find("-3"), std::string::npos) << "Output did not contain '-3': " << s;
}

TEST_F(OperatorLongLongTest_54, StreamAndCStrAreConsistentAfterInsertion_54) {
  std::ostringstream oss;
  YAML::Emitter out(oss);

  out << 777LL;

  const std::string stream_str = oss.str();
  const char* cstr = out.c_str();
  ASSERT_NE(cstr, nullptr);
  const std::string cstr_str(cstr);

  // Avoid assuming exact equality, but they should at least both contain the inserted value.
  const std::string token = std::to_string(777LL);
  EXPECT_NE(stream_str.find(token), std::string::npos) << stream_str;
  EXPECT_NE(cstr_str.find(token), std::string::npos) << cstr_str;
}

TEST_F(OperatorLongLongTest_54, ErrorIsObservableWhenUnderlyingStreamIsBad_54) {
  std::ostringstream oss;
  oss.setstate(std::ios::badbit);  // Make the stream unusable before constructing the emitter.
  YAML::Emitter out(oss);

  // Should not crash; error should be observable via good() and/or GetLastError().
  out << 1LL;

  if (out.good()) {
    EXPECT_FALSE(out.GetLastError().empty())
        << "Emitter reports good()==true but no last error after writing to bad stream";
  } else {
    SUCCEED() << "Emitter reports good()==false after writing to bad stream";
  }
}
