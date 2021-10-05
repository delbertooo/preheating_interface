#include "LibPreheatingInterface.hpp"

using namespace LibPreheatingInterface;

PowerOffCommand::PowerOffCommand(CommandHelper &helper) : AbstractCommand(helper) {}

PowerOffResult PowerOffCommand::PowerOff() {
    return helper.Run(LibScheduling::RunnableSequence{}
        .Run([this]{ remote.PressOff(); })
        .Wait(1000)
        .Run([this]{ remote.ReleaseOff(); })
        .Wait(3000));
}
