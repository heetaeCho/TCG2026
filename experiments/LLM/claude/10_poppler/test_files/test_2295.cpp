#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cstring>

// Include necessary headers
#include "poppler-action.h"
#include "Link.h"

// We need to mock LinkNamed since we can't construct it easily
// and we need to control getName() return value

class MockLinkNamed : public LinkNamed {
public:
    MockLinkNamed() : LinkNamed(nullptr) {}
    MOCK_CONST_METHOD0(getName, const std::string&());
    MOCK_CONST_METHOD0(isOk, bool());
    MOCK_CONST_METHOD0(getKind, LinkActionKind());
};

// Since build_named is a static function in the .cc file, we need to
// either expose it or test it through the public interface.
// Given the constraints, let's try to access it. If build_named is static
// (file-local), we may need an alternative approach.

// Forward declare or include the function if accessible
extern void build_named(PopplerAction *action, const LinkNamed *link);

class BuildNamedTest_2295 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(&action, 0, sizeof(PopplerAction));
    }

    void TearDown() override {
        if (action.named.named_dest) {
            g_free(action.named.named_dest);
            action.named.named_dest = nullptr;
        }
    }

    PopplerAction action;
};

// Test that build_named copies a normal name string
TEST_F(BuildNamedTest_2295, NormalNameIsCopied_2295) {
    MockLinkNamed mockLink;
    std::string testName = "GoToPage";
    EXPECT_CALL(mockLink, getName())
        .WillOnce(::testing::ReturnRef(testName));

    build_named(&action, &mockLink);

    ASSERT_NE(action.named.named_dest, nullptr);
    EXPECT_STREQ(action.named.named_dest, "GoToPage");
}

// Test with an empty string name
TEST_F(BuildNamedTest_2295, EmptyNameResultsInEmptyString_2295) {
    MockLinkNamed mockLink;
    std::string emptyName = "";
    EXPECT_CALL(mockLink, getName())
        .WillOnce(::testing::ReturnRef(emptyName));

    build_named(&action, &mockLink);

    // c_str() of empty string is not nullptr, it points to '\0'
    // So the condition `name != nullptr` should be true
    ASSERT_NE(action.named.named_dest, nullptr);
    EXPECT_STREQ(action.named.named_dest, "");
}

// Test with a longer name string
TEST_F(BuildNamedTest_2295, LongNameIsCopied_2295) {
    MockLinkNamed mockLink;
    std::string longName(1024, 'A');
    EXPECT_CALL(mockLink, getName())
        .WillOnce(::testing::ReturnRef(longName));

    build_named(&action, &mockLink);

    ASSERT_NE(action.named.named_dest, nullptr);
    EXPECT_STREQ(action.named.named_dest, longName.c_str());
    EXPECT_EQ(strlen(action.named.named_dest), 1024u);
}

// Test with a name containing special characters
TEST_F(BuildNamedTest_2295, SpecialCharactersInName_2295) {
    MockLinkNamed mockLink;
    std::string specialName = "Go To\nPage #1 & \"test\"";
    EXPECT_CALL(mockLink, getName())
        .WillOnce(::testing::ReturnRef(specialName));

    build_named(&action, &mockLink);

    ASSERT_NE(action.named.named_dest, nullptr);
    EXPECT_STREQ(action.named.named_dest, "Go To\nPage #1 & \"test\"");
}

// Test with a name containing unicode/UTF-8 characters
TEST_F(BuildNamedTest_2295, Utf8NameIsCopied_2295) {
    MockLinkNamed mockLink;
    std::string utf8Name = "Ünîcödé_Nàmé";
    EXPECT_CALL(mockLink, getName())
        .WillOnce(::testing::ReturnRef(utf8Name));

    build_named(&action, &mockLink);

    ASSERT_NE(action.named.named_dest, nullptr);
    EXPECT_STREQ(action.named.named_dest, "Ünîcödé_Nàmé");
}

// Test that the result is a copy (g_strdup), not the same pointer
TEST_F(BuildNamedTest_2295, NameIsDuplicated_2295) {
    MockLinkNamed mockLink;
    std::string testName = "TestDest";
    EXPECT_CALL(mockLink, getName())
        .WillOnce(::testing::ReturnRef(testName));

    build_named(&action, &mockLink);

    ASSERT_NE(action.named.named_dest, nullptr);
    // The pointer should not be the same as the original c_str()
    EXPECT_NE(static_cast<const void*>(action.named.named_dest),
              static_cast<const void*>(testName.c_str()));
    EXPECT_STREQ(action.named.named_dest, "TestDest");
}

// Test with a single character name
TEST_F(BuildNamedTest_2295, SingleCharacterName_2295) {
    MockLinkNamed mockLink;
    std::string singleChar = "X";
    EXPECT_CALL(mockLink, getName())
        .WillOnce(::testing::ReturnRef(singleChar));

    build_named(&action, &mockLink);

    ASSERT_NE(action.named.named_dest, nullptr);
    EXPECT_STREQ(action.named.named_dest, "X");
}

// Test with a name containing null bytes embedded (std::string can hold them)
TEST_F(BuildNamedTest_2295, NameWithEmbeddedNullTruncatesAtFirst_2295) {
    MockLinkNamed mockLink;
    std::string nameWithNull = std::string("Hello\0World", 11);
    EXPECT_CALL(mockLink, getName())
        .WillOnce(::testing::ReturnRef(nameWithNull));

    build_named(&action, &mockLink);

    // c_str() returns pointer, g_strdup uses strlen which stops at first \0
    ASSERT_NE(action.named.named_dest, nullptr);
    EXPECT_STREQ(action.named.named_dest, "Hello");
}
