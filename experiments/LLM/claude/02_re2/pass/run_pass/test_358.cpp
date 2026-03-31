#include "re2/regexp.h"
#include "re2/re2.h"
#include "gtest/gtest.h"
#include <map>
#include <string>

namespace re2 {

class NamedCapturesWalkerTest_358 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that TakeMap returns NULL when called on a freshly constructed walker
// (before any Walk has been performed)
TEST_F(NamedCapturesWalkerTest_358, TakeMapReturnsNullInitially_358) {
    // We can test TakeMap indirectly through Regexp's NamedCaptures interface
    // But for direct testing of NamedCapturesWalker, the map_ starts as NULL
    // Testing via Regexp::NamedCaptures which uses NamedCapturesWalker internally

    // A regexp with no named captures should return NULL from NamedCaptures
    Regexp* re = Regexp::Parse("abc", Regexp::LikePerl, NULL);
    ASSERT_NE(re, nullptr);
    
    std::map<std::string, int>* captures = re->NamedCaptures();
    EXPECT_EQ(captures, nullptr);
    
    re->Decref();
}

// Test that NamedCaptures returns a valid map for a regexp with named groups
TEST_F(NamedCapturesWalkerTest_358, TakeMapReturnsMapWithNamedCaptures_358) {
    Regexp* re = Regexp::Parse("(?P<first>\\w+)\\s(?P<second>\\w+)", Regexp::LikePerl, NULL);
    ASSERT_NE(re, nullptr);
    
    std::map<std::string, int>* captures = re->NamedCaptures();
    ASSERT_NE(captures, nullptr);
    
    EXPECT_EQ(captures->size(), 2u);
    EXPECT_NE(captures->find("first"), captures->end());
    EXPECT_NE(captures->find("second"), captures->end());
    EXPECT_EQ((*captures)["first"], 1);
    EXPECT_EQ((*captures)["second"], 2);
    
    delete captures;
    re->Decref();
}

// Test with a single named capture group
TEST_F(NamedCapturesWalkerTest_358, SingleNamedCapture_358) {
    Regexp* re = Regexp::Parse("(?P<name>\\d+)", Regexp::LikePerl, NULL);
    ASSERT_NE(re, nullptr);
    
    std::map<std::string, int>* captures = re->NamedCaptures();
    ASSERT_NE(captures, nullptr);
    
    EXPECT_EQ(captures->size(), 1u);
    EXPECT_EQ((*captures)["name"], 1);
    
    delete captures;
    re->Decref();
}

// Test with unnamed capture groups only - should return NULL
TEST_F(NamedCapturesWalkerTest_358, UnnamedCapturesReturnNull_358) {
    Regexp* re = Regexp::Parse("(\\w+)\\s(\\w+)", Regexp::LikePerl, NULL);
    ASSERT_NE(re, nullptr);
    
    std::map<std::string, int>* captures = re->NamedCaptures();
    EXPECT_EQ(captures, nullptr);
    
    re->Decref();
}

// Test with mixed named and unnamed capture groups
TEST_F(NamedCapturesWalkerTest_358, MixedNamedAndUnnamedCaptures_358) {
    Regexp* re = Regexp::Parse("(\\w+)(?P<named>\\d+)(\\w+)", Regexp::LikePerl, NULL);
    ASSERT_NE(re, nullptr);
    
    std::map<std::string, int>* captures = re->NamedCaptures();
    ASSERT_NE(captures, nullptr);
    
    EXPECT_EQ(captures->size(), 1u);
    EXPECT_NE(captures->find("named"), captures->end());
    EXPECT_EQ((*captures)["named"], 2);
    
    delete captures;
    re->Decref();
}

// Test with no capture groups at all
TEST_F(NamedCapturesWalkerTest_358, NoCaptureGroups_358) {
    Regexp* re = Regexp::Parse("abc\\d+", Regexp::LikePerl, NULL);
    ASSERT_NE(re, nullptr);
    
    std::map<std::string, int>* captures = re->NamedCaptures();
    EXPECT_EQ(captures, nullptr);
    
    re->Decref();
}

// Test with multiple named captures to verify correct index assignment
TEST_F(NamedCapturesWalkerTest_358, MultipleNamedCapturesCorrectIndices_358) {
    Regexp* re = Regexp::Parse("(?P<a>x)(?P<b>y)(?P<c>z)", Regexp::LikePerl, NULL);
    ASSERT_NE(re, nullptr);
    
    std::map<std::string, int>* captures = re->NamedCaptures();
    ASSERT_NE(captures, nullptr);
    
    EXPECT_EQ(captures->size(), 3u);
    EXPECT_EQ((*captures)["a"], 1);
    EXPECT_EQ((*captures)["b"], 2);
    EXPECT_EQ((*captures)["c"], 3);
    
    delete captures;
    re->Decref();
}

}  // namespace re2
