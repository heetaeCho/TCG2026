#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "catch2/internal/catch_string_manip.hpp"



using namespace Catch;

using namespace std;



class PluraliseTest_596 : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}



    pluralise CreatePluraliser(std::uint64_t count, StringRef label) {

        return pluralise(count, label);

    }

};



TEST_F(PluraliseTest_596, OutputSingleItem_596) {

    std::ostringstream os;

    os << CreatePluraliser(1, "item");

    EXPECT_EQ(os.str(), "1 item");

}



TEST_F(PluraliseTest_596, OutputMultipleItems_596) {

    std::ostringstream os;

    os << CreatePluraliser(2, "item");

    EXPECT_EQ(os.str(), "2 items");

}



TEST_F(PluraliseTest_596, ZeroCount_596) {

    std::ostringstream os;

    os << CreatePluraliser(0, "item");

    EXPECT_EQ(os.str(), "0 items");

}



TEST_F(PluraliseTest_596, LargeCount_596) {

    std::ostringstream os;

    os << CreatePluraliser(123456789, "item");

    EXPECT_EQ(os.str(), "123456789 items");

}



TEST_F(PluraliseTest_596, EmptyLabel_596) {

    std::ostringstream os;

    os << CreatePluraliser(1, "");

    EXPECT_EQ(os.str(), "1 ");

}



TEST_F(PluraliseTest_596, SingleCharacterLabel_596) {

    std::ostringstream os;

    os << CreatePluraliser(2, "a");

    EXPECT_EQ(os.str(), "2 as");

}
