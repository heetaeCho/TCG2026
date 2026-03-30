#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/re2/re2/prefilter.h"

#include "./TestProjects/re2/re2/prefilter.cc"



using namespace re2;



class PrefilterInfoTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(PrefilterInfoTest_547, Quest_ReturnsNewInfoObject_547) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* result = Prefilter::Info::Quest(a);

    

    EXPECT_NE(result, nullptr);

    EXPECT_FALSE(result->is_exact());

    EXPECT_EQ(result->TakeMatch()->Op(), Prefilter::ALL);



    delete result;

}



TEST_F(PrefilterInfoTest_547, Quest_DeletesOriginalObject_547) {

    Prefilter::Info* a = new Prefilter::Info();

    Prefilter::Info* original_address = a;



    Prefilter::Info* result = Prefilter::Info::Quest(a);

    

    EXPECT_NE(result, original_address);



    delete result;

}



TEST_F(PrefilterInfoTest_547, TakeMatch_ReturnsNonNullPointer_547) {

    Prefilter::Info* info = new Prefilter::Info();

    Prefilter* match = info->TakeMatch();



    EXPECT_NE(match, nullptr);

    

    delete info;

}



TEST_F(PrefilterInfoTest_547, IsExact_DefaultValueFalse_547) {

    Prefilter::Info* info = new Prefilter::Info();

    

    EXPECT_FALSE(info->is_exact());

    

    delete info;

}



TEST_F(PrefilterInfoTest_547, ToString_ReturnsNonEmptyString_547) {

    Prefilter::Info* info = new Prefilter::Info();

    std::string str = info->ToString();



    EXPECT_FALSE(str.empty());



    delete info;

}
