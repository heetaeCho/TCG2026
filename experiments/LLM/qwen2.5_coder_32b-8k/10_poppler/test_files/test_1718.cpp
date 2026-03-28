#include <gtest/gtest.h>

#include "StructTreeRoot.h"

#include "Object.h"



class StructTreeRootTest_1718 : public ::testing::Test {

protected:

    struct MockPDFDoc {};

    Dict rootDict;

    std::unique_ptr<MockPDFDoc> doc;



    void SetUp() override {

        doc = std::make_unique<MockPDFDoc>();

    }

};



TEST_F(StructTreeRootTest_1718, GetClassMap_ReturnsNullPtrWhenNotDict_1718) {

    StructTreeRoot structTreeRoot(doc.get(), rootDict);

    EXPECT_EQ(nullptr, structTreeRoot.getClassMap());

}



TEST_F(StructTreeRootTest_1718, GetClassMap_ReturnsValidPtrWhenDict_1718) {

    Object dictObject(new Dict());

    rootDict.dictAdd("ClassMap", std::move(dictObject));

    StructTreeRoot structTreeRoot(doc.get(), rootDict);

    EXPECT_NE(nullptr, structTreeRoot.getClassMap());

}



TEST_F(StructTreeRootTest_1718, GetRoleMap_ReturnsNullPtrWhenNotDict_1718) {

    StructTreeRoot structTreeRoot(doc.get(), rootDict);

    EXPECT_EQ(nullptr, structTreeRoot.getRoleMap());

}



TEST_F(StructTreeRootTest_1718, GetRoleMap_ReturnsValidPtrWhenDict_1718) {

    Object dictObject(new Dict());

    rootDict.dictAdd("RoleMap", std::move(dictObject));

    StructTreeRoot structTreeRoot(doc.get(), rootDict);

    EXPECT_NE(nullptr, structTreeRoot.getRoleMap());

}



TEST_F(StructTreeRootTest_1718, GetNumChildren_ReturnsZeroWhenNoChildren_1718) {

    StructTreeRoot structTreeRoot(doc.get(), rootDict);

    EXPECT_EQ(0u, structTreeRoot.getNumChildren());

}



TEST_F(StructTreeRootTest_1718, GetChild_ReturnsNullptrWhenIndexOutOfBounds_1718) {

    StructTreeRoot structTreeRoot(doc.get(), rootDict);

    EXPECT_EQ(nullptr, structTreeRoot.getChild(0));

}
