// TEST_ID: 657
#include <gtest/gtest.h>

#include <set>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/stlemitter.h"

namespace {

class StlEmitterSetTest_657 : public ::testing::Test {};

TEST_F(StlEmitterSetTest_657, ReturnsSameEmitterReference_657) {
  YAML::Emitter out;
  const std::set<int> s{1, 2, 3};

  YAML::Emitter& ref = (out << s);
  EXPECT_EQ(&ref, &out);
}

TEST_F(StlEmitterSetTest_657, EmitsElementsInSortedOrder_657) {
  YAML::Emitter out;

  // Use distinct tokens to avoid accidental substring overlaps.
  const std::set<int> s{3333, 11, 222};

  out << s;

  ASSERT_TRUE(out.good()) << out.GetLastError();
  const std::string text = out.c_str();

  // Each element should appear somewhere in the output.
  const auto p11 = text.find("11");
  const auto p222 = text.find("222");
  const auto p3333 = text.find("3333");

  ASSERT_NE(p11, std::string::npos) << text;
  ASSERT_NE(p222, std::string::npos) << text;
  ASSERT_NE(p3333, std::string::npos) << text;

  // std::set is ordered; emitted sequence should preserve that order.
  EXPECT_LT(p11, p222) << text;
  EXPECT_LT(p222, p3333) << text;
}

TEST_F(StlEmitterSetTest_657, EmitsEmptySetKeepsEmitterGood_657) {
  YAML::Emitter out;
  const std::set<int> empty;

  out << empty;

  EXPECT_TRUE(out.good()) << out.GetLastError();

  // Don't assume a specific YAML representation; just ensure something
  // observable happened and the string API is internally consistent.
  const char* cstr = out.c_str();
  ASSERT_NE(cstr, nullptr);
  EXPECT_EQ(out.size(), std::string(cstr).size());
}

TEST_F(StlEmitterSetTest_657, WritingToProvidedOStreamProducesOutput_657) {
  std::ostringstream oss;
  YAML::Emitter out(oss);

  const std::set<int> s{1, 2, 3};
  out << s;

  EXPECT_TRUE(out.good()) << out.GetLastError();

  // The emitter was constructed with an ostream; verify the stream received data.
  const std::string stream_text = oss.str();
  EXPECT_FALSE(stream_text.empty());

  // Also ensure c_str() is non-empty and consistent with size().
  const std::string cstr_text = out.c_str();
  EXPECT_FALSE(cstr_text.empty());
  EXPECT_EQ(out.size(), cstr_text.size());
}

TEST_F(StlEmitterSetTest_657, MultipleEmitsAppendToOutput_657) {
  YAML::Emitter out;
  const std::set<int> s{4, 5};

  out << s;
  ASSERT_TRUE(out.good()) << out.GetLastError();
  const std::size_t size_after_first = out.size();

  out << s;
  ASSERT_TRUE(out.good()) << out.GetLastError();
  const std::size_t size_after_second = out.size();

  EXPECT_GT(size_after_second, size_after_first);
}

}  // namespace