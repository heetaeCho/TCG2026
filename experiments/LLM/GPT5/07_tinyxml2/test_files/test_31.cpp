// File: ./TestProjects/tinyxml2/test_xmlvisitor_31.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class XMLVisitorTest_31 : public ::testing::Test {
protected:
    tinyxml2::XMLDocument doc_;
};

class RecordingVisitor_31 : public tinyxml2::XMLVisitor {
public:
    bool called = false;
    const tinyxml2::XMLText* lastText = nullptr;
    bool returnValue = true;

    bool Visit(const tinyxml2::XMLText& text) override {
        called = true;
        lastText = &text;
        return returnValue;
    }
};

}  // namespace

TEST_F(XMLVisitorTest_31, DefaultVisitReturnsTrue_31) {
    tinyxml2::XMLText* text = doc_.NewText("hello");
    ASSERT_NE(text, nullptr);

    tinyxml2::XMLVisitor visitor;
    EXPECT_TRUE(visitor.Visit(*text));
}

TEST_F(XMLVisitorTest_31, DefaultVisitReturnsTrueForEmptyText_31) {
    tinyxml2::XMLText* text = doc_.NewText("");
    ASSERT_NE(text, nullptr);

    tinyxml2::XMLVisitor visitor;
    EXPECT_TRUE(visitor.Visit(*text));
}

TEST_F(XMLVisitorTest_31, OverriddenVisitIsInvokedAndCanReturnFalse_31) {
    tinyxml2::XMLText* text = doc_.NewText("payload");
    ASSERT_NE(text, nullptr);

    RecordingVisitor_31 visitor;
    visitor.returnValue = false;

    EXPECT_FALSE(visitor.Visit(*text));
    EXPECT_TRUE(visitor.called);
    EXPECT_EQ(visitor.lastText, text);
}

TEST_F(XMLVisitorTest_31, VirtualDispatchWorksThroughBasePointer_31) {
    tinyxml2::XMLText* text = doc_.NewText("dispatch");
    ASSERT_NE(text, nullptr);

    RecordingVisitor_31 derived;
    derived.returnValue = true;

    tinyxml2::XMLVisitor* basePtr = &derived;
    EXPECT_TRUE(basePtr->Visit(*text));

    EXPECT_TRUE(derived.called);
    EXPECT_EQ(derived.lastText, text);
}

TEST_F(XMLVisitorTest_31, OverriddenVisitCanReturnTrue_31) {
    tinyxml2::XMLText* text = doc_.NewText("ok");
    ASSERT_NE(text, nullptr);

    RecordingVisitor_31 visitor;
    visitor.returnValue = true;

    EXPECT_TRUE(visitor.Visit(*text));
    EXPECT_TRUE(visitor.called);
    EXPECT_EQ(visitor.lastText, text);
}

TEST_F(XMLVisitorTest_31, VisitAcceptsLargeTextPayload_31) {
    std::string large(100000, 'x');
    tinyxml2::XMLText* text = doc_.NewText(large.c_str());
    ASSERT_NE(text, nullptr);

    tinyxml2::XMLVisitor visitor;
    EXPECT_TRUE(visitor.Visit(*text));
}
