#include "PowerOffCommand.hpp"
#include "../HardwareInterface/actions.hpp"

Commands::PowerOffCommand::PowerOffCommand(HardwareInterface::PreheatingRemote &remote) : remote(remote) { }

Commands::PowerOffResult Commands::PowerOffCommand::PowerOff() {
    HardwareInterface::PressOffButton pressOffButton;
    HardwareInterface::ReleaseOffButton releaseOffButton;
    auto answer = remote.Execute(RunnableSequence{}
        .Run(pressOffButton)
        .Wait(1000)
        .Run(releaseOffButton)
        .Wait(3000));
    return {answer};
}
