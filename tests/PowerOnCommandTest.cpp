#include "catch.hpp"

#include "../Commands/PowerOn.hpp"
#include "../PreheatingAnswer.hpp"

class MockHardwareExecutor : public IPreheatingCommandExecutor {
public:
    std::vector<unsigned long> green;
    std::vector<unsigned long> red;
    PreheatingAnswer Run() {
        return PreheatingAnswer{green, red};
    }
};


TEST_CASE( "PowerOnCommand", "[PowerOnCommand]" ) {
    MockHardwareExecutor executor;

    SECTION( "is success when there is one long green flash" ) {
        executor.green.push_back(1000);
        
        PowerOnCommand cmd{executor};
        PreheatingCommandResult result = cmd.Execute();

        REQUIRE( result.IsError() == false );
    }
    
    SECTION( "is error without any flashes" ) {
        PowerOnCommand cmd(executor);
        PreheatingCommandResult result = cmd.Execute();

        REQUIRE( result.IsError() == true );
    }
}
