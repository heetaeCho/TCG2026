#include <gtest/gtest.h>

#include <gmock/gmock.h>



namespace re2 {



class PrefilterTest_548 : public ::testing::Test {

protected:

    // No need to set up or tear down specific instances of Info for this test.

};



TEST_F(PrefilterTest_548, StarReturnsNonNullPointer_548) {

    Prefilter::Info* info = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Star(info);

    EXPECT_NE(result, nullptr);

    delete info;

    delete result;

}



TEST_F(PrefilterTest_548, StarDoesNotModifyOriginalInfo_548) {

    Prefilter::Info* info = new Prefilter::Info();

    Prefilter::Info::Star(info);



    // Verify that the original info object is not modified.

    EXPECT_FALSE(info->is_exact());

    delete info;

}



TEST_F(PrefilterTest_548, StarOfNullReturnsNonNullPointer_548) {

    Prefilter::Info* result = Prefilter::Info::Star(nullptr);

    EXPECT_NE(result, nullptr);

    delete result;

}



}  // namespace re2
