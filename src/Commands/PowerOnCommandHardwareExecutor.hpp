
#include "../HardwareInterface/HardwareExecutor.hpp"
#include "../HardwareInterface/PreheatingRemote.hpp"
#include "../HardwareInterface/actions.hpp"

#ifndef __COMMANDS_POWERONCOMMANDHARDWAREEXECUTOR_HPP
#define __COMMANDS_POWERONCOMMANDHARDWAREEXECUTOR_HPP 1

namespace Commands {

class PowerOnCommandHardwareExecutor : public HardwareInterface::HardwareExecutor {
private:
    HardwareInterface::PreheatingRemote &remote;
public:
    PowerOnCommandHardwareExecutor(HardwareInterface::PreheatingRemote &remote) : remote(remote) { }
    HardwareInterface::PreheatingAnswer Run() override {
        HardwareInterface::PressOnButton pressOnButton;
        HardwareInterface::ReleaseOnButton releaseOnButton;
        return remote.Execute(RunnableSequence().Run(pressOnButton).Wait(1000).Run(releaseOnButton).Wait(3000));
    }
};

}

#endif
