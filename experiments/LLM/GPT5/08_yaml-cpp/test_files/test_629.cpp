// TEST_ID: 629
#include <gtest/gtest.h>

#include <cstddef>
#include <sstream>
#include <string>

// Pull in YAML::ostream_wrapper definition from the library.
#include <yaml-cpp/ostream_wrapper.h>

// Forward-declare the function under test (implemented in emitterutils.cpp).
namespace YAML {
namespace Utils {
bool WriteSingleQuotedString(ostream_wrapper& out, const char* str, std::size_t size);
}  // namespace Utils
}  // namespace YAML

namespace {

class WriteSingleQuotedStringTest_629 : public ::testing::Test {
protected:
  static std::string Run_629(const std::string& input, bool* ok) {
    std::ostringstream oss;
    YAML::ostream_wrapper out(oss);

    *ok = YAML::Utils::WriteSingleQuotedString(out, input.data(), input.size());
    return oss.str();
  }

  static std::string RunWithSize_629(const char* ptr, std::size_t size, bool* ok) {
    std::ostringstream oss;
    YAML::ostream_wrapper out(oss);

    *ok = YAML::Utils::WriteSingleQuotedString(out, ptr, size);
    return oss.str();
  }
};

TEST_F(WriteSingleQuotedStringTest_629, EmptyString_WritesTwoQuotesAndReturnsTrue_629) {
  bool ok = false;
  const std::string out = Run_629(std::string{}, &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "''");
}

TEST_F(WriteSingleQuotedStringTest_629, SimpleAscii_WrappedInSingleQuotesAndReturnsTrue_629) {
  bool ok = false;
  const std::string out = Run_629("hello", &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "'hello'");
}

TEST_F(WriteSingleQuotedStringTest_629, SingleQuote_IsDoubledInsideSingleQuotes_629) {
  bool ok = false;
  const std::string out = Run_629("can't", &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "'can''t'");
}

TEST_F(WriteSingleQuotedStringTest_629, MultipleSingleQuotes_AllAreDoubled_629) {
  bool ok = false;
  const std::string out = Run_629("'''", &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "''''''''");  // outer quotes + each internal quote doubled
}

TEST_F(WriteSingleQuotedStringTest_629, SizeShorterThanCString_OnlyProcessesProvidedSize_629) {
  bool ok = false;
  const char* str = "abcd";
  const std::string out = RunWithSize_629(str, 2u, &ok);

  EXPECT_TRUE(ok);
  EXPECT_EQ(out, "'ab'");
}

TEST_F(WriteSingleQuotedStringTest_629, ContainsNewline_ReturnsFalseAndDoesNotWriteClosingQuote_629) {
  bool ok = true;  // ensure call actually changes it on failure
  const std::string input = std::string("a\nb", 3);
  const std::string out = Run_629(input, &ok);

  EXPECT_FALSE(ok);

  // Observable behavior: opening quote is written, then 'a', then it bails out on '\n'
  EXPECT_EQ(out, "'a");
}

TEST_F(WriteSingleQuotedStringTest_629, NewlineAsFirstCharacter_ReturnsFalseAfterOpeningQuote_629) {
  bool ok = true;
  const std::string input = std::string("\n", 1);
  const std::string out = Run_629(input, &ok);

  EXPECT_FALSE(ok);

  // It writes the opening quote before encountering the newline.
  EXPECT_EQ(out, "'");
}

}  // namespace