#include "catch.hpp"

#include "../src/Commands/PowerOnCommand.hpp"
#include "../src/HardwareInterface/PreheatingAnswer.hpp"


using namespace Commands;

TEST_CASE( "PowerOnResult", "[PowerOnResult]" ) {

    SECTION( "is success when there are two long green flashes" ) {
        HardwareInterface::PreheatingAnswer answer{
            {2000, 2000},
            {}
        };

        PowerOnResult result{answer};
        
        REQUIRE( result.IsError() == false );
    }

    SECTION( "is error without any flashes" ) {
        HardwareInterface::PreheatingAnswer answer{
            {},
            {}
        };

        PowerOnResult result{answer};

        REQUIRE( result.IsError() == true );
    }

    SECTION( "low battery with at least 4 fast red flashes" ) {
        HardwareInterface::PreheatingAnswer answer{
            {},
            {200, 200, 200, 200}
        };

        PowerOnResult result{answer};

        REQUIRE( result.IsError() == true );
        REQUIRE( result.IsLowBattery() == true );
    }

    SECTION( "out of range when at least 4 fast green flashes" ) {
        HardwareInterface::PreheatingAnswer answer{
            {200, 200, 200, 200},
            {}
        };

        PowerOnResult result{answer};

        REQUIRE( result.IsError() == true );
        REQUIRE( result.IsOutOfRange() == true );
    }

    SECTION( "normal out of range scenario" ) {
        HardwareInterface::PreheatingAnswer answer{
            {2000, 200, 200, 200, 200},
            {2000}
        };

        PowerOnResult result{answer};
        REQUIRE( result.IsError() == true );
        REQUIRE( result.IsOutOfRange() == true );
    }
}
