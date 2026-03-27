#include <gtest/gtest.h>

#include "poppler/StructTreeRoot.h"

#include "gmock/gmock.h"



using namespace testing;



class MockPDFDoc {

public:

    MOCK_METHOD(Dict*, getCatalog, (), (const));

};



class StructTreeRootTest_1720 : public ::testing::Test {

protected:

    StrictMock<MockPDFDoc> mockPdfDoc;

    Dict rootDict;

    StructTreeRoot* structTreeRoot;



    void SetUp() override {

        structTreeRoot = new StructTreeRoot(&mockPdfDoc, rootDict);

    }



    void TearDown() override {

        delete structTreeRoot;

    }

};



TEST_F(StructTreeRootTest_1720, FindParentElement_NormalOperation_1720) {

    int key = 42;

    unsigned mcid = 0;

    StructElement* expectedElement = new StructElement();

    Parent parent = {Ref::INVALID(), expectedElement};

    structTreeRoot->parentTree[key].push_back(parent);



    const StructElement* result = structTreeRoot->findParentElement(key, mcid);

    EXPECT_EQ(result, expectedElement);



    delete expectedElement;

}



TEST_F(StructTreeRootTest_1720, FindParentElement_KeyNotFound_1720) {

    int key = 999;

    unsigned mcid = 0;



    const StructElement* result = structTreeRoot->findParentElement(key, mcid);

    EXPECT_EQ(result, nullptr);

}



TEST_F(StructTreeRootTest_1720, FindParentElement_McidOutOfRange_1720) {

    int key = 42;

    unsigned mcid = 1; // Assuming there's only one element in the vector for this test

    StructElement* expectedElement = new StructElement();

    Parent parent = {Ref::INVALID(), expectedElement};

    structTreeRoot->parentTree[key].push_back(parent);



    const StructElement* result = structTreeRoot->findParentElement(key, mcid);

    EXPECT_EQ(result, nullptr);



    delete expectedElement;

}



TEST_F(StructTreeRootTest_1720, FindParentElement_McidBoundaryCondition_1720) {

    int key = 42;

    unsigned mcid = 0; // Boundary condition for the first element

    StructElement* expectedElement = new StructElement();

    Parent parent = {Ref::INVALID(), expectedElement};

    structTreeRoot->parentTree[key].push_back(parent);



    const StructElement* result = structTreeRoot->findParentElement(key, mcid);

    EXPECT_EQ(result, expectedElement);



    delete expectedElement;

}
