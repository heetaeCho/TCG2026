#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-optcontent-private.h"

#include "OptionalContent.h"



using namespace Poppler;

using ::testing::_;

using ::testing::NiceMock;



class MockOCGs : public OCGs {

public:

    MOCK_CONST_METHOD0(getOCGs, const std::unordered_map<Ref, std::unique_ptr<OptionalContentGroup>> &());

    MOCK_CONST_METHOD0(getOrderArray, const Array *());

    MOCK_CONST_METHOD0(getRBGroupsArray, const Array *());

};



class OptContentModelPrivateTest : public ::testing::Test {

protected:

    NiceMock<MockOCGs> mockOCGs;

    std::unique_ptr<OptContentModelPrivate> optContentModelPrivate;



    void SetUp() override {

        optContentModelPrivate = std::make_unique<OptContentModelPrivate>(nullptr, &mockOCGs);

    }

};



TEST_F(OptContentModelPrivateTest, ConstructWithEmptyOCGs_2769) {

    std::unordered_map<Ref, std::unique_ptr<OptionalContentGroup>> emptyOCGs;

    EXPECT_CALL(mockOCGs, getOCGs()).WillOnce(::testing::ReturnRef(emptyOCGs));

    EXPECT_CALL(mockOCGs, getOrderArray()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mockOCGs, getRBGroupsArray()).WillOnce(::testing::Return(nullptr));



    ASSERT_NE(optContentModelPrivate->m_rootNode, nullptr);

    EXPECT_EQ(optContentModelPrivate->m_optContentItems.size(), 0);

}



TEST_F(OptContentModelPrivateTest, ConstructWithNonEmptyOCGs_2769) {

    std::unordered_map<Ref, std::unique_ptr<OptionalContentGroup>> oCGs;

    Ref ref1{1, 0};

    Ref ref2{2, 0};

    oCGs[ref1] = std::make_unique<OptionalContentGroup>();

    oCGs[ref2] = std::make_unique<OptionalContentGroup>();



    EXPECT_CALL(mockOCGs, getOCGs()).WillOnce(::testing::ReturnRef(oCGs));

    EXPECT_CALL(mockOCGs, getOrderArray()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mockOCGs, getRBGroupsArray()).WillOnce(::testing::Return(nullptr));



    ASSERT_NE(optContentModelPrivate->m_rootNode, nullptr);

    EXPECT_EQ(optContentModelPrivate->m_optContentItems.size(), 2);

}



TEST_F(OptContentModelPrivateTest, ConstructWithOrderArray_2769) {

    std::unordered_map<Ref, std::unique_ptr<OptionalContentGroup>> oCGs;

    Ref ref1{1, 0};

    Ref ref2{2, 0};

    oCGs[ref1] = std::make_unique<OptionalContentGroup>();

    oCGs[ref2] = std::make_unique<OptionalContentGroup>();



    Array* mockOrderArray = new Array();

    EXPECT_CALL(mockOCGs, getOCGs()).WillOnce(::testing::ReturnRef(oCGs));

    EXPECT_CALL(mockOCGs, getOrderArray()).WillOnce(::testing::Return(mockOrderArray));

    EXPECT_CALL(mockOCGs, getRBGroupsArray()).WillOnce(::testing::Return(nullptr));



    ASSERT_NE(optContentModelPrivate->m_rootNode, nullptr);

    EXPECT_EQ(optContentModelPrivate->m_optContentItems.size(), 2);



    delete mockOrderArray;

}



TEST_F(OptContentModelPrivateTest, ConstructWithRBGroupsArray_2769) {

    std::unordered_map<Ref, std::unique_ptr<OptionalContentGroup>> oCGs;

    Ref ref1{1, 0};

    Ref ref2{2, 0};

    oCGs[ref1] = std::make_unique<OptionalContentGroup>();

    oCGs[ref2] = std::make_unique<OptionalContentGroup>();



    Array* mockRBGroupsArray = new Array();

    EXPECT_CALL(mockOCGs, getOCGs()).WillOnce(::testing::ReturnRef(oCGs));

    EXPECT_CALL(mockOCGs, getOrderArray()).WillOnce(::testing::Return(nullptr));

    EXPECT_CALL(mockOCGs, getRBGroupsArray()).WillOnce(::testing::Return(mockRBGroupsArray));



    ASSERT_NE(optContentModelPrivate->m_rootNode, nullptr);

    EXPECT_EQ(optContentModelPrivate->m_optContentItems.size(), 2);



    delete mockRBGroupsArray;

}
