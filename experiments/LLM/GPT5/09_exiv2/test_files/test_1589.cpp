// TEST_ID 1589
// File: test_sonymn_int_printmultiburstmodes_1589.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

#include "sonymn_int.hpp"  // Exiv2::Internal::SonyMakerNote
#include "exiv2/types.hpp"
#include "exiv2/value.hpp"
#include "exiv2/exif.hpp"

namespace {

class TestValue1589 : public Exiv2::Value {
 public:
  TestValue1589(Exiv2::TypeId type, size_t count, std::string text)
      : Exiv2::Value(type), count_(count), text_(std::move(text)) {}

  const size_t count() override { return count_; }

  const std::ostream& write(std::ostream& os) override {
    os << text_;
    return os;
  }

 private:
  size_t count_;
  std::string text_;
};

}  // namespace

class SonyMakerNotePrintMultiBurstModeTest_1589 : public ::testing::Test {
 protected:
  Exiv2::Internal::SonyMakerNote mn_;
};

TEST_F(SonyMakerNotePrintMultiBurstModeTest_1589, CountNotOne_WrapsValueInParentheses_1589) {
  std::ostringstream os;
  TestValue1589 v(Exiv2::undefined, 0, "SENTINEL");

  auto& ret = mn_.printMultiBurstMode(os, v, nullptr);

  EXPECT_EQ(&ret, &os);
  EXPECT_EQ(os.str(), "(SENTINEL)");
}

TEST_F(SonyMakerNotePrintMultiBurstModeTest_1589, CountGreaterThanOne_WrapsValueInParentheses_1589) {
  std::ostringstream os;
  TestValue1589 v(Exiv2::undefined, 2, "V2");

  mn_.printMultiBurstMode(os, v, nullptr);

  EXPECT_EQ(os.str(), "(V2)");
}

TEST_F(SonyMakerNotePrintMultiBurstModeTest_1589, TypeNotUndefined_WrapsValueInParentheses_1589) {
  std::ostringstream os;
  TestValue1589 v(Exiv2::asciiString, 1, "TYPE_ASCII");

  mn_.printMultiBurstMode(os, v, nullptr);

  EXPECT_EQ(os.str(), "(TYPE_ASCII)");
}

TEST_F(SonyMakerNotePrintMultiBurstModeTest_1589, CountAndTypeMismatch_WrapsValueInParentheses_1589) {
  std::ostringstream os;
  TestValue1589 v(Exiv2::unsignedShort, 99, "BOTH_BAD");

  mn_.printMultiBurstMode(os, v, nullptr);

  EXPECT_EQ(os.str(), "(BOTH_BAD)");
}

TEST_F(SonyMakerNotePrintMultiBurstModeTest_1589, PreservesExistingStreamContent_WhenWrapping_1589) {
  std::ostringstream os;
  os << "prefix:";
  TestValue1589 v(Exiv2::asciiString, 1, "X");

  mn_.printMultiBurstMode(os, v, nullptr);

  EXPECT_EQ(os.str(), "prefix:(X)");
}

TEST_F(SonyMakerNotePrintMultiBurstModeTest_1589, ValidUndefinedCountOne_ReturnsSameStreamReference_1589) {
  std::ostringstream os;
  TestValue1589 v(Exiv2::undefined, 1, "SHOULD_NOT_BE_WRAPPED_IF_EARLY_BRANCH");

  auto& ret = mn_.printMultiBurstMode(os, v, nullptr);

  EXPECT_EQ(&ret, &os);
}

TEST_F(SonyMakerNotePrintMultiBurstModeTest_1589, ValidUndefinedCountOne_DoesNotUseWrappingFormat_1589) {
  // This checks the observable difference between the documented wrapping branch
  // and the other path. We only assert it is not *exactly* the wrapping string.
  std::ostringstream os;
  const std::string sentinel = "UNLIKELY_TO_MATCH_BOOL_RENDER";
  TestValue1589 v(Exiv2::undefined, 1, sentinel);

  mn_.printMultiBurstMode(os, v, nullptr);

  EXPECT_NE(os.str(), "(" + sentinel + ")");
}