#include "executor.h"
#include "utils.h"

bool	save_std_io(int saved_std_io[2])
{
	saved_std_io[0] = dup(STDIN_FILENO);
	saved_std_io[1] = dup(STDOUT_FILENO);
	if (saved_std_io[0] == -1 || saved_std_io[1] == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(NULL);
		safe_close(&saved_std_io[0]);
		safe_close(&saved_std_io[1]);
		return (false);
	}
	return (true);
}

bool	redirect_scmd_io(t_shell *shell, int *read_fd, int *write_fd)
{
	bool	ret;

	ret = true;
	if (dup2(*read_fd, STDIN_FILENO) == -1 || \
		dup2(*write_fd, STDOUT_FILENO) == -1)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(NULL);
		ret = false;
	}
	if (shell->subshell_level != 0)
	{
		safe_close_all_pipes(shell);
		safe_close(read_fd);
		safe_close(write_fd);
	}
	return (ret);
}

bool	redirect_subshell_io(t_shell *shell, t_cmd_table *cmd_table)
{
	int		read_fd;
	int		write_fd;
	bool	ret;

	ret = true;
	read_fd = -1;
	write_fd = -1;
	if (!handle_io_redirect(shell, &read_fd, &write_fd, cmd_table->io_red_list))
		ret = false;
	else if ((read_fd != -1 && dup2(read_fd, STDIN_FILENO) == -1) || \
		(write_fd != -1 && dup2(write_fd, STDOUT_FILENO) == -1))
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(NULL);
		shell->exit_code = GENERAL_ERROR;
		ret = false;
	}
	safe_close(&read_fd);
	safe_close(&write_fd);
	return (ret);
}

bool	restore_std_io(int saved_std_io[2])
{
	bool	error;

	error = false;
	if (saved_std_io[0] != -1)
		if (dup2(saved_std_io[0], STDIN_FILENO) == -1)
			error = true;
	if (!error && saved_std_io[1] != -1)
		if (dup2(saved_std_io[1], STDOUT_FILENO) == -1)
			error = true;
	if (error)
	{
		ft_dprintf(STDERR_FILENO, "%s: ", PROGRAM_NAME);
		perror(NULL);
		return (false);
	}
	return (true);
}
