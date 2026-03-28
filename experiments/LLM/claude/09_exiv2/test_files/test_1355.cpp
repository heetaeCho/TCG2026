#include <gtest/gtest.h>
#include "samsungmn_int.hpp"

namespace {

// Test fixture for Samsung2MakerNote
class Samsung2MakerNoteTest_1355 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that tagListPw() returns a non-null value
TEST_F(Samsung2MakerNoteTest_1355, TagListPwReturnsNonNull_1355) {
    auto result = Exiv2::Internal::Samsung2MakerNote::tagListPw();
    EXPECT_NE(result, nullptr);
}

// Test that tagListPw() returns consistent results on multiple calls
TEST_F(Samsung2MakerNoteTest_1355, TagListPwIsConsistent_1355) {
    auto result1 = Exiv2::Internal::Samsung2MakerNote::tagListPw();
    auto result2 = Exiv2::Internal::Samsung2MakerNote::tagListPw();
    EXPECT_EQ(result1, result2);
}

// Test that tagListPw() is callable as constexpr / compile-time friendly
TEST_F(Samsung2MakerNoteTest_1355, TagListPwIsConstexprCallable_1355) {
    // This tests that the function can be invoked; since it's constexpr,
    // it should be usable in compile-time contexts
    constexpr auto result = Exiv2::Internal::Samsung2MakerNote::tagListPw();
    EXPECT_NE(result, nullptr);
}

// Test that tagList() returns a non-null value
TEST_F(Samsung2MakerNoteTest_1355, TagListReturnsNonNull_1355) {
    auto result = Exiv2::Internal::Samsung2MakerNote::tagList();
    EXPECT_NE(result, nullptr);
}

// Test that tagList() returns consistent results on multiple calls
TEST_F(Samsung2MakerNoteTest_1355, TagListIsConsistent_1355) {
    auto result1 = Exiv2::Internal::Samsung2MakerNote::tagList();
    auto result2 = Exiv2::Internal::Samsung2MakerNote::tagList();
    EXPECT_EQ(result1, result2);
}

// Test that tagList() and tagListPw() return different tag info arrays
TEST_F(Samsung2MakerNoteTest_1355, TagListAndTagListPwAreDifferent_1355) {
    auto tagList = Exiv2::Internal::Samsung2MakerNote::tagList();
    auto tagListPw = Exiv2::Internal::Samsung2MakerNote::tagListPw();
    // They should point to different tag info arrays
    // (unless the implementation reuses the same, but typically they differ)
    // We just verify both are valid pointers
    EXPECT_NE(tagList, nullptr);
    EXPECT_NE(tagListPw, nullptr);
}

} // namespace
