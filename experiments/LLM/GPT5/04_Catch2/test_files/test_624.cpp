// TextFlow_Columns_PlusRvalue_624_test.cpp
#include <gtest/gtest.h>
#include <sstream>

#include "catch2/internal/catch_textflow.hpp"

using namespace Catch::TextFlow;

namespace {
    // Helper: stream any printable object to std::string via operator<<
    template <typename T>
    std::string ToStringViaStream(const T& t) {
        std::ostringstream oss;
        oss << t;
        return oss.str();
    }
}

// 1) Normal operation: rvalue + rvalue yields same printed result as building via += in order.
TEST(TextFlowColumnsPlusRvalue_624, PlusRvalue_ProducesSameAsAccumulate_624) {
    Column a{"Alpha"};
    Column b{"Beta"};

    // Path under test: rvalue + rvalue
    Columns viaPlus = std::move(a) + std::move(b);

    // Oracle via only public interface (+=)
    Columns viaAccumulate;
    viaAccumulate += Column{"Alpha"};
    viaAccumulate += Column{"Beta"};

    EXPECT_EQ(ToStringViaStream(viaPlus), ToStringViaStream(viaAccumulate));
}

// 2) Order is preserved: A + B should not match result of B then A (built through +=).
TEST(TextFlowColumnsPlusRvalue_624, PlusRvalue_PreservesOrder_624) {
    Column a{"Left"};
    Column b{"Right"};

    Columns ab = std::move(a) + std::move(b);

    Columns ba;
    ba += Column{"Right"};
    ba += Column{"Left"};

    // If order matters in rendering, these should differ.
    // We assert inequality to catch accidental reordering.
    EXPECT_NE(ToStringViaStream(ab), ToStringViaStream(ba));
}

// 3) Boundary case: empty strings as columns.
TEST(TextFlowColumnsPlusRvalue_624, PlusRvalue_WorksWithEmptyColumns_624) {
    Column empty1{""};
    Column empty2{""};

    Columns viaPlus = std::move(empty1) + std::move(empty2);

    Columns viaAccumulate;
    viaAccumulate += Column{""};
    viaAccumulate += Column{""};

    EXPECT_EQ(ToStringViaStream(viaPlus), ToStringViaStream(viaAccumulate));
}

// 4) Settings propagation through rvalues: width/indent/initialIndent should be reflected
//    exactly as when building the same two Columns and accumulating via +=.
//    This does not assert *what* formatting is, only that both construction paths are equivalent.
TEST(TextFlowColumnsPlusRvalue_624, PlusRvalue_RespectsColumnSettings_624) {
    Column c1{"One"};
    c1.width(10).indent(2).initialIndent(1);  // use public modifiers only

    Column c2{"Two"};
    c2.width(12).indent(0).initialIndent(3);

    Columns viaPlus = std::move(c1) + std::move(c2);

    Columns viaAccumulate;
    Column d1{"One"};
    d1.width(10).indent(2).initialIndent(1);

    Column d2{"Two"};
    d2.width(12).indent(0).initialIndent(3);

    viaAccumulate += std::move(d1);
    viaAccumulate += std::move(d2);

    EXPECT_EQ(ToStringViaStream(viaPlus), ToStringViaStream(viaAccumulate));
}

// 5) Mixed content boundary: very short + very long text, to surface potential width/line-wrap issues
//    while still treating implementation as a black box (compare two public construction paths).
TEST(TextFlowColumnsPlusRvalue_624, PlusRvalue_MixedShortAndLongTexts_624) {
    const std::string shortTxt = "X";
    const std::string longTxt =
        "This is a very long piece of text intended to exceed typical console widths "
        "so that whatever wrapping/flowing strategy is used will activate.";

    Column cShort{shortTxt};
    Column cLong{longTxt};
    cShort.width(8).indent(1);
    cLong.width(50).initialIndent(4);

    Columns viaPlus = std::move(cShort) + std::move(cLong);

    Columns viaAccumulate;
    Column dShort{shortTxt}; dShort.width(8).indent(1);
    Column dLong{longTxt};   dLong.width(50).initialIndent(4);
    viaAccumulate += std::move(dShort);
    viaAccumulate += std::move(dLong);

    EXPECT_EQ(ToStringViaStream(viaPlus), ToStringViaStream(viaAccumulate));
}
