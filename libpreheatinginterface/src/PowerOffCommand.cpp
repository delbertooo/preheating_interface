#include "LibPreheatingInterface.hpp"

using namespace LibPreheatingInterface;

PowerOffCommand::PowerOffCommand(CommandHelper &helper) : AbstractCommand(helper) {}


struct pressOff : public LibScheduling::Runnable
{
        LibPreheatingInterface::PreheatingRemote &remote;
        pressOff(LibPreheatingInterface::PreheatingRemote &remote) : remote(remote) {}
        void operator()() const override
        {
                remote.PressOff();
        }
};

struct releaseOff : public LibScheduling::Runnable
{
        LibPreheatingInterface::PreheatingRemote &remote;
        releaseOff(LibPreheatingInterface::PreheatingRemote &remote) : remote(remote) {}
        void operator()() const override
        {
                remote.ReleaseOff();
        }
};

PowerOffResult PowerOffCommand::PowerOff() {
    return helper.Run(LibScheduling::RunnableSequence{}
        // .Run([this]{ remote.PressOff(); })
        .Run(pressOff{remote})
        .Wait(1000)
        // .Run([this]{ remote.ReleaseOff(); })
        .Run(releaseOff{remote})
        .Wait(3000));
}
