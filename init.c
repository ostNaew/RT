/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ajaehaer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:37:59 by ajaehaer          #+#    #+#             */
/*   Updated: 2019/03/30 16:31:23 by ejommy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "engine_render.h"
#include "init.h"

static void			validate_data(t_init_data data, int *status)
{
	if (data.master > 2)
		*status = -1;
	else if (data.port == -1)
		*status = -1;
	else if ((data.master & (1 << 1)) && data.host == NULL)
		*status = -1;
	else if (data.map == NULL)
		*status = -1;
}

static int			process_option(t_init_data *data, int *arg_num, char **argv)
{
	if (ft_strequ(argv[*arg_num], "-m"))
		data->master |= (1 << 0);
	else if (ft_strequ(argv[*arg_num], "-p") && data->port == 0)
	{
		data->port = ft_atoi(argv[*arg_num + 1]);
		data->port = data->port == 0 ? -1 : data->port;
		*arg_num += 1;
	}
	else if (ft_strequ(argv[*arg_num], "-host"))
	{
		data->host = ft_strdup(argv[*arg_num + 1]);
		*arg_num += 1;
	}
	else if (ft_strequ(argv[*arg_num], "-s"))
		data->master |= (1 << 1);
	else
		return (0);
	return (1);
}

static t_init_data	process_args(int argc, char **argv, int *status)
{
	t_init_data	res;
	int			i;

	i = 0;
	*status = 0;
	res = (t_init_data){NULL, NULL, 0, 0};
	while (++i < argc && *status == 0)
	{
		if (process_option(&res, &i, argv))
			continue;
		else if (res.map == NULL)
			res.map = ft_strdup(argv[i]);
		else
			*status = -1;
	}
	if (*status == 0)
		validate_data(res, status);
	return (res);
}

static void			initial_render(t_render *render, char **argv)
{
	char	*sym;

	sym = ft_strrchr(argv[0], '/');
	render->location = ft_strsub(argv[0], 0, sym - argv[0]);
	render->lights = NULL;
	render->materials = NULL;
	render->images = NULL;
	render->map_str = NULL;
	render->scene.objects = NULL;
	render->render_needed = 1;
	render->path_tracing = 0;
	render->working = 0;
	render->task = NULL;
	render->path_tracing = 0;
	render->window_width = WINDOW_WIDTH;
	render->window_height = WINDOW_HEIGHT;
	render->autosave = 0;
	render->mode = STANDALONE;
}

int					init(t_render *render, int argc, char **argv)
{
	t_json		json;
	t_init_data	data;
	int			status;

	initial_render(render, argv);
	data = process_args(argc, argv, &status);
	json = new_json();
	if (status == 0 && (render->map_str = read_map(data.map)))
	{
		json = json_parse(render->map_str);
		if (json.type != JSON_OBJECT || process_map(render, json, 1))
			status = -3;
	}
	else
		status = -4;
	if (!status && data.master != 0)
	{
		render->mode = (data.master & (1 << 1)) ? SLAVE : MASTER;
		init_network(render, (data.master & 1) ? NULL : data.host, data.port);
	}
	free(data.host);
	free(data.map);
	json_destroy(&json);
	return (status);
}
