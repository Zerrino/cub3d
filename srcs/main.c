/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexafer <alexafer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 13:52:28 by alexafer          #+#    #+#             */
/*   Updated: 2024/05/15 04:06:37 by alexafer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


#include <stdio.h>
#include <math.h>

// Définir une structure pour le cercle
typedef struct {
    double centerX;
    double centerY;
    double radius;
} Circle;

// Fonction pour calculer le pourcentage d'occupation d'une case par le cercle
double getOccupationPercentage(Circle circle, double cellX, double cellY) {
    double cellCenterX = cellX + 0.5;
    double cellCenterY = cellY + 0.5;
    double distance = sqrt(pow(cellCenterX - circle.centerX, 2) + pow(cellCenterY - circle.centerY, 2));

    if (distance <= circle.radius - 0.5) {
        return 100; // Le cercle couvre complètement la cellule
    } else if (distance > circle.radius + 0.5) {
        return 0;   // Le cercle ne touche pas la cellule
    } else {
        return 50;  // Le cercle couvre partiellement la cellule (approximation)
    }
}
// Fonction pour recalculer la grille en fonction du déplacement du cercle
void recalculateGrid(double newArray[9][9], double offsetX, double offsetY, Circle circle) {
    Circle newCircle = {circle.centerX + offsetX, circle.centerY + offsetY, circle.radius};

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            newArray[i][j] = getOccupationPercentage(newCircle, i, j);
        }
    }
}

int main() {
    // Initialiser le cercle centré à la position (1,1) avec un rayon de 1
    Circle circle = {1.5, 1.5, 1};

    // Initialiser le tableau
    double array[9][9];

    // Calculer les valeurs initiales
    recalculateGrid(array, 0, 0, circle);

    // Afficher la grille initiale
    printf("Initial Grid:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%f ", array[i][j]);
        }
        printf("\n");
    }

    // Déplacer le cercle de 10% vers l'axe X
    double offsetX = 1;
    double offsetY = 1;

    recalculateGrid(array, offsetX, offsetY, circle);

	
    // Afficher la nouvelle grille
    printf("\nGrid after moving 10%% to the right:\n");
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            printf("%f ", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
