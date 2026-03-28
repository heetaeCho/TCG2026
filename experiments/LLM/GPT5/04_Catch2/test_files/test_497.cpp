The TEST_ID is 497

--- PROMPT START ---

You are given a partial implementation of a C++ class.
This class is already implemented and used in the actual codebase.
Your task is to write unit tests for the given interface, using Google Test (and Google Mock if needed), while strictly following the constraints below.

[Constraints]
1. **Do NOT re-implement or infer the internal logic** of any function.  
   You must treat the implementation as a black box.
2. **Write tests only based on the provided interface** — that is, based on:
   - Function signatures
   - Observable behavior (e.g., return values, effects visible through public functions or callback invocations)
3. **You may use Google Mock**:
   - Only when mocking external collaborators (e.g., passed-in handlers, callbacks, or dependencies)
   - Not to simulate internal behavior of the class under test
4. **Do NOT access or rely on private/internal state**, such as internal buffers, counters, or helper function behavior.
5. Include test cases for:
   - Normal operation
   - Boundary conditions
   - Exceptional or error cases (if observable through the interface)
   - Verification of external interactions (e.g., mock handler calls and their parameters)
6. Each test case should clearly indicate what behavior is being tested, and should follow consistent naming conventions.

[Requirements]
1. add TEST_ID for every Test name
   e.g.) TEST_F(WriteBatchTest_85, PutIncreasesCount_85), where The TEST_ID is 85

[Partial Code]
File name : Catch2/src/catch2/internal/catch_run_context.cpp
```cpp
namespace Catch { class RunContext { public: IGeneratorTracker* acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const& lineInfo ) { using namespace Generators; GeneratorTracker* tracker = GeneratorTracker::acquire( m_trackerContext, TestCaseTracking::NameAndLocationRef( generatorName, lineInfo ) ); m_lastAssertionInfo.lineInfo = lineInfo; return tracker; } }; }
```

---
[Known or Inferred Dependencies (Optional)]
File name : Catch2/src/catch2/internal/catch_stringref.hpp
```cpp
namespace Catch { class StringRef { private const char * m_start= s_empty; private size_type m_size= 0; public  StringRef (const char * rawChars); public constexpr StringRef() noexcept = default; public constexpr StringRef( char const* rawChars, size_type size ) noexcept : m_start( rawChars ), m_size( size ); public StringRef( std::string const& stdString ) noexcept : m_start( stdString.c_str() ), m_size( stdString.size() ); public StringRef::StringRef( char const* rawChars ) noexcept : StringRef( rawChars, std::strlen(rawChars) ); public const bool operator< (StringRef rhs); public  std::string & operator+= (std::string & lhs, StringRef rhs); public  std::ostream & operator<< (std::ostream & os, StringRef str); public  std::string operator+ (StringRef lhs, StringRef rhs); public const int compare (StringRef rhs); public explicit operator std::string() const; public auto operator == ( StringRef other ) const noexcept -> bool; public auto operator != (StringRef other) const noexcept -> bool; public constexpr auto operator[] ( size_type index ) const noexcept -> char; public constexpr auto empty() const noexcept -> bool; public constexpr auto size() const noexcept -> size_type; public constexpr StringRef substr(size_type start, size_type length) const noexcept; public constexpr char const* data() const noexcept; public constexpr const_iterator begin() const; public constexpr const_iterator end() const; public bool StringRef::operator<(StringRef rhs) const noexcept; public int StringRef::compare( StringRef rhs ) const; }; }}
```

File name : Catch2/src/catch2/internal/catch_source_line_info.hpp
```cpp
namespace Catch { struct SourceLineInfo { public const char * file; public std::size_t line; public SourceLineInfo() = delete; public constexpr SourceLineInfo( char const* _file, std::size_t _line ) noexcept: file( _file ), line( _line ); public const bool operator== (const SourceLineInfo & other); public const bool operator< (const SourceLineInfo & other); public  std::ostream & operator<< (std::ostream & os, const SourceLineInfo & info); public bool SourceLineInfo::operator == ( SourceLineInfo const& other ) const noexcept; public bool SourceLineInfo::operator < ( SourceLineInfo const& other ) const noexcept; }; }}
```

File name : Catch2/src/catch2/catch_assertion_info.hpp
```cpp
namespace Catch { struct AssertionInfo { public StringRef macroName; public StringRef capturedExpression; public struct ResultDisposition::Flags resultDisposition; }; }}
```

File name : Catch2/src/catch2/internal/catch_run_context.hpp
```cpp
namespace Catch { class RunContext : public IResultCapture { private TestRunInfo m_runInfo; private const TestCaseHandle * m_activeTestCase= nullptr; private ITracker * m_testCaseTracker= nullptr; private Optional<AssertionResult> m_lastResult; private Totals m_totals; private IEventListenerPtr m_reporter; private std::vector<ScopedMessage> m_messageScopes; private AssertionInfo m_lastAssertionInfo; private std::vector<SectionEndInfo> m_unfinishedSections; private std::vector<ITracker *> m_activeSections; private TrackerContext m_trackerContext; private Detail::unique_ptr<OutputRedirect> m_outputRedirect; private FatalConditionHandler m_fatalConditionhandler; private bool m_lastAssertionPassed= false; private bool m_shouldReportUnexpected= true; private bool m_includeSuccessfulResults; public explicit RunContext (const IConfig * _config, IEventListenerPtr && reporter); public RunContext( RunContext const& ) = delete; public RunContext::RunContext(IConfig const* _config, IEventListenerPtr&& reporter) : m_runInfo(_config->name()), m_config(_config), m_reporter(CATCH_MOVE(reporter)), m_lastAssertionInfo; public  void ~RunContext () override; public  Totals runTest (const TestCaseHandle & testCase); public  void handleExpr (const AssertionInfo & info, const ITransientExpression & expr, AssertionReaction & reaction) override; public  void handleMessage (const AssertionInfo & info, struct ResultWas::OfType resultType, std::string && message, AssertionReaction & reaction) override; public  void handleUnexpectedExceptionNotThrown (const AssertionInfo & info, AssertionReaction & reaction) override; public  void handleUnexpectedInflightException (const AssertionInfo & info, std::string && message, AssertionReaction & reaction) override; public  void handleIncomplete (const AssertionInfo & info) override; public  void handleNonExpr (const AssertionInfo & info, struct ResultWas::OfType resultType, AssertionReaction & reaction) override; public  void notifyAssertionStarted (const AssertionInfo & info) override; public  bool sectionStarted (StringRef sectionName, const SourceLineInfo & sectionLineInfo, Counts & assertions) override; public  void sectionEnded (SectionEndInfo && endInfo) override; public  void sectionEndedEarly (SectionEndInfo && endInfo) override; public  IGeneratorTracker * acquireGeneratorTracker (StringRef generatorName, const SourceLineInfo & lineInfo) override; public  IGeneratorTracker * createGeneratorTracker (StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr && generator) override; public  void benchmarkPreparing (StringRef name) override; public  void benchmarkStarting (const BenchmarkInfo & info) override; public  void benchmarkEnded (const BenchmarkStats<> & stats) override; public  void benchmarkFailed (StringRef error) override; public  void pushScopedMessage (const MessageInfo & message) override; public  void popScopedMessage (const MessageInfo & message) override; public  void emplaceUnscopedMessage (MessageBuilder && builder) override; public const std::string getCurrentTestName () override; public const const AssertionResult * getLastResult () override; public  void exceptionEarlyReported () override; public  void handleFatalErrorCondition (StringRef message) override; public  bool lastAssertionPassed () override; public  void assertionPassed () override; public const bool aborting (); private  void runCurrentTest (); private  void invokeActiveTestCase (); private  void resetAssertionInfo (); private  bool testForMissingAssertions (Counts & assertions); private  void assertionEnded (AssertionResult && result); private  void reportExpr (const AssertionInfo & info, struct ResultWas::OfType resultType, const ITransientExpression * expr, bool negated); private  void populateReaction (AssertionReaction & reaction); private  void handleUnfinishedSections (); public RunContext& operator =( RunContext const& ) = delete; public RunContext::~RunContext(); public Totals RunContext::runTest(TestCaseHandle const& testCase); private void RunContext::assertionEnded(AssertionResult&& result); private void RunContext::resetAssertionInfo(); public void RunContext::notifyAssertionStarted( AssertionInfo const& info ); public bool RunContext::sectionStarted( StringRef sectionName, SourceLineInfo const& sectionLineInfo, Counts& assertions ); public IGeneratorTracker* RunContext::acquireGeneratorTracker( StringRef generatorName, SourceLineInfo const& lineInfo ); public IGeneratorTracker* RunContext::createGeneratorTracker( StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr&& generator ); private bool RunContext::testForMissingAssertions(Counts& assertions); public void RunContext::sectionEnded(SectionEndInfo&& endInfo); public void RunContext::sectionEndedEarly(SectionEndInfo&& endInfo); public void RunContext::benchmarkPreparing( StringRef name ); public void RunContext::benchmarkStarting( BenchmarkInfo const& info ); public void RunContext::benchmarkEnded( BenchmarkStats<> const& stats ); public void RunContext::benchmarkFailed( StringRef error ); public void RunContext::pushScopedMessage(MessageInfo const & message); public void RunContext::popScopedMessage(MessageInfo const & message); public void RunContext::emplaceUnscopedMessage( MessageBuilder&& builder ); public std::string RunContext::getCurrentTestName() const; public const AssertionResult * RunContext::getLastResult() const; public void RunContext::exceptionEarlyReported(); public void RunContext::handleFatalErrorCondition( StringRef message ); public bool RunContext::lastAssertionPassed(); public void RunContext::assertionPassed(); public bool RunContext::aborting() const; private void RunContext::runCurrentTest(); private void RunContext::invokeActiveTestCase(); private void RunContext::handleUnfinishedSections(); public void RunContext::handleExpr( AssertionInfo const& info, ITransientExpression const& expr, AssertionReaction& reaction ); private void RunContext::reportExpr( AssertionInfo const &info, ResultWas::OfType resultType, ITransientExpression const *expr, bool negated ); public void RunContext::handleMessage( AssertionInfo const& info, ResultWas::OfType resultType, std::string&& message, AssertionReaction& reaction ); public void RunContext::handleUnexpectedExceptionNotThrown( AssertionInfo const& info, AssertionReaction& reaction ); public void RunContext::handleUnexpectedInflightException( AssertionInfo const& info, std::string&& message, AssertionReaction& reaction ); private void RunContext::populateReaction( AssertionReaction& reaction ); public void RunContext::handleIncomplete( AssertionInfo const& info ); public void RunContext::handleNonExpr( AssertionInfo const &info, ResultWas::OfType resultType, AssertionReaction &reaction ); }; }}
```

File name : Catch2/src/catch2/internal/catch_run_context.cpp
```cpp
namespace Catch { namespace Generators { struct GeneratorTracker : public TestCaseTracking::TrackerBase, public IGeneratorTracker { public GeneratorBasePtr m_generator; public GeneratorTracker( TestCaseTracking::NameAndLocation&& nameAndLocation, TrackerContext& ctx, ITracker* parent ): TrackerBase( CATCH_MOVE( nameAndLocation ), ctx, parent ); public static GeneratorTracker* acquire( TrackerContext& ctx, TestCaseTracking::NameAndLocationRef const& nameAndLocation ); public bool isGeneratorTracker() const override; public auto hasGenerator() const -> bool override; public void close() override; public auto getGenerator() const -> GeneratorBasePtr const& override; public void setGenerator( GeneratorBasePtr&& generator ) override; }; }} }}
```


--- PROMPT END ---
