#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Catalog.h"

#include "NameTree.h"



using namespace testing;



class MockNameTree : public NameTree {

public:

    MOCK_METHOD(int, numEntries, (), (override));

    MOCK_METHOD(const GooString*, getName, (int), (const, override));

};



class CatalogTest_673 : public Test {

protected:

    MockNameTree mockDestNameTree;

    Catalog catalog{nullptr};



    void SetUp() override {

        ON_CALL(mockDestNameTree, numEntries()).WillByDefault(Return(2));

        EXPECT_CALL(catalog, getDestNameTree())

            .WillRepeatedly(Return(&mockDestNameTree));

    }

};



TEST_F(CatalogTest_673, GetDestNameTreeName_ReturnsCorrectName_NormalOperation_673) {

    const char* expectedName1 = "Destination1";

    const char* expectedName2 = "Destination2";



    EXPECT_CALL(mockDestNameTree, getName(0))

        .WillOnce(Return(new GooString(expectedName1)));

    EXPECT_CALL(mockDestNameTree, getName(1))

        .WillOnce(Return(new GooString(expectedName2)));



    EXPECT_STREQ(catalog.getDestNameTreeName(0)->c_str(), expectedName1);

    EXPECT_STREQ(catalog.getDestNameTreeName(1)->c_str(), expectedName2);

}



TEST_F(CatalogTest_673, GetDestNameTreeName_ReturnsNullForInvalidIndex_BoundaryCondition_673) {

    EXPECT_CALL(mockDestNameTree, getName(2))

        .WillOnce(Return(static_cast<const GooString*>(nullptr)));



    EXPECT_EQ(catalog.getDestNameTreeName(2), nullptr);

}



TEST_F(CatalogTest_673, GetDestNameTreeName_CallsGetNameWithCorrectIndex_VerificationOfExternalInteractions_673) {

    EXPECT_CALL(mockDestNameTree, getName(0)).WillOnce(Return(new GooString("Destination1")));



    catalog.getDestNameTreeName(0);

}



TEST_F(CatalogTest_673, GetDestNameTreeName_ReturnsNullWhenNoEntries_BoundaryCondition_673) {

    ON_CALL(mockDestNameTree, numEntries()).WillByDefault(Return(0));



    EXPECT_EQ(catalog.getDestNameTreeName(0), nullptr);

}
