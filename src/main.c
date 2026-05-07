/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 13:49:28 by kel               #+#    #+#             */
/*   Updated: 2026/05/07 10:06:47 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int ac, char *av[])
{
	t_cub	*cub;

	if (ac != 2)
		simple_error_exit(ERR_ARGS);
	cub = ft_calloc(1, sizeof(t_cub));
	if (!cub)
		simple_error_exit(ERR_MALLOC);
	if (parse_n_init_map(cub, av[1]))
	{
		clean_cub3d(cub);
		free(cub);
		exit(EXIT_FAILURE);
	}
	// Start Render Loop
	// clean up
	clean_cub3d(cub);
	free(cub);
	return (0);
}
