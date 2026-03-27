#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_console_colour.hpp"



using namespace Catch;

using ::testing::_;

using ::testing::Return;

using ::testing::Ref;



class MockOstream : public std::ostream {

public:

    using std::ostream::ostream;

    MOCK_METHOD(std::ostream&, operator<<, (int), (override));

};



TEST_F(ColourGuardTest_425, EngageCallsEngageImpl_425) {

    MockOstream mockStream;

    ColourImpl::Code code = static_cast<ColourImpl::Code>(1);

    const ColourImpl* colourImpl = nullptr;



    auto guard = new ColourImpl::ColourGuard(code, colourImpl);



    EXPECT_CALL(*static_cast<MockOstream*>(&mockStream), operator<<(_))

        .WillOnce(Return(std::ref(mockStream)));



    mockStream << *guard;

}



TEST_F(ColourGuardTest_425, EngageReturnsReferenceToSelf_425) {

    MockOstream mockStream;

    ColourImpl::Code code = static_cast<ColourImpl::Code>(1);

    const ColourImpl* colourImpl = nullptr;



    auto guard = new ColourImpl::ColourGuard(code, colourImpl);



    EXPECT_CALL(*static_cast<MockOstream*>(&mockStream), operator<<(_))

        .WillOnce(Return(std::ref(mockStream)));



    ColourImpl::ColourGuard& result = mockStream << *guard;

    EXPECT_EQ(&result, guard);

}



TEST_F(ColourGuardTest_425, MoveConstructorWorks_425) {

    MockOstream mockStream;

    ColourImpl::Code code = static_cast<ColourImpl::Code>(1);

    const ColourImpl* colourImpl = nullptr;



    auto originalGuard = new ColourImpl::ColourGuard(code, colourImpl);

    ColourImpl::ColourGuard movedGuard(std::move(*originalGuard));



    EXPECT_CALL(*static_cast<MockOstream*>(&mockStream), operator<<(_))

        .WillOnce(Return(std::ref(mockStream)));



    mockStream << movedGuard;

}



TEST_F(ColourGuardTest_425, MoveAssignmentWorks_425) {

    MockOstream mockStream;

    ColourImpl::Code code = static_cast<ColourImpl::Code>(1);

    const ColourImpl* colourImpl = nullptr;



    auto originalGuard = new ColourImpl::ColourGuard(code, colourImpl);

    auto guardToAssign = new ColourImpl::ColourGuard(static_cast<ColourImpl::Code>(2), colourImpl);



    *guardToAssign = std::move(*originalGuard);



    EXPECT_CALL(*static_cast<MockOstream*>(&mockStream), operator<<(_))

        .WillOnce(Return(std::ref(mockStream)));



    mockStream << *guardToAssign;

}



TEST_F(ColourGuardTest_425, CopyConstructorDeleted_425) {

    ColourImpl::Code code = static_cast<ColourImpl::Code>(1);

    const ColourImpl* colourImpl = nullptr;



    auto guard = new ColourImpl::ColourGuard(code, colourImpl);



    EXPECT_DELETED_FUNCTION(ColourImpl::ColourGuard copy(guard));

}



TEST_F(ColourGuardTest_425, CopyAssignmentDeleted_425) {

    MockOstream mockStream;

    ColourImpl::Code code = static_cast<ColourImpl::Code>(1);

    const ColourImpl* colourImpl = nullptr;



    auto guard = new ColourImpl::ColourGuard(code, colourImpl);



    EXPECT_DELETED_FUNCTION(guard->operator=(guard));

}
