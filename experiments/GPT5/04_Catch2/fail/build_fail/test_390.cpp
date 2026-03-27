// File: parserrefimpl_cardinality_test_390.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the production header that contains BoundRef and ParserRefImpl
#include "catch2/internal/catch_clara.hpp"

using ::testing::AtLeast;
using ::testing::Return;
using ::testing::StrictMock;

namespace Catch { namespace Clara { namespace Detail {

// Mock for the external collaborator BoundRef.
class MockBoundRef : public BoundRef {
public:
    ~MockBoundRef() override = default;
    MOCK_METHOD(bool, isContainer, (), (const, override));
    MOCK_METHOD(bool, isFlag, (), (const, override));
};

// Minimal derived type so we can inject a custom BoundRef into ParserRefImpl.
class TestableParserRef_390 : public ParserRefImpl<TestableParserRef_390> {
public:
    explicit TestableParserRef_390(std::shared_ptr<BoundRef> ref)
        : ParserRefImpl<TestableParserRef_390>(ref) {}

    // Expose cardinality() for testing (already public, this is just explicit).
    using ParserRefImpl<TestableParserRef_390>::cardinality;
};

}}} // namespace Catch::Clara::Detail

// --- Tests ---

// Verifies: When the underlying BoundRef reports it is a container,
// ParserRefImpl::cardinality() returns 0 and does not call unrelated APIs.
TEST(ParserRefImplCardinalityTest_390, ReturnsZeroWhenRefIsContainer_390) {
    using namespace Catch::Clara::Detail;

    auto mockRef = std::make_shared<StrictMock<MockBoundRef>>();

    // cardinality() should consult isContainer() (possibly multiple times).
    EXPECT_CALL(*mockRef, isContainer()).Times(AtLeast(1)).WillRepeatedly(Return(true));
    // Ensure no accidental dependency on isFlag().
    EXPECT_CALL(*mockRef, isFlag()).Times(0);

    TestableParserRef_390 parser(mockRef);

    EXPECT_EQ(static_cast<size_t>(0), parser.cardinality());
    // Optional: consistency across repeated calls (still observable behavior).
    EXPECT_EQ(static_cast<size_t>(0), parser.cardinality());
}

// Verifies: When the underlying BoundRef is not a container,
// ParserRefImpl::cardinality() returns 1.
TEST(ParserRefImplCardinalityTest_390, ReturnsOneWhenRefIsNotContainer_390) {
    using namespace Catch::Clara::Detail;

    auto mockRef = std::make_shared<StrictMock<MockBoundRef>>();

    EXPECT_CALL(*mockRef, isContainer()).Times(AtLeast(1)).WillRepeatedly(Return(false));
    EXPECT_CALL(*mockRef, isFlag()).Times(0);

    TestableParserRef_390 parser(mockRef);

    EXPECT_EQ(static_cast<size_t>(1), parser.cardinality());
    EXPECT_EQ(static_cast<size_t>(1), parser.cardinality());
}
