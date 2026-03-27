// EOFStream_test_202.cpp
#include <gtest/gtest.h>

#include "Stream.h"

namespace {

class EOFStreamTest_202 : public ::testing::Test {};

TEST_F(EOFStreamTest_202, DefaultArgumentReturnsFalse_202) {
  EOFStream s;
  EXPECT_FALSE(s.isBinary());
}

TEST_F(EOFStreamTest_202, ExplicitTrueReturnsFalse_202) {
  EOFStream s;
  EXPECT_FALSE(s.isBinary(true));
}

TEST_F(EOFStreamTest_202, ExplicitFalseReturnsFalse_202) {
  EOFStream s;
  EXPECT_FALSE(s.isBinary(false));
}

TEST_F(EOFStreamTest_202, ConstObjectCallableReturnsFalse_202) {
  const EOFStream s;
  EXPECT_FALSE(s.isBinary());
  EXPECT_FALSE(s.isBinary(true));
  EXPECT_FALSE(s.isBinary(false));
}

}  // namespace