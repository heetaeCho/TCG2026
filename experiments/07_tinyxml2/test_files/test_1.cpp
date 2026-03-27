#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class StrPairTest : public ::testing::Test {

protected:

    StrPair sp;

};



TEST_F(StrPairTest_1, SetAssignsValuesCorrectly_1) {

    char start[] = "start";

    char end[] = "end";

    int flags = 0x100;



    sp.Set(start, end, flags);



    EXPECT_STREQ(sp.GetStr(), start);

}



TEST_F(StrPairTest_1, SetFlagsIncludeNEEDS_FLUSH_1) {

    char start[] = "start";

    char end[] = "end";

    int flags = 0x100;



    sp.Set(start, end, flags);



    EXPECT_EQ(sp._flags & StrPair::NEEDS_FLUSH, StrPair::NEEDS_FLUSH);

}



TEST_F(StrPairTest_1, ResetClearsValues_1) {

    char start[] = "start";

    char end[] = "end";

    int flags = 0x100;



    sp.Set(start, end, flags);

    sp.Reset();



    EXPECT_STREQ(sp.GetStr(), "");

}



TEST_F(StrPairTest_1, EmptyReturnsTrueAfterReset_1) {

    char start[] = "start";

    char end[] = "end";

    int flags = 0x100;



    sp.Set(start, end, flags);

    sp.Reset();



    EXPECT_TRUE(sp.Empty());

}



TEST_F(StrPairTest_1, SetStrAssignsStringCorrectly_1) {

    const char* str = "new string";

    int flags = 0x200;



    sp.SetStr(str, flags);



    EXPECT_STREQ(sp.GetStr(), str);

}



TEST_F(StrPairTest_1, EmptyReturnsFalseAfterSetStr_1) {

    const char* str = "new string";

    int flags = 0x200;



    sp.SetStr(str, flags);



    EXPECT_FALSE(sp.Empty());

}
