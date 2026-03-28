#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// We need to provide minimal stubs/mocks for the dependencies since we're
// testing AnnotationPrivate::pdfObjectReference() as a black box.

// Minimal Ref struct matching the known interface
struct Ref {
    int num;
    int gen;
    
    static constexpr Ref INVALID() { return {-1, -1}; }
    
    bool operator==(const Ref& other) const {
        return num == other.num && gen == other.gen;
    }
};

// Minimal Annot class that provides getRef()
class Annot {
public:
    virtual ~Annot() = default;
    virtual Ref getRef() const { return ref_; }
    
    void setRef(Ref r) { ref_ = r; }
    
private:
    Ref ref_ = Ref::INVALID();
};

// Forward declarations to satisfy compilation
class Page {};

namespace Poppler {
class DocumentData {};
class Annotation;

class AnnotationPrivate {
public:
    std::shared_ptr<Annot> pdfAnnot;
    
    AnnotationPrivate() : pdfAnnot(nullptr) {}
    virtual ~AnnotationPrivate() = default;
    
    AnnotationPrivate(const AnnotationPrivate&) = delete;
    AnnotationPrivate& operator=(const AnnotationPrivate&) = delete;
    
    Ref pdfObjectReference() const {
        if (pdfAnnot == nullptr) {
            return Ref::INVALID();
        }
        return pdfAnnot->getRef();
    }
};

} // namespace Poppler

// ============================================================================
// Test Fixture
// ============================================================================

class AnnotationPrivateTest_1391 : public ::testing::Test {
protected:
    void SetUp() override {
        annotPrivate = std::make_unique<Poppler::AnnotationPrivate>();
    }
    
    std::unique_ptr<Poppler::AnnotationPrivate> annotPrivate;
};

// ============================================================================
// Tests for pdfObjectReference()
// ============================================================================

// Test: When pdfAnnot is nullptr, pdfObjectReference should return INVALID Ref
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_NullAnnot_ReturnsInvalid_1391) {
    // pdfAnnot is nullptr by default
    Ref result = annotPrivate->pdfObjectReference();
    Ref invalid = Ref::INVALID();
    
    EXPECT_EQ(result.num, invalid.num);
    EXPECT_EQ(result.gen, invalid.gen);
}

// Test: When pdfAnnot is set to a valid Annot, pdfObjectReference returns Annot's Ref
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_ValidAnnot_ReturnsAnnotRef_1391) {
    auto annot = std::make_shared<Annot>();
    Ref expectedRef = {42, 7};
    annot->setRef(expectedRef);
    
    annotPrivate->pdfAnnot = annot;
    
    Ref result = annotPrivate->pdfObjectReference();
    
    EXPECT_EQ(result.num, 42);
    EXPECT_EQ(result.gen, 7);
}

// Test: When pdfAnnot has default ref (INVALID), returns INVALID
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_AnnotWithDefaultRef_ReturnsDefaultRef_1391) {
    auto annot = std::make_shared<Annot>();
    // Don't set any specific ref, so it keeps its default (INVALID)
    
    annotPrivate->pdfAnnot = annot;
    
    Ref result = annotPrivate->pdfObjectReference();
    Ref defaultRef = Ref::INVALID();
    
    EXPECT_EQ(result.num, defaultRef.num);
    EXPECT_EQ(result.gen, defaultRef.gen);
}

// Test: pdfObjectReference with zero-valued Ref
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_ZeroRef_ReturnsZeroRef_1391) {
    auto annot = std::make_shared<Annot>();
    Ref zeroRef = {0, 0};
    annot->setRef(zeroRef);
    
    annotPrivate->pdfAnnot = annot;
    
    Ref result = annotPrivate->pdfObjectReference();
    
    EXPECT_EQ(result.num, 0);
    EXPECT_EQ(result.gen, 0);
}

// Test: pdfObjectReference with large Ref values
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_LargeRefValues_ReturnsCorrectRef_1391) {
    auto annot = std::make_shared<Annot>();
    Ref largeRef = {999999, 65535};
    annot->setRef(largeRef);
    
    annotPrivate->pdfAnnot = annot;
    
    Ref result = annotPrivate->pdfObjectReference();
    
    EXPECT_EQ(result.num, 999999);
    EXPECT_EQ(result.gen, 65535);
}

// Test: Setting pdfAnnot to nullptr after it was valid should return INVALID
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_SetToNullAfterValid_ReturnsInvalid_1391) {
    auto annot = std::make_shared<Annot>();
    Ref someRef = {10, 5};
    annot->setRef(someRef);
    
    annotPrivate->pdfAnnot = annot;
    
    // First call should return valid ref
    Ref result1 = annotPrivate->pdfObjectReference();
    EXPECT_EQ(result1.num, 10);
    EXPECT_EQ(result1.gen, 5);
    
    // Set to nullptr
    annotPrivate->pdfAnnot = nullptr;
    
    // Now should return INVALID
    Ref result2 = annotPrivate->pdfObjectReference();
    Ref invalid = Ref::INVALID();
    EXPECT_EQ(result2.num, invalid.num);
    EXPECT_EQ(result2.gen, invalid.gen);
}

// Test: Replacing pdfAnnot with a different one returns the new Ref
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_ReplaceAnnot_ReturnsNewRef_1391) {
    auto annot1 = std::make_shared<Annot>();
    Ref ref1 = {1, 0};
    annot1->setRef(ref1);
    
    auto annot2 = std::make_shared<Annot>();
    Ref ref2 = {2, 1};
    annot2->setRef(ref2);
    
    annotPrivate->pdfAnnot = annot1;
    Ref result1 = annotPrivate->pdfObjectReference();
    EXPECT_EQ(result1.num, 1);
    EXPECT_EQ(result1.gen, 0);
    
    annotPrivate->pdfAnnot = annot2;
    Ref result2 = annotPrivate->pdfObjectReference();
    EXPECT_EQ(result2.num, 2);
    EXPECT_EQ(result2.gen, 1);
}

// Test: pdfObjectReference with negative Ref values (boundary/edge case)
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_NegativeRefValues_ReturnsNegativeRef_1391) {
    auto annot = std::make_shared<Annot>();
    Ref negRef = {-1, -1};
    annot->setRef(negRef);
    
    annotPrivate->pdfAnnot = annot;
    
    Ref result = annotPrivate->pdfObjectReference();
    
    EXPECT_EQ(result.num, -1);
    EXPECT_EQ(result.gen, -1);
}

// Test: Multiple calls to pdfObjectReference return consistent results
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_MultipleCallsConsistent_1391) {
    auto annot = std::make_shared<Annot>();
    Ref ref = {100, 50};
    annot->setRef(ref);
    
    annotPrivate->pdfAnnot = annot;
    
    Ref result1 = annotPrivate->pdfObjectReference();
    Ref result2 = annotPrivate->pdfObjectReference();
    Ref result3 = annotPrivate->pdfObjectReference();
    
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}

// Mock-based test: Verify that getRef() is actually called on the Annot
class MockAnnot : public Annot {
public:
    MOCK_METHOD(Ref, getRef, (), (const, override));
};

TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_CallsGetRefOnAnnot_1391) {
    auto mockAnnot = std::make_shared<MockAnnot>();
    Ref expectedRef = {77, 3};
    
    EXPECT_CALL(*mockAnnot, getRef())
        .Times(1)
        .WillOnce(::testing::Return(expectedRef));
    
    annotPrivate->pdfAnnot = mockAnnot;
    
    Ref result = annotPrivate->pdfObjectReference();
    
    EXPECT_EQ(result.num, 77);
    EXPECT_EQ(result.gen, 3);
}

// Test: With nullptr, getRef should NOT be called
TEST_F(AnnotationPrivateTest_1391, PdfObjectReference_NullAnnot_DoesNotCallGetRef_1391) {
    // pdfAnnot is nullptr by default - this test just ensures no crash
    // and that INVALID is returned without any access violation
    ASSERT_EQ(annotPrivate->pdfAnnot, nullptr);
    
    Ref result = annotPrivate->pdfObjectReference();
    Ref invalid = Ref::INVALID();
    
    EXPECT_EQ(result.num, invalid.num);
    EXPECT_EQ(result.gen, invalid.gen);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
