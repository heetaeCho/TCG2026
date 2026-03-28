#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_translate_exception.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"
#include "catch2/interfaces/catch_interfaces_exception.hpp"
#include "catch2/internal/catch_context.hpp"

using namespace Catch;
using namespace Catch::Detail;

// Mock for IMutableRegistryHub
class MockMutableRegistryHub : public IMutableRegistryHub {
public:
    MOCK_METHOD(void, registerReporter, (const std::string& name, IReporterFactoryPtr factory), (override));
    MOCK_METHOD(void, registerListener, (Detail::unique_ptr<EventListenerFactory> factory), (override));
    MOCK_METHOD(void, registerTest, (Detail::unique_ptr<TestCaseInfo>&& testInfo, Detail::unique_ptr<ITestInvoker>&& invoker), (override));
    MOCK_METHOD(void, registerTranslator, (Detail::unique_ptr<IExceptionTranslator>&& translator), (override));
    MOCK_METHOD(void, registerTagAlias, (const std::string& alias, const std::string& tag, const SourceLineInfo& lineInfo), (override));
    MOCK_METHOD(void, registerStartupException, (), (override));
    MOCK_METHOD(IMutableEnumValuesRegistry&, getMutableEnumValuesRegistry, (), (override));
    ~MockMutableRegistryHub() override = default;
};

// A concrete IExceptionTranslator for testing
class TestExceptionTranslator : public IExceptionTranslator {
public:
    std::string translate(ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd) const override {
        return "test translation";
    }
    
    bool translatorWasMoved = false;
};

// Since registerTranslatorImpl calls getMutableRegistryHub(), which is a global function,
// we need to test through the public interface. The function registers a translator
// with the global registry hub. We can verify it doesn't crash and properly
// forwards the translator.

class RegisterTranslatorTest_248 : public ::testing::Test {
protected:
    void SetUp() override {
        // Clean up any previous state if needed
    }
    
    void TearDown() override {
    }
};

// Test that registerTranslatorImpl accepts a valid translator without crashing
TEST_F(RegisterTranslatorTest_248, RegisterValidTranslator_248) {
    auto translator = Detail::unique_ptr<IExceptionTranslator>(new TestExceptionTranslator());
    
    // This should not throw - it registers the translator with the global registry hub
    EXPECT_NO_THROW(Detail::registerTranslatorImpl(CATCH_MOVE(translator)));
}

// Test that after move, the unique_ptr is null (ownership transferred)
TEST_F(RegisterTranslatorTest_248, TranslatorOwnershipTransferred_248) {
    auto translator = Detail::unique_ptr<IExceptionTranslator>(new TestExceptionTranslator());
    
    Detail::registerTranslatorImpl(CATCH_MOVE(translator));
    
    // After move, the original unique_ptr should be null
    EXPECT_FALSE(static_cast<bool>(translator));
}

// Test registering multiple translators
TEST_F(RegisterTranslatorTest_248, RegisterMultipleTranslators_248) {
    auto translator1 = Detail::unique_ptr<IExceptionTranslator>(new TestExceptionTranslator());
    auto translator2 = Detail::unique_ptr<IExceptionTranslator>(new TestExceptionTranslator());
    
    EXPECT_NO_THROW(Detail::registerTranslatorImpl(CATCH_MOVE(translator1)));
    EXPECT_NO_THROW(Detail::registerTranslatorImpl(CATCH_MOVE(translator2)));
}

// Test that a derived exception translator can be registered
class DerivedExceptionTranslator : public TestExceptionTranslator {
public:
    std::string translate(ExceptionTranslators::const_iterator it, ExceptionTranslators::const_iterator itEnd) const override {
        return "derived translation";
    }
};

TEST_F(RegisterTranslatorTest_248, RegisterDerivedTranslator_248) {
    auto translator = Detail::unique_ptr<IExceptionTranslator>(new DerivedExceptionTranslator());
    
    EXPECT_NO_THROW(Detail::registerTranslatorImpl(CATCH_MOVE(translator)));
}

// Test unique_ptr behavior with nullptr (edge case)
TEST_F(RegisterTranslatorTest_248, UniquePtr_NullptrConstruction_248) {
    Detail::unique_ptr<IExceptionTranslator> ptr(nullptr);
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test unique_ptr release mechanism
TEST_F(RegisterTranslatorTest_248, UniquePtr_Release_248) {
    auto raw = new TestExceptionTranslator();
    Detail::unique_ptr<IExceptionTranslator> ptr(raw);
    
    auto released = ptr.release();
    EXPECT_EQ(released, raw);
    EXPECT_EQ(ptr.get(), nullptr);
    
    // Clean up since we released ownership
    delete released;
}

// Test unique_ptr reset
TEST_F(RegisterTranslatorTest_248, UniquePtr_Reset_248) {
    auto ptr = Detail::unique_ptr<IExceptionTranslator>(new TestExceptionTranslator());
    EXPECT_TRUE(static_cast<bool>(ptr));
    
    ptr.reset();
    EXPECT_FALSE(static_cast<bool>(ptr));
    EXPECT_EQ(ptr.get(), nullptr);
}

// Test unique_ptr move constructor
TEST_F(RegisterTranslatorTest_248, UniquePtr_MoveConstructor_248) {
    auto raw = new TestExceptionTranslator();
    Detail::unique_ptr<IExceptionTranslator> ptr1(raw);
    
    Detail::unique_ptr<IExceptionTranslator> ptr2(CATCH_MOVE(ptr1));
    
    EXPECT_EQ(ptr2.get(), raw);
    EXPECT_EQ(ptr1.get(), nullptr);
}

// Test unique_ptr dereference
TEST_F(RegisterTranslatorTest_248, UniquePtr_Dereference_248) {
    auto translator = new TestExceptionTranslator();
    Detail::unique_ptr<IExceptionTranslator> ptr(translator);
    
    EXPECT_EQ(&(*ptr), translator);
    EXPECT_EQ(ptr.get(), translator);
}

// Test unique_ptr arrow operator
TEST_F(RegisterTranslatorTest_248, UniquePtr_ArrowOperator_248) {
    auto translator = new TestExceptionTranslator();
    Detail::unique_ptr<IExceptionTranslator> ptr(translator);
    
    EXPECT_EQ(ptr.operator->(), translator);
}

// Test unique_ptr explicit bool conversion
TEST_F(RegisterTranslatorTest_248, UniquePtr_BoolConversion_248) {
    Detail::unique_ptr<IExceptionTranslator> nullPtr(nullptr);
    EXPECT_FALSE(static_cast<bool>(nullPtr));
    
    Detail::unique_ptr<IExceptionTranslator> validPtr(new TestExceptionTranslator());
    EXPECT_TRUE(static_cast<bool>(validPtr));
}

// Test unique_ptr reset with new pointer
TEST_F(RegisterTranslatorTest_248, UniquePtr_ResetWithNewPointer_248) {
    auto translator1 = new TestExceptionTranslator();
    auto translator2 = new TestExceptionTranslator();
    
    Detail::unique_ptr<IExceptionTranslator> ptr(translator1);
    EXPECT_EQ(ptr.get(), translator1);
    
    ptr.reset(translator2);
    EXPECT_EQ(ptr.get(), translator2);
}
