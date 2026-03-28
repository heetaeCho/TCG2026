#include "gtest/gtest.h"
#include "graph.h"
#include "string_piece.h"
#include <vector>
#include <string>

// Test fixture for the matches struct
class MatchesTest_166 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(MatchesTest_166, MatchesNodeWithSamePath_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("foo.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("foo.cc", 0);
    EXPECT_TRUE(m(&node));
}

TEST_F(MatchesTest_166, DoesNotMatchNodeWithDifferentPath_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("foo.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("bar.cc", 0);
    EXPECT_FALSE(m(&node));
}

TEST_F(MatchesTest_166, MatchesEmptyPath_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece(""));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("", 0);
    EXPECT_TRUE(m(&node));
}

TEST_F(MatchesTest_166, EmptyPathDoesNotMatchNonEmptyNode_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece(""));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("something", 0);
    EXPECT_FALSE(m(&node));
}

TEST_F(MatchesTest_166, NonEmptyPathDoesNotMatchEmptyNode_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("something"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("", 0);
    EXPECT_FALSE(m(&node));
}

TEST_F(MatchesTest_166, MatchesWithPathContainingSlashes_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("dir/foo.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("dir/foo.cc", 0);
    EXPECT_TRUE(m(&node));
}

TEST_F(MatchesTest_166, MatchesWithSecondElementInVector_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("first.cc"));
    paths.push_back(StringPiece("second.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin() + 1;
    matches m(it);
    
    Node node("second.cc", 0);
    EXPECT_TRUE(m(&node));
}

TEST_F(MatchesTest_166, SecondElementDoesNotMatchFirst_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("first.cc"));
    paths.push_back(StringPiece("second.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin() + 1;
    matches m(it);
    
    Node node("first.cc", 0);
    EXPECT_FALSE(m(&node));
}

TEST_F(MatchesTest_166, MatchesWithSpecialCharactersInPath_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("path with spaces/file.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("path with spaces/file.cc", 0);
    EXPECT_TRUE(m(&node));
}

TEST_F(MatchesTest_166, CaseSensitiveMatch_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("Foo.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("foo.cc", 0);
    EXPECT_FALSE(m(&node));
}

TEST_F(MatchesTest_166, MatchesLongPath_166) {
    std::string long_path(1000, 'a');
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece(long_path));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node(long_path, 0);
    EXPECT_TRUE(m(&node));
}

TEST_F(MatchesTest_166, SubstringDoesNotMatch_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("foo"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("foobar", 0);
    EXPECT_FALSE(m(&node));
}

TEST_F(MatchesTest_166, SuperstringDoesNotMatch_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("foobar"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node("foo", 0);
    EXPECT_FALSE(m(&node));
}

TEST_F(MatchesTest_166, NodeWithSlashBitsStillMatchesByPath_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("dir/file.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    // slash_bits shouldn't affect the path() comparison
    Node node("dir/file.cc", 1);
    EXPECT_TRUE(m(&node));
}

TEST_F(MatchesTest_166, MatchesMultipleNodesWithSamePredicate_166) {
    std::vector<StringPiece> paths;
    paths.push_back(StringPiece("target.cc"));
    
    std::vector<StringPiece>::iterator it = paths.begin();
    matches m(it);
    
    Node node1("target.cc", 0);
    Node node2("other.cc", 0);
    Node node3("target.cc", 0);
    
    EXPECT_TRUE(m(&node1));
    EXPECT_FALSE(m(&node2));
    EXPECT_TRUE(m(&node3));
}
