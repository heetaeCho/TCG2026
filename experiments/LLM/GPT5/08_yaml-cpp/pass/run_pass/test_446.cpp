// File: ./TestProjects/yaml-cpp/test/emitterstate_seterror_test_446.cpp

#include <gtest/gtest.h>

#include <string>

#include "emitterstate.h"

namespace {

class EmitterStateTest_446 : public ::testing::Test {
 protected:
  YAML::EmitterState state;
};

TEST_F(EmitterStateTest_446, SetErrorSetsLastErrorAndMarksNotGood_446) {
  const std::string err = "some error";
  EXPECT_NO_THROW(state.SetError(err));

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), err);
}

TEST_F(EmitterStateTest_446, SetErrorAcceptsEmptyString_446) {
  EXPECT_NO_THROW(state.SetError(""));

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), "");
}

TEST_F(EmitterStateTest_446, SetErrorOverwritesPreviousError_446) {
  EXPECT_NO_THROW(state.SetError("first"));
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), "first");

  EXPECT_NO_THROW(state.SetError("second"));
  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), "second");
}

TEST_F(EmitterStateTest_446, SetErrorHandlesLongString_446) {
  const std::string long_err(10000, 'x');  // large but reasonable for a unit test
  EXPECT_NO_THROW(state.SetError(long_err));

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), long_err);
}

TEST_F(EmitterStateTest_446, SetErrorPreservesNonAsciiBytes_446) {
  // Use UTF-8 bytes in a std::string (no assumptions about encoding beyond byte preservation).
  const std::string err = u8"에러: invalid ⚠️";
  EXPECT_NO_THROW(state.SetError(err));

  EXPECT_FALSE(state.good());
  EXPECT_EQ(state.GetLastError(), err);
}

}  // namespace