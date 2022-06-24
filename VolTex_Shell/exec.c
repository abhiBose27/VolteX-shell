#include "headers.h"

int exec(char **parameters, int *nb_par)
{
	if (strcmp(parameters[0], "exit") == 0)
		exit(0);
	if (strcmp(parameters[0], commands[0]) == 0 || strcmp(parameters[0], default_commands[0]) == 0)
	{
		char *path = pwd(*nb_par);
		printf("%s\n", path);
		return 0;
	}
	if (strcmp(parameters[0], commands[1]) == 0 || strcmp(parameters[0], default_commands[1]) == 0)
	{
		helppage(*nb_par, parameters, commands, default_commands);
		return 0;
	}
	if (strcmp(parameters[0], commands[2]) == 0 || strcmp(parameters[0], default_commands[2]) == 0)
	{
		create_dir(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[3]) == 0 || strcmp(parameters[0], default_commands[3]) == 0)
	{
		touch(parameters, *nb_par);
		return 0;
	}
	if (strcmp(parameters[0], commands[4]) == 0 || strcmp(parameters[0], default_commands[4]) == 0)
	{
		mv(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[5]) == 0 || strcmp(parameters[0], default_commands[5]) == 0)
	{
		remove_dir(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[6]) == 0 || strcmp(parameters[0], default_commands[6]) == 0)
	{
		change_color(parameters[1]);
		return 0;
	}
	if (strcmp(parameters[0], commands[7]) == 0 || strcmp(parameters[0], default_commands[7]) == 0)
	{
		clean(*nb_par);
		return 0;
	}
	if (strcmp(parameters[0], commands[8]) == 0 || strcmp(parameters[0], default_commands[8]) == 0)
	{
		_tree(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[9]) == 0 || strcmp(parameters[0], default_commands[9]) == 0)
	{
		_delete(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[10]) == 0 || strcmp(parameters[0], default_commands[10]) == 0)
	{
		_cat(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[11]) == 0 || strcmp(parameters[0], default_commands[11]) == 0)
	{
		_ls(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[12]) == 0 || strcmp(parameters[0], default_commands[12]) == 0)
	{
		cd(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[13]) == 0 || strcmp(parameters[0], default_commands[13]) == 0)
	{
		_echo(parameters, *nb_par);
		return 0;
	}
	if (strcmp(parameters[0], commands[14]) == 0 || strcmp(parameters[0], default_commands[14]) == 0)
	{
		bg(parameters, *nb_par);
		return 0;
	}
	if (strcmp(parameters[0], commands[15]) == 0 || strcmp(parameters[0], default_commands[15]) == 0)
	{
		sleep_fun(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[16]) == 0 || strcmp(parameters[0], default_commands[16]) == 0)
	{
		print_jobs(back_count, back);
		return 0;
	}
	if (strcmp(parameters[0], commands[17]) == 0 || strcmp(parameters[0], default_commands[17]) == 0)
	{
		grep(*nb_par, parameters);
		return 0;
	}

	if (strcmp(parameters[0], commands[18]) == 0 || strcmp(parameters[0], default_commands[18]) == 0)
	{
		calc(atoi(parameters[1]));
		return 0;
	}
	if (strcmp(parameters[0], commands[19]) == 0 || strcmp(parameters[0], default_commands[19]) == 0)
	{
		get_host_name(*nb_par, parameters);
		return 0;
	}
	if (strcmp(parameters[0], commands[20]) == 0 || strcmp(parameters[0], default_commands[20]) == 0)
	{
		alias(*nb_par, parameters, commands);
		return 0;
	}

	if (strcmp(parameters[0], commands[21]) == 0 || strcmp(parameters[0], default_commands[21]) == 0)
	{
		// strcat(dirname, "/history");
		remove("/tmp/.history");
		exit(1);
	}

	if (strcmp(parameters[0], commands[22]) == 0 || strcmp(parameters[0], default_commands[22]) == 0)
	{
		set_env(parameters, *nb_par);
		return 0;
	}

	if (strcmp(parameters[0], commands[23]) == 0 || strcmp(parameters[0], default_commands[23]) == 0)
	{
		unset_env(parameters, *nb_par);
		return 0;
	}

	if (strcmp(parameters[0], commands[24]) == 0 || strcmp(parameters[0], default_commands[24]) == 0)
	{
		play(*nb_par);
		return 0;
	}

	if (strcmp(parameters[0], commands[25]) == 0 || strcmp(parameters[0], default_commands[25]) == 0)
	{
		SpaceInvaders(*nb_par);
		return 0;
	}
	if (strcmp(parameters[0], commands[26]) == 0 || strcmp(parameters[0], default_commands[26]) == 0)
	{
		history(*nb_par);
		return 0;
	}
	return 1;
}