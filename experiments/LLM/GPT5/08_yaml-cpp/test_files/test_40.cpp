// File: test/emitter_operator_unsigned_char_test_40.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "yaml-cpp/emitter.h"

namespace {

class EmitterOperatorUnsignedCharTest_40 : public ::testing::Test {
protected:
  static std::string EmitWithChar(char ch) {
    std::stringstream ss;
    {
      YAML::Emitter emitter(ss);
      emitter << ch;
    }
    return ss.str();
  }

  static std::string EmitWithUnsignedChar(unsigned char uch) {
    std::stringstream ss;
    {
      YAML::Emitter emitter(ss);
      emitter << uch;
    }
    return ss.str();
  }

  static std::string EmitWithTwoChars(char a, char b) {
    std::stringstream ss;
    {
      YAML::Emitter emitter(ss);
      emitter << a << b;
    }
    return ss.str();
  }

  static std::string EmitWithTwoUnsignedChars(unsigned char a, unsigned char b) {
    std::stringstream ss;
    {
      YAML::Emitter emitter(ss);
      emitter << a << b;
    }
    return ss.str();
  }
};

TEST_F(EmitterOperatorUnsignedCharTest_40, ReturnsSameEmitterReference_40) {
  std::stringstream ss;
  YAML::Emitter emitter(ss);

  YAML::Emitter& ret = (emitter << static_cast<unsigned char>('A'));
  EXPECT_EQ(&ret, &emitter);
}

TEST_F(EmitterOperatorUnsignedCharTest_40, MatchesCharOverloadForPrintableAscii_40) {
  const unsigned char v = static_cast<unsigned char>('Z');
  const char c = static_cast<char>(v);

  EXPECT_EQ(EmitWithUnsignedChar(v), EmitWithChar(c));
}

TEST_F(EmitterOperatorUnsignedCharTest_40, MatchesCharOverloadForZeroValue_40) {
  const unsigned char v = static_cast<unsigned char>(0u);
  const char c = static_cast<char>(v);

  EXPECT_EQ(EmitWithUnsignedChar(v), EmitWithChar(c));
}

TEST_F(EmitterOperatorUnsignedCharTest_40, MatchesCharOverloadForMaxUnsignedChar_40) {
  const unsigned char v = static_cast<unsigned char>(255u);
  const char c = static_cast<char>(v);

  EXPECT_EQ(EmitWithUnsignedChar(v), EmitWithChar(c));
}

TEST_F(EmitterOperatorUnsignedCharTest_40, SupportsChainingAndMatchesCharChaining_40) {
  const unsigned char a = static_cast<unsigned char>('A');
  const unsigned char b = static_cast<unsigned char>('B');

  EXPECT_EQ(EmitWithTwoUnsignedChars(a, b),
            EmitWithTwoChars(static_cast<char>(a), static_cast<char>(b)));
}

TEST_F(EmitterOperatorUnsignedCharTest_40, PreservesGoodStateSameAsCharWrite_40) {
  std::stringstream ss1;
  std::stringstream ss2;

  YAML::Emitter e_char(ss1);
  YAML::Emitter e_uchar(ss2);

  const unsigned char v = static_cast<unsigned char>(200u);

  e_char << static_cast<char>(v);
  e_uchar << v;

  EXPECT_EQ(e_uchar.good(), e_char.good());
  EXPECT_EQ(e_uchar.GetLastError(), e_char.GetLastError());
}

}  // namespace
