//
// Created by gorod on 17.04.2026.
//

#ifndef RC_VEHICLE_TERMINAL_COMPLETIONCONTROLLER_H
#define RC_VEHICLE_TERMINAL_COMPLETIONCONTROLLER_H
#include "IUpdateable.h"
#include "LocalCommandsListener.h"


class CompletionController : public IUpdateable, LocalCommandsListener
{

public:
    CompletionController();
    ~CompletionController() override;
    void update(float tpf) override;
    void complete() override;
    void onCommandReceived(const LocalCommand& global_command) override;
    void attachCompletionFlagData(bool* completeFlag)
    {
        this->completeFlagInputLevel = completeFlag;
    }

private:
    bool* completeFlagInputLevel = nullptr;
};


#endif //RC_VEHICLE_TERMINAL_COMPLETIONCONTROLLER_H