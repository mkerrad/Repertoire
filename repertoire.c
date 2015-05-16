#include <stdio.h>
#include <string.h>

struct tcontact
{
    char nom[30];
    char prenom[30];
    char adresse[50];
    char CP[30];
    char ville[30];
    char admail[30];
    char numtel[30];
};

void ajout(struct tcontact tab[100],int *nbelem);
void affichage(struct tcontact tab[100],int indice);
void recherche(struct tcontact tab[100],int nbelem,int *numcontact);
void modif(struct tcontact tab[100],int nbelem);
void suppr(struct tcontact tab[100],int *nbelem);

int main()
{
    FILE *fichier;
    struct tcontact tab[100];
    int nbelem,choix,i,numcontact,trouve = 0;

    do
    {
        choix = 6; // choix initialise a 6 afin de pouvoir rentrer dans la boucle
        printf("Bienvenue dans votre repertoire : \n\n0- Afficher les contacts\n\n1- Saisie d'un contact\n\n2- Recherche d'un contact\n\n3- Modification d'un contact\n\n4- Suppresion d'un contact\n\n5- Quitter");
        printf("\n\n"); // affichage du menu
        fflush(stdin);
        scanf("%d",&choix);
        while (choix != 0 && choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5)
        {
            printf("Erreur de saisie, veuillez entrer une valeur correcte : ");
            fflush(stdin);
            scanf("%d",&choix);
        } // gestion des erreurs  de saisie pour le choix des options
        switch (choix) // gestion des differents cas de choix
        {
            case 0:
            fichier = fopen ("Repertoire.txt","r"); // ouverture du fichier en mode lecture
            i = 0;
            if (fichier != NULL && i == 0 && trouve == 0) // trouve booleen permettant de determiner la fin de lecture des contacts
            {
                while (fgetc(fichier) != EOF) // boucle de lecture et de recuperation des contacts du fichier "repertoire.txt"
                {
                    fscanf(fichier,"%s", tab[i].nom);
                    fscanf(fichier,"%s", tab[i].prenom);
                    fscanf(fichier,"%s", tab[i].adresse);
                    fscanf(fichier,"%s", tab[i].CP);
                    fscanf(fichier,"%s", tab[i].ville);
                    fscanf(fichier,"%s", tab[i].admail);
                    fscanf(fichier,"%s", tab[i].numtel);
                    i = i + 1;
                    nbelem = nbelem + 1;
                    trouve = 1;
                }
            }
            fclose(fichier); // fermeture du fichier
            if (nbelem < 1)
                printf("\nRepertoire vide\n");
            for (i=0;i<nbelem;i++)
                affichage(tab,i);
            break;
            case 1:
            ajout(tab,&nbelem);
            nbelem = nbelem + 1;
            break;
            case 2:
            recherche(tab,nbelem,&numcontact);
            break;
            case 3:
            if (nbelem < 1)
                printf("\nRepertoire vide\n");
            else
                modif(tab,nbelem);
            break;
            case 4:
            if (nbelem < 1)
                printf("\nRepertoire vide\n");
            else
                suppr(tab,&nbelem);
            break;
            case 5:
                printf("Au revoir !\n");
                fichier = fopen ("Repertoire.txt","w"); // ouverture du fichier en mode ecriture
                for (i=0;i<nbelem;i++) // boucle d'ecriture des nouveaux contacts dans le fichier
                {
                    fputs ("\n",fichier);
                    fputs (tab[i].nom,fichier);
                    fputs ("\n",fichier);
                    fputs (tab[i].prenom,fichier);
                    fputs ("\n",fichier);
                    fputs (tab[i].adresse,fichier);
                    fputs ("\n",fichier);
                    fputs (tab[i].CP,fichier);
                    fputs ("\n",fichier);
                    fputs (tab[i].ville,fichier);
                    fputs ("\n",fichier);
                    fputs (tab[i].admail,fichier);
                    fputs ("\n",fichier);
                    fputs (tab[i].numtel,fichier);
                }
                if (fichier == NULL) // verification du contenu du fichier
                    printf("Erreur lors de l'ouverture du fichier");
                else
                {
                    printf("Votre repertoire est disponible dans le fichier repertoire.txt");
                    fclose(fichier);
                }
            break;
            default: break;
        }
    }while(choix != 5);
    return (0);
}

void ajout(struct tcontact tab[100], int *nbelem)
{
    printf("Les contacts se presentent sous la forme suivante : \n\nNom,prenom,adresse,code postal,ville,adresse mail,numero de telephone\n");
    printf("\nContact %d : \n",*nbelem+1);
    printf("Nom du contact : ");
    fflush(stdin);
    scanf("%s",tab[*nbelem].nom);
    printf("Prenom du contact : ");
    fflush(stdin);
    scanf("%s",tab[*nbelem].prenom);
    printf("Adresse du contact (mots separes par un point): ");
    fflush(stdin);
    gets(tab[*nbelem].adresse);
    printf("Code postal du contact : ");
    fflush(stdin);
    scanf("%s",tab[*nbelem].CP);
    printf("Ville du contact : ");
    fflush(stdin);
    gets(tab[*nbelem].ville);
    printf("Adresse mail du contact : ");
    fflush(stdin);
    scanf("%s",tab[*nbelem].admail);
    printf("Numero de telephone du contact : ");
    fflush(stdin);
    gets(tab[*nbelem].numtel);
}

void affichage(struct tcontact tab[100],int indice)
{
    printf("\nContact %d: \n",indice+1);
    printf("Nom du contact : ");
    printf("%s\n",tab[indice].nom);
    printf("Prenom du contact : ");
    printf("%s\n",tab[indice].prenom);
    printf("Adresse du contact : ");
    printf("%s\n",tab[indice].adresse);
    printf("Code postal du contact : ");
    printf("%s\n",tab[indice].CP);
    printf("Ville du contact : ");
    printf("%s\n",tab[indice].ville);
    printf("Adresse mail du contact : ");
    printf("%s\n",tab[indice].admail);
    printf("Numero de telephone du contact : ");
    printf("%s\n\n",tab[indice].numtel);
}

void recherche(struct tcontact tab[100],int nbelem,int *numcontact)
{
    char nom[30];
    int i=0,j=0,trouve=0;

    if (nbelem == 0)
        printf("Aucun contact saisi\n");
    else
    {
        printf("\nSaisissez le nom du contact que vous recherchez : ");
        scanf("%s",nom);
        while (trouve == 0 && i < nbelem)
        {
            j = strcmp(tab[i].nom,nom); //fonction de comparaison entre deux chaines de caracteres, renvoie 0 si identiques
            if (j == 0)
            {
                trouve = 1;  // booleen de test
                *numcontact = i; // recuperation de l'indice auquel on trouve notre contact
                affichage(tab,*numcontact); // affichage de ce contact
            }
            i++;
        }
    }
}

void modif(struct tcontact tab[100],int nbelem)
{
    int choix,numcontact;
    char rep;

    recherche(tab,nbelem,&numcontact); // utilisation de la fonction recherche pour recuperer l'indice du contact cherche
    if (numcontact>=nbelem) // controle de la valeur reçue
        printf("Contact non saisi au prealable");
    else
    {
        do // boucle de modification des elements d'un contact
        {
            printf("Quelle modification voulez-vous apporter ? \n1- Nom du contact\n2- Prenom du contact\n3- Adresse du contact\n4- Code postal du contact\n5- Ville du contact\n6- Adresse mail du contact\n7- Numero de telephone du contact\n");
            scanf("%d",&choix);
            switch (choix)
            {
                case 1:
                fflush(stdin);
                scanf("%s",tab[numcontact].nom);
                break;
                case 2:
                fflush(stdin);
                scanf("%s",tab[numcontact].prenom);
                break;
                case 3:
                fflush(stdin);
                gets(tab[numcontact].adresse);
                break;
                case 4:
                fflush(stdin);
                scanf("%s",tab[numcontact].CP);
                break;
                case 5:
                fflush(stdin);
                gets(tab[numcontact].ville);
                break;
                case 6:
                fflush(stdin);
                scanf("%s",tab[numcontact].admail);
                break;
                case 7:
                fflush(stdin);
                gets(tab[numcontact].numtel);
                break;
            }
            fflush(stdin);
            printf("\nVoulez-vous proceder a une autre modification sur ce contact ? (o/n) : ");
            scanf("%c",&rep);
        }while(rep=='o');
    }
}

void suppr(struct tcontact tab[100],int *nbelem)
{
    int i,numcontact,vrai=0;

    recherche(tab,*nbelem,&numcontact); // utilisation de la fonction recherche pour recuperer l'indice du contact cherche
    for(i = numcontact;i < *nbelem;i++) // decalage des elements de ce contact au dernier indice du tableau
    {
        tab[i]=tab[i+1];
        vrai = 1;
    }
    if (vrai == 1) // mise a zero de cette derniere case du tableau afin de supprimer la valeur du contact
    {
        strcpy(tab[*nbelem-1].nom,"\0");
        strcpy(tab[*nbelem-1].prenom,"\0");
        strcpy(tab[*nbelem-1].adresse,"\0");
        strcpy(tab[*nbelem-1].CP,"\0");
        strcpy(tab[*nbelem-1].ville,"\0");
        strcpy(tab[*nbelem-1].admail,"\0");
        strcpy(tab[*nbelem-1].numtel,"\0");
        *nbelem = *nbelem - 1;
        printf("Contact supprime\n");
    }
    else
        printf("Ce contact n'existe pas.\n\n");
}
