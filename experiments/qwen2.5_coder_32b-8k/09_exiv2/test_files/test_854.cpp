#include <gtest/gtest.h>

#include "exiv2/value.hpp"



using namespace Exiv2;



class LangAltValueTest_854 : public ::testing::Test {

protected:

    LangAltValue langAltValue;

};



TEST_F(LangAltValueTest_854, InitialCountIsZero_854) {

    EXPECT_EQ(langAltValue.count(), 0);

}



TEST_F(LangAltValueTest_854, CountIncreasesAfterRead_854) {

    std::string buffer = "en-US:Hello,en-GB:World";

    langAltValue.read(buffer);

    EXPECT_GT(langAltValue.count(), 0);

}



TEST_F(LangAltValueTest_854, CountReflectsNumberOfEntries_854) {

    std::string buffer = "en-US:Hello,en-GB:World,fr-FR:Bonjour";

    langAltValue.read(buffer);

    EXPECT_EQ(langAltValue.count(), 3);

}



TEST_F(LangAltValueTest_854, CountDoesNotDecreaseAfterRead_854) {

    std::string buffer1 = "en-US:Hello,en-GB:World";

    std::string buffer2 = "fr-FR:Bonjour";

    langAltValue.read(buffer1);

    size_t initialCount = langAltValue.count();

    langAltValue.read(buffer2);

    EXPECT_GE(langAltValue.count(), initialCount);

}



TEST_F(LangAltValueTest_854, CloneReturnsNonNullPointer_854) {

    LangAltValue::UniquePtr clone = langAltValue.clone();

    EXPECT_NE(clone.get(), nullptr);

}



TEST_F(LangAltValueTest_854, ToStringReturnsNonEmptyString_854) {

    std::string buffer = "en-US:Hello";

    langAltValue.read(buffer);

    EXPECT_FALSE(langAltValue.toString(0).empty());

}



TEST_F(LangAltValueTest_854, ToInt64ThrowsForInvalidIndex_854) {

    EXPECT_THROW(langAltValue.toInt64(0), std::out_of_range);

}



TEST_F(LangAltValueTest_854, ToUint32ThrowsForInvalidIndex_854) {

    EXPECT_THROW(langAltValue.toUint32(0), std::out_of_range);

}



TEST_F(LangAltValueTest_854, ToFloatThrowsForInvalidIndex_854) {

    EXPECT_THROW(langAltValue.toFloat(0), std::out_of_range);

}



TEST_F(LangAltValueTest_854, ToRationalThrowsForInvalidIndex_854) {

    EXPECT_THROW(langAltValue.toRational(0), std::out_of_range);

}
