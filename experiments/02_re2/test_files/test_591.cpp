#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "pcre.h"

#include "absl/strings/string_view.h"



namespace re2 {



using ::testing::_;

using ::testing::Return;



class PCRETest_591 : public ::testing::Test {

protected:

    std::string pattern = "test_pattern";

    PCRE_Options options;

};



TEST_F(PCRETest_591, ConstructorWithPatternAndOptions_591) {

    PCRE pcre(pattern.c_str(), options);

}



TEST_F(PCRETest_591, HitLimit_ReturnsFalseInitially_591) {

    PCRE pcre(pattern.c_str(), options);

    EXPECT_FALSE(pcre.HitLimit());

}



TEST_F(PCRETest_591, ClearHitLimit_DoesNotThrow_591) {

    PCRE pcre(pattern.c_str(), options);

    pcre.ClearHitLimit();

}



TEST_F(PCRETest_591, NumberOfCapturingGroups_ReturnsNonNegative_591) {

    PCRE pcre(pattern.c_str(), options);

    EXPECT_GE(pcre.NumberOfCapturingGroups(), 0);

}



TEST_F(PCRETest_591, Replace_WithValidPatternAndRewrite_ReturnsTrue_591) {

    PCRE pcre(pattern.c_str(), options);

    std::string str = "test_string";

    absl::string_view rewrite = "rewrite_pattern";

    EXPECT_TRUE(PCRE::Replace(&str, pcre, rewrite));

}



TEST_F(PCRETest_591, GlobalReplace_WithValidPatternAndRewrite_ReturnsCount_591) {

    PCRE pcre(pattern.c_str(), options);

    std::string str = "test_string";

    absl::string_view rewrite = "rewrite_pattern";

    EXPECT_GE(PCRE::GlobalReplace(&str, pcre, rewrite), 0);

}



TEST_F(PCRETest_591, Extract_WithValidPatternAndRewrite_ReturnsTrue_591) {

    PCRE pcre(pattern.c_str(), options);

    std::string out;

    absl::string_view text = "test_string";

    absl::string_view rewrite = "rewrite_pattern";

    EXPECT_TRUE(PCRE::Extract(text, pcre, rewrite, &out));

}



TEST_F(PCRETest_591, CheckRewriteString_WithValidRewrite_ReturnsTrue_591) {

    PCRE pcre(pattern.c_str(), options);

    std::string error;

    absl::string_view rewrite = "rewrite_pattern";

    EXPECT_TRUE(pcre.CheckRewriteString(rewrite, &error));

}



TEST_F(PCRETest_591, QuoteMeta_ReturnsQuotedString_591) {

    absl::string_view unquoted = "test_string.*";

    std::string quoted = PCRE::QuoteMeta(unquoted);

    EXPECT_EQ(quoted, "test_string\\.\\*");

}



TEST_F(PCRETest_591, DoMatch_WithValidText_ReturnsTrue_591) {

    PCRE pcre(pattern.c_str(), options);

    absl::string_view text = "test_pattern";

    size_t consumed;

    EXPECT_TRUE(pcre.DoMatch(text, Anchor::ANCHOR_START, &consumed, nullptr, 0));

}



TEST_F(PCRETest_591, DoMatch_WithInvalidText_ReturnsFalse_591) {

    PCRE pcre(pattern.c_str(), options);

    absl::string_view text = "invalid_text";

    size_t consumed;

    EXPECT_FALSE(pcre.DoMatch(text, Anchor::ANCHOR_START, &consumed, nullptr, 0));

}



} // namespace re2
