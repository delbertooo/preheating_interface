#include "LibPreheatingInterface.hpp"

using namespace LibPreheatingInterface;

PowerOnCommand::PowerOnCommand(CommandHelper &helper) : AbstractCommand(helper) {}

PowerOnResult PowerOnCommand::PowerOn() {
return helper.Run(LibScheduling::RunnableSequence{}
        .Run([this]() { remote.PressOn(); })
        .Wait(1000)
        .Run([this]() { remote.ReleaseOn(); })
        .Wait(3000));
}
