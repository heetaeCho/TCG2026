#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.h"



using namespace tinyxml2;

using ::testing::Return;

using ::testing::_;



class XMLDeclarationTest_67 : public ::testing::Test {

protected:

    XMLDocument* doc = new XMLDocument();

    XMLDeclaration* decl = new XMLDeclaration(doc);



    virtual ~XMLDeclarationTest_67() {

        delete decl;

        delete doc;

    }

};



TEST_F(XMLDeclarationTest_67, ToDeclaration_ReturnsSelfPointer_67) {

    EXPECT_EQ(decl->ToDeclaration(), decl);

}



// Assuming ShallowClone returns a valid pointer and is not null

TEST_F(XMLDeclarationTest_67, ShallowClone_ReturnsNonNullPointer_67) {

    XMLNode* clone = decl->ShallowClone(doc);

    EXPECT_NE(clone, nullptr);

    delete clone;

}



// Assuming ShallowEqual returns true when comparing with itself

TEST_F(XMLDeclarationTest_67, ShallowEqual_ReturnsTrueWhenComparingWithSelf_67) {

    EXPECT_TRUE(decl->ShallowEqual(decl));

}



// Assuming ShallowEqual returns false when comparing with a different object

TEST_F(XMLDeclarationTest_67, ShallowEqual_ReturnsFalseWhenComparingWithDifferentObject_67) {

    XMLDocument* anotherDoc = new XMLDocument();

    XMLDeclaration* anotherDecl = new XMLDeclaration(anotherDoc);

    EXPECT_FALSE(decl->ShallowEqual(anotherDecl));

    delete anotherDecl;

    delete anotherDoc;

}



// Mocking the XMLVisitor to verify if Accept calls VisitEnter and VisitExit

class MockXMLVisitor : public XMLVisitor {

public:

    MOCK_METHOD(bool, VisitEnter, (const XMLElement &), (override));

    MOCK_METHOD(bool, VisitExit, (const XMLElement &), (override));

};



TEST_F(XMLDeclarationTest_67, Accept_CallsVisitDeclaration_67) {

    MockXMLVisitor mockVisitor;

    EXPECT_CALL(mockVisitor, VisitDeclaration(_)).WillOnce(Return(true));

    decl->Accept(&mockVisitor);

}
