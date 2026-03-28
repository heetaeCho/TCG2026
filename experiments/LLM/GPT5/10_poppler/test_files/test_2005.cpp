#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/annot_stamp_final.h"
#include "./TestProjects/poppler/poppler/PDFDoc.h"
#include "./TestProjects/poppler/poppler/Dict.h"

// Mock the PDFDoc class
class MockPDFDoc : public PDFDoc {
public:
    MockPDFDoc() : PDFDoc(nullptr, {}, {}, nullptr) {}

    MOCK_METHOD(XRef*, getXRef, (), (const, override));
};

// Test Fixture for the `getFinalStampExtGStateDict` function
class AnnotStampTest_2005 : public ::testing::Test {
protected:
    // Helper function to mock XRef and return it when needed
    XRef* mockXRef() {
        XRef* mockXRef = new XRef();
        return mockXRef;
    }
};

// Test case for normal operation of `getFinalStampExtGStateDict`
TEST_F(AnnotStampTest_2005, GetFinalStampExtGStateDict_ReturnsValidDict_2005) {
    // Create a mock PDFDoc object
    MockPDFDoc doc;
    XRef* mockXRef = mockXRef();

    // Set expectations on the mock XRef object
    EXPECT_CALL(doc, getXRef())
        .WillOnce(testing::Return(mockXRef));

    // Call the function under test
    Dict* extGStateDict = getFinalStampExtGStateDict(&doc);

    // Check if the returned Dict is not nullptr
    ASSERT_NE(extGStateDict, nullptr);

    // Check the expected keys in the Dict
    EXPECT_TRUE(extGStateDict->hasKey("a0"));
    EXPECT_TRUE(extGStateDict->hasKey("a1"));
}

// Test case for boundary condition: check if the dict has keys "CA" and "ca"
TEST_F(AnnotStampTest_2005, GetFinalStampExtGStateDict_ContainsExpectedKeys_2005) {
    // Create a mock PDFDoc object
    MockPDFDoc doc;
    XRef* mockXRef = mockXRef();

    // Set expectations on the mock XRef object
    EXPECT_CALL(doc, getXRef())
        .WillOnce(testing::Return(mockXRef));

    // Call the function under test
    Dict* extGStateDict = getFinalStampExtGStateDict(&doc);

    // Check that the keys "CA" and "ca" exist within the "a0" and "a1" sub-dictionaries
    Object a0DictObj = extGStateDict->lookup("a0", 0);
    Dict* a0Dict = a0DictObj.getDict();
    EXPECT_TRUE(a0Dict->hasKey("CA"));
    EXPECT_TRUE(a0Dict->hasKey("ca"));

    Object a1DictObj = extGStateDict->lookup("a1", 0);
    Dict* a1Dict = a1DictObj.getDict();
    EXPECT_TRUE(a1Dict->hasKey("CA"));
    EXPECT_TRUE(a1Dict->hasKey("ca"));
}

// Test case for exceptional case: if the XRef is null
TEST_F(AnnotStampTest_2005, GetFinalStampExtGStateDict_ThrowsIfXRefNull_2005) {
    // Create a mock PDFDoc object that returns a null XRef
    MockPDFDoc doc;
    EXPECT_CALL(doc, getXRef())
        .WillOnce(testing::Return(nullptr));

    // Expect the function to throw an exception if XRef is null
    EXPECT_THROW(getFinalStampExtGStateDict(&doc), std::runtime_error);
}

// Test case for boundary condition: test if the Dict size is correct
TEST_F(AnnotStampTest_2005, GetFinalStampExtGStateDict_CorrectDictSize_2005) {
    // Create a mock PDFDoc object
    MockPDFDoc doc;
    XRef* mockXRef = mockXRef();

    // Set expectations on the mock XRef object
    EXPECT_CALL(doc, getXRef())
        .WillOnce(testing::Return(mockXRef));

    // Call the function under test
    Dict* extGStateDict = getFinalStampExtGStateDict(&doc);

    // Check if the size of the dict is as expected
    EXPECT_EQ(extGStateDict->getLength(), 2);
}

// Test case for boundary condition: validate key-value pairs for "CA" and "ca"
TEST_F(AnnotStampTest_2005, GetFinalStampExtGStateDict_ValidKeyValuePairs_2005) {
    // Create a mock PDFDoc object
    MockPDFDoc doc;
    XRef* mockXRef = mockXRef();

    // Set expectations on the mock XRef object
    EXPECT_CALL(doc, getXRef())
        .WillOnce(testing::Return(mockXRef));

    // Call the function under test
    Dict* extGStateDict = getFinalStampExtGStateDict(&doc);

    // Verify the correct values for "CA" and "ca" in the "a0" and "a1" dictionaries
    Object a0DictObj = extGStateDict->lookup("a0", 0);
    Dict* a0Dict = a0DictObj.getDict();
    EXPECT_EQ(a0Dict->lookup("CA", 0).getFloat(), 0.588235);
    EXPECT_EQ(a0Dict->lookup("ca", 0).getFloat(), 0.588235);

    Object a1DictObj = extGStateDict->lookup("a1", 0);
    Dict* a1Dict = a1DictObj.getDict();
    EXPECT_EQ(a1Dict->lookup("CA", 0).getFloat(), 1);
    EXPECT_EQ(a1Dict->lookup("ca", 0).getFloat(), 1);
}