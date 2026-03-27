#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"

#include "re2/prefilter.h"



namespace re2 {

using ::testing::Eq;

using ::testing::IsNull;



class PrefilterTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(PrefilterTest_563, FromRE2_NullRE2_ReturnsNull_563) {

    const RE2* re2 = nullptr;

    Prefilter* result = Prefilter::FromRE2(re2);

    EXPECT_THAT(result, IsNull());

}



TEST_F(PrefilterTest_563, FromRE2_ValidRE2WithNullRegexp_ReturnsNull_563) {

    // Mock a RE2 object with a null Regexp

    RE2 mock_re2("");

    const_cast<re2::Regexp*&>(mock_re2.Regexp()) = nullptr;

    Prefilter* result = Prefilter::FromRE2(&mock_re2);

    EXPECT_THAT(result, IsNull());

}



TEST_F(PrefilterTest_563, FromRE2_ValidRE2_ReturnsNonNull_563) {

    RE2 valid_re2("abc");

    Prefilter* result = Prefilter::FromRE2(&valid_re2);

    EXPECT_THAT(result, Not(IsNull()));

    delete result;

}



TEST_F(PrefilterTest_563, FromRE2_MultipleCallsWithSameRE2_ReturnsDistinctInstances_563) {

    RE2 re2("abc");

    Prefilter* result1 = Prefilter::FromRE2(&re2);

    Prefilter* result2 = Prefilter::FromRE2(&re2);

    EXPECT_THAT(result1, Not(Eq(result2)));

    delete result1;

    delete result2;

}



} // namespace re2
