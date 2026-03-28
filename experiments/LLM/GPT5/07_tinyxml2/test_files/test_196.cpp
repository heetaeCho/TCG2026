// File: ./TestProjects/tinyxml2/tests/XMLTextAcceptTest_196.cpp

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "tinyxml2.h"

using ::testing::Ref;
using ::testing::Return;
using ::testing::StrictMock;

namespace tinyxml2 {

class MockXMLVisitor_196 : public XMLVisitor {
public:
    MOCK_METHOD(bool, Visit, (const XMLText& text), (override));
};

class XMLTextAcceptTest_196 : public ::testing::Test {
protected:
    XMLDocument doc_;
};

TEST_F(XMLTextAcceptTest_196, Accept_ForwardsToVisitorVisitAndReturnsTrue_196) {
    XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    StrictMock<MockXMLVisitor_196> visitor;
    EXPECT_CALL(visitor, Visit(Ref(*text))).WillOnce(Return(true));

    EXPECT_TRUE(text->Accept(&visitor));
}

TEST_F(XMLTextAcceptTest_196, Accept_ForwardsToVisitorVisitAndReturnsFalse_196) {
    XMLText* text = doc_.NewText("world");
    ASSERT_NE(text, nullptr);

    StrictMock<MockXMLVisitor_196> visitor;
    EXPECT_CALL(visitor, Visit(Ref(*text))).WillOnce(Return(false));

    EXPECT_FALSE(text->Accept(&visitor));
}

TEST_F(XMLTextAcceptTest_196, Accept_CanBeCalledMultipleTimes_196) {
    XMLText* text = doc_.NewText("repeat");
    ASSERT_NE(text, nullptr);

    StrictMock<MockXMLVisitor_196> visitor;
    EXPECT_CALL(visitor, Visit(Ref(*text)))
        .WillOnce(Return(true))
        .WillOnce(Return(false))
        .WillOnce(Return(true));

    EXPECT_TRUE(text->Accept(&visitor));
    EXPECT_FALSE(text->Accept(&visitor));
    EXPECT_TRUE(text->Accept(&visitor));
}

#if !defined(NDEBUG)
// In debug builds, TIXMLASSERT(visitor) should fire for nullptr.
TEST_F(XMLTextAcceptTest_196, Accept_DeathOnNullVisitor_DebugOnly_196) {
    XMLText* text = doc_.NewText("x");
    ASSERT_NE(text, nullptr);

    EXPECT_DEATH(
        {
            (void)text->Accept(nullptr);
        },
        ".*");
}
#endif

}  // namespace tinyxml2
