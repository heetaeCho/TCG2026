// TEST_ID: 154
#include <gtest/gtest.h>

#include <sstream>
#include <vector>

// Prefer local project headers (yaml-cpp internal layout in this workspace)
#include "scanner.h"
#include "token.h"

namespace {

class ScannerPopTest_154 : public ::testing::Test {
 protected:
  static YAML::Scanner MakeScanner(const std::string& input) {
    std::istringstream in(input);
    return YAML::Scanner(in);
  }

  static std::vector<YAML::Token::TYPE> DrainTypes(YAML::Scanner& s,
                                                   std::size_t max_steps = 10000) {
    std::vector<YAML::Token::TYPE> out;
    for (std::size_t i = 0; i < max_steps; ++i) {
      if (s.empty())
        break;

      // Observe current token, then advance using pop().
      YAML::Token& t = s.peek();
      out.push_back(t.type);
      s.pop();
    }
    return out;
  }
};

}  // namespace

TEST_F(ScannerPopTest_154, PopDoesNotThrowOnEmptyDocument_154) {
  auto scanner = MakeScanner("");
  // Even if there are implicit stream tokens, pop should be safe to call.
  EXPECT_NO_THROW(scanner.pop());
}

TEST_F(ScannerPopTest_154, PopIsSafeWhenCalledRepeatedlyAfterExhaustion_154) {
  auto scanner = MakeScanner("a: b\n");

  // Drain whatever tokens are exposed through the public interface.
  ASSERT_NO_THROW({
    (void)DrainTypes(scanner);
  });

  // After exhaustion, repeated pop() should not crash.
  EXPECT_NO_THROW(scanner.pop());
  EXPECT_NO_THROW(scanner.pop());
  EXPECT_NO_THROW(scanner.pop());
}

TEST_F(ScannerPopTest_154, PopAdvancesToANewTokenWhenNotEmpty_154) {
  auto scanner = MakeScanner("a: b\n");

  // Ensure we are positioned at some token (peek forces queue population).
  ASSERT_FALSE(scanner.empty());
  YAML::Token& first = scanner.peek();
  const YAML::Token::TYPE firstType = first.type;
  const YAML::Mark firstMark = scanner.mark();

  ASSERT_NO_THROW(scanner.pop());

  // If there are more tokens, peek/mark should now refer to the next token.
  if (!scanner.empty()) {
    YAML::Token& second = scanner.peek();
    const YAML::Token::TYPE secondType = second.type;
    const YAML::Mark secondMark = scanner.mark();

    // We avoid assuming exact YAML tokenization; we only assert that
    // the scanner's observable "current token" changes after pop().
    EXPECT_TRUE(secondType != firstType || secondMark != firstMark);
  }
}

TEST_F(ScannerPopTest_154, PopEventuallyMakesScannerEmptyForFiniteInput_154) {
  auto scanner = MakeScanner("a: b\nc: d\n");

  // Drain with a safety cap to detect non-advancing behavior.
  const auto types = DrainTypes(scanner, /*max_steps=*/10000);

  // For a finite input, we should finish within the cap and become empty.
  EXPECT_TRUE(scanner.empty());

  // And we should have observed at least one token via the public API.
  EXPECT_FALSE(types.empty());
}

TEST_F(ScannerPopTest_154, PopSequenceIsDeterministicForSameInput_154) {
  // Black-box determinism check: same input should yield the same observed
  // sequence of token types when repeatedly peek()+pop()'d to exhaustion.
  auto scanner1 = MakeScanner("list: [1, 2, 3]\n");
  auto scanner2 = MakeScanner("list: [1, 2, 3]\n");

  const auto t1 = DrainTypes(scanner1);
  const auto t2 = DrainTypes(scanner2);

  EXPECT_EQ(t1, t2);
  EXPECT_TRUE(scanner1.empty());
  EXPECT_TRUE(scanner2.empty());
}
