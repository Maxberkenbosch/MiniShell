#include <unistd.h>
#include "minishell.h"

void	ft_dupstds(int in, int out)
{
	if (dup2(in, STDIN_FILENO) < 0 || \
		dup2(out, STDOUT_FILENO) < 0)
		error_handle("dup2");
}
