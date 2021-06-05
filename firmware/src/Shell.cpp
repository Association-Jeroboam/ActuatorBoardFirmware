/*
    Copyright (C) 2016 Jonathan Struebel

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

/**
 * @file    common/shellcfg.c
 * @brief   CLI shell config.
 *
 * @addtogroup SHELL
 * @{
 */

#include <stdlib.h>
#include <cstring>
#include "hal.h"
#include "chprintf.h"
#include "shell.h"
#include "BuildConf.hpp"
#include "Logging.hpp"
#include "CanProtocol.hpp"
#include "PliersManager.hpp"


char** endptr;

/*
 * Shell history buffer
 */
char history_buffer[SHELL_MAX_HIST_BUFF];

/*
 * Shell completion buffer
 */
char* completion_buffer[SHELL_MAX_COMPLETIONS];

/*
 * Shell commands
 */

static void cmd_pliers(BaseSequentialStream* chp, int argc, char* argv[]) {
    (void)chp;
    if (argc == 2) {
        enum pliersID id = (enum pliersID)atoi(argv[0]);
        enum pliersState state = (enum pliersState)atoi(argv[1]);
        if(id > PLIERS_REAR_FAR_LEFT){
            Logging::println("Bad ID");
            goto usage;
        }

        if(state > PLIERS_CLOSE){
            Logging::println("Bad state");
            goto usage;
        }

        canFrame_t frame = {
            .ID = CAN_PLIERS_ID,
            .len = CAN_PLIERS_LEN,
        };
        frame.data.pliersData = {
            .plierID = id,
            .state = state,
        };
        PliersManager::instance()->processFrame(frame);
    } else {
        goto usage;
    }
    return;

usage:
    Logging::println("usage:");
    Logging::println("pliers [pliersID] [open/close]");
}

static const ShellCommand commands[] = {
    {"pliers", cmd_pliers},
    {NULL, NULL},
};
/*
 * Shell configuration
 */
ShellConfig shell_cfg = {
    (BaseSequentialStream*)&SHELL_DRIVER,
    commands,
    history_buffer,
    sizeof(history_buffer),
    completion_buffer};

/** @} */
