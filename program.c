#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef char string[80];

// Structure qui represente un etudiant avec ses infos et ses notes
struct Etudiant{
    string nom;
    string prenom;
    double notemaths;
    double notealgo;
    double notebd;
    double moyenne;   // calculee automatiquement a partir des 3 notes
};

// Le tableau qui contient tous les etudiants (50 max)
struct Etudiant etudiant[50];
int nb_etudiant = 0;  // on commence avec 0 etudiant bien sur

// Affiche toutes les infos d'un etudiant de facon lisible
void AFFICHE_ETU(struct Etudiant e){
    printf("NOM     : %s\n", e.nom);
    printf("PRENOM  : %s\n", e.prenom);
    printf("============Notes==========\n");
    printf("MATHS   : %.2f\n", e.notemaths);
    printf("ALGO    : %.2f\n", e.notealgo);
    printf("BDD     : %.2f\n", e.notebd);
    printf("===========Moyenne=========\n");
    printf("MOYENNE : %.2f\n\n", e.moyenne);
}

// Ouvre le fichier, lit chaque ligne et remplit le tableau d'etudiants
// Si le fichier n'existe pas, on previent l'utilisateur et on arrete
void charger_fichier(char* nomfichier){
    FILE *fichier = fopen(nomfichier, "r");
    if (fichier == NULL){
        printf("fichier non trouve\n");
        return;
    }
    // on lit 5 valeurs par ligne : nom prenom note1 note2 note3
    while (fscanf(fichier, "%s %s %lf %lf %lf",
        etudiant[nb_etudiant].nom,
        etudiant[nb_etudiant].prenom,
        &etudiant[nb_etudiant].notemaths,
        &etudiant[nb_etudiant].notealgo,
        &etudiant[nb_etudiant].notebd) == 5){
            // on calcule la moyenne des 3 notes directement
            etudiant[nb_etudiant].moyenne = (etudiant[nb_etudiant].notemaths +
                                             etudiant[nb_etudiant].notealgo +
                                             etudiant[nb_etudiant].notebd) / 3;
            nb_etudiant++;
    }
    fclose(fichier);
    printf("nombre des etudiants : %d\n", nb_etudiant);
}

// Additionne toutes les moyennes et divise par le nombre d'etudiants
double Moyenne_classe(){
    double M = 0;
    for(int i = 0; i < nb_etudiant; i++)
        M += etudiant[i].moyenne;
    return M / nb_etudiant;
}

// Parcourt le tableau pour trouver le meilleur et le moins bon
// On suppose au depart que le premier etudiant est les deux a la fois
void meilleur_moins_bon_etu(){
    double max = etudiant[0].moyenne;
    double min = etudiant[0].moyenne;
    int INDEXMIN = 0, INDEXMAX = 0;
    for(int i = 0; i < nb_etudiant; i++){
        if(etudiant[i].moyenne < min){ min = etudiant[i].moyenne; INDEXMIN = i; }
        if(etudiant[i].moyenne > max){ max = etudiant[i].moyenne; INDEXMAX = i; }
    }
    printf("Le moins bon : %s %s (%.2f)\n", etudiant[INDEXMIN].nom, etudiant[INDEXMIN].prenom, min);
    printf("Le meilleur  : %s %s (%.2f)\n", etudiant[INDEXMAX].nom, etudiant[INDEXMAX].prenom, max);
}

// Recherche simple : on parcourt du debut jusqu'a trouver le nom
// Pas besoin que le tableau soit trie, ca marche toujours
void recherche_nom_sequentielle(char* nom){
    bool trouvee = false;
    int i = 0;
    while((i < nb_etudiant) && !trouvee){
        if(strcmp(nom, etudiant[i].nom) == 0)
            trouvee = true;
        else
            i++;
    }
    if(trouvee) AFFICHE_ETU(etudiant[i]);
    else printf("Etudiant non trouve\n");
}

// Tri par insertion : on prend chaque etudiant et on le place
// au bon endroit selon sa moyenne (du plus haut au plus bas)
void tri_insertion_dec(){
    for(int i = 1; i < nb_etudiant; i++){
        struct Etudiant temp = etudiant[i];
        int j = i - 1;
        while(j >= 0 && etudiant[j].moyenne < temp.moyenne){
            etudiant[j+1] = etudiant[j];
            j--;
        }
        etudiant[j+1] = temp;
    }
}

// Meme principe que le tri par moyenne mais cette fois
// on trie par ordre alphabetique grace a strcmp
void tri_nom_alphabetique(){
    for(int i = 1; i < nb_etudiant; i++){
        struct Etudiant temp = etudiant[i];
        int j = i - 1;
        while(j >= 0 && strcmp(etudiant[j].nom, temp.nom) > 0){
            etudiant[j+1] = etudiant[j];
            j--;
        }
        etudiant[j+1] = temp;
    }
}

// Recherche dichotomique : beaucoup plus rapide que la sequentielle
// ATTENTION : le tableau doit etre trie par nom avant d'appeler cette fonction !
// On coupe le tableau en deux a chaque etape jusqu'a trouver le nom
void recherche_dichotomique(char* nom){
    int gauche = 0, droite = nb_etudiant - 1;
    bool trouvee = false;
    while(gauche <= droite && !trouvee){
        int milieu = (gauche + droite) / 2;
        int cmp = strcmp(nom, etudiant[milieu].nom);
        if(cmp == 0){ trouvee = true; AFFICHE_ETU(etudiant[milieu]); }
        else if(cmp > 0) gauche = milieu + 1;  // on cherche a droite
        else droite = milieu - 1;               // on cherche a gauche
    }
    if(!trouvee) printf("Etudiant non trouve\n");
}

int main(){
    // on charge le fichier une seule fois au demarrage
    charger_fichier("fichier.txt");

    int choix;
    char nom[80];

    do {
        printf("\n===== MENU =====\n");
        printf("1. Afficher tous les etudiants\n");
        printf("2. Moyenne de la classe\n");
        printf("3. Meilleur et moins bon etudiant\n");
        printf("4. Recherche sequentielle par nom\n");
        printf("5. Tri par moyenne decroissante\n");
        printf("6. Tri alphabetique + recherche dichotomique\n");
        printf("0. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if(choix == 1){
            // on affiche tout le monde
            for(int i = 0; i < nb_etudiant; i++)
                AFFICHE_ETU(etudiant[i]);
        }
        else if(choix == 2){
            printf("moyenne de la classe : %.2f\n", Moyenne_classe());
        }
        else if(choix == 3){
            meilleur_moins_bon_etu();
        }
        else if(choix == 4){
            // on demande le nom et on lance la recherche
            printf("entrez le nom : ");
            scanf("%s", nom);
            recherche_nom_sequentielle(nom);
        }
        else if(choix == 5){
            tri_insertion_dec();
            printf("Tri par moyenne effectue !\n");
            for(int i = 0; i < nb_etudiant; i++)
                AFFICHE_ETU(etudiant[i]);
        }
        else if(choix == 6){
            // on trie d'abord par nom sinon la dichotomique ne marche pas !
            tri_nom_alphabetique();
            printf("Entrez le nom a rechercher : ");
            scanf("%s", nom);
            recherche_dichotomique(nom);
        }
        else if(choix == 0){
            printf("au revoir!\n");
        }
        else{
            printf("choix invalide\n");
        }

    } while(choix != 0);
    return 0;
}