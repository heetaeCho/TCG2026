#include <gtest/gtest.h>

#include "tinyxml2.h"



using namespace tinyxml2;



class XMLDeclarationTest_202 : public ::testing::Test {

protected:

    XMLDocument doc;

    XMLDeclaration* decl;



    void SetUp() override {

        decl = new XMLDeclaration(&doc);

        decl->SetValue("version=\"1.0\" encoding=\"UTF-8\"");

    }



    void TearDown() override {

        delete decl;

    }

};



TEST_F(XMLDeclarationTest_202, ShallowCloneWithProvidedDocument_202) {

    XMLDocument newDoc(false, Whitespace::COLLAPSE_WHITESPACE);

    XMLDeclaration* clone = static_cast<XMLDeclaration*>(decl->ShallowClone(&newDoc));

    

    ASSERT_NE(clone, nullptr);

    EXPECT_EQ(clone->GetDocument(), &newDoc);

    EXPECT_STREQ(clone->Value(), decl->Value());

    

    newDoc.DeleteNode(clone);

}



TEST_F(XMLDeclarationTest_202, ShallowCloneWithNullDocument_202) {

    XMLDeclaration* clone = static_cast<XMLDeclaration*>(decl->ShallowClone(nullptr));

    

    ASSERT_NE(clone, nullptr);

    EXPECT_EQ(clone->GetDocument(), decl->GetDocument());

    EXPECT_STREQ(clone->Value(), decl->Value());



    doc.DeleteNode(clone);

}



TEST_F(XMLDeclarationTest_202, ShallowCloneWithSameDocument_202) {

    XMLDeclaration* clone = static_cast<XMLDeclaration*>(decl->ShallowClone(&doc));

    

    ASSERT_NE(clone, nullptr);

    EXPECT_EQ(clone->GetDocument(), decl->GetDocument());

    EXPECT_STREQ(clone->Value(), decl->Value());



    doc.DeleteNode(clone);

}
