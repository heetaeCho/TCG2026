#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/annot_stamp_confidential.h"

#include "TestProjects/poppler/poppler/PDFDoc.h"



// Mocking XRef as it's used internally by Dict and PDFDoc

class MockXRef : public XRef {

public:

    MOCK_METHOD(XRef*, getXRef, (), (override));

};



// Test Fixture for the getConfidentialStampExtGStateDict function

class GetConfidentialStampExtGStateDictTest_2003 : public ::testing::Test {

protected:

    std::unique_ptr<MockXRef> mockXRef;

    std::unique_ptr<PDFDoc> pdfDoc;



    void SetUp() override {

        mockXRef = std::make_unique<MockXRef>();

        pdfDoc = std::make_unique<PDFDoc>(std::make_unique<GooString>("dummy.pdf"), std::optional<GooString>(), std::optional<GooString>(), [](){});

        ON_CALL(*mockXRef, getXRef()).WillByDefault(::testing::Return(mockXRef.get()));

    }

};



// Test normal operation

TEST_F(GetConfidentialStampExtGStateDictTest_2003, ReturnsValidDict_2003) {

    Dict* extGStateDict = getConfidentialStampExtGStateDict(pdfDoc.get());

    EXPECT_NE(extGStateDict, nullptr);

}



// Test that the returned dictionary has the correct structure

TEST_F(GetConfidentialStampExtGStateDictTest_2003, CorrectStructure_2003) {

    Dict* extGStateDict = getConfidentialStampExtGStateDict(pdfDoc.get());

    EXPECT_TRUE(extGStateDict->hasKey("a0"));

    EXPECT_TRUE(extGStateDict->hasKey("a1"));



    const Object& a0Obj = extGStateDict->lookupNF("a0");

    EXPECT_TRUE(a0Obj.isDict());



    const Object& a1Obj = extGStateDict->lookupNF("a1");

    EXPECT_TRUE(a1Obj.isDict());

}



// Test that the nested dictionaries have correct values

TEST_F(GetConfidentialStampExtGStateDictTest_2003, CorrectNestedValues_2003) {

    Dict* extGStateDict = getConfidentialStampExtGStateDict(pdfDoc.get());



    const Object& a0Obj = extGStateDict->lookupNF("a0");

    const Dict* a0Dict = a0Obj.getDict();

    EXPECT_TRUE(a0Dict->hasKey("CA"));

    EXPECT_TRUE(a0Dict->hasKey("ca"));



    int caValue;

    bool isCaInt = a0Dict->lookupInt("CA", std::nullopt, &caValue);

    EXPECT_TRUE(isCaInt);

    EXPECT_EQ(caValue, 588235); // Note: The value is stored as an integer representation of the float 0.588235



    bool isCaFloat = a0Dict->lookupNF("CA").isReal();

    EXPECT_TRUE(isCaFloat);



    const Object& a1Obj = extGStateDict->lookupNF("a1");

    const Dict* a1Dict = a1Obj.getDict();

    EXPECT_TRUE(a1Dict->hasKey("CA"));

    EXPECT_TRUE(a1Dict->hasKey("ca"));



    isCaInt = a1Dict->lookupInt("CA", std::nullopt, &caValue);

    EXPECT_TRUE(isCaInt);

    EXPECT_EQ(caValue, 1); // Note: The value is stored as an integer representation of the float 1.0



    isCaFloat = a1Dict->lookupNF("CA").isReal();

    EXPECT_TRUE(isCaFloat);

}



// Test boundary conditions (none expected in this case)

// Test exceptional or error cases (none expected in this case)



int main(int argc, char **argv) {

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();

}
