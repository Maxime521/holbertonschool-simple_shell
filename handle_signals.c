#include <stdio.h>
#include <signal.h>
#include <unistd.h>

/**
 * handle_sigint - Signal handler for SIGINT (Ctrl+C).
 * @sig: Signal number.
 */
void handle_sigint(int sig)
{
	(void)sig; /* Unused parameter */
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * setup_signal_handlers - Set up signal handlers.
 */
void setup_signal_handlers(void)
{
	struct sigaction sa;

	sa.sa_handler = handle_sigint;
	sa.sa_flags = SA_RESTART; /* Restart interrupted system calls */
	sigaction(SIGINT, &sa, NULL);
}

