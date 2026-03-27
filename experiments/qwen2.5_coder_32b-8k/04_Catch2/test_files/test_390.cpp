#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;

using namespace Catch::Clara::Detail;



class MockBoundRef : public BoundRef {

public:

    MOCK_CONST_METHOD0(isContainer, bool());

};



class ParserRefImplTest_390 : public ::testing::Test {

protected:

    std::shared_ptr<MockBoundRef> mock_bound_ref_;

    ParserRefImpl<ParserRefImpl<MockBoundRef>> parser_ref_impl_;



    ParserRefImplTest_390() 

        : mock_bound_ref_(std::make_shared<MockBoundRef>()),

          parser_ref_impl_(mock_bound_ref_) {}

};



TEST_F(ParserRefImplTest_390, Cardinality_ReturnsZeroForContainer_390) {

    EXPECT_CALL(*mock_bound_ref_, isContainer()).WillOnce(::testing::Return(true));

    EXPECT_EQ(parser_ref_impl_.cardinality(), 0);

}



TEST_F(ParserRefImplTest_390, Cardinality_ReturnsOneForNonContainer_390) {

    EXPECT_CALL(*mock_bound_ref_, isContainer()).WillOnce(::testing::Return(false));

    EXPECT_EQ(parser_ref_impl_.cardinality(), 1);

}
