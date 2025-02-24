#pragma once

#include <linux/poll.h>
#include <linux/interrupt.h>
#include "../inc/config.h"

int send_msg(char* buffer);
static irqreturn_t send_signal(int signal_number);
static void get_data(char* buffer, int& signal, int& data);
