#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/catch_tostring.hpp"

#include "./TestProjects/Catch2/src/catch2/internal/catch_reusable_string_stream.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;



class ReusableStringStreamMock : public ReusableStringStream {

public:

    MOCK_METHOD(const std::string, str, (), (const, override));

    MOCK_METHOD(void, str, (const std::string&), (override));

    MOCK_METHOD(template<typename T> auto, operator<<, (T const& value), (->ReusableStringStream&, override));

};



TEST(rangeToStringTest_90, EmptyVector_ReturnsEmptyBraces_90) {

    std::vector<bool> v;

    EXPECT_EQ("{ }", rangeToString(v));

}



TEST(rangeToStringTest_90, SingleTrueElement_ReturnsTrueInBraces_90) {

    std::vector<bool> v = {true};

    EXPECT_EQ("{ true }", rangeToString(v));

}



TEST(rangeToStringTest_90, SingleFalseElement_ReturnsFalseInBraces_90) {

    std::vector<bool> v = {false};

    EXPECT_EQ("{ false }", rangeToString(v));

}



TEST(rangeToStringTest_90, MultipleElements_ReturnsCommaSeparatedValues_90) {

    std::vector<bool> v = {true, false, true, true, false};

    EXPECT_EQ("{ true, false, true, true, false }", rangeToString(v));

}



TEST(rangeToStringTest_90, LargeVector_ReturnsCorrectString_90) {

    std::vector<bool> v(10, true);

    std::string expected = "{ ";

    for (size_t i = 0; i < 10; ++i) {

        if (i > 0) expected += ", ";

        expected += "true";

    }

    expected += " }";

    EXPECT_EQ(expected, rangeToString(v));

}



TEST(rangeToStringTest_90, MixedVector_ReturnsCorrectString_90) {

    std::vector<bool> v = {false, true, false, true, false};

    EXPECT_EQ("{ false, true, false, true, false }", rangeToString(v));

}
