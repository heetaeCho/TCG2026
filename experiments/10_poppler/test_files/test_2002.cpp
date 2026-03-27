#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/poppler/annot_stamp_as_is.h"

#include "TestProjects/poppler/poppler/PDFDoc.h"



using ::testing::Return;

using ::testing::_;



class PDFDocMock : public PDFDoc {

public:

    MOCK_METHOD(XRef*, getXRef, (), (override));

};



TEST_F(PDFDocMock, GetAsIsStampExtGStateDict_ReturnsValidDict_2002) {

    XRef* mockXRef = new XRef();

    EXPECT_CALL(*this, getXRef()).WillRepeatedly(Return(mockXRef));



    Dict* result = getAsIsStampExtGStateDict(this);

    ASSERT_NE(result, nullptr);



    // Verify the structure of the returned dictionary

    const Object& a0Obj = result->lookupNF("a0");

    EXPECT_TRUE(a0Obj.isDict());

    const Dict* a0Dict = a0Obj.getDict();

    EXPECT_EQ(a0Dict->getLength(), 2);

    EXPECT_FLOAT_EQ(a0Dict->lookupNF("CA").getNum(), 0.588235f);

    EXPECT_FLOAT_EQ(a0Dict->lookupNF("ca").getNum(), 0.588235f);



    const Object& a1Obj = result->lookupNF("a1");

    EXPECT_TRUE(a1Obj.isDict());

    const Dict* a1Dict = a1Obj.getDict();

    EXPECT_EQ(a1Dict->getLength(), 2);

    EXPECT_FLOAT_EQ(a1Dict->lookupNF("CA").getNum(), 1.0f);

    EXPECT_FLOAT_EQ(a1Dict->lookupNF("ca").getNum(), 1.0f);



    delete result;

    delete mockXRef;

}



TEST_F(PDFDocMock, GetAsIsStampExtGStateDict_ReturnsNewObject_2002) {

    XRef* mockXRef = new XRef();

    EXPECT_CALL(*this, getXRef()).WillRepeatedly(Return(mockXRef));



    Dict* result1 = getAsIsStampExtGStateDict(this);

    Dict* result2 = getAsIsStampExtGStateDict(this);



    EXPECT_NE(result1, result2);  // Ensure that each call returns a new object



    delete result1;

    delete result2;

    delete mockXRef;

}
