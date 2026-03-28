#include "gtest/gtest.h"
#include "tag.h"
#include "token.h"

namespace YAML {

// Helper to create a Token with specific data and value
static Token MakeToken(int tagType, const std::string& value = "", const std::vector<std::string>& params = {}) {
    Token token(Token::TAG, Mark());
    token.data = tagType;
    token.value = value;
    token.params = params;
    return token;
}

// Test VERBATIM tag type
TEST(TagTest_677, VerbatimTag_SetsTypeAndValue_677) {
    Token token = MakeToken(Tag::VERBATIM, "!my-verbatim-tag");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::VERBATIM);
    EXPECT_EQ(tag.value, "!my-verbatim-tag");
    EXPECT_EQ(tag.handle, "");
}

// Test PRIMARY_HANDLE tag type
TEST(TagTest_677, PrimaryHandleTag_SetsTypeAndValue_677) {
    Token token = MakeToken(Tag::PRIMARY_HANDLE, "my-primary-value");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::PRIMARY_HANDLE);
    EXPECT_EQ(tag.value, "my-primary-value");
    EXPECT_EQ(tag.handle, "");
}

// Test SECONDARY_HANDLE tag type
TEST(TagTest_677, SecondaryHandleTag_SetsTypeAndValue_677) {
    Token token = MakeToken(Tag::SECONDARY_HANDLE, "my-secondary-value");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::SECONDARY_HANDLE);
    EXPECT_EQ(tag.value, "my-secondary-value");
    EXPECT_EQ(tag.handle, "");
}

// Test NAMED_HANDLE tag type
TEST(TagTest_677, NamedHandleTag_SetsTypeHandleAndValue_677) {
    Token token = MakeToken(Tag::NAMED_HANDLE, "!my-handle!", {"my-suffix"});
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::NAMED_HANDLE);
    EXPECT_EQ(tag.handle, "!my-handle!");
    EXPECT_EQ(tag.value, "my-suffix");
}

// Test NON_SPECIFIC tag type
TEST(TagTest_677, NonSpecificTag_SetsTypeOnly_677) {
    Token token = MakeToken(Tag::NON_SPECIFIC, "should-be-ignored");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::NON_SPECIFIC);
    EXPECT_EQ(tag.handle, "");
    EXPECT_EQ(tag.value, "");
}

// Test VERBATIM with empty value
TEST(TagTest_677, VerbatimTag_EmptyValue_677) {
    Token token = MakeToken(Tag::VERBATIM, "");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::VERBATIM);
    EXPECT_EQ(tag.value, "");
    EXPECT_EQ(tag.handle, "");
}

// Test PRIMARY_HANDLE with empty value
TEST(TagTest_677, PrimaryHandleTag_EmptyValue_677) {
    Token token = MakeToken(Tag::PRIMARY_HANDLE, "");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::PRIMARY_HANDLE);
    EXPECT_EQ(tag.value, "");
    EXPECT_EQ(tag.handle, "");
}

// Test SECONDARY_HANDLE with empty value
TEST(TagTest_677, SecondaryHandleTag_EmptyValue_677) {
    Token token = MakeToken(Tag::SECONDARY_HANDLE, "");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::SECONDARY_HANDLE);
    EXPECT_EQ(tag.value, "");
    EXPECT_EQ(tag.handle, "");
}

// Test NAMED_HANDLE with empty handle and suffix
TEST(TagTest_677, NamedHandleTag_EmptyHandleAndSuffix_677) {
    Token token = MakeToken(Tag::NAMED_HANDLE, "", {""});
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::NAMED_HANDLE);
    EXPECT_EQ(tag.handle, "");
    EXPECT_EQ(tag.value, "");
}

// Test NAMED_HANDLE with non-empty handle and empty suffix
TEST(TagTest_677, NamedHandleTag_NonEmptyHandleEmptySuffix_677) {
    Token token = MakeToken(Tag::NAMED_HANDLE, "!e!", {""});
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::NAMED_HANDLE);
    EXPECT_EQ(tag.handle, "!e!");
    EXPECT_EQ(tag.value, "");
}

// Test VERBATIM with special characters in value
TEST(TagTest_677, VerbatimTag_SpecialCharactersInValue_677) {
    Token token = MakeToken(Tag::VERBATIM, "tag:yaml.org,2002:str");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::VERBATIM);
    EXPECT_EQ(tag.value, "tag:yaml.org,2002:str");
    EXPECT_EQ(tag.handle, "");
}

// Test NAMED_HANDLE preserves handle from token value and suffix from params
TEST(TagTest_677, NamedHandleTag_HandleFromValueSuffixFromParams_677) {
    Token token = MakeToken(Tag::NAMED_HANDLE, "!yaml!", {"tag:yaml.org,2002:"});
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::NAMED_HANDLE);
    EXPECT_EQ(tag.handle, "!yaml!");
    EXPECT_EQ(tag.value, "tag:yaml.org,2002:");
}

// Test NON_SPECIFIC with value that should not be stored
TEST(TagTest_677, NonSpecificTag_ValueNotStored_677) {
    Token token = MakeToken(Tag::NON_SPECIFIC, "some-value");
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::NON_SPECIFIC);
    // NON_SPECIFIC does not set value, handle and value should remain default
    EXPECT_EQ(tag.handle, "");
    EXPECT_EQ(tag.value, "");
}

// Test VERBATIM with long value
TEST(TagTest_677, VerbatimTag_LongValue_677) {
    std::string longValue(1000, 'x');
    Token token = MakeToken(Tag::VERBATIM, longValue);
    Tag tag(token);

    EXPECT_EQ(tag.type, Tag::VERBATIM);
    EXPECT_EQ(tag.value, longValue);
}

}  // namespace YAML
