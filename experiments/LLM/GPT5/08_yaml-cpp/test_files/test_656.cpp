// TEST_ID: 656
#include <gtest/gtest.h>

#include <list>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/stlemitter.h"

namespace {

template <typename T>
std::string EmitListToString(const std::list<T>& v) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);
  emitter << v;
  return ss.str();
}

}  // namespace

class StlEmitterListOperatorTest_656 : public ::testing::Test {};

TEST_F(StlEmitterListOperatorTest_656, ReturnsSameEmitterReference_656) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  const std::list<int> v = {1, 2, 3};

  YAML::Emitter& ret = (emitter << v);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(StlEmitterListOperatorTest_656, EmitsIntegersThatAppearInOutputInOrder_656) {
  const std::list<int> v = {1, 2, 3};
  const std::string out = EmitListToString(v);

  // Observable behavior: output should contain the emitted element representations.
  ASSERT_NE(out.find("1"), std::string::npos);
  ASSERT_NE(out.find("2"), std::string::npos);
  ASSERT_NE(out.find("3"), std::string::npos);

  // Order is an observable property for a std::list.
  const auto p1 = out.find("1");
  const auto p2 = out.find("2");
  const auto p3 = out.find("3");
  EXPECT_LT(p1, p2);
  EXPECT_LT(p2, p3);
}

TEST_F(StlEmitterListOperatorTest_656, EmitsStringsThatAppearInOutput_656) {
  const std::list<std::string> v = {"alpha", "beta"};
  const std::string out = EmitListToString(v);

  EXPECT_NE(out.find("alpha"), std::string::npos);
  EXPECT_NE(out.find("beta"), std::string::npos);
}

TEST_F(StlEmitterListOperatorTest_656, EmptyListDoesNotPutEmitterIntoErrorState_656) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  const std::list<int> empty;
  emitter << empty;

  // We intentionally do not assume a specific textual representation (e.g. "[]").
  EXPECT_TRUE(emitter.good());
  EXPECT_TRUE(emitter.GetLastError().empty());

  // Basic sanity: c_str() is usable and size() is consistent with it.
  const char* c = emitter.c_str();
  ASSERT_NE(c, nullptr);
  EXPECT_EQ(emitter.size(), std::strlen(c));
}

TEST_F(StlEmitterListOperatorTest_656, LargeListProducesNonEmptyOutputAndContainsEndpoints_656) {
  std::list<int> v;
  for (int i = 0; i < 100; ++i) v.push_back(i);

  const std::string out = EmitListToString(v);

  EXPECT_FALSE(out.empty());
  EXPECT_NE(out.find("0"), std::string::npos);
  EXPECT_NE(out.find("99"), std::string::npos);
}

namespace {
struct Streamable_656 {
  int v{};
};

std::ostream& operator<<(std::ostream& os, const Streamable_656& s) {
  os << "Streamable(" << s.v << ")";
  return os;
}
}  // namespace

TEST_F(StlEmitterListOperatorTest_656, WorksWithUserDefinedStreamableType_656) {
  const std::list<Streamable_656> v = {Streamable_656{1}, Streamable_656{2}};
  const std::string out = EmitListToString(v);

  EXPECT_NE(out.find("Streamable(1)"), std::string::npos);
  EXPECT_NE(out.find("Streamable(2)"), std::string::npos);
}