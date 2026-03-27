#include <gtest/gtest.h>

#include "StructElement.h"

#include <gmock/gmock.h>



class MockStructTreeRoot : public StructTreeRoot {

public:

    MOCK_METHOD(Ref, getRef, (), (const));

};



class MockAttribute : public Attribute {

public:

    MOCK_METHOD(Attribute::Type, getType, (), (const));

};



class StructElementTest_1693 : public ::testing::Test {

protected:

    MockStructTreeRoot mockTreeRoot;

    StructElement* element;



    void SetUp() override {

        element = new StructElement(42, &mockTreeRoot, nullptr);

    }



    void TearDown() override {

        delete element;

    }

};



TEST_F(StructElementTest_1693, GetMCID_ReturnsCorrectValue_1693) {

    EXPECT_EQ(element->getMCID(), 42);

}



TEST_F(StructElementTest_1693, GetType_ReturnsValidType_1693) {

    StructElement::Type type = element->getType();

    EXPECT_TRUE(type >= StructElement::typeUnknown && type <= StructElement::typeFigure);

}



TEST_F(StructElementTest_1693, IsOk_ReturnsTrue_1693) {

    EXPECT_TRUE(element->isOk());

}



TEST_F(StructElementTest_1693, GetObjectRef_ReturnsValidRef_1693) {

    Ref ref = element->getObjectRef();

    EXPECT_FALSE(ref.isNone());

}



TEST_F(StructElementTest_1693, HasPageRef_ReturnsFalse_1693) {

    EXPECT_FALSE(element->hasPageRef());

}



TEST_F(StructElementTest_1693, GetParent_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getParent(), nullptr);

}



TEST_F(StructElementTest_1693, HasStmRef_ReturnsFalse_1693) {

    EXPECT_FALSE(element->hasStmRef());

}



TEST_F(StructElementTest_1693, GetStructTreeRoot_ReturnsValidPointer_1693) {

    EXPECT_EQ(element->getStructTreeRoot(), &mockTreeRoot);

}



TEST_F(StructElementTest_1693, GetID_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getID(), nullptr);

}



TEST_F(StructElementTest_1693, GetLanguage_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getLanguage(), nullptr);

}



TEST_F(StructElementTest_1693, GetRevision_ReturnsZero_1693) {

    EXPECT_EQ(element->getRevision(), 0u);

}



TEST_F(StructElementTest_1693, GetTitle_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getTitle(), nullptr);

}



TEST_F(StructElementTest_1693, GetExpandedAbbr_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getExpandedAbbr(), nullptr);

}



TEST_F(StructElementTest_1693, GetNumChildren_ReturnsZero_1693) {

    EXPECT_EQ(element->getNumChildren(), 0u);

}



TEST_F(StructElementTest_1693, GetChild_OutOfBounds_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getChild(0), nullptr);

}



TEST_F(StructElementTest_1693, HasAttribute_NoAttributes_ReturnsNullptr_1693) {

    MockAttribute mockAttribute;

    EXPECT_CALL(mockAttribute, getType()).WillOnce(::testing::Return(Attribute::typeTitle));

    EXPECT_EQ(element->findAttribute(Attribute::typeTitle, true, Attribute::OwnerSelf), nullptr);

}



TEST_F(StructElementTest_1693, GetNumAttributes_ReturnsZero_1693) {

    EXPECT_EQ(element->getNumAttributes(), 0u);

}



TEST_F(StructElementTest_1693, GetAttribute_OutOfBounds_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getAttribute(0), nullptr);

}



TEST_F(StructElementTest_1693, GetAltText_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getAltText(), nullptr);

}



TEST_F(StructElementTest_1693, GetActualText_ReturnsNullptr_1693) {

    EXPECT_EQ(element->getActualText(), nullptr);

}



TEST_F(StructElementTest_1693, GetText_EmptyContent_ReturnsEmptyString_1693) {

    GooString* text = element->getText().copy();

    EXPECT_TRUE(text->isEmpty());

    delete text;

}



TEST_F(StructElementTest_1693, GetTextSpans_NoContent_ReturnsEmptyArray_1693) {

    TextSpanArray spans = element->getTextSpans();

    EXPECT_EQ(spans.size(), 0u);

}
