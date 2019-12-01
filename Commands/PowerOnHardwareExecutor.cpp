
#include "PreheatingCommand.hpp"
#include "HardwareExecutor/HardwareExecutor.hpp"

class PowerOnCommandHardwareExecutor : public PreheatingCommand, IPreheatingCommandExecutor {
public:
    PreheatingAnswer Run() {
        return Execute(RunnableSequence().Run(pressOnButton).Wait(3000));
    }
};
