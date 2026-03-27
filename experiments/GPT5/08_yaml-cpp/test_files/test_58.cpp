// TEST_ID: 58
#include <gtest/gtest.h>

#include <sstream>
#include <type_traits>

#include "yaml-cpp/emitter.h"

namespace {

class OperatorEmitterManipTest_58 : public ::testing::Test {
 protected:
  std::stringstream ss_;
};

TEST_F(OperatorEmitterManipTest_58, ReturnsSameEmitterReference_DefaultConstructed_58) {
  YAML::Emitter out;

  // Use a well-known manipulator from yaml-cpp that has type EMITTER_MANIP.
  YAML::Emitter& ret = (out << YAML::BeginSeq);

  EXPECT_EQ(&ret, &out);
}

TEST_F(OperatorEmitterManipTest_58, ReturnsSameEmitterReference_StreamConstructed_58) {
  YAML::Emitter out(ss_);

  YAML::Emitter& ret = (out << YAML::BeginMap);

  EXPECT_EQ(&ret, &out);
}

TEST_F(OperatorEmitterManipTest_58, SupportsChainingMultipleManipulators_58) {
  YAML::Emitter out(ss_);

  // The main observable behavior of operator<< here is:
  // - it returns an Emitter& so chaining is possible
  // - it should not throw for normal, library-provided manipulators
  EXPECT_NO_THROW({
    YAML::Emitter& ret =
        (out << YAML::BeginSeq << YAML::Flow << YAML::EndSeq << YAML::Newline);
    EXPECT_EQ(&ret, &out);
  });
}

TEST_F(OperatorEmitterManipTest_58, AcceptsArbitraryManipulatorValueAndReturnsReference_58) {
  YAML::Emitter out(ss_);

  // Boundary / error-like case: pass a value that is not a documented manipulator.
  // We do NOT assume what internal logic does; we only verify the operator contract:
  // returns an Emitter& and does not throw (if throwing is observable, this catches it).
  using ManipT = decltype(YAML::BeginSeq);  // typically EMITTER_MANIP
  static_assert(std::is_enum<ManipT>::value || std::is_integral<ManipT>::value,
                "Expected manipulator type to be enum-like/integral.");

  const ManipT invalid = static_cast<ManipT>(-1);

  EXPECT_NO_THROW({
    YAML::Emitter& ret = (out << invalid);
    EXPECT_EQ(&ret, &out);
  });
}

TEST_F(OperatorEmitterManipTest_58, DoesNotInvalidateEmitterForNormalManipulator_58) {
  YAML::Emitter out(ss_);

  EXPECT_NO_THROW({
    (out << YAML::BeginSeq);
  });

  // Observable sanity check via public API (without assuming exact formatting/output).
  EXPECT_TRUE(out.good());
}

}  // namespace
