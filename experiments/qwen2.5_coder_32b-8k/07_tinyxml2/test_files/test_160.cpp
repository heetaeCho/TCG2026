#include <gtest/gtest.h>

#include "tinyxml2.h"

#include <gmock/gmock.h>



using namespace tinyxml2;

using namespace testing;



class StrPairTest_160 : public Test {

protected:

    StrPair strPair;

};



TEST_F(StrPairTest_160, NormalOperation_GetStr_160) {

    char buffer[] = "Hello";

    strPair.Set(buffer, buffer + 5, 0);

    EXPECT_STREQ(strPair.GetStr(), "Hello");

}



TEST_F(StrPairTest_160, BoundaryCondition_EmptyString_160) {

    char buffer[] = "";

    strPair.Set(buffer, buffer, 0);

    EXPECT_STREQ(strPair.GetStr(), "");

}



TEST_F(StrPairTest_160, NewlineNormalization_CR_LF_160) {

    char buffer[] = "Line\r\nEnd";

    strPair.Set(buffer, buffer + 8, NEEDS_NEWLINE_NORMALIZATION);

    EXPECT_STREQ(strPair.GetStr(), "Line\nEnd");

}



TEST_F(StrPairTest_160, NewlineNormalization_CR_Only_160) {

    char buffer[] = "Line\rEnd";

    strPair.Set(buffer, buffer + 7, NEEDS_NEWLINE_NORMALIZATION);

    EXPECT_STREQ(strPair.GetStr(), "Line\nEnd");

}



TEST_F(StrPairTest_160, NewlineNormalization_LF_Only_160) {

    char buffer[] = "Line\nEnd";

    strPair.Set(buffer, buffer + 7, NEEDS_NEWLINE_NORMALIZATION);

    EXPECT_STREQ(strPair.GetStr(), "Line\nEnd");

}



TEST_F(StrPairTest_160, EntityProcessing_AmpersandQuot_160) {

    char buffer[] = "This &quot;is&quot; a test";

    strPair.Set(buffer, buffer + 20, NEEDS_ENTITY_PROCESSING);

    EXPECT_STREQ(strPair.GetStr(), "This \"is\" a test");

}



TEST_F(StrPairTest_160, EntityProcessing_AmpersandAmp_160) {

    char buffer[] = "This &amp; is a test";

    strPair.Set(buffer, buffer + 20, NEEDS_ENTITY_PROCESSING);

    EXPECT_STREQ(strPair.GetStr(), "This & is a test");

}



TEST_F(StrPairTest_160, EntityProcessing_AmpersandApos_160) {

    char buffer[] = "This &apos;is&apos; a test";

    strPair.Set(buffer, buffer + 22, NEEDS_ENTITY_PROCESSING);

    EXPECT_STREQ(strPair.GetStr(), "This 'is' a test");

}



TEST_F(StrPairTest_160, EntityProcessing_AmpersandLt_160) {

    char buffer[] = "This &lt;is&lt; a test";

    strPair.Set(buffer, buffer + 20, NEEDS_ENTITY_PROCESSING);

    EXPECT_STREQ(strPair.GetStr(), "This <is< a test");

}



TEST_F(StrPairTest_160, EntityProcessing_AmpersandGt_160) {

    char buffer[] = "This &gt;is&gt; a test";

    strPair.Set(buffer, buffer + 20, NEEDS_ENTITY_PROCESSING);

    EXPECT_STREQ(strPair.GetStr(), "This >is> a test");

}



TEST_F(StrPairTest_160, EntityProcessing_UnrecognizedEntity_160) {

    char buffer[] = "This &unknown; is a test";

    strPair.Set(buffer, buffer + 24, NEEDS_ENTITY_PROCESSING);

    EXPECT_STREQ(strPair.GetStr(), "This &unknown; is a test");

}



TEST_F(StrPairTest_160, WhitespaceCollapsing_SingleSpace_160) {

    char buffer[] = "Hello World";

    strPair.Set(buffer, buffer + 11, NEEDS_WHITESPACE_COLLAPSING);

    EXPECT_STREQ(strPair.GetStr(), "Hello World");

}



TEST_F(StrPairTest_160, WhitespaceCollapsing_MultipleSpaces_160) {

    char buffer[] = "Hello   World";

    strPair.Set(buffer, buffer + 13, NEEDS_WHITESPACE_COLLAPSING);

    EXPECT_STREQ(strPair.GetStr(), "Hello World");

}



TEST_F(StrPairTest_160, WhitespaceCollapsing_NewlinesAndTabs_160) {

    char buffer[] = "Hello\n\tWorld";

    strPair.Set(buffer, buffer + 13, NEEDS_WHITESPACE_COLLAPSING);

    EXPECT_STREQ(strPair.GetStr(), "Hello World");

}



TEST_F(StrPairTest_160, Combination_NewlinesEntitiesWhitespace_160) {

    char buffer[] = "Line\r\nThis &quot;is&quot;\t a test";

    strPair.Set(buffer, buffer + 32, NEEDS_NEWLINE_NORMALIZATION | NEEDS_ENTITY_PROCESSING | NEEDS_WHITESPACE_COLLAPSING);

    EXPECT_STREQ(strPair.GetStr(), "Line\nThis \"is\" a test");

}



TEST_F(StrPairTest_160, ExceptionalCase_NullStartPointer_160) {

    char* nullPtr = nullptr;

    strPair.Set(nullPtr, nullPtr, 0);

    EXPECT_EQ(strPair.GetStr(), "");

}



TEST_F(StrPairTest_160, ExceptionalCase_EndBeforeStart_160) {

    char buffer[] = "Hello";

    strPair.Set(buffer + 5, buffer, 0);

    EXPECT_EQ(strPair.GetStr(), "");

}
