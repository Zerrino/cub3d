/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 00:35:16 by alexafer          #+#    #+#             */
/*   Updated: 2024/05/17 05:52:11 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../includes/get_next_line.h"
# include "../libft/libft.h"
# ifndef X
# define X 5
# endif

# ifndef Y
# define Y 5
# endif

typedef struct s_circle
{
	int	x;
	int	y;
	double	centerX;
	double	centerY;
	double	radius;
}	t_circle;

typedef struct s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	double	array[64 * Y][64 * X];
	t_circle	circle;
}	t_cub;

#endif
