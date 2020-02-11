
#include <UnitTest++/UnitTest++.h>
#include <UnitTest++/DeferredTestResult.h>


using namespace UnitTest;


class SimlinqTestReporter : public TestReporter {
public:
    
    void ReportTestStart(const UnitTest::TestDetails &test) override {
        currentTest ++;
        success = true;
        lastTestFailures.clear();
    }
    
    
    void ReportTestFinish(const UnitTest::TestDetails &test, float secondsElapsed) override {
        auto testName = std::string(test.suiteName) + "::" + std::string(test.testName);
        
        printf("%6s : %-4d %s\n", success ? "ok" : "NOT OK", currentTest, testName.c_str());
        
        if (lastTestFailures.size() > 0) {
            printf("     failures:\n");
            for (auto failure : lastTestFailures) {
                auto message = std::string(failure.failureStr);
                size_t i = 0;
                while((i = message.find("'", i)) != std::string::npos) {
                    message.replace(i, 1, "''");
                    i += 2;
                }
                printf("      - line: %d\n        message: '%s'\n", failure.lineNumber, message.c_str());
                
            }
            printf("    ...\n");
        }
    }
    
    
    void ReportFailure(const UnitTest::TestDetails &test, const char *failure) override {
        using namespace std;
        success = false;
        lastTestFailures.push_back(DeferredTestFailure(test.lineNumber, failure));
        
        const int bufferSize = 1024;
        char buffer[bufferSize];
        
        failures.push_back(buffer);
    }
    
    
    
    void ReportSummary(int totalTestCount, int failedTestCount, int failureCount, float secondsElapsed) override {
        printf("1..%d\n", totalTestCount);
        if (failureCount > 0) {
            for (auto& failure: failures)
                printf("%s\n", failure.c_str());
            printf("FAILURE: %d out of %d tests failed (%d failures).\n", failedTestCount, totalTestCount, failureCount);
        } else {
            printf("Success: %d tests passed.\n", totalTestCount);
        }

        printf("Test time: %.2f seconds.\n", secondsElapsed);

    }
    
private:
    int currentTest = 0;
    bool success;
    
    std::vector<DeferredTestFailure> lastTestFailures;
    std::vector<std::string> failures;
};






int main(int, const char *[])
{
    SimlinqTestReporter reporter;
    TestRunner runner(reporter);
    return runner.RunTestsIf(Test::GetTestList(), NULL, True(), 0);
   return UnitTest::RunAllTests();
}
