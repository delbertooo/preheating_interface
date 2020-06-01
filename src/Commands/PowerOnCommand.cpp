#include "PowerOnCommand.hpp"
#include "../HardwareInterface/actions.hpp"

Commands::PowerOnCommand::PowerOnCommand(HardwareInterface::PreheatingRemote &remote) : remote(remote) { }

Commands::PowerOnResult Commands::PowerOnCommand::PowerOn() {
    HardwareInterface::PressOnButton pressOnButton;
    HardwareInterface::ReleaseOnButton releaseOnButton;
    auto answer = remote.Execute(RunnableSequence{}
        .Run(pressOnButton)
        .Wait(1000)
        .Run(releaseOnButton)
        .Wait(3000));
    return {answer};
}
