/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:52:28 by alexafer          #+#    #+#             */
/*   Updated: 2024/05/17 05:53:51 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#include <stdio.h>
#include <math.h>

// Définir une structure pour le cercle
typedef struct {
	int	x;
	int	y;
    double centerX;
    double centerY;
    double radius;
} Circle;

// Fonction pour calculer le pourcentage d'occupation d'une case par le cercle
double getOccupationPercentage(t_circle circle, double cellX, double cellY) {
    double cellCenterX = cellX;
    double cellCenterY = cellY;
    double distance = sqrt(pow(cellCenterX - circle.centerX, 2) + pow(cellCenterY - circle.centerY, 2));

    if (distance <= circle.radius) {
        return 100; // Le cercle couvre complètement la cellule
    } else if (distance > circle.radius) {
        return 0;   // Le cercle ne touche pas la cellule
    } else {
		printf("ret 50");
        return 50;  // Le cercle couvre partiellement la cellule (approximation)
    }
}
// Fonction pour recalculer la grille en fonction du déplacement du cercle
void recalculateGrid(double newArray[64 * Y][64 * X], double offsetX, double offsetY, t_circle *circle) {
    t_circle newCircle = {X, Y, circle->centerX + offsetX, circle->centerY + offsetY, circle->radius};

    for (int i = 0; i < (64 * Y); i++) {
        for (int j = 0; j < (64 * X); j++) {
            newArray[i][j] = getOccupationPercentage(newCircle, j, i);
        }
    }
	*circle = newCircle;
}


void ft_display_circle(void *mlx_ptr, void *win_ptr, int color, t_circle circle, double array[64 * Y][64 * X])
{
	int	i;
	int	j;

	j = 0;
	while (j < 64 * Y)
	{
		i = 0;
		while (i < 64 * X)
		{
			if (!(array[j][i] == 0.000000))
			{
				mlx_pixel_put(mlx_ptr, win_ptr, i, j, color);
				//printf("array[j][i] == %f\n", array[j][i]);
			}
			//else
			//	printf("array[j][i] == %f\n", array[j][i]);
			i++;
		}
		j++;
	}	
}

int	key_hook(int keycode, t_cub *cub)
{
	if (keycode == 53)
	{
		mlx_destroy_window(cub->mlx_ptr, cub->win_ptr);
		exit (0);
	}
	if (keycode == 13)
	{
		mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
    	recalculateGrid(cub->array, 0, -1, &cub->circle);
		ft_display_circle(cub->mlx_ptr, cub->win_ptr, 0x00FF0000, cub->circle, cub->array);
		
	}
	if (keycode == 0)
	{
		mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
    	recalculateGrid(cub->array, -1, 0, &cub->circle);
		ft_display_circle(cub->mlx_ptr, cub->win_ptr, 0x00FF0000, cub->circle, cub->array);
	
	}
	if (keycode == 1)
	{
		mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
    	recalculateGrid(cub->array, 0, 1, &cub->circle);
		ft_display_circle(cub->mlx_ptr, cub->win_ptr, 0x00FF0000, cub->circle, cub->array);
	}
	if (keycode == 2)
	{
		mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
    	recalculateGrid(cub->array, 1, 0, &cub->circle);
		ft_display_circle(cub->mlx_ptr, cub->win_ptr, 0x00FF0000, cub->circle, cub->array);
	
	}
	printf("keycode : %d\n", keycode);
	return (0);
}

void	ft_run(t_cub *cub)
{
	mlx_clear_window(cub->mlx_ptr, cub->win_ptr);
	ft_display_circle(cub->mlx_ptr, cub->win_ptr, 0x00FF0000, cub->circle, cub->array);
	mlx_key_hook(cub->win_ptr, key_hook, cub);
	mlx_loop(cub->mlx_ptr);
}

int main()
{
	t_cub	cub;

    // Initialiser le cercle centré à la position (1,1) avec un rayon de 1
	t_circle circle = {X, Y, (64 * (X / 2)) + 32, (64 * (Y / 2)) + 32, 100};
	cub.circle = circle;
    // Initialiser le tableau

    // Calculer les valeurs initiales
    recalculateGrid(cub.array, 0, 0, &cub.circle);

    // Afficher la grille initiale
    //printf("Initial Grid:\n");
    //for (int i = 0; i < 64 * Y; i++) {
    //    for (int j = 0; j < 64 * X; j++) {
    //        printf("%f ", array[i][j]);
    //    }
    //    printf("\n");
    //}

    // Déplacer le cercle de 10% vers l'axe X
    double offsetX = 1;
    double offsetY = 1;


	
    // Afficher la nouvelle grille
    //printf("\nGrid after moving 10%% to the right:\n");
    //for (int i = 0; i < 64 * Y; i++) {
    //    for (int j = 0; j < 64 * X; j++) {
    //        printf("%f ", array[i][j/]);
    //    }
    //    printf("\n");
 	cub.mlx_ptr = mlx_init();
	cub.win_ptr = mlx_new_window(cub.mlx_ptr, 64 * X, 64 * Y, "cub3D");   //}
	mlx_do_key_autorepeaton(cub.mlx_ptr);
	ft_run(&cub);
	return (0);
}
