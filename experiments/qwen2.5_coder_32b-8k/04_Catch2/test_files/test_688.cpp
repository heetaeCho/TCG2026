#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_reporter_spec_parser.cpp"



using namespace Catch::Detail;



TEST(splitReporterSpec_688, EmptyString_ReturnsEmptyVector_688) {

    auto result = splitReporterSpec("");

    EXPECT_TRUE(result.empty());

}



TEST(splitReporterSpec_688, SinglePart_NoSeparator_ReturnsSingleElementVector_688) {

    auto result = splitReporterSpec("singlepart");

    ASSERT_EQ(result.size(), 1);

    EXPECT_EQ(result[0], "singlepart");

}



TEST(splitReporterSpec_688, MultipleParts_SingleSeparator_ReturnsMultipleElementsVector_688) {

    auto result = splitReporterSpec("part1::part2");

    ASSERT_EQ(result.size(), 2);

    EXPECT_EQ(result[0], "part1");

    EXPECT_EQ(result[1], "part2");

}



TEST(splitReporterSpec_688, MultipleParts_MultipleSeparators_ReturnsMultipleElementsVector_688) {

    auto result = splitReporterSpec("part1::part2::part3");

    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0], "part1");

    EXPECT_EQ(result[1], "part2");

    EXPECT_EQ(result[2], "part3");

}



TEST(splitReporterSpec_688, TrailingSeparator_ReturnsExtraEmptyString_688) {

    auto result = splitReporterSpec("part1::part2::");

    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0], "part1");

    EXPECT_EQ(result[1], "part2");

    EXPECT_TRUE(result[2].empty());

}



TEST(splitReporterSpec_688, LeadingSeparator_ReturnsEmptyStringAndPart_688) {

    auto result = splitReporterSpec("::part1");

    ASSERT_EQ(result.size(), 2);

    EXPECT_TRUE(result[0].empty());

    EXPECT_EQ(result[1], "part1");

}



TEST(splitReporterSpec_688, ConsecutiveSeparators_ReturnsEmptyStringsBetweenParts_688) {

    auto result = splitReporterSpec("part1::::part2");

    ASSERT_EQ(result.size(), 3);

    EXPECT_EQ(result[0], "part1");

    EXPECT_TRUE(result[1].empty());

    EXPECT_TRUE(result[2].empty());

    EXPECT_EQ(result[3], "part2");

}
