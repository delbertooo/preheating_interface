
#include "PreheatingCommand.hpp"
#include "HardwareExecutor/HardwareExecutor.hpp"
#include "../actions.hpp"

class PowerOnCommandHardwareExecutor : public PreheatingCommand, IPreheatingCommandExecutor {
public:
    PreheatingAnswer Run() {
        PressOnButton pressOnButton;
        ReleaseOnButton releaseOnButton;
        return Execute(RunnableSequence().Run(pressOnButton).Wait(1000).Run(releaseOnButton).Wait(3000));
    }
};
