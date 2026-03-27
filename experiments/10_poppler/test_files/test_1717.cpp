#include <gtest/gtest.h>

#include "StructTreeRoot.h"

#include "Object.h"



class StructTreeRootTest : public ::testing::Test {

protected:

    class MockPDFDoc : public PDFDoc {

    public:

        MOCK_METHOD(const Dict&, getCatalog, (), (const));

    };



    MockPDFDoc mockDoc;

    Dict rootDict;

    StructTreeRoot structTreeRoot;



    StructTreeRootTest() : structTreeRoot(&mockDoc, rootDict) {}

};



TEST_F(StructTreeRootTest_1717, GetRoleMap_ReturnsNullptrWhenNotADict_1717) {

    Object nonDictObj;

    nonDictObj = 42; // Set to an integer type

    structTreeRoot.roleMap = nonDictObj;



    EXPECT_EQ(structTreeRoot.getRoleMap(), nullptr);

}



TEST_F(StructTreeRootTest_1717, GetRoleMap_ReturnsDictPointerWhenADict_1717) {

    Object dictObj(new Dict());

    structTreeRoot.roleMap = dictObj;



    EXPECT_NE(structTreeRoot.getRoleMap(), nullptr);

}



TEST_F(StructTreeRootTest_1717, GetRoleMap_BoundaryCondition_EmptyDict_1717) {

    Object emptyDictObj(new Dict());

    structTreeRoot.roleMap = emptyDictObj;



    EXPECT_NE(structTreeRoot.getRoleMap(), nullptr);

}



TEST_F(StructTreeRootTest_1717, GetRoleMap_ExceptionalCase_ErrorObject_1717) {

    Object errorObj;

    errorObj = Object::error();

    structTreeRoot.roleMap = errorObj;



    EXPECT_EQ(structTreeRoot.getRoleMap(), nullptr);

}
