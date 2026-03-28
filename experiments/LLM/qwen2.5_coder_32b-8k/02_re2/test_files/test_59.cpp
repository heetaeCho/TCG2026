#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "_re2.cc"

#include "re2/re2.h"



namespace re2_python {



class RE2MatchShimTest_59 : public ::testing::Test {

protected:

    re2::RE2 pattern_;

    py::buffer buffer_;



    RE2MatchShimTest_59() : pattern_("abc") {}



    void SetUp() override {

        // Setup the buffer with some sample data

        std::string data = "abc";

        buffer_ = py::bytes(data).request();

    }

};



TEST_F(RE2MatchShimTest_59, MatchFoundAtStart_59) {

    ssize_t pos = 0;

    ssize_t endpos = 3;



    auto result = RE2MatchShim(pattern_, re2::RE2::ANCHOR_START, buffer_, pos, endpos);

    EXPECT_EQ(result.size(), 2); // one match + full match

    EXPECT_EQ(result[0], std::make_pair(0, 3)); // full match

    EXPECT_EQ(result[1], std::make_pair(0, 3)); // capturing group $0 (whole match)

}



TEST_F(RE2MatchShimTest_59, MatchNotFound_59) {

    ssize_t pos = 1;

    ssize_t endpos = 4;



    auto result = RE2MatchShim(pattern_, re2::RE2::ANCHOR_START, buffer_, pos, endpos);

    EXPECT_EQ(result.size(), 2); // one match + full match

    EXPECT_EQ(result[0], std::make_pair(-1, -1)); // no match for full pattern

    EXPECT_EQ(result[1], std::make_pair(-1, -1)); // no match for capturing group $0

}



TEST_F(RE2MatchShimTest_59, MatchWithCapturingGroups_59) {

    re2::RE2 pattern_with_groups_("a(b)c");

    ssize_t pos = 0;

    ssize_t endpos = 3;



    auto result = RE2MatchShim(pattern_with_groups_, re2::RE2::ANCHOR_START, buffer_, pos, endpos);

    EXPECT_EQ(result.size(), 3); // full match + two capturing groups

    EXPECT_EQ(result[0], std::make_pair(0, 3)); // full match "abc"

    EXPECT_EQ(result[1], std::make_pair(1, 2)); // capturing group $1 (b)

    EXPECT_EQ(result[2], std::make_pair(-1, -1)); // no match for capturing group $2

}



TEST_F(RE2MatchShimTest_59, MatchWithAnchors_59) {

    ssize_t pos = 0;

    ssize_t endpos = 3;



    auto result_start_anchor = RE2MatchShim(pattern_, re2::RE2::ANCHOR_START, buffer_, pos, endpos);

    EXPECT_EQ(result_start_anchor[0], std::make_pair(0, 3)); // match at start



    auto result_end_anchor = RE2MatchShim(pattern_, re2::RE2::ANCHOR_END, buffer_, pos, endpos);

    EXPECT_EQ(result_end_anchor[0], std::make_pair(0, 3)); // match at end



    auto result_unanchored = RE2MatchShim(pattern_, re2::RE2::UNANCHORED, buffer_, pos, endpos);

    EXPECT_EQ(result_unanchored[0], std::make_pair(0, 3)); // unanchored match

}



TEST_F(RE2MatchShimTest_59, MatchWithDifferentPositions_59) {

    ssize_t pos = 1;

    ssize_t endpos = 4;



    auto result = RE2MatchShim(pattern_, re2::RE2::UNANCHORED, buffer_, pos, endpos);

    EXPECT_EQ(result.size(), 2); // one match + full match

    EXPECT_EQ(result[0], std::make_pair(-1, -1)); // no match for full pattern



    ssize_t pos_within = 0;

    ssize_t endpos_within = 3;



    auto result_within = RE2MatchShim(pattern_, re2::RE2::UNANCHORED, buffer_, pos_within, endpos_within);

    EXPECT_EQ(result_within.size(), 2); // one match + full match

    EXPECT_EQ(result_within[0], std::make_pair(0, 3)); // full match "abc"

}



TEST_F(RE2MatchShimTest_59, MatchWithEmptyBuffer_59) {

    py::buffer empty_buffer = py::bytes("").request();

    ssize_t pos = 0;

    ssize_t endpos = 0;



    auto result = RE2MatchShim(pattern_, re2::RE2::ANCHOR_START, empty_buffer, pos, endpos);

    EXPECT_EQ(result.size(), 2); // one match + full match

    EXPECT_EQ(result[0], std::make_pair(-1, -1)); // no match for full pattern

    EXPECT_EQ(result[1], std::make_pair(-1, -1)); // no match for capturing group $0

}



TEST_F(RE2MatchShimTest_59, MatchWithNullDataInBuffer_59) {

    py_buffer null_data_buffer = {};

    buffer_.obj = nullptr;

    ssize_t pos = 0;

    ssize_t endpos = 3;



    auto result = RE2MatchShim(pattern_, re2::RE2::ANCHOR_START, buffer_, pos, endpos);

    EXPECT_EQ(result.size(), 2); // one match + full match

    EXPECT_EQ(result[0], std::make_pair(-1, -1)); // no match for full pattern

    EXPECT_EQ(result[1], std::make_pair(-1, -1)); // no match for capturing group $0

}



TEST_F(RE2MatchShimTest_59, MatchWithLargeEndpos_59) {

    ssize_t pos = 0;

    ssize_t endpos = 10; // larger than buffer size



    auto result = RE2MatchShim(pattern_, re2::RE2::ANCHOR_START, buffer_, pos, endpos);

    EXPECT_EQ(result.size(), 2); // one match + full match

    EXPECT_EQ(result[0], std::make_pair(0, 3)); // match "abc"

    EXPECT_EQ(result[1], std::make_pair(0, 3)); // capturing group $0 (whole match)

}



} // namespace re2_python
