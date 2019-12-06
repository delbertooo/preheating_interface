#include "catch.hpp"

#include "../Commands/PowerOnCommand.hpp"
#include "../HardwareInterface/PreheatingAnswer.hpp"

class MockHardwareExecutor : public HardwareInterface::HardwareExecutor {
public:
    std::vector<unsigned long> green;
    std::vector<unsigned long> red;
    HardwareInterface::PreheatingAnswer Run() {
        return {green, red};
    }
};

using namespace Commands;

TEST_CASE( "PowerOnCommand", "[PowerOnCommand]" ) {
    MockHardwareExecutor executor;

    SECTION( "is success when there are two long green flashes" ) {
        executor.green.push_back(2000);
        executor.green.push_back(2000);

        PowerOnCommand cmd{executor};
        PreheatingCommandResult result = cmd.Execute();

        REQUIRE( result.IsError() == false );
    }

    SECTION( "is error without any flashes" ) {
        PowerOnCommand cmd{executor};
        PreheatingCommandResult result = cmd.Execute();

        REQUIRE( result.IsError() == true );
    }

    SECTION( "low battery with at least 4 fast red flashes" ) {
        executor.red.push_back(200);
        executor.red.push_back(200);
        executor.red.push_back(200);
        executor.red.push_back(200);

        PowerOnCommand cmd{executor};
        PreheatingCommandResult result = cmd.Execute();

        REQUIRE( result.IsError() == true );
        REQUIRE( result.ErrorMessage() == "ERROR_LOW_BATTERY");
    }

    SECTION( "out of range when at least 4 fast green flashes" ) {
        executor.green.push_back(200);
        executor.green.push_back(200);
        executor.green.push_back(200);
        executor.green.push_back(200);

        PowerOnCommand cmd{executor};
        PreheatingCommandResult result = cmd.Execute();

        REQUIRE( result.IsError() == true );
        REQUIRE( result.ErrorMessage() == "ERROR_OUT_OF_RANGE");
    }

    SECTION( "normal out of range scenario" ) {
        executor.green.push_back(2000);
        executor.red.push_back(2000);
        executor.green.push_back(200);
        executor.green.push_back(200);
        executor.green.push_back(200);
        executor.green.push_back(200);

        PowerOnCommand cmd{executor};
        PreheatingCommandResult result = cmd.Execute();

        REQUIRE( result.IsError() == true );
        REQUIRE( result.ErrorMessage() == "ERROR_OUT_OF_RANGE");
    }
}
