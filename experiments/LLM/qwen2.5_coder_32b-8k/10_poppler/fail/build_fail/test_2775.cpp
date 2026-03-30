#include <gtest/gtest.h>

#include "poppler/qt5/src/poppler-page-transition.cc"

#include "poppler/Object.h"



using namespace Poppler;



// Mock Object class if necessary for testing

class MockObject : public Object {

public:

    MOCK_METHOD(ObjType, getType, (), (const));

};



TEST_F(PageTransitionDataTest_2775, ConstructorWithNullPointer_2775) {

    PageTransitionData ptd(nullptr);

    EXPECT_EQ(ptd.pt, nullptr);

}



TEST_F(PageTransitionDataTest_2775, CopyConstructor_2775) {

    MockObject mockObj;

    PageTransitionData original(&mockObj);

    PageTransitionData copy(original);

    EXPECT_NE(copy.pt, nullptr);

}



TEST_F(PageTransitionDataTest_2775, Destructor_2775) {

    MockObject mockObj;

    PageTransitionData* ptd = new PageTransitionData(&mockObj);

    delete ptd;

    // Assuming no observable side effects other than memory management

}



TEST_F(PageTransitionDataTest_2775, AssignmentOperatorDeleted_2775) {

    MockObject mockObj1, mockObj2;

    PageTransitionData ptd1(&mockObj1), ptd2(&mockObj2);

    EXPECT_FALSE((std::is_assignable<PageTransitionData&, const PageTransitionData&>::value));

}



TEST_F(PageTransitionDataTest_2775, ConstructorWithValidObject_2775) {

    MockObject mockObj;

    EXPECT_CALL(mockObj, getType()).Times(1).WillOnce(::testing::Return(objDict));

    PageTransitionData ptd(&mockObj);

    EXPECT_NE(ptd.pt, nullptr);

}



TEST_F(PageTransitionDataTest_2775, ConstructorWithInvalidObjectType_2775) {

    MockObject mockObj;

    EXPECT_CALL(mockObj, getType()).Times(1).WillOnce(::testing::Return(objNone));

    PageTransitionData ptd(&mockObj);

    EXPECT_EQ(ptd.pt, nullptr);

}
