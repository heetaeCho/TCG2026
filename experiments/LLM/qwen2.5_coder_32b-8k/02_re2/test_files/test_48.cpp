#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "re2/re2.h"



using namespace re2;

using ::testing::Return;



class LazyRE2Test_48 : public ::testing::Test {

protected:

    const char* pattern = "test_pattern";

    RE2::CannedOptions options;

    LazyRE2 lazy_re2{pattern, options};

};



TEST_F(LazyRE2Test_48, GetReturnsNonNullPointer_48) {

    EXPECT_NE(lazy_re2.get(), nullptr);

}



TEST_F(LazyRE2Test_48, MultipleGetCallsReturnSameInstance_48) {

    RE2* first_call = lazy_re2.get();

    RE2* second_call = lazy_re2.get();

    EXPECT_EQ(first_call, second_call);

}



// Assuming RE2::CannedOptions can be default constructed and used without issue

TEST_F(LazyRE2Test_48, DefaultConstructedOptionsWork_48) {

    LazyRE2 default_options_lazy_re2{pattern};

    EXPECT_NE(default_options_lazy_re2.get(), nullptr);

}
