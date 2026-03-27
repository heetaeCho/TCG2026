// test_textflow_spacer_618.cpp
#include <gtest/gtest.h>
#include <limits>
#include <vector>

// Include the public interface for Column
#include "catch2/internal/catch_textflow.hpp"

// Forward declare Spacer in the proper namespace (implementation is in the .cpp)
namespace Catch { namespace TextFlow {
    Column Spacer(size_t spaceWidth);
}}

// A simple test fixture in case future tests need shared setup/teardown
class TextFlowSpacerTest_618 : public ::testing::Test {};

TEST_F(TextFlowSpacerTest_618, Spacer_SetsWidthToGivenValues_618) {
    using Catch::TextFlow::Spacer;
    // A small selection of boundary/typical values
    const std::vector<size_t> cases = {
        0u, 1u, 2u, 10u, 79u, 80u, 1000u
    };

    for (size_t w : cases) {
        auto col = Spacer(w);
        EXPECT_EQ(col.width(), w) << "Spacer should set width() to the requested value";
    }
}

TEST_F(TextFlowSpacerTest_618, Spacer_HugeWidth_DoesNotThrowAndIsObservable_618) {
    using Catch::TextFlow::Spacer;
    const size_t huge = std::numeric_limits<size_t>::max() / 2; // large but avoids overflow math

    // Construction should not throw given we only pass a size and observe via width()
    EXPECT_NO_THROW({
        auto col = Spacer(huge);
        EXPECT_EQ(col.width(), huge);
    });
}

TEST_F(TextFlowSpacerTest_618, Spacer_ResultIsIndependentAcrossInstances_618) {
    using Catch::TextFlow::Spacer;
    auto a = Spacer(10);
    auto b = Spacer(20);

    EXPECT_EQ(a.width(), 10u);
    EXPECT_EQ(b.width(), 20u);

    // Mutate one and ensure the other is unaffected (observable behavior via public API)
    a.width(5);
    EXPECT_EQ(a.width(), 5u);
    EXPECT_EQ(b.width(), 20u);
}

TEST_F(TextFlowSpacerTest_618, Spacer_OverridesWhateverDefaultWidthMightBe_618) {
    using Catch::TextFlow::Spacer;
    using Catch::TextFlow::Column;

    Column defaultCol{""};
    const size_t defaultW = defaultCol.width();

    // Choose a target width different from the default (purely to avoid vacuous equality)
    const size_t requested = (defaultW == 42u) ? 43u : 42u;

    auto spaced = Spacer(requested);
    EXPECT_EQ(spaced.width(), requested);
    // Sanity: confirm we did not retroactively alter the default column
    EXPECT_EQ(defaultCol.width(), defaultW);
}
