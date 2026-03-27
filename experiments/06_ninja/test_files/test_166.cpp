#include <gtest/gtest.h>

#include "graph.h"

#include "string_piece.h"



class MatchesTest_166 : public ::testing::Test {

protected:

    void SetUp() override {

        node_path = "test_path";

        slash_bits = 0;

        node = new Node(node_path, slash_bits);

        string_piece = StringPiece(node_path);

        matches_obj = matches(std::vector<StringPiece>::iterator(&string_piece));

    }



    void TearDown() override {

        delete node;

    }



    std::string node_path;

    uint64_t slash_bits;

    Node* node;

    StringPiece string_piece;

    matches matches_obj;

};



TEST_F(MatchesTest_166, MatchingNodePath_166) {

    EXPECT_TRUE(matches_obj(node));

}



TEST_F(MatchesTest_166, NonMatchingNodePath_166) {

    Node non_matching_node("other_path", slash_bits);

    EXPECT_FALSE(matches_obj(&non_matching_node));

}



TEST_F(MatchesTest_166, EmptyStringPiece_166) {

    StringPiece empty_string_piece;

    matches empty_matches(std::vector<StringPiece>::iterator(&empty_string_piece));

    EXPECT_FALSE(empty_matches(node));

}



TEST_F(MatchesTest_166, NullNodePointer_166) {

    Node* null_node = nullptr;

    EXPECT_FALSE(matches_obj(null_node));

}
