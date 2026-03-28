// TEST_ID: 147
#include <gtest/gtest.h>

#include <atomic>
#include <string>
#include <thread>
#include <vector>

#include "exp.h"  // YAML::Exp::ScanScalarEndInFlow, EndScalarInFlow, BlankOrBreak, Comment

namespace {

using YAML::RegEx;

class ScanScalarEndInFlowTest_147 : public ::testing::Test {
 protected:
  static RegEx Expected() {
    // Mirror the *publicly available* expression used to define ScanScalarEndInFlow,
    // without asserting any particular YAML semantics for what it matches.
    return (YAML::Exp::EndScalarInFlow() |
            (YAML::Exp::BlankOrBreak() + YAML::Exp::Comment()));
  }
};

TEST_F(ScanScalarEndInFlowTest_147, ReturnsSameInstanceAcrossCalls_147) {
  const RegEx* first = &YAML::Exp::ScanScalarEndInFlow();
  const RegEx* second = &YAML::Exp::ScanScalarEndInFlow();
  const RegEx* third = &YAML::Exp::ScanScalarEndInFlow();

  EXPECT_EQ(first, second);
  EXPECT_EQ(second, third);
}

TEST_F(ScanScalarEndInFlowTest_147, MatchesAgreesWithComposedExpression_OnRepresentativeInputs_147) {
  const RegEx& sut = YAML::Exp::ScanScalarEndInFlow();
  const RegEx expected = Expected();

  const std::vector<std::string> inputs = {
      "", "a", "Z", "0",
      " ", "\t", "\n", "\r",
      "#", " #", "\t#", "\n#",
      "[]", "{}", ":", ",", "-", "?",
      "abc", "abc def", "abc#def",
      " #comment", "\n #comment",
      "x\ny", "x\r\ny",
  };

  for (const auto& s : inputs) {
    SCOPED_TRACE(::testing::Message() << "input: \"" << s << "\"");
    EXPECT_EQ(sut.Matches(s), expected.Matches(s));
    EXPECT_EQ(sut.Match(s), expected.Match(s));
  }
}

TEST_F(ScanScalarEndInFlowTest_147, MatchesAgreesWithComposedExpression_OnLongInput_147) {
  const RegEx& sut = YAML::Exp::ScanScalarEndInFlow();
  const RegEx expected = Expected();

  // Boundary-ish: long string with a mix of characters.
  std::string long_input;
  long_input.reserve(10000);
  for (int i = 0; i < 10000; ++i) {
    switch (i % 11) {
      case 0: long_input.push_back('a'); break;
      case 1: long_input.push_back(' '); break;
      case 2: long_input.push_back('#'); break;
      case 3: long_input.push_back('\n'); break;
      case 4: long_input.push_back('\t'); break;
      case 5: long_input.push_back(':'); break;
      case 6: long_input.push_back(','); break;
      case 7: long_input.push_back(']'); break;
      case 8: long_input.push_back('}'); break;
      case 9: long_input.push_back('?'); break;
      default: long_input.push_back('-'); break;
    }
  }

  EXPECT_EQ(sut.Matches(long_input), expected.Matches(long_input));
  EXPECT_EQ(sut.Match(long_input), expected.Match(long_input));
}

TEST_F(ScanScalarEndInFlowTest_147, CallableFromMultipleThreadsAndReturnsSameAddress_147) {
  constexpr int kThreads = 8;
  std::vector<const RegEx*> addrs(kThreads, nullptr);

  std::vector<std::thread> threads;
  threads.reserve(kThreads);
  for (int i = 0; i < kThreads; ++i) {
    threads.emplace_back([&, i]() {
      // Call repeatedly to exercise static initialization / access.
      const RegEx* last = nullptr;
      for (int j = 0; j < 1000; ++j) {
        last = &YAML::Exp::ScanScalarEndInFlow();
      }
      addrs[i] = last;
    });
  }
  for (auto& t : threads) t.join();

  ASSERT_NE(addrs[0], nullptr);
  for (int i = 1; i < kThreads; ++i) {
    EXPECT_EQ(addrs[0], addrs[i]);
  }
}

TEST_F(ScanScalarEndInFlowTest_147, AgreesWithComposedExpression_OnSingleCharacterInputs_147) {
  const RegEx& sut = YAML::Exp::ScanScalarEndInFlow();
  const RegEx expected = Expected();

  // Boundary: all byte values in a conservative printable-ish subset + common controls.
  const std::vector<char> chars = {
      '\0', '\t', '\n', '\r', ' ',
      '#', '-', '?', ':', ',', '[', ']', '{', '}', '"', '\'',
      'a', 'Z', '0', '_',
  };

  for (char ch : chars) {
    const std::string s(1, ch);
    SCOPED_TRACE(::testing::Message() << "char code: " << static_cast<int>(static_cast<unsigned char>(ch)));
    EXPECT_EQ(sut.Matches(s), expected.Matches(s));
    EXPECT_EQ(sut.Match(s), expected.Match(s));
  }
}

}  // namespace
