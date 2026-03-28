#include <gtest/gtest.h>

// Include the real library header under test.
#include "tinyxml2.h"

namespace {

using tinyxml2::XMLVisitor;

// A simple derived visitor to access the base implementation and to test override dispatch.
class TestVisitor_29 : public XMLVisitor {
public:
    bool CallBaseVisitExit_29(const tinyxml2::XMLElement& element) {
        return XMLVisitor::VisitExit(element);
    }

    bool VisitExit(const tinyxml2::XMLElement& element) override {
        last_seen_29 = &element;
        ++call_count_29;
        return return_value_29;
    }

    const tinyxml2::XMLElement* last_seen_29 = nullptr;
    int call_count_29 = 0;
    bool return_value_29 = true;
};

class XMLVisitorTest_29 : public ::testing::Test {};

}  // namespace

TEST_F(XMLVisitorTest_29, DefaultVisitExitReturnsTrue_29) {
    // Black-box observable behavior: default implementation returns true.
    // The parameter is unused in the default implementation, so we can pass any valid reference.
    XMLVisitor v;

    // We don't have a public way to construct a real XMLElement without other tinyxml2 types.
    // However, VisitExit takes a const reference and the default impl ignores it; so we only
    // need a reference that is not dereferenced by the function.
    const tinyxml2::XMLElement* dummy = reinterpret_cast<const tinyxml2::XMLElement*>(0x1);
    ASSERT_NE(dummy, nullptr);

    EXPECT_TRUE(v.VisitExit(*dummy));
}

TEST_F(XMLVisitorTest_29, DefaultVisitExitIsConstRefFriendly_29) {
    // Boundary-ish: ensure it accepts a const reference and still returns true.
    XMLVisitor v;

    const tinyxml2::XMLElement* dummy = reinterpret_cast<const tinyxml2::XMLElement*>(0x1);
    ASSERT_NE(dummy, nullptr);

    const tinyxml2::XMLElement& ref = *dummy;
    EXPECT_TRUE(v.VisitExit(ref));
}

TEST_F(XMLVisitorTest_29, OverrideIsDispatchedViaBasePointer_29) {
    // Verify external interaction: virtual dispatch calls the override and passes the same reference.
    TestVisitor_29 derived;
    XMLVisitor* base = &derived;

    const tinyxml2::XMLElement* dummy = reinterpret_cast<const tinyxml2::XMLElement*>(0x1);
    ASSERT_NE(dummy, nullptr);

    derived.return_value_29 = false;
    EXPECT_FALSE(base->VisitExit(*dummy));
    EXPECT_EQ(derived.call_count_29, 1);
    EXPECT_EQ(derived.last_seen_29, dummy);
}

TEST_F(XMLVisitorTest_29, OverrideReturnValuePropagates_29) {
    TestVisitor_29 derived;
    XMLVisitor& base_ref = derived;

    const tinyxml2::XMLElement* dummy = reinterpret_cast<const tinyxml2::XMLElement*>(0x1);
    ASSERT_NE(dummy, nullptr);

    derived.return_value_29 = true;
    EXPECT_TRUE(base_ref.VisitExit(*dummy));

    derived.return_value_29 = false;
    EXPECT_FALSE(base_ref.VisitExit(*dummy));

    EXPECT_EQ(derived.call_count_29, 2);
}

TEST_F(XMLVisitorTest_29, DerivedCanCallBaseImplementation_29) {
    // Ensure the base implementation remains callable and returns true.
    TestVisitor_29 derived;

    const tinyxml2::XMLElement* dummy = reinterpret_cast<const tinyxml2::XMLElement*>(0x1);
    ASSERT_NE(dummy, nullptr);

    EXPECT_TRUE(derived.CallBaseVisitExit_29(*dummy));
}

TEST_F(XMLVisitorTest_29, BaseAndOverrideBehaviorsAreIndependent_29) {
    // Base impl always true; override may differ. This checks both paths are observable.
    TestVisitor_29 derived;
    XMLVisitor* base_ptr = &derived;

    const tinyxml2::XMLElement* dummy = reinterpret_cast<const tinyxml2::XMLElement*>(0x1);
    ASSERT_NE(dummy, nullptr);

    derived.return_value_29 = false;
    EXPECT_FALSE(base_ptr->VisitExit(*dummy));                // override
    EXPECT_TRUE(derived.CallBaseVisitExit_29(*dummy));        // base

    EXPECT_EQ(derived.call_count_29, 1);
    EXPECT_EQ(derived.last_seen_29, dummy);
}
