#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Assuming Catalog and NameTree are defined in the appropriate headers.

class MockNameTree : public NameTree {

public:

    MOCK_METHOD(int, numEntries, (), (override));

};



class CatalogTest_675 : public ::testing::Test {

protected:

    MockNameTree mockJSNameTree;

    Catalog catalog{nullptr}; // Assuming PDFDoc* can be nullptr for testing purposes.



    void SetUp() override {

        // Use the address of mockJSNameTree to simulate getJSNameTree returning it.

        auto getJSNameTreeMock = [&]() -> NameTree* { return &mockJSNameTree; };

        catalog.getJSNameTree = getJSNameTreeMock;

    }

};



TEST_F(CatalogTest_675, NumJSShouldReturnZeroWhenNoEntries_675) {

    EXPECT_CALL(mockJSNameTree, numEntries()).WillOnce(::testing::Return(0));

    EXPECT_EQ(catalog.numJS(), 0);

}



TEST_F(CatalogTest_675, NumJSShouldReturnCorrectCountWhenEntriesExist_675) {

    EXPECT_CALL(mockJSNameTree, numEntries()).WillOnce(::testing::Return(5));

    EXPECT_EQ(catalog.numJS(), 5);

}



TEST_F(CatalogTest_675, NumJSCalledExactlyOnce_675) {

    ::testing::Expectation exp = EXPECT_CALL(mockJSNameTree, numEntries()).Times(1).WillOnce(::testing::Return(3));

    catalog.numJS();

    ::testing::Mock::VerifyAndClearExpectations(&mockJSNameTree);

}
