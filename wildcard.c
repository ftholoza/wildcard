/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:33:45 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/24 18:32:49 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcard.h"

t_dlist	*get_files(void)
{
	DIR				*dir_fd;
	struct dirent	*dir;
	char			*name_dir;
	t_dlist			*files;

	files = NULL;
	name_dir = pwd(2);
	if (!name_dir)
		return (NULL);
	dir_fd = opendir(name_dir);
	free(name_dir);
	if (dir_fd == NULL)
	{
		perror(name_dir);
		return (NULL);
	}
	dir = readdir(dir_fd);
	while (dir != NULL)
	{
		files = add_element(dir->d_name, files);
		dir = readdir(dir_fd);
	}
	closedir(dir_fd);
	return (files);
}

t_wildcard	*init_wildcard(char *patern, char *name)
{
	t_wildcard	*data;

	data = malloc(sizeof(*data));
	if (!data)
		return (data);
	data->i = 0;
	data->j = 0;
	data->match = 0;
	data->start_patern = -1;
	data->patern = patern;
	data->name = name;
	return (data);
}

int	wildcard_check(t_wildcard *data)
{
	if (data->name[data->j] && data->patern[data->i]
		&& data->patern[data->i] == data->name[data->j])
	{
		data->i++;
		data->j++;
		return (1);
	}
	else if (data->patern[data->i] && data->name[data->j]
		&& data->patern[data->i] == '*')
	{
		data->start_patern = data->i;
		data->match = data->j;
		data->i++;
		return (1);
	}
	else if (data->patern[data->i] && data->name[data->j]
		&& data->start_patern != -1)
	{
		data->i = data->start_patern + 1;
		data->match++;
		data->j = data->match;
		return (1);
	}
	else
		return (0);
}

int	is_match(char *patern, char *name)
{
	t_wildcard	*data;
	int			temp;

	data = init_wildcard(patern, name);
	while (name[data->j])
	{
		if (!wildcard_check(data))
		{
			free(data);
			return (0);
		}
	}
	while (patern[data->i] == '*')
		data->i++;
	temp = data->i;
	free(data);
	return (temp / ft_strlen(patern));
}

t_dlist	*wildcard(char *patern)
{
	t_dlist			*files;
	t_dlist			*temp;
	t_dlist			*temp2;

	files = get_files();
	temp = files;
	if (!files)
		return (NULL);
	while (temp != NULL)
	{
		if (!is_match(patern, temp->data))
		{
			temp2 = temp;
			temp = temp->next;
			ft_dl_remove_from(&files, temp2, del);
		}
		else
		{
			temp = temp->next;
		}
	}
	return (files);
}

/*int	main(int argc, char **argv)
{
	t_dlist	*files;

	if (argc != 2)
		return (0);
	files = wildcard(argv[1]);
	if (!files)
		return (0);
	print_dlist(files);
	ft_dl_clear(&files, del);
}*/