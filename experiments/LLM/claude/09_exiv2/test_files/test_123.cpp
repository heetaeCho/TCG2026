#include <gtest/gtest.h>
#include <sstream>
#include "exiv2/tags.hpp"

// Test that the operator<< outputs the integer representation of IfdId values
TEST(IfdIdStreamOperator_123, OutputsIntegerValue_123) {
    std::ostringstream os;
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(0);
    os << id;
    EXPECT_EQ(os.str(), "0");
}

TEST(IfdIdStreamOperator_123, OutputsNonZeroValue_123) {
    std::ostringstream os;
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(1);
    os << id;
    EXPECT_EQ(os.str(), "1");
}

TEST(IfdIdStreamOperator_123, OutputsLargerValue_123) {
    std::ostringstream os;
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(42);
    os << id;
    EXPECT_EQ(os.str(), "42");
}

TEST(IfdIdStreamOperator_123, OutputsNegativeValue_123) {
    std::ostringstream os;
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(-1);
    os << id;
    EXPECT_EQ(os.str(), "-1");
}

TEST(IfdIdStreamOperator_123, ReturnsStreamReference_123) {
    std::ostringstream os;
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(5);
    std::ostream& result = (os << id);
    EXPECT_EQ(&result, &os);
}

TEST(IfdIdStreamOperator_123, ChainingMultipleOutputs_123) {
    std::ostringstream os;
    Exiv2::IfdId id1 = static_cast<Exiv2::IfdId>(1);
    Exiv2::IfdId id2 = static_cast<Exiv2::IfdId>(2);
    os << id1 << " " << id2;
    EXPECT_EQ(os.str(), "1 2");
}

TEST(IfdIdStreamOperator_123, MaxIntValue_123) {
    std::ostringstream os;
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(std::numeric_limits<int>::max());
    os << id;
    EXPECT_EQ(os.str(), std::to_string(std::numeric_limits<int>::max()));
}

TEST(IfdIdStreamOperator_123, MinIntValue_123) {
    std::ostringstream os;
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(std::numeric_limits<int>::min());
    os << id;
    EXPECT_EQ(os.str(), std::to_string(std::numeric_limits<int>::min()));
}

TEST(IfdIdStreamOperator_123, StreamStatePreserved_123) {
    std::ostringstream os;
    os << "prefix_";
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(10);
    os << id;
    os << "_suffix";
    EXPECT_EQ(os.str(), "prefix_10_suffix");
}

TEST(IfdIdStreamOperator_123, MultipleCallsAppend_123) {
    std::ostringstream os;
    Exiv2::IfdId id = static_cast<Exiv2::IfdId>(7);
    os << id;
    os << id;
    os << id;
    EXPECT_EQ(os.str(), "777");
}
