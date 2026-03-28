#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/StructElement.h"



class StructElementTest_1699 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common objects or states here if necessary

    }



    void TearDown() override {

        // Cleanup any common objects or states here if necessary

    }

};



TEST_F(StructElementTest_1699, GetID_ReturnsNullptr_WhenIsContentTrue_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    EXPECT_CALL(*element.s, isContent()).WillOnce(testing::Return(true));

    EXPECT_EQ(element.getID(), nullptr);

}



TEST_F(StructElementTest_1699, GetID_ReturnsNonNull_WhenIsContentFalse_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    EXPECT_CALL(*element.s, isContent()).WillOnce(testing::Return(false));

    EXPECT_NE(element.getID(), nullptr);

}



TEST_F(StructElementTest_1699, IsOk_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    bool result = element.isOk();

    EXPECT_TRUE(result);  // Assuming isOk() should return true by default or based on internal state

}



TEST_F(StructElementTest_1699, IsContent_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    bool result = element.isContent();

    EXPECT_TRUE(result);  // Assuming isContent() should return true or false based on internal state

}



TEST_F(StructElementTest_1699, GetMCID_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    int mcid = element.getMCID();

    EXPECT_EQ(mcid, -1);  // Assuming getMCID() should return a default value like -1 if not set

}



TEST_F(StructElementTest_1699, GetObjectRef_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    Ref ref = element.getObjectRef();

    EXPECT_TRUE(ref.isNone());  // Assuming getObjectRef() should return a null reference by default

}



TEST_F(StructElementTest_1699, GetParentRef_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    Ref ref = element.getParentRef();

    EXPECT_TRUE(ref.isNone());  // Assuming getParentRef() should return a null reference by default

}



TEST_F(StructElementTest_1699, GetParent_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    StructElement* parent = element.getParent();

    EXPECT_EQ(parent, nullptr);  // Assuming getParent() should return a null pointer by default

}



TEST_F(StructElementTest_1699, HasStmRef_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    bool result = element.hasStmRef();

    EXPECT_FALSE(result);  // Assuming hasStmRef() should return false by default

}



TEST_F(StructElementTest_1699, GetStructTreeRoot_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    StructTreeRoot* root = element.getStructTreeRoot();

    EXPECT_EQ(root, nullptr);  // Assuming getStructTreeRoot() should return a null pointer by default

}



TEST_F(StructElementTest_1699, GetLanguage_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    GooString* language = element.getLanguage();

    EXPECT_EQ(language, nullptr);  // Assuming getLanguage() should return a null pointer if not set

}



TEST_F(StructElementTest_1699, GetRevision_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    unsigned int revision = element.getRevision();

    EXPECT_EQ(revision, 0);  // Assuming getRevision() should return 0 by default

}



TEST_F(StructElementTest_1699, GetTitle_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    GooString* title = element.getTitle();

    EXPECT_EQ(title, nullptr);  // Assuming getTitle() should return a null pointer if not set

}



TEST_F(StructElementTest_1699, GetExpandedAbbr_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    GooString* expandedAbbr = element.getExpandedAbbr();

    EXPECT_EQ(expandedAbbr, nullptr);  // Assuming getExpandedAbbr() should return a null pointer if not set

}



TEST_F(StructElementTest_1699, GetNumChildren_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    unsigned numChildren = element.getNumChildren();

    EXPECT_EQ(numChildren, 0);  // Assuming getNumChildren() should return 0 by default

}



TEST_F(StructElementTest_1699, GetChild_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    StructElement* child = element.getChild(0);

    EXPECT_EQ(child, nullptr);  // Assuming getChild() should return a null pointer if index is out of bounds

}



TEST_F(StructElementTest_1699, GetNumAttributes_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    unsigned numAttributes = element.getNumAttributes();

    EXPECT_EQ(numAttributes, 0);  // Assuming getNumAttributes() should return 0 by default

}



TEST_F(StructElementTest_1699, GetAttribute_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    const Attribute* attribute = element.getAttribute(0);

    EXPECT_EQ(attribute, nullptr);  // Assuming getAttribute() should return a null pointer if index is out of bounds

}



TEST_F(StructElementTest_1699, GetAltText_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    GooString* altText = element.getAltText();

    EXPECT_EQ(altText, nullptr);  // Assuming getAltText() should return a null pointer if not set

}



TEST_F(StructElementTest_1699, GetActualText_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    GooString* actualText = element.getActualText();

    EXPECT_EQ(actualText, nullptr);  // Assuming getActualText() should return a null pointer if not set

}



TEST_F(StructElementTest_1699, GetText_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    GooString* text = element.getText();

    EXPECT_NE(text, nullptr);  // Assuming getText() should return a non-null pointer with empty or constructed string

}



TEST_F(StructElementTest_1699, GetTextSpans_ReturnsExpectedValue_NormalOperation_1699) {

    StructElement element;  // Assuming default constructor is available for testing

    TextSpanArray textSpans = element.getTextSpans();

    EXPECT_EQ(textSpans.size(), 0);  // Assuming getTextSpans() should return an empty array by default

}

```


