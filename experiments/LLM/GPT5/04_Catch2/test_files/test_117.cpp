// File: iTransientExpression_ostream_tests_117.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

// Include the provided interface header
#include "catch2/internal/catch_decomposer.hpp"

namespace Catch {

// A strict mock that only mocks the external interaction point we observe:
// the virtual streamReconstructedExpression. We do not simulate any internal logic.
class MockTransientExpression : public ITransientExpression {
public:
    MockTransientExpression(bool isBinary, bool result)
        : ITransientExpression(isBinary, result) {}

    // Match the interface exactly; keep it const and override.
    MOCK_METHOD(void, streamReconstructedExpression, (std::ostream& os), (const, override));
};

} // namespace Catch

using ::testing::Ref;

//
// Normal operation: operator<< calls streamReconstructedExpression and returns the same stream
//
TEST(TransientExpressionOstreamTest_117, CallsStreamReconstructionAndReturnsSameStream_117) {
    std::ostringstream oss;
    Catch::MockTransientExpression expr(/*isBinary=*/true, /*result=*/true);

    // Expect the virtual call with the very same stream reference,
    // and have the mock write a recognizable payload into it.
    EXPECT_CALL(expr, streamReconstructedExpression(Ref(oss)))
        .WillOnce([&](std::ostream& os) { os << "reconstructed"; });

    // Call the free operator<< explicitly to avoid ADL surprises.
    std::ostream& ret = Catch::operator<<(oss, static_cast<Catch::ITransientExpression const&>(expr));

    // Verify output came from the mocked reconstruction and that chaining reference is identical.
    EXPECT_EQ(oss.str(), "reconstructed");
    EXPECT_EQ(&ret, &oss);
}

//
// Chaining: ensure returned stream allows further insertions seamlessly
//
TEST(TransientExpressionOstreamTest_117, SupportsChainingAfterInsertion_117) {
    std::ostringstream oss;
    Catch::MockTransientExpression expr(/*isBinary=*/false, /*result=*/false);

    EXPECT_CALL(expr, streamReconstructedExpression(Ref(oss)))
        .WillOnce([&](std::ostream& os) { os << "X"; });

    // Chain another insertion right away
    (Catch::operator<<(oss, static_cast<Catch::ITransientExpression const&>(expr))) << "Y";

    EXPECT_EQ(oss.str(), "XY");
}

//
// Boundary/edge behavior: if the reconstruction writes nothing, the operator still returns the stream unchanged
//
TEST(TransientExpressionOstreamTest_117, NoOutputFromReconstructionLeavesStreamContentIntact_117) {
    std::ostringstream oss;
    oss << "pre:";

    Catch::MockTransientExpression expr(/*isBinary=*/true, /*result=*/false);

    // The reconstruction is called but does not write anything.
    EXPECT_CALL(expr, streamReconstructedExpression(Ref(oss)))
        .WillOnce([](std::ostream&) { /* no-op */ });

    std::ostream& ret = Catch::operator<<(oss, static_cast<Catch::ITransientExpression const&>(expr));
    ret << "post";

    EXPECT_EQ(oss.str(), "pre:post");
    EXPECT_EQ(&ret, &oss);
}
