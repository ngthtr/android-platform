#include "../inc/signal_handler.h"
#include <linux/kernel.h>
#include <linux/string.h>

int app_pid = 0;
struct task_struct* task;

static int SIGNAL_1 = 123;
static int SIGNAL_2 = 456;


int send_msg(char* buffer)
{
	int signal;
	int data;
	get_data(buffer, signal, data);
    printk("%s: with buffer = %s => signal = %d, data = %d\n", TAG, buffer, signal, data);

    if (signal == SIGNAL_1)
    {
        send_signal(44);
    } else
    if (signal == SIGNAL_2)
    {

    }
    return SUCCESS_STATUS;
}

irqreturn_t send_signal(int signal_number)
{
	printk("%s: Interrupt was triggered and ISR was called!, app_pid = %d\n", TAG, app_pid);
	
	if(task == NULL) 
	{
		printk("%s: Task is null\n", TAG);
		return IRQ_HANDLED;
	}
	
	struct siginfo info;
	memset(&info, 0, sizeof(info));
	info.si_signo = signal_number;
	info.si_code = SI_QUEUE;

	/* Send the signal */
	if(send_sig_info(SIGUSR1, (struct kernel_siginfo *) &info, task) < 0)
	{
		printk("%s: Error sending signal\n", TAG);
	}
	return IRQ_HANDLED;
}

void get_data(char* buffer, int& signal, int& data)
{
	char* signal_chr = buffer;
    char* data_chr = strchr(buffer, '_'); 
    if (data_chr != NULL) {
        *data_chr = '\0';
        data_chr++;
    }
    sscanf(signal_chr, "%d", &signal);
    sscanf(data_chr, "%d", &data);
}