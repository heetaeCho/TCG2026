#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/StructElement.h"



class StructElementTest_1696 : public ::testing::Test {

protected:

    StructTreeRoot *treeRoot;

    StructElement *parent;

    StructElement *element;



    void SetUp() override {

        treeRoot = new StructTreeRoot();

        parent = new StructElement(treeRoot, nullptr);

        element = new StructElement(treeRoot, parent);

    }



    void TearDown() override {

        delete element;

        delete parent;

        delete treeRoot;

    }

};



TEST_F(StructElementTest_1696, GetParentReturnsCorrectParent_1696) {

    EXPECT_EQ(element->getParent(), parent);

}



TEST_F(StructElementTest_1696, GetParentReturnsNullWhenNoParent_1696) {

    StructElement *noParentElement = new StructElement(treeRoot, nullptr);

    EXPECT_EQ(noParentElement->getParent(), nullptr);

    delete noParentElement;

}



TEST_F(StructElementTest_1696, IsBlockReturnsFalseByDefault_1696) {

    EXPECT_FALSE(element->isBlock());

}



TEST_F(StructElementTest_1696, IsInlineReturnsFalseByDefault_1696) {

    EXPECT_FALSE(element->isInline());

}



TEST_F(StructElementTest_1696, IsGroupingReturnsFalseByDefault_1696) {

    EXPECT_FALSE(element->isGrouping());

}



TEST_F(StructElementTest_1696, HasPageRefReturnsFalseByDefault_1696) {

    Ref ref;

    EXPECT_FALSE(element->getPageRef(ref));

}



TEST_F(StructElementTest_1696, HasStmRefReturnsFalseByDefault_1696) {

    Ref ref;

    EXPECT_FALSE(element->getStmRef(ref));

}



TEST_F(StructElementTest_1696, FindAttributeReturnsNullWhenNotFound_1696) {

    Attribute *attribute = element->findAttribute(Attribute::Type::Title, false, Attribute::Owner::Self);

    EXPECT_EQ(attribute, nullptr);

}



TEST_F(StructElementTest_1696, GetTypeReturnsDefaultType_1696) {

    EXPECT_EQ(element->getType(), StructElement::Type::Unknown);

}



TEST_F(StructElementTest_1696, IsOkReturnsTrueByDefault_1696) {

    EXPECT_TRUE(element->isOk());

}



TEST_F(StructElementTest_1696, IsContentReturnsFalseByDefault_1696) {

    EXPECT_FALSE(element->isContent());

}



TEST_F(StructElementTest_1696, IsObjectRefReturnsFalseByDefault_1696) {

    EXPECT_FALSE(element->isObjectRef());

}



TEST_F(StructElementTest_1696, GetMCIDReturnsZeroByDefault_1696) {

    EXPECT_EQ(element->getMCID(), 0);

}



TEST_F(StructElementTest_1696, GetObjectRefReturnsNullByDefault_1696) {

    Ref ref = element->getObjectRef();

    EXPECT_TRUE(ref.isNone());

}



TEST_F(StructElementTest_1696, GetParentRefReturnsNullByDefault_1696) {

    Ref ref = element->getParentRef();

    EXPECT_TRUE(ref.isNone());

}



TEST_F(StructElementTest_1696, GetStructTreeRootReturnsCorrectTreeRoot_1696) {

    EXPECT_EQ(element->getStructTreeRoot(), treeRoot);

}



TEST_F(StructElementTest_1696, GetIDReturnsNullByDefault_1696) {

    const GooString *id = element->getID();

    EXPECT_EQ(id, nullptr);

}



TEST_F(StructElementTest_1696, GetLanguageReturnsNullByDefault_1696) {

    GooString *language = element->getLanguage();

    EXPECT_EQ(language, nullptr);

}



TEST_F(StructElementTest_1696, GetRevisionReturnsZeroByDefault_1696) {

    EXPECT_EQ(element->getRevision(), 0);

}



TEST_F(StructElementTest_1696, GetTitleReturnsNullByDefault_1696) {

    const GooString *title = element->getTitle();

    EXPECT_EQ(title, nullptr);

}



TEST_F(StructElementTest_1696, GetExpandedAbbrReturnsNullByDefault_1696) {

    const GooString *expandedAbbr = element->getExpandedAbbr();

    EXPECT_EQ(expandedAbbr, nullptr);

}



TEST_F(StructElementTest_1696, GetNumChildrenReturnsZeroWhenNoChildren_1696) {

    EXPECT_EQ(element->getNumChildren(), 0);

}



TEST_F(StructElementTest_1696, GetChildThrowsExceptionForInvalidIndex_1696) {

    EXPECT_THROW(element->getChild(0), std::out_of_range);

}



TEST_F(StructElementTest_1696, AppendChildIncreasesNumChildren_1696) {

    StructElement *child = new StructElement(treeRoot, element);

    element->appendChild(child);

    EXPECT_EQ(element->getNumChildren(), 1);

    delete child;

}



TEST_F(StructElementTest_1696, GetNumAttributesReturnsZeroWhenNoAttributes_1696) {

    EXPECT_EQ(element->getNumAttributes(), 0);

}



TEST_F(StructElementTest_1696, GetAttributeThrowsExceptionForInvalidIndex_1696) {

    EXPECT_THROW(element->getAttribute(0), std::out_of_range);

}



TEST_F(StructElementTest_1696, AppendAttributeIncreasesNumAttributes_1696) {

    Attribute *attribute = new Attribute(Attribute::Type::Title);

    element->appendAttribute(attribute);

    EXPECT_EQ(element->getNumAttributes(), 1);

    delete attribute;

}



TEST_F(StructElementTest_1696, GetAltTextReturnsNullByDefault_1696) {

    const GooString *altText = element->getAltText();

    EXPECT_EQ(altText, nullptr);

}



TEST_F(StructElementTest_1696, GetActualTextReturnsNullByDefault_1696) {

    const GooString *actualText = element->getActualText();

    EXPECT_EQ(actualText, nullptr);

}



TEST_F(StructElementTest_1696, GetTextReturnsEmptyStringByDefault_1696) {

    GooString *text = element->getText().copy();

    EXPECT_TRUE(text->isEmpty());

    delete text;

}



TEST_F(StructElementTest_1696, GetTextSpansReturnsEmptyArrayByDefault_1696) {

    TextSpanArray spans = element->getTextSpans();

    EXPECT_EQ(spans.size(), 0);

}
