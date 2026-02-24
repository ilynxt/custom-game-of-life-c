 /**
 Jeu de la vie : 
	les cellules mortes restent mortes
	les cellules vivantes actualisent leur compteur de vie avec la somme de leurs voisins
	les cellules vivantes meurent si leur compteur de vie actualisé dépasse strictement un seuil
	les cellules survivantes peuvent incrémenter/décrémenter leur compteur de vie
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

// Prototypes des fonctions
void lecture_plateau(int taille, int plateau[taille][taille]);
void affichage_plateau(int taille, int plateau[taille][taille]);
void copie_plateau(int taille, int dest[taille][taille], int src[taille][taille]);
void extinction_population(int taille, int plateau[taille][taille], int *retour);
void invariance_population(int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille], int *retour);
void mise_a_jour_compteur_vie(int i, int j, int seuil, int n, int taille, int plateau[taille][taille]);
void mise_a_jour_des_coins_compteurs_vie(int seuil, int n, int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille]);
void mise_a_jour_des_bords_compteurs_vie(int seuil, int n, int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille]);
void mise_a_jour_des_8_compteurs_vie(int seuil, int n, int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille]);
void nouvelle_population(int seuil, int n, int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille]);
void evolution(int taille, int seuil, int iterations, int n, int plateau[taille][taille], int *retour);

void lecture_plateau(int taille, int plateau[taille][taille]){
	for (int i = 0; i < taille; i++){
		for (int j = 0; j < taille; j++){
			scanf("%1d", &plateau[i][j]);
		}
	}
}

void affichage_plateau(int taille, int plateau[taille][taille]){
	for (int i = 0; i < taille; i++){
		for (int j = 0; j < taille; j++){
			printf("%1d ", plateau[i][j]);
		}
		printf("\n");
	}
	printf("_________________________________________________________________________\n");
}

// Dans string.h, la déclaration de la fonction de copie d'une chaîne source src dans une chaine destination dest
// char *strcpy(char *dest, const char *src);
// ON FAIT PAREIL!
void copie_plateau(int taille, int dest[taille][taille], int src[taille][taille]){
	for (int i = 0; i < taille; i++){
		for (int j = 0; j < taille; j++){
			dest[i][j] = src[i][j];
		}
	}
}

void extinction_population(int taille, int plateau[taille][taille], int *retour){
	*retour = 1; // on part du principe que toutes les cellules sont mortes
	for (int i = 0; i < taille; i++){
		for (int j = 0; j < taille; j++){
			if (plateau[i][j] != 0){///cellule vivantes
				*retour = 0; 
				return;
			}
		}
	}
}

void invariance_population(int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille], int *retour){
	*retour = 1; // on part du principe qu'il n'y a pas de changement
	for (int i = 0; i < taille; i++){
		for (int j = 0; j < taille; j++){
			if (plateau[i][j] != plateau_iteratif[i][j]){
				*retour = 0; // il y a un changement
				return;
			}
		}
	}
}
// n incrémentation/décrémentation du compteur de vie
void mise_a_jour_compteur_vie(int i, int j, int seuil, int n, int taille, int plateau[taille][taille]){
	
	// mort de la cellule 
	if (plateau[i][j] > seuil){
		plateau[i][j] = 0;
	}
	else {
		// survie de la cellule
		// conserve son compteur de vie : n = 0
		// ou suit une règle de mise à jour supplémentaire 
		// si l’on souhaite la faire évoluer autrement, 
		// par exemple en incrémentant/décrémentant légèrement le compteur).
		// donc si plateau[i][j] = 0 et n > 0 alors une cellule morte devient vivante
		plateau[i][j] = plateau[i][j] + n;
	}
}

// calcul en fonction des 3 voisins des 4 coins
// n incrémentation/décrémentation du compteur de vie
void mise_a_jour_des_coins_compteurs_vie(int seuil, int n, int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille]){
	// Coin en haut à gauche [0][0]
	// une cellule morte ne renâit pas
	if (plateau_iteratif[0][0] != 0){
		plateau_iteratif[0][0] = plateau[0][1] + plateau[1][1] + plateau[1][0];
		mise_a_jour_compteur_vie(0, 0, seuil, n, taille, plateau_iteratif);
	}
		
	// Coin en haut à droite [0][taille-1] 
	if (plateau_iteratif[0][taille-1]){
		plateau_iteratif[0][taille-1]  = plateau[0][taille-2] + plateau[1][taille-2] + plateau[1][taille-1];
		mise_a_jour_compteur_vie(0, taille-1, seuil, n, taille, plateau_iteratif);
	}
	
	// Coin en bas à gauche [taille-1][0]
	if (plateau_iteratif[taille-1][0]){
		plateau_iteratif[taille-1][0]  = plateau[taille-2][0] + plateau[taille-2][1] + plateau[taille-1][1];
		mise_a_jour_compteur_vie(taille-1, 0, seuil, n, taille, plateau_iteratif);
	}

	// Coin en bas à droite [taille-1][taille-1]
	if (plateau_iteratif[taille-1][taille-1] != 0){
		plateau_iteratif[taille-1][taille-1] = plateau[taille-2][taille-1] + plateau[taille-2][taille-2] + plateau[taille-1][taille-2];
		mise_a_jour_compteur_vie(taille-1, taille-1, seuil, n, taille, plateau_iteratif);
	}
}

// calcul en fonction des (taille - 2) voisins des 4 bords sans les coins
// n incrémentation/décrémentation du compteur de vie
void mise_a_jour_des_bords_compteurs_vie(int seuil, int n, int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille]){
	// Bord haut : ligne 0
	for (int j = 1; j < taille-1; j++){
		// une cellule morte ne renâit pas
		if (plateau_iteratif[0][j] == 0){
			continue;
		}
		plateau_iteratif[0][j] = plateau[0][j-1] + plateau[0][j+1] // ligne courante
						+ plateau[1][j-1] + plateau[1][j] + plateau[1][j+1]; // ligne du dessous
		mise_a_jour_compteur_vie(0, j, seuil, n, taille, plateau_iteratif);
	}
	
	// Bord bas : ligne taille-1
	for (int j = 1; j < taille-1; j++){
		// une cellule morte ne renâit pas
		if (plateau_iteratif[taille-1][j] == 0){
			continue;
		}
		plateau_iteratif[taille-1][j] =  plateau[taille-2][j-1] + plateau[taille-2][j] + plateau[taille-2][j+1]	// ligne du dessus
								+  plateau[taille-1][j-1] + plateau[taille-1][j+1];  // ligne courante
		mise_a_jour_compteur_vie(taille-1, j, seuil, n, taille, plateau_iteratif);
	}
	
	// Bord gauche : colonne 0
	for (int i = 1; i < taille-1; i++){
		// une cellule morte ne renâit pas
		if (plateau_iteratif[i][0] == 0){
			continue;
		}
		plateau_iteratif[i][0] = plateau[i-1][0] + plateau[i+1][0] 				// colonne courante
						+ plateau[i-1][1] + plateau[i][1] + plateau[i+1][1]; 	// colonne à droite
		mise_a_jour_compteur_vie(i, 0, seuil, n, taille, plateau_iteratif);
	}
	
	// Bord droite : colonne taille-1
	for (int i = 1; i < taille-1; i++){
		// une cellule morte ne renâit pas
		if (plateau_iteratif[i][taille-1] == 0){
			continue;
		}
		plateau_iteratif[i][taille-1] = plateau[i-1][taille-2] + plateau[i][taille-2] + plateau[i+1][taille-2] 	// colonne à gauche
								+ plateau[i-1][taille-1] + plateau[i+1][taille-1]; // colonne courante
		mise_a_jour_compteur_vie(i, taille-1, seuil, n, taille, plateau_iteratif);
	}
}

// ni les coins ni les bords, l'intérieur du plateau [taille – 2][taille – 2]
// calcul en fonction des 8 voisins
// n incrémentation/décrémentation du compteur de vie
void mise_a_jour_des_8_compteurs_vie(int seuil, int n, int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille]){
	for (int i = 1; i < taille-1; i++){
		for (int j = 1; j < taille-1; j++) {
			// une cellule morte ne renâit pas
			if (plateau_iteratif[i][j] == 0){
				continue; // LE BUG ETAIT LA avec un return à la place du continue
			}
			plateau_iteratif[i][j] = plateau[i-1][j-1] + plateau[i-1][j] + plateau[i-1][j+1]	// ligne du dessus
							+  plateau[i][j-1] + plateau[i][j+1]  								// ligne courante
							+  plateau[i+1][j-1] + plateau[i+1][j] + plateau[i+1][j+1];			// ligne du dessous
			mise_a_jour_compteur_vie(i, j, seuil, n, taille, plateau_iteratif);	
		}
	}
}
void nouvelle_population(int seuil, int n, int taille, int plateau[taille][taille], int plateau_iteratif[taille][taille]){
	mise_a_jour_des_coins_compteurs_vie(seuil, n, taille, plateau, plateau_iteratif);
	mise_a_jour_des_bords_compteurs_vie(seuil, n, taille, plateau, plateau_iteratif);
	mise_a_jour_des_8_compteurs_vie(seuil, n, taille, plateau, plateau_iteratif);
	copie_plateau(taille, plateau, plateau_iteratif);
}

void evolution(int taille, int seuil, int iterations, int n, int plateau[taille][taille], int *retour){
	int plateau_iteratif[taille][taille];
	copie_plateau(taille, plateau_iteratif, plateau);
	
	for (int i = 0; i < iterations; i++){
		nouvelle_population(seuil, n, taille, plateau, plateau_iteratif);
		affichage_plateau(taille, plateau);
		
		int extinction;
		extinction_population(taille, plateau, &extinction);
		if (extinction == 1) {
			*retour = 1;
			return;
		}
		
		int invariance;
		if (i != 0) {
			invariance_population(taille, plateau, plateau_iteratif, &invariance);
			if (invariance == 1) {
				*retour = 2;
				return;
			}
		}
	}
	*retour = 0;
}

// FICHIERS
int main() {
	int taille = 0;
	int seuil = 0;
	int iterations = 0;
	
	scanf("%d", &taille);
	scanf("%d", &seuil);
	scanf("%d", &iterations);
	
	int plateau[taille][taille];
	lecture_plateau(taille, plateau);
	printf("_________________________________________________________________________\n");
	affichage_plateau(taille, plateau);
	
	int n = 0; // n incrémentation/décrémentation du compteur de vie
	int k;
    evolution(taille, seuil, iterations, n, plateau, &k);
	if (k == 1) {
		printf("Jeu de la vie terminé par extinction de la population \n");
	} else if (k == 2) {
		printf("Jeu de la vie terminé car le plateau devient invariant (aucune cellule n'est modifiée) \n");
	} else {
		printf("Jeu de la vie terminé au bout de %d\n", iterations);
	}
	
	return 0;
}