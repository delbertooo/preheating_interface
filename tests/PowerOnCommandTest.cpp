#include "catch.hpp"

#include "../Commands/PowerOn.hpp"
#include "../PreheatingAnswer.hpp"

class MockHardwareExecutor : public IPreheatingCommandExecutor {
public:
    std::vector<unsigned long> green;
    std::vector<unsigned long> red;
    //MockHardwareExecutor(std::vector<unsigned long> green, std::vector<unsigned long> red) : green(green), red(red) {};
    PreheatingAnswer Run() {
        return PreheatingAnswer(green, red);
    }
};


TEST_CASE( "PowerOnCommand", "[PowerOnCommand]" ) {
    MockHardwareExecutor executor;

    SECTION( "is success when there is one long green flash" ) {
        executor.green.push_back(1000);
        
        PowerOnCommand cmd(executor);
        IPreheatingCommandResult *result = &cmd.Execute();

        REQUIRE( result->IsError() == false );
    }
    
}
