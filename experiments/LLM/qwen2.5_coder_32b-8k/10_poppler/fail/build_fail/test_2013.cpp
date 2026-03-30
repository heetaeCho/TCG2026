#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler/annot_stamp_for_public_release.h"

#include "poppler/PDFDoc.h"

#include "poppler/Dict.h"



using namespace testing;



class GetForPublicReleaseStampExtGStateDictTest : public Test {

protected:

    MockXRef mockXRef;

    PDFDoc doc{nullptr, std::nullopt, std::nullopt, nullptr};



    void SetUp() override {

        ON_CALL(mockXRef, getXRef()).WillByDefault(Return(&mockXRef));

        doc.setXRef(&mockXRef);

    }

};



TEST_F(GetForPublicReleaseStampExtGStateDictTest_2013, ReturnsNonNullPtr_2013) {

    Dict* result = getForPublicReleaseStampExtGStateDict(&doc);

    EXPECT_NE(result, nullptr);

}



TEST_F(GetForPublicReleaseStampExtGStateDictTest_2013, ContainsA0DictionaryWithCorrectValues_2013) {

    Dict* result = getForPublicReleaseStampExtGStateDict(&doc);

    const Object& a0Obj = result->lookupNF("a0");

    EXPECT_TRUE(a0Obj.isDict());



    Dict* a0Dict = a0Obj.getDict();

    const Object& caA0Obj = a0Dict->lookupNF("CA");

    const Object& caA1Obj = a0Dict->lookupNF("ca");



    EXPECT_EQ(caA0Obj.getNum(), 0.588235);

    EXPECT_EQ(caA1Obj.getNum(), 0.588235);

}



TEST_F(GetForPublicReleaseStampExtGStateDictTest_2013, ContainsA1DictionaryWithCorrectValues_2013) {

    Dict* result = getForPublicReleaseStampExtGStateDict(&doc);

    const Object& a1Obj = result->lookupNF("a1");

    EXPECT_TRUE(a1Obj.isDict());



    Dict* a1Dict = a1Obj.getDict();

    const Object& caA0Obj = a1Dict->lookupNF("CA");

    const Object& caA1Obj = a1Dict->lookupNF("ca");



    EXPECT_EQ(caA0Obj.getNum(), 1.0);

    EXPECT_EQ(caA1Obj.getNum(), 1.0);

}



TEST_F(GetForPublicReleaseStampExtGStateDictTest_2013, CorrectNumberOfEntriesInRootDict_2013) {

    Dict* result = getForPublicReleaseStampExtGStateDict(&doc);

    EXPECT_EQ(result->getLength(), 2); // "a0" and "a1"

}



TEST_F(GetForPublicReleaseStampExtGStateDictTest_2013, EntriesAreAccessibleByKeys_2013) {

    Dict* result = getForPublicReleaseStampExtGStateDict(&doc);

    EXPECT_TRUE(result->hasKey("a0"));

    EXPECT_TRUE(result->hasKey("a1"));

}



TEST_F(GetForPublicReleaseStampExtGStateDictTest_2013, NonExistentKeysReturnNonDictObjects_2013) {

    Dict* result = getForPublicReleaseStampExtGStateDict(&doc);

    const Object& nonExistentObj = result->lookupNF("nonexistent");

    EXPECT_FALSE(nonExistentObj.isDict());

}
