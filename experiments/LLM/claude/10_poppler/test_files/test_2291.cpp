#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include poppler glib headers
extern "C" {
#include <poppler.h>
}

#include "Link.h"
#include "GooString.h"

// Since build_goto_dest is static, we need to test it through the public API
// or include the .cc file directly for testing purposes
// We include the implementation file to access the static function
#include "poppler-action.cc"

using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

class MockLinkGoTo : public LinkGoTo {
public:
    MockLinkGoTo() : LinkGoTo(nullptr) {}
    MOCK_METHOD(bool, isOk, (), (const, override));
    MOCK_METHOD(const LinkDest*, getDest, (), (const));
    MOCK_METHOD(const GooString*, getNamedDest, (), (const));
};

class BuildGotoDestTest_2291 : public ::testing::Test {
protected:
    void SetUp() override {
        memset(&action, 0, sizeof(PopplerAction));
    }

    void TearDown() override {
        if (action.goto_dest.dest) {
            poppler_dest_free(action.goto_dest.dest);
            action.goto_dest.dest = nullptr;
        }
    }

    PopplerAction action;
};

// Test: When link is not OK, dest should be created with nulls
TEST_F(BuildGotoDestTest_2291, LinkNotOk_CreatesNullDest_2291) {
    NiceMock<MockLinkGoTo> mockLink;
    ON_CALL(mockLink, isOk()).WillByDefault(Return(false));

    build_goto_dest(nullptr, &action, &mockLink);

    ASSERT_NE(action.goto_dest.dest, nullptr);
    // When link is not ok, we expect a dest created from dest_new_goto(nullptr, nullptr)
    EXPECT_EQ(action.goto_dest.dest->type, POPPLER_DEST_UNKNOWN);
}

// Test: When link is OK and has a LinkDest, uses dest_new_goto with document and dest
TEST_F(BuildGotoDestTest_2291, LinkOkWithDest_CreatesGotoDest_2291) {
    NiceMock<MockLinkGoTo> mockLink;
    LinkDest linkDest;
    ON_CALL(mockLink, isOk()).WillByDefault(Return(true));
    ON_CALL(mockLink, getDest()).WillByDefault(Return(&linkDest));
    ON_CALL(mockLink, getNamedDest()).WillByDefault(Return(nullptr));

    build_goto_dest(nullptr, &action, &mockLink);

    ASSERT_NE(action.goto_dest.dest, nullptr);
}

// Test: When link is OK with named dest, uses dest_new_named
TEST_F(BuildGotoDestTest_2291, LinkOkWithNamedDest_CreatesNamedDest_2291) {
    NiceMock<MockLinkGoTo> mockLink;
    GooString namedDest("TestDest");
    ON_CALL(mockLink, isOk()).WillByDefault(Return(true));
    ON_CALL(mockLink, getDest()).WillByDefault(Return(nullptr));
    ON_CALL(mockLink, getNamedDest()).WillByDefault(Return(&namedDest));

    build_goto_dest(nullptr, &action, &mockLink);

    ASSERT_NE(action.goto_dest.dest, nullptr);
    EXPECT_EQ(action.goto_dest.dest->type, POPPLER_DEST_NAMED);
    EXPECT_STREQ(action.goto_dest.dest->named_dest, "TestDest");
}

// Test: When link is OK but has neither dest nor named dest
TEST_F(BuildGotoDestTest_2291, LinkOkNoDests_CreatesDefaultDest_2291) {
    NiceMock<MockLinkGoTo> mockLink;
    ON_CALL(mockLink, isOk()).WillByDefault(Return(true));
    ON_CALL(mockLink, getDest()).WillByDefault(Return(nullptr));
    ON_CALL(mockLink, getNamedDest()).WillByDefault(Return(nullptr));

    build_goto_dest(nullptr, &action, &mockLink);

    ASSERT_NE(action.goto_dest.dest, nullptr);
}

// Test: When link is OK, dest takes priority over named_dest
TEST_F(BuildGotoDestTest_2291, LinkOkDestPriorityOverNamed_2291) {
    NiceMock<MockLinkGoTo> mockLink;
    LinkDest linkDest;
    GooString namedDest("ShouldNotBeUsed");
    ON_CALL(mockLink, isOk()).WillByDefault(Return(true));
    ON_CALL(mockLink, getDest()).WillByDefault(Return(&linkDest));
    ON_CALL(mockLink, getNamedDest()).WillByDefault(Return(&namedDest));

    build_goto_dest(nullptr, &action, &mockLink);

    ASSERT_NE(action.goto_dest.dest, nullptr);
    // Since dest is non-null, it should use dest_new_goto, not dest_new_named
    // So named_dest field should not be "ShouldNotBeUsed" (it's not a named dest type)
    EXPECT_NE(action.goto_dest.dest->type, POPPLER_DEST_NAMED);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
