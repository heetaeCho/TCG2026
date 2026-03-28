// TEST_ID: 200
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tinyxml2.h"

using ::testing::_;
using ::testing::Return;

namespace tinyxml2 {

// Expose protected XMLComment ctor for testing Accept() behavior in isolation.
class TestableXMLComment_200 final : public XMLComment {
public:
	explicit TestableXMLComment_200(XMLDocument* doc) : XMLComment(doc) {}
	~TestableXMLComment_200() override = default;
};

class MockXMLVisitor_200 : public XMLVisitor {
public:
	MOCK_METHOD(bool, Visit, (const XMLComment& comment), (override));
};

class XMLCommentAcceptTest_200 : public ::testing::Test {
protected:
	XMLDocument doc_;
	TestableXMLComment_200 comment_{&doc_};
};

TEST_F(XMLCommentAcceptTest_200, ReturnsTrueWhenVisitorReturnsTrue_200) {
	MockXMLVisitor_200 visitor;

	EXPECT_CALL(visitor, Visit(_)).WillOnce(Return(true));

	const bool result = comment_.Accept(&visitor);
	EXPECT_TRUE(result);
}

TEST_F(XMLCommentAcceptTest_200, ReturnsFalseWhenVisitorReturnsFalse_200) {
	MockXMLVisitor_200 visitor;

	EXPECT_CALL(visitor, Visit(_)).WillOnce(Return(false));

	const bool result = comment_.Accept(&visitor);
	EXPECT_FALSE(result);
}

TEST_F(XMLCommentAcceptTest_200, CallsVisitExactlyOnceWithSameObject_200) {
	MockXMLVisitor_200 visitor;

	EXPECT_CALL(visitor, Visit(::testing::Truly([this](const XMLComment& c) {
		return &c == &comment_;
	}))).WillOnce(Return(true));

	EXPECT_TRUE(comment_.Accept(&visitor));
}

#if !defined(NDEBUG) && GTEST_HAS_DEATH_TEST
TEST_F(XMLCommentAcceptTest_200, DeathOnNullVisitorInDebugBuild_200) {
	// Accept() asserts that visitor is non-null (via TIXMLASSERT / assert).
	EXPECT_DEATH({ (void)comment_.Accept(nullptr); }, "");
}
#endif

}  // namespace tinyxml2
