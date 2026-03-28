#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "./TestProjects/re2/re2/regexp.h"



using namespace re2;



class RegexpTest_158 : public ::testing::Test {

protected:

    Regexp* CreateCaptureRegexp(int cap) {

        ParseFlags flags = 0;

        auto sub_regexp = Regexp::LiteralString(nullptr, 0, flags);

        return Regexp::Capture(sub_regexp, flags, cap);

    }

};



TEST_F(RegexpTest_158, Cap_ReturnsCorrectValueForCapture_158) {

    int expected_cap = 42;

    auto regexp = CreateCaptureRegexp(expected_cap);

    EXPECT_EQ(regexp->cap(), expected_cap);

}



TEST_F(RegexpTest_158, Cap_ReturnsZeroForNonCapture_158) {

    ParseFlags flags = 0;

    auto regexp = Regexp::LiteralString(nullptr, 0, flags);

    EXPECT_EQ(regexp->cap(), 0);

}



TEST_F(RegexpTest_158, Cap_BoundaryConditionWithMaxInt_158) {

    int max_int_cap = std::numeric_limits<int>::max();

    auto regexp = CreateCaptureRegexp(max_int_cap);

    EXPECT_EQ(regexp->cap(), max_int_cap);

}



TEST_F(RegexpTest_158, Cap_BoundaryConditionWithMinInt_158) {

    int min_int_cap = std::numeric_limits<int>::min();

    auto regexp = CreateCaptureRegexp(min_int_cap);

    EXPECT_EQ(regexp->cap(), min_int_cap);

}



// Assuming Parse function can fail and return nullptr

TEST_F(RegexpTest_158, Parse_ReturnsNullptrOnInvalidInput_158) {

    RegexpStatus status;

    auto regexp = Regexp::Parse("invalid regex", 0, &status);

    EXPECT_EQ(regexp, nullptr);

}



// Assuming NamedCaptures can be empty

TEST_F(RegexpTest_158, NamedCaptures_ReturnsEmptyMapForNoNamedCaptures_158) {

    auto regexp = CreateCaptureRegexp(1);

    std::map<std::string, int>* named_captures = regexp->NamedCaptures();

    EXPECT_TRUE(named_captures->empty());

}



// Assuming CaptureNames can be empty

TEST_F(RegexpTest_158, CaptureNames_ReturnsEmptyMapForNoCaptureNames_158) {

    auto regexp = CreateCaptureRegexp(1);

    std::map<int, std::string>* capture_names = regexp->CaptureNames();

    EXPECT_TRUE(capture_names->empty());

}
