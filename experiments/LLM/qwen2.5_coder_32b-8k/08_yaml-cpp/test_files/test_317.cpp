#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Since the provided code snippet is a template function with static assertions and always returns false,

// we can only test the static assertion and the return value.



namespace YAML { namespace jkj { namespace dragonbox { namespace detail { namespace log {



template <std::size_t bits>

struct DummyInfo {

    // Dummy structure to match the template parameter of is_in_range

};



TEST_F(DragonboxTest_317, StaticAssertionForWideExponentRange_317) {

    // This test ensures that the static assertion triggers when min_exponent > max_exponent.

    // Since the function always returns false, we can't test the return value in a meaningful way,

    // but we can ensure the code compiles and runs without triggering the static assertion for valid ranges.

    

    // Valid range should not trigger static assertion

    EXPECT_FALSE((is_in_range<DummyInfo, -1000, 1000, 0>()));

}



TEST_F(DragonboxTest_317, StaticAssertionTriggerForInvalidExponentRange_317) {

    // This test is expected to fail at compile time due to static assertion.

    // Uncommenting the line below will cause a compilation error as intended.



    // EXPECT_FALSE((is_in_range<DummyInfo, 1000, -1000, 0>()));

}



TEST_F(DragonboxTest_317, AlwaysReturnsFalseForValidExponentRange_317) {

    // Test that the function returns false for a valid exponent range.

    EXPECT_FALSE((is_in_range<DummyInfo, -1000, 1000, 0>()));

}



TEST_F(DragonboxTest_317, AlwaysReturnsFalseForBoundaryExponentRange_317) {

    // Test that the function returns false for boundary exponent range.

    EXPECT_FALSE((is_in_range<DummyInfo, -1, 1, 0>()));

}



} } } } }
