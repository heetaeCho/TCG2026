#include <gtest/gtest.h>
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// A dummy derived class to test ParserRefImpl, since required() returns DerivedT&
class DummyParser : public ParserRefImpl<DummyParser> {
public:
    using ParserRefImpl::ParserRefImpl; // inherit constructors
    DummyParser(std::shared_ptr<BoundRef> const& ref) : ParserRefImpl(ref) {}
};

class ParserRefImplTest_388 : public ::testing::Test {
protected:
    std::shared_ptr<BoundRef> dummyRef = nullptr; // not used directly, but required for construction
    DummyParser parser{dummyRef};
};

// Normal operation: required() returns a reference to DerivedT
TEST_F(ParserRefImplTest_388, RequiredReturnsSelfReference_388) {
    auto& result = parser.required();
    EXPECT_EQ(&result, &parser);
}

// Boundary check: multiple calls to required() still return same object
TEST_F(ParserRefImplTest_388, MultipleRequiredCallsReturnSameObject_388) {
    auto& result1 = parser.required();
    auto& result2 = parser.required();
    EXPECT_EQ(&result1, &parser);
    EXPECT_EQ(&result2, &parser);
    EXPECT_EQ(&result1, &result2);
}

// Type correctness: return type of required() is DummyParser&
TEST_F(ParserRefImplTest_388, RequiredReturnsCorrectType_388) {
    auto& result = parser.required();
    bool isDummyParser = std::is_same<decltype(result), DummyParser&>::value;
    EXPECT_TRUE(isDummyParser);
}
