// File: test/emitter_null_insertion_test_45.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"
#include "yaml-cpp/null.h"

namespace {

class EmitterNullInsertionTest_45 : public ::testing::Test {
protected:
  static void ExpectEmitterStatesEqual(const YAML::Emitter& a, const YAML::Emitter& b) {
    // Compare only observable/public state.
    EXPECT_EQ(a.good(), b.good());
    EXPECT_EQ(a.size(), b.size());
    EXPECT_EQ(a.GetLastError(), b.GetLastError());

    // c_str() is observable; compare content (guard against null pointers).
    const char* ac = a.c_str();
    const char* bc = b.c_str();
    ASSERT_NE(ac, nullptr);
    ASSERT_NE(bc, nullptr);
    EXPECT_STREQ(ac, bc);
  }
};

TEST_F(EmitterNullInsertionTest_45, ReturnsSameEmitterReference_45) {
  YAML::Emitter out;

  YAML::Emitter* addr_before = &out;
  YAML::Emitter& ret = (out << YAML::_Null{});
  YAML::Emitter* addr_after = &ret;

  EXPECT_EQ(addr_before, addr_after);
}

TEST_F(EmitterNullInsertionTest_45, OperatorEqualsDirectWriteOnFreshEmitter_45) {
  YAML::_Null n{};

  YAML::Emitter via_op;
  YAML::Emitter via_write;

  via_op << n;
  via_write.Write(n);

  ExpectEmitterStatesEqual(via_op, via_write);
}

TEST_F(EmitterNullInsertionTest_45, ChainingTwoNullInsertionsMatchesTwoWrites_45) {
  YAML::_Null n{};

  YAML::Emitter via_op;
  YAML::Emitter via_write;

  via_op << n << n;
  via_write.Write(n).Write(n);

  ExpectEmitterStatesEqual(via_op, via_write);
}

TEST_F(EmitterNullInsertionTest_45, WorksWithExternalOstreamAndMatchesWrite_45) {
  YAML::_Null n{};

  std::ostringstream oss1;
  std::ostringstream oss2;

  YAML::Emitter via_op(oss1);
  YAML::Emitter via_write(oss2);

  via_op << n;
  via_write.Write(n);

  ExpectEmitterStatesEqual(via_op, via_write);

  // Also compare what was written to the provided streams (observable effect).
  EXPECT_EQ(oss1.str(), oss2.str());
}

TEST_F(EmitterNullInsertionTest_45, MatchesWriteEvenWhenUnderlyingStreamIsBad_45) {
  YAML::_Null n{};

  std::ostringstream oss1;
  std::ostringstream oss2;
  oss1.setstate(std::ios::badbit);
  oss2.setstate(std::ios::badbit);

  YAML::Emitter via_op(oss1);
  YAML::Emitter via_write(oss2);

  // Black-box: we don't assume how errors are reported; we only require consistency
  // between operator<< and direct Write under the same conditions.
  via_op << n;
  via_write.Write(n);

  ExpectEmitterStatesEqual(via_op, via_write);
  EXPECT_EQ(oss1.str(), oss2.str());
}

}  // namespace
