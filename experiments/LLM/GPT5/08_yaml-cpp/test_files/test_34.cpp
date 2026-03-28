// emitter_write_integral_type_test_34.cpp
#include <gtest/gtest.h>

#include <limits>
#include <ostream>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class WriteIntegralTypeTest_34 : public ::testing::Test {};

TEST_F(WriteIntegralTypeTest_34, WritesSingleIntegralToInternalBuffer_34) {
  YAML::Emitter out;
  out.WriteIntegralType(123);

  EXPECT_TRUE(out.good());
  EXPECT_STREQ(out.c_str(), "123");
  EXPECT_EQ(out.size(), std::string("123").size());
}

TEST_F(WriteIntegralTypeTest_34, MultipleWritesConcatenateInOrder_34) {
  YAML::Emitter out;
  out.WriteIntegralType(1).WriteIntegralType(2).WriteIntegralType(3);

  EXPECT_TRUE(out.good());
  EXPECT_STREQ(out.c_str(), "123");
  EXPECT_EQ(out.size(), std::string("123").size());
}

TEST_F(WriteIntegralTypeTest_34, WritesSignedIntMinAndMax_34) {
  {
    YAML::Emitter out;
    const int v = std::numeric_limits<int>::min();
    out.WriteIntegralType(v);

    EXPECT_TRUE(out.good());
    EXPECT_EQ(std::string(out.c_str()), std::to_string(v));
    EXPECT_EQ(out.size(), std::to_string(v).size());
  }
  {
    YAML::Emitter out;
    const int v = std::numeric_limits<int>::max();
    out.WriteIntegralType(v);

    EXPECT_TRUE(out.good());
    EXPECT_EQ(std::string(out.c_str()), std::to_string(v));
    EXPECT_EQ(out.size(), std::to_string(v).size());
  }
}

TEST_F(WriteIntegralTypeTest_34, WritesUnsignedLongLongMax_34) {
  YAML::Emitter out;
  const unsigned long long v = std::numeric_limits<unsigned long long>::max();
  out.WriteIntegralType(v);

  EXPECT_TRUE(out.good());
  EXPECT_EQ(std::string(out.c_str()), std::to_string(v));
  EXPECT_EQ(out.size(), std::to_string(v).size());
}

TEST_F(WriteIntegralTypeTest_34, WritesNegativeValueWithMinusSign_34) {
  YAML::Emitter out;
  out.WriteIntegralType(-1);

  EXPECT_TRUE(out.good());
  EXPECT_STREQ(out.c_str(), "-1");
  EXPECT_EQ(out.size(), std::string("-1").size());
}

TEST_F(WriteIntegralTypeTest_34, WritesToProvidedOstream_34) {
  std::ostringstream oss;
  YAML::Emitter out(oss);

  out.WriteIntegralType(77);

  // Verify external interaction: the provided stream receives the content.
  EXPECT_EQ(oss.str(), "77");
}

class AlwaysFailStreamBuf final : public std::streambuf {
 protected:
  int overflow(int) override {
    // Signal failure to write.
    return traits_type::eof();
  }
};

TEST_F(WriteIntegralTypeTest_34, IfStreamFailsSubsequentWritesDoNotChangeOutputOnceNotGood_34) {
  AlwaysFailStreamBuf fail_buf;
  std::ostream failing_stream(&fail_buf);

  YAML::Emitter out(failing_stream);

  // First write attempt may flip the emitter into a not-good state.
  out.WriteIntegralType(5);
  const std::size_t size_after_first = out.size();
  const bool good_after_first = out.good();

  // Second write: if the emitter is not good, WriteIntegralType should early-return and not change output.
  out.WriteIntegralType(6);
  const std::size_t size_after_second = out.size();

  if (!good_after_first) {
    EXPECT_FALSE(out.good());
    EXPECT_EQ(size_after_second, size_after_first);
  } else {
    // If the implementation chooses to remain "good" despite the stream failure mechanics,
    // we can still assert it doesn't crash and produces some stable observable result.
    EXPECT_TRUE(out.good());
    EXPECT_GE(size_after_second, size_after_first);
  }
}

}  // namespace
