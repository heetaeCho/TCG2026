#include <gtest/gtest.h>
#include "exiv2/bmffimage.hpp"

class IlocTest_1191 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test default constructor creates Iloc with all zeros
TEST_F(IlocTest_1191, DefaultConstructor_1191) {
    Exiv2::Iloc iloc;
    EXPECT_EQ(iloc.ID_, 0u);
    EXPECT_EQ(iloc.start_, 0u);
    EXPECT_EQ(iloc.length_, 0u);
}

// Test parameterized constructor with specific values
TEST_F(IlocTest_1191, ParameterizedConstructor_1191) {
    Exiv2::Iloc iloc(42, 100, 200);
    EXPECT_EQ(iloc.ID_, 42u);
    EXPECT_EQ(iloc.start_, 100u);
    EXPECT_EQ(iloc.length_, 200u);
}

// Test toString with default values (all zeros)
TEST_F(IlocTest_1191, ToStringDefaultValues_1191) {
    Exiv2::Iloc iloc;
    std::string result = iloc.toString();
    // Should contain ID = 0, from,length = 0,0
    EXPECT_NE(result.find("ID = 0"), std::string::npos);
    EXPECT_NE(result.find("0,0"), std::string::npos);
}

// Test toString with specific values
TEST_F(IlocTest_1191, ToStringWithValues_1191) {
    Exiv2::Iloc iloc(5, 10, 20);
    std::string result = iloc.toString();
    EXPECT_NE(result.find("ID = 5"), std::string::npos);
    EXPECT_NE(result.find("from,length = 10,20"), std::string::npos);
}

// Test toString with large values
TEST_F(IlocTest_1191, ToStringWithLargeValues_1191) {
    Exiv2::Iloc iloc(4294967295u, 4294967295u, 4294967295u);
    std::string result = iloc.toString();
    EXPECT_NE(result.find("ID = 4294967295"), std::string::npos);
    EXPECT_NE(result.find("from,length = 4294967295,4294967295"), std::string::npos);
}

// Test toString with only ID set
TEST_F(IlocTest_1191, ToStringOnlyID_1191) {
    Exiv2::Iloc iloc(99, 0, 0);
    std::string result = iloc.toString();
    EXPECT_NE(result.find("ID = 99"), std::string::npos);
    EXPECT_NE(result.find("from,length = 0,0"), std::string::npos);
}

// Test toString with only start set
TEST_F(IlocTest_1191, ToStringOnlyStart_1191) {
    Exiv2::Iloc iloc(0, 500, 0);
    std::string result = iloc.toString();
    EXPECT_NE(result.find("ID = 0"), std::string::npos);
    EXPECT_NE(result.find("from,length = 500,0"), std::string::npos);
}

// Test toString with only length set
TEST_F(IlocTest_1191, ToStringOnlyLength_1191) {
    Exiv2::Iloc iloc(0, 0, 1024);
    std::string result = iloc.toString();
    EXPECT_NE(result.find("ID = 0"), std::string::npos);
    EXPECT_NE(result.find("from,length = 0,1024"), std::string::npos);
}

// Test constructor with partial arguments (only ID)
TEST_F(IlocTest_1191, ConstructorWithOnlyID_1191) {
    Exiv2::Iloc iloc(7);
    EXPECT_EQ(iloc.ID_, 7u);
    EXPECT_EQ(iloc.start_, 0u);
    EXPECT_EQ(iloc.length_, 0u);
}

// Test constructor with two arguments (ID and start)
TEST_F(IlocTest_1191, ConstructorWithIDAndStart_1191) {
    Exiv2::Iloc iloc(7, 15);
    EXPECT_EQ(iloc.ID_, 7u);
    EXPECT_EQ(iloc.start_, 15u);
    EXPECT_EQ(iloc.length_, 0u);
}

// Test toString returns non-empty string
TEST_F(IlocTest_1191, ToStringReturnsNonEmpty_1191) {
    Exiv2::Iloc iloc(1, 2, 3);
    std::string result = iloc.toString();
    EXPECT_FALSE(result.empty());
}

// Test that toString format includes expected structure
TEST_F(IlocTest_1191, ToStringFormatStructure_1191) {
    Exiv2::Iloc iloc(1, 2, 3);
    std::string result = iloc.toString();
    EXPECT_EQ(result, "ID = 1 from,length = 2,3");
}

// Test member accessibility and modification
TEST_F(IlocTest_1191, MemberModification_1191) {
    Exiv2::Iloc iloc;
    iloc.ID_ = 10;
    iloc.start_ = 20;
    iloc.length_ = 30;
    std::string result = iloc.toString();
    EXPECT_NE(result.find("ID = 10"), std::string::npos);
    EXPECT_NE(result.find("from,length = 20,30"), std::string::npos);
}

// Test boundary value: 1
TEST_F(IlocTest_1191, BoundaryValueOne_1191) {
    Exiv2::Iloc iloc(1, 1, 1);
    std::string result = iloc.toString();
    EXPECT_NE(result.find("ID = 1"), std::string::npos);
    EXPECT_NE(result.find("from,length = 1,1"), std::string::npos);
}
