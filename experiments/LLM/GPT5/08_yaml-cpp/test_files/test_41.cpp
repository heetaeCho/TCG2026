// TEST_ID = 41
//
// Unit tests for:
//   YAML::operator<<(YAML::Emitter&, const YAML::_Alias&)
//
// Constraints honored:
// - Treat implementation as black box
// - Test only observable behavior via public API (c_str/size/good/GetLastError) and return references
// - No private state access, no re-implementation of internals

#include <gtest/gtest.h>

#include <cstddef>
#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/emittermanip.h"

namespace {

static std::string EmitterOutput(const YAML::Emitter& e) {
  const char* p = e.c_str();
  const std::size_t n = e.size();
  if (!p || n == 0) return std::string();
  return std::string(p, p + n);
}

class AliasOperatorTest_41 : public ::testing::Test {
 protected:
  static YAML::_Alias MakeAlias(const std::string& s) { return YAML::_Alias(s); }
};

}  // namespace

TEST_F(AliasOperatorTest_41, ReturnsSameEmitterReference_41) {
  YAML::Emitter emitter;
  YAML::_Alias a = MakeAlias("id");

  YAML::Emitter& ret = (emitter << a);
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(AliasOperatorTest_41, ProducesSameOutputAsDirectWrite_41) {
  YAML::Emitter viaOp;
  YAML::Emitter viaWrite;

  YAML::_Alias a = MakeAlias("abc");

  viaOp << a;
  viaWrite.Write(a);

  EXPECT_EQ(EmitterOutput(viaOp), EmitterOutput(viaWrite));
  EXPECT_EQ(viaOp.size(), viaWrite.size());
  EXPECT_EQ(viaOp.good(), viaWrite.good());
  EXPECT_EQ(viaOp.GetLastError(), viaWrite.GetLastError());
}

TEST_F(AliasOperatorTest_41, HandlesEmptyAliasContent_41) {
  YAML::Emitter viaOp;
  YAML::Emitter viaWrite;

  YAML::_Alias a = MakeAlias("");

  EXPECT_NO_THROW(viaOp << a);
  EXPECT_NO_THROW(viaWrite.Write(a));

  EXPECT_EQ(EmitterOutput(viaOp), EmitterOutput(viaWrite));
  EXPECT_EQ(viaOp.size(), viaWrite.size());
}

TEST_F(AliasOperatorTest_41, HandlesSpecialCharactersInAliasContent_41) {
  YAML::Emitter viaOp;
  YAML::Emitter viaWrite;

  // Include whitespace and some punctuation; do not assume formatting rules.
  YAML::_Alias a = MakeAlias("a b\tc\n:[]{}#?,&*");

  viaOp << a;
  viaWrite.Write(a);

  EXPECT_EQ(EmitterOutput(viaOp), EmitterOutput(viaWrite));
  EXPECT_EQ(viaOp.size(), viaWrite.size());
}

TEST_F(AliasOperatorTest_41, SupportsChainingMultipleAliasInsertions_41) {
  YAML::Emitter viaOp;
  YAML::Emitter viaWrite;

  YAML::_Alias a1 = MakeAlias("first");
  YAML::_Alias a2 = MakeAlias("second");
  YAML::_Alias a3 = MakeAlias("third");

  // Verify chaining compiles and returns same emitter reference.
  YAML::Emitter& chained = (viaOp << a1 << a2 << a3);
  EXPECT_EQ(&chained, &viaOp);

  viaWrite.Write(a1).Write(a2).Write(a3);

  EXPECT_EQ(EmitterOutput(viaOp), EmitterOutput(viaWrite));
  EXPECT_EQ(viaOp.size(), viaWrite.size());
}

TEST_F(AliasOperatorTest_41, LargeAliasContentDoesNotThrowAndMatchesWrite_41) {
  YAML::Emitter viaOp;
  YAML::Emitter viaWrite;

  std::string big(1 << 16, 'x');  // 65536 chars
  YAML::_Alias a = MakeAlias(big);

  EXPECT_NO_THROW(viaOp << a);
  EXPECT_NO_THROW(viaWrite.Write(a));

  EXPECT_EQ(EmitterOutput(viaOp), EmitterOutput(viaWrite));
  EXPECT_EQ(viaOp.size(), viaWrite.size());
}

TEST_F(AliasOperatorTest_41, WorksWithStreamBackedEmitterAndMatchesWrite_41) {
  std::stringstream ssOp;
  std::stringstream ssWrite;

  YAML::Emitter viaOp(ssOp);
  YAML::Emitter viaWrite(ssWrite);

  YAML::_Alias a = MakeAlias("streamed");

  viaOp << a;
  viaWrite.Write(a);

  EXPECT_EQ(EmitterOutput(viaOp), EmitterOutput(viaWrite));
  EXPECT_EQ(viaOp.size(), viaWrite.size());
}

TEST_F(AliasOperatorTest_41, DoesNotThrowEvenIfUnderlyingStreamIsBad_41) {
  std::stringstream ss;
  ss.setstate(std::ios::badbit);  // Put stream into a bad state before using it.

  YAML::Emitter emitter(ss);
  YAML::_Alias a = MakeAlias("x");

  // We do not assume how errors are reported; just ensure operator<< is safe to call.
  EXPECT_NO_THROW(emitter << a);

  // If implementation exposes error info, it should be queryable without throwing.
  EXPECT_NO_THROW((void)emitter.good());
  EXPECT_NO_THROW((void)emitter.GetLastError());
  EXPECT_NO_THROW((void)emitter.size());
  EXPECT_NO_THROW((void)emitter.c_str());
}
