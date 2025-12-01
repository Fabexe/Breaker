#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

void initSDL() {
    // Initialiser SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("Erreur de l'initialisationde SDL : %s\n", SDL_GetError());
        return 0;
    }
    
    // Initialiser SDL_mixer
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

    // Initialiser SDL_ttf
    if (TTF_Init() < 0) {
        printf("Erreur d'initialisation de SDL_ttf : %s\n", TTF_GetError());
        SDL_Quit();
        return 0;
    }

    // Créer une fenêtre
    gWindow = SDL_CreateWindow("Breaker", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 400, 650, SDL_WINDOW_SHOWN);

    // Créer le renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    // Définition de la couleur de fond
    SDL_SetRenderDrawColor(gRenderer, 192, 192, 192, 255);  // Blanc
    SDL_RenderClear(gRenderer);
    SDL_RenderPresent(gRenderer);

}

TTF_Font *chargerPolice(const char *chemin, int taille) {
    TTF_Font *police = TTF_OpenFont(chemin, taille);
    if (!police) {
        printf("Erreur de chargement de la police : %s\n", TTF_GetError());
    }
    return police;
}

// Variable état du jeu (0 = neutre ; 1 = win ; 2 = lose)
float gVariableJeu = 0;

void closeSDL() {
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

void startLoop() {
    SDL_Event a;
    int gVariableFin = 0;

    // Charger le Titre
    TTF_Font* gTTFTitre = chargerPolice("fonts/font.ttf", 64);
    SDL_Surface* gSurfaceTitre = TTF_RenderText_Solid(gTTFTitre, "BREAKER", (SDL_Color){255, 0, 0, 255});
    SDL_Texture* gTextureTitre = SDL_CreateTextureFromSurface(gRenderer, gSurfaceTitre);
    SDL_Rect gRectTitre;
    gRectTitre.x = 50;
    gRectTitre.y = 100;
    gRectTitre.w = 300;
    gRectTitre.h = 80;
    SDL_FreeSurface(gSurfaceTitre);

    // Charger les informations
    TTF_Font* gTTFInfo = chargerPolice("fonts/font.ttf", 64);
    SDL_Surface* gSurfaceInfo = TTF_RenderText_Solid(gTTFInfo, "PRESS -P- FOR PLAY", (SDL_Color){0, 0, 0, 255});
    SDL_Texture* gTextureInfo = SDL_CreateTextureFromSurface(gRenderer, gSurfaceInfo);
    SDL_Rect gRectInfo;
    gRectInfo.x = 25;
    gRectInfo.y = 250;
    gRectInfo.w = 350;
    gRectInfo.h = 60;
    SDL_FreeSurface(gSurfaceInfo);

    // Charger les crédits
    TTF_Font* gTTFCredit = chargerPolice("fonts/font.ttf", 64);
    SDL_Surface* gSurfaceCredit = TTF_RenderText_Solid(gTTFCredit, "MADE BY F.P. FROM BTS1CIEL", (SDL_Color){0, 0, 0, 255});
    SDL_Texture* gTextureCredit = SDL_CreateTextureFromSurface(gRenderer, gSurfaceCredit);
    SDL_Rect gRectCredit;
    gRectCredit.x = 0;
    gRectCredit.y = 630;
    gRectCredit.w = 300;
    gRectCredit.h = 20;
    SDL_FreeSurface(gSurfaceCredit);

    while (!gVariableFin) {
        while (SDL_PollEvent(&a) != 0) {
            if (a.type == SDL_QUIT) {
                gVariableFin = 1;
            }
        }

        const Uint8* gControleMenu = SDL_GetKeyboardState(NULL);
        if (gControleMenu[SDL_SCANCODE_P]) {
            gVariableFin = 1;
        }

        // Afficher le rendu
        SDL_RenderCopy(gRenderer, gTextureTitre, NULL, &gRectTitre);
        SDL_RenderCopy(gRenderer, gTextureInfo, NULL, &gRectInfo);
        SDL_RenderCopy(gRenderer, gTextureCredit, NULL, &gRectCredit);

        // Mettre à jour l'affichage
        SDL_RenderPresent(gRenderer);

        // Effacer l'écran
        SDL_RenderClear(gRenderer);        

        // Ajouter une légère pause pour contrôler la vitesse du jeu
        SDL_Delay(16);
    }

    SDL_DestroyTexture(gTextureTitre);
    SDL_DestroyTexture(gTextureInfo);
    SDL_DestroyTexture(gTextureCredit);

}

void appLoop() {
    SDL_Event e;
    int quit = 0;

    // Génération de couleurs RGBA
    SDL_Color gColorRouge = {255, 0, 0, 255}; // Rouge (RGBA)
    SDL_Color gColorVert = {0, 255, 0, 255}; // Vert (RGBA)
    SDL_Color gColorBleu = {0, 0, 255, 255}; // Bleu (RGBA)
    SDL_Color gColorJaune = {255, 255, 0, 255}; // Jaune (RGBA)
    SDL_Color gColorFuchsia = {255, 0, 255, 255}; // Fuchsia (RGBA)
    SDL_Color gColorNoir = {0, 0, 0, 255}; // Noir (RGBA)
    SDL_Color gColorGris = {192, 192, 192, 255}; // Gris (RGBA)
    SDL_Color gColorBlanc = {255, 255, 255, 255}; // Blanc (RGBA)

    // Affichage du joueur
    SDL_Surface* gSurfaceJoueur = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceJoueur, NULL, SDL_MapRGBA(gSurfaceJoueur->format, gColorRouge.r, gColorRouge.g, gColorRouge.b, gColorRouge.a));
    SDL_Texture* gTextureJoueur = SDL_CreateTextureFromSurface(gRenderer, gSurfaceJoueur);
    SDL_Rect gRectJoueur;
    gRectJoueur.x = 170;
    gRectJoueur.y = 631;
    gRectJoueur.w = 60;
    gRectJoueur.h = 9;
    SDL_FreeSurface(gSurfaceJoueur);

    // Affichage de la balle
    SDL_Surface* gSurfaceBalle = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBalle, NULL, SDL_MapRGBA(gSurfaceBalle->format, gColorBlanc.r, gColorBlanc.g, gColorBlanc.b, gColorBlanc.a));
    SDL_Texture* gTextureBalle = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBalle);
    SDL_Rect gRectBalle;
    gRectBalle.x = 190;
    gRectBalle.y = 500;
    gRectBalle.w = 10;
    gRectBalle.h = 10;
    SDL_FreeSurface(gSurfaceBalle);

    // Affichage du collisionneur gauche 1
    SDL_Surface* gSurfaceCollisionGauche1 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceCollisionGauche1, NULL, SDL_MapRGBA(gSurfaceCollisionGauche1->format, gColorRouge.r, gColorRouge.g, gColorRouge.b, gColorRouge.a));
    SDL_Texture* gTextureCollisionGauche1 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceCollisionGauche1);
    SDL_Rect gRectCollisionGauche1;
    gRectCollisionGauche1.x = 170;
    gRectCollisionGauche1.y = 630;
    gRectCollisionGauche1.w = 15;
    gRectCollisionGauche1.h = 3;
    SDL_FreeSurface(gSurfaceCollisionGauche1);

    // Affichage du collisionneur gauche 2
    SDL_Surface* gSurfaceCollisionGauche2 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceCollisionGauche2, NULL, SDL_MapRGBA(gSurfaceCollisionGauche2->format, gColorRouge.r, gColorRouge.g, gColorRouge.b, gColorRouge.a));
    SDL_Texture* gTextureCollisionGauche2 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceCollisionGauche2);
    SDL_Rect gRectCollisionGauche2;
    gRectCollisionGauche2.x = 185;
    gRectCollisionGauche2.y = 630;
    gRectCollisionGauche2.w = 15;
    gRectCollisionGauche2.h = 3;
    SDL_FreeSurface(gSurfaceCollisionGauche2);

    // Affichage du collisionneur droit 1
    SDL_Surface* gSurfaceCollisionDroit1 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceCollisionDroit1, NULL, SDL_MapRGBA(gSurfaceCollisionDroit1->format, gColorRouge.r, gColorRouge.g, gColorRouge.b, gColorRouge.a));
    SDL_Texture* gTextureCollisionDroit1 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceCollisionDroit1);
    SDL_Rect gRectCollisionDroit1;
    gRectCollisionDroit1.x = 200;
    gRectCollisionDroit1.y = 630;
    gRectCollisionDroit1.w = 15;
    gRectCollisionDroit1.h = 3;
    SDL_FreeSurface(gSurfaceCollisionDroit1);

    // Affichage du collisionneur droit 2
    SDL_Surface* gSurfaceCollisionDroit2 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceCollisionDroit2, NULL, SDL_MapRGBA(gSurfaceCollisionDroit2->format, gColorRouge.r, gColorRouge.g, gColorRouge.b, gColorRouge.a));
    SDL_Texture* gTextureCollisionDroit2 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceCollisionDroit2);
    SDL_Rect gRectCollisionDroit2;
    gRectCollisionDroit2.x = 215;
    gRectCollisionDroit2.y = 630;
    gRectCollisionDroit2.w = 15;
    gRectCollisionDroit2.h = 3;
    SDL_FreeSurface(gSurfaceCollisionDroit2);

    // Affichage du mur haut
    SDL_Surface* gSurfaceMurHaut = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceMurHaut, NULL, SDL_MapRGBA(gSurfaceMurHaut->format, gColorNoir.r, gColorNoir.g, gColorNoir.b, gColorNoir.a));
    SDL_Texture* gTextureMurHaut = SDL_CreateTextureFromSurface(gRenderer, gSurfaceMurHaut);
    SDL_Rect gRectMurHaut;
    gRectMurHaut.x = 0;
    gRectMurHaut.y = 0;
    gRectMurHaut.w = 400;
    gRectMurHaut.h = 5;
    SDL_FreeSurface(gSurfaceMurHaut);

    // Affichage du mur bas
    SDL_Surface* gSurfaceMurBas = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceMurBas, NULL, SDL_MapRGBA(gSurfaceMurBas->format, gColorNoir.r, gColorNoir.g, gColorNoir.b, gColorNoir.a));
    SDL_Texture* gTextureMurBas = SDL_CreateTextureFromSurface(gRenderer, gSurfaceMurBas);
    SDL_Rect gRectMurBas;
    gRectMurBas.x = 0;
    gRectMurBas.y = 645;
    gRectMurBas.w = 400;
    gRectMurBas.h = 5;
    SDL_FreeSurface(gSurfaceMurBas);

    // Affichage du mur gauche
    SDL_Surface* gSurfaceMurGauche = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceMurGauche, NULL, SDL_MapRGBA(gSurfaceMurGauche->format, gColorNoir.r, gColorNoir.g, gColorNoir.b, gColorNoir.a));
    SDL_Texture* gTextureMurGauche = SDL_CreateTextureFromSurface(gRenderer, gSurfaceMurGauche);
    SDL_Rect gRectMurGauche;
    gRectMurGauche.x = 0;
    gRectMurGauche.y = 0;
    gRectMurGauche.w = 5;
    gRectMurGauche.h = 650;
    SDL_FreeSurface(gSurfaceMurGauche);

    // Affichage du mur droit
    SDL_Surface* gSurfaceMurDroit = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceMurDroit, NULL, SDL_MapRGBA(gSurfaceMurDroit->format, gColorNoir.r, gColorNoir.g, gColorNoir.b, gColorNoir.a));
    SDL_Texture* gTextureMurDroit = SDL_CreateTextureFromSurface(gRenderer, gSurfaceMurDroit);
    SDL_Rect gRectMurDroit;
    gRectMurDroit.x = 395;
    gRectMurDroit.y = 0;
    gRectMurDroit.w = 5;
    gRectMurDroit.h = 650;
    SDL_FreeSurface(gSurfaceMurDroit);

    // Affichage de la brique 1
    SDL_Surface* gSurfaceBrique1 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique1, NULL, SDL_MapRGBA(gSurfaceBrique1->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique1 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique1);
    SDL_Rect gRectBrique1;
    gRectBrique1.x = 60;
    gRectBrique1.y = 100;
    gRectBrique1.w = 30;
    gRectBrique1.h = 10;
    SDL_FreeSurface(gSurfaceBrique1);

    // Affichage de la brique 2
    SDL_Surface* gSurfaceBrique2 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique2, NULL, SDL_MapRGBA(gSurfaceBrique2->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique2 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique2);
    SDL_Rect gRectBrique2;
    gRectBrique2.x = 110;
    gRectBrique2.y = 100;
    gRectBrique2.w = 30;
    gRectBrique2.h = 10;
    SDL_FreeSurface(gSurfaceBrique2);

    // Affichage de la brique 3
    SDL_Surface* gSurfaceBrique3 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique3, NULL, SDL_MapRGBA(gSurfaceBrique3->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique3 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique3);
    SDL_Rect gRectBrique3;
    gRectBrique3.x = 160;
    gRectBrique3.y = 100;
    gRectBrique3.w = 30;
    gRectBrique3.h = 10;
    SDL_FreeSurface(gSurfaceBrique3);

    // Affichage de la brique 4
    SDL_Surface* gSurfaceBrique4 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique4, NULL, SDL_MapRGBA(gSurfaceBrique4->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique4 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique4);
    SDL_Rect gRectBrique4;
    gRectBrique4.x = 210;
    gRectBrique4.y = 100;
    gRectBrique4.w = 30;
    gRectBrique4.h = 10;
    SDL_FreeSurface(gSurfaceBrique4);

    // Affichage de la brique 5
    SDL_Surface* gSurfaceBrique5 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique5, NULL, SDL_MapRGBA(gSurfaceBrique5->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique5 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique5);
    SDL_Rect gRectBrique5;
    gRectBrique5.x = 260;
    gRectBrique5.y = 100;
    gRectBrique5.w = 30;
    gRectBrique5.h = 10;
    SDL_FreeSurface(gSurfaceBrique5);

    // Affichage de la brique 6
    SDL_Surface* gSurfaceBrique6 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique6, NULL, SDL_MapRGBA(gSurfaceBrique6->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique6 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique6);
    SDL_Rect gRectBrique6;
    gRectBrique6.x = 310;
    gRectBrique6.y = 100;
    gRectBrique6.w = 30;
    gRectBrique6.h = 10;
    SDL_FreeSurface(gSurfaceBrique6);

    // Affichage de la brique 7
    SDL_Surface* gSurfaceBrique7 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique7, NULL, SDL_MapRGBA(gSurfaceBrique7->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique7 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique7);
    SDL_Rect gRectBrique7;
    gRectBrique7.x = 60;
    gRectBrique7.y = 140;
    gRectBrique7.w = 30;
    gRectBrique7.h = 10;
    SDL_FreeSurface(gSurfaceBrique7);

    // Affichage de la brique 8
    SDL_Surface* gSurfaceBrique8 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique8, NULL, SDL_MapRGBA(gSurfaceBrique8->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique8 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique8);
    SDL_Rect gRectBrique8;
    gRectBrique8.x = 110;
    gRectBrique8.y = 140;
    gRectBrique8.w = 30;
    gRectBrique8.h = 10;
    SDL_FreeSurface(gSurfaceBrique8);

    // Affichage de la brique 9
    SDL_Surface* gSurfaceBrique9 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique9, NULL, SDL_MapRGBA(gSurfaceBrique9->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique9 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique9);
    SDL_Rect gRectBrique9;
    gRectBrique9.x = 160;
    gRectBrique9.y = 140;
    gRectBrique9.w = 30;
    gRectBrique9.h = 10;
    SDL_FreeSurface(gSurfaceBrique9);

    // Affichage de la brique 10
    SDL_Surface* gSurfaceBrique10 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique10, NULL, SDL_MapRGBA(gSurfaceBrique10->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique10 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique10);
    SDL_Rect gRectBrique10;
    gRectBrique10.x = 210;
    gRectBrique10.y = 140;
    gRectBrique10.w = 30;
    gRectBrique10.h = 10;
    SDL_FreeSurface(gSurfaceBrique10);

    // Affichage de la brique 11
    SDL_Surface* gSurfaceBrique11 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique11, NULL, SDL_MapRGBA(gSurfaceBrique11->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique11 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique11);
    SDL_Rect gRectBrique11;
    gRectBrique11.x = 260;
    gRectBrique11.y = 140;
    gRectBrique11.w = 30;
    gRectBrique11.h = 10;
    SDL_FreeSurface(gSurfaceBrique11);

    // Affichage de la brique 12
    SDL_Surface* gSurfaceBrique12 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique12, NULL, SDL_MapRGBA(gSurfaceBrique12->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique12 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique12);
    SDL_Rect gRectBrique12;
    gRectBrique12.x = 310;
    gRectBrique12.y = 140;
    gRectBrique12.w = 30;
    gRectBrique12.h = 10;
    SDL_FreeSurface(gSurfaceBrique12);

    // Affichage de la brique 13
    SDL_Surface* gSurfaceBrique13 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique13, NULL, SDL_MapRGBA(gSurfaceBrique13->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique13 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique13);
    SDL_Rect gRectBrique13;
    gRectBrique13.x = 60;
    gRectBrique13.y = 180;
    gRectBrique13.w = 30;
    gRectBrique13.h = 10;
    SDL_FreeSurface(gSurfaceBrique13);

    // Affichage de la brique 14
    SDL_Surface* gSurfaceBrique14 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique14, NULL, SDL_MapRGBA(gSurfaceBrique14->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique14 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique14);
    SDL_Rect gRectBrique14;
    gRectBrique14.x = 110;
    gRectBrique14.y = 180;
    gRectBrique14.w = 30;
    gRectBrique14.h = 10;
    SDL_FreeSurface(gSurfaceBrique14);

    // Affichage de la brique 15
    SDL_Surface* gSurfaceBrique15 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique15, NULL, SDL_MapRGBA(gSurfaceBrique15->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique15 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique15);
    SDL_Rect gRectBrique15;
    gRectBrique15.x = 160;
    gRectBrique15.y = 180;
    gRectBrique15.w = 30;
    gRectBrique15.h = 10;
    SDL_FreeSurface(gSurfaceBrique15);

    // Affichage de la brique 16
    SDL_Surface* gSurfaceBrique16 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique16, NULL, SDL_MapRGBA(gSurfaceBrique16->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique16 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique16);
    SDL_Rect gRectBrique16;
    gRectBrique16.x = 210;
    gRectBrique16.y = 180;
    gRectBrique16.w = 30;
    gRectBrique16.h = 10;
    SDL_FreeSurface(gSurfaceBrique16);

    // Affichage de la brique 17
    SDL_Surface* gSurfaceBrique17 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique17, NULL, SDL_MapRGBA(gSurfaceBrique17->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique17 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique17);
    SDL_Rect gRectBrique17;
    gRectBrique17.x = 260;
    gRectBrique17.y = 180;
    gRectBrique17.w = 30;
    gRectBrique17.h = 10;
    SDL_FreeSurface(gSurfaceBrique17);

    // Affichage de la brique 18
    SDL_Surface* gSurfaceBrique18 = SDL_CreateRGBSurface(0, 100, 100, 32, 0, 0, 0, 0);
    SDL_FillRect(gSurfaceBrique18, NULL, SDL_MapRGBA(gSurfaceBrique18->format, gColorJaune.r, gColorJaune.g, gColorJaune.b, gColorJaune.a));
    SDL_Texture* gTextureBrique18 = SDL_CreateTextureFromSurface(gRenderer, gSurfaceBrique18);
    SDL_Rect gRectBrique18;
    gRectBrique18.x = 310;
    gRectBrique18.y = 180;
    gRectBrique18.w = 30;
    gRectBrique18.h = 10;
    SDL_FreeSurface(gSurfaceBrique18);

    // Variables pour la direction de la balle
    float gVariableBalleX = 0; // 0 = Balle verticale ; 1 = Balle gauche+ ; 2 = Balle gauche- ; 3 = Balle droite- ; 4 = Balle droite+
    float gVariableBalleY = 0; // 0 = Balle descend ; 1 = Balle monte

    // Variables état des briques (0 = Neutre ; 1 = Détruit)
    int gVariableBrique1 = 0;
    int gVariableBrique2 = 0;
    int gVariableBrique3 = 0;
    int gVariableBrique4 = 0;
    int gVariableBrique5 = 0;
    int gVariableBrique6 = 0;
    int gVariableBrique7 = 0;
    int gVariableBrique8 = 0;
    int gVariableBrique9 = 0;
    int gVariableBrique10 = 0;
    int gVariableBrique11 = 0;
    int gVariableBrique12 = 0;
    int gVariableBrique13 = 0;
    int gVariableBrique14 = 0;
    int gVariableBrique15 = 0;
    int gVariableBrique16 = 0;
    int gVariableBrique17 = 0;
    int gVariableBrique18 = 0;

    // Chargement des sons
    Mix_Music* gMusicBoing = Mix_LoadMUS("sounds/bounce.mp3");
    Mix_Music* gMusicDestruct = Mix_LoadMUS("sounds/destruct.mp3");

    // Boucle jeu
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = 1;
            }
        }

        // Détection des collisions du joueur
        if (SDL_HasIntersection(&gRectJoueur, &gRectMurGauche) == SDL_TRUE) {
            gRectJoueur.x += 5;
            gRectCollisionGauche1.x += 5;
            gRectCollisionGauche2.x += 5;
            gRectCollisionDroit1.x += 5;
            gRectCollisionDroit2.x += 5;
        }

        if (SDL_HasIntersection(&gRectJoueur, &gRectMurDroit) == SDL_TRUE) {
            gRectJoueur.x -= 5;
            gRectCollisionGauche1.x -= 5;
            gRectCollisionGauche2.x -= 5;
            gRectCollisionDroit1.x -= 5;
            gRectCollisionDroit2.x -= 5;
        }

        // Déplacement automatique de la balle
        if (gVariableBalleY == 0) {
            gRectBalle.y += 3;
        }
        else {
            gRectBalle.y -= 3;
        }

        if (gVariableBalleX == 1) {
            gRectBalle.x -= 5;
        }
        else if (gVariableBalleX == 2) {
            gRectBalle.x -= 3;
        }
        else if (gVariableBalleX == 3) {
            gRectBalle.x += 3;
        }
        else if (gVariableBalleX == 4) {
            gRectBalle.x += 5;
        }

        if (SDL_HasIntersection(&gRectBalle, &gRectJoueur) == SDL_TRUE) {
            gVariableBalleY = 1;
            Mix_PlayMusic(gMusicBoing, 1);
        }

        if (SDL_HasIntersection(&gRectBalle, &gRectMurHaut) == SDL_TRUE) {
            gVariableBalleY = 0;
            Mix_PlayMusic(gMusicBoing, 1);
        }

        if (SDL_HasIntersection(&gRectBalle, &gRectCollisionGauche1) == SDL_TRUE) {
            gVariableBalleX = 1;
            Mix_PlayMusic(gMusicBoing, 1);
        }
        else if (SDL_HasIntersection(&gRectBalle, &gRectCollisionGauche2) == SDL_TRUE) {
            gVariableBalleX = 2;
            Mix_PlayMusic(gMusicBoing, 1);
        }
        else if (SDL_HasIntersection(&gRectBalle, &gRectCollisionDroit1) == SDL_TRUE) {
            gVariableBalleX = 3;
            Mix_PlayMusic(gMusicBoing, 1);
        }
        else if (SDL_HasIntersection(&gRectBalle, &gRectCollisionDroit2) == SDL_TRUE) {
            gVariableBalleX = 4;
            Mix_PlayMusic(gMusicBoing, 1);
        }

        if (SDL_HasIntersection(&gRectBalle, &gRectMurGauche) == SDL_TRUE) {
            if (gVariableBalleX == 1) {
                gVariableBalleX = 4;
                Mix_PlayMusic(gMusicBoing, 1);
            }
            else {
                gVariableBalleX = 3;
                Mix_PlayMusic(gMusicBoing, 1);
            }
        }
        else if (SDL_HasIntersection(&gRectBalle, &gRectMurDroit) == SDL_TRUE) {
            if (gVariableBalleX == 4) {
                gVariableBalleX = 1;
                Mix_PlayMusic(gMusicBoing, 1);
            }
            else {
                gVariableBalleX = 2;
                Mix_PlayMusic(gMusicBoing, 1);
            }
        }

        if (SDL_HasIntersection(&gRectBalle, &gRectMurBas) == SDL_TRUE) {
            gVariableJeu = 2;
            quit = 1;
        }

        // Détection de la collision de la balle sur les briques
        if (gVariableBrique1 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique1) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique1);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique1 = 1;
        }

        if (gVariableBrique2 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique2) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique2);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique2 = 1;
        }

        if (gVariableBrique3 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique3) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique3);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique3 = 1;
        }

        if (gVariableBrique4 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique4) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique4);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique4 = 1;
        }

        if (gVariableBrique5 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique5) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique5);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique5 = 1;
        }

        if (gVariableBrique6 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique6) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique6);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique6 = 1;
        }

        if (gVariableBrique7 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique7) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique7);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique7 = 1;
        }

        if (gVariableBrique8 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique8) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique8);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique8 = 1;
        }

        if (gVariableBrique9 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique9) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique9);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique9 = 1;
        }

        if (gVariableBrique10 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique10) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique10);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique10 = 1;
        }

        if (gVariableBrique11 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique11) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique11);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique11 = 1;
        }

        if (gVariableBrique12 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique12) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique12);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique12 = 1;
        }

        if (gVariableBrique13 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique13) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique13);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique13 = 1;
        }

        if (gVariableBrique14 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique14) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique14);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique14 = 1;
        }

        if (gVariableBrique15 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique15) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique15);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique15 = 1;
        }

        if (gVariableBrique16 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique16) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique16);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique16 = 1;
        }

        if (gVariableBrique17 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique17) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique17);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique17 = 1;
        }

        if (gVariableBrique18 == 0 && SDL_HasIntersection(&gRectBalle, &gRectBrique18) == SDL_TRUE) {
            if (gVariableBalleY == 0) {
                gVariableBalleY = 1;
            }
            else if (gVariableBalleY == 1) {
                gVariableBalleY = 0;
            }
            SDL_DestroyTexture(gTextureBrique18);
            Mix_PlayMusic(gMusicDestruct, 1);
            gVariableBrique18 = 1;
        }

        // Gérer les mouvements du joueur
        const Uint8* gMoveJoueur = SDL_GetKeyboardState(NULL);
        if (gMoveJoueur[SDL_SCANCODE_LEFT] && gRectJoueur.x > 0) {
            gRectJoueur.x -= 5;
            gRectCollisionGauche1.x -= 5;
            gRectCollisionGauche2.x -= 5;
            gRectCollisionDroit1.x -= 5;
            gRectCollisionDroit2.x -= 5;
        }

        if (gMoveJoueur[SDL_SCANCODE_RIGHT] && gRectJoueur.x > 0) {
            gRectJoueur.x += 5;
            gRectCollisionGauche1.x += 5;
            gRectCollisionGauche2.x += 5;
            gRectCollisionDroit1.x += 5;
            gRectCollisionDroit2.x += 5;
        }

        // Condition du jeu si victoire
        if (gVariableBrique1 && gVariableBrique2 && gVariableBrique3 && gVariableBrique4 && gVariableBrique5 && gVariableBrique6 && gVariableBrique7 && gVariableBrique8 && gVariableBrique9 && gVariableBrique10 && gVariableBrique11 && gVariableBrique12 && gVariableBrique13 && gVariableBrique14 && gVariableBrique15 && gVariableBrique16 && gVariableBrique17 && gVariableBrique18 == 1) {
            gVariableJeu = 1;
            quit = 1;
        }
        
        // Dessiner les textures
        SDL_RenderCopy(gRenderer, gTextureJoueur, NULL, &gRectJoueur);
        SDL_RenderCopy(gRenderer, gTextureBalle, NULL, &gRectBalle);
        SDL_RenderCopy(gRenderer, gTextureCollisionGauche1, NULL, &gRectCollisionGauche1);
        SDL_RenderCopy(gRenderer, gTextureCollisionGauche2, NULL, &gRectCollisionGauche2);
        SDL_RenderCopy(gRenderer, gTextureCollisionDroit1, NULL, &gRectCollisionDroit1);
        SDL_RenderCopy(gRenderer, gTextureCollisionDroit2, NULL, &gRectCollisionDroit2);
        SDL_RenderCopy(gRenderer, gTextureMurHaut, NULL, &gRectMurHaut);
        SDL_RenderCopy(gRenderer, gTextureMurBas, NULL, &gRectMurBas);
        SDL_RenderCopy(gRenderer, gTextureMurGauche, NULL, &gRectMurGauche);
        SDL_RenderCopy(gRenderer, gTextureMurDroit, NULL, &gRectMurDroit);
        SDL_RenderCopy(gRenderer, gTextureBrique1, NULL, &gRectBrique1);
        SDL_RenderCopy(gRenderer, gTextureBrique2, NULL, &gRectBrique2);
        SDL_RenderCopy(gRenderer, gTextureBrique3, NULL, &gRectBrique3);
        SDL_RenderCopy(gRenderer, gTextureBrique4, NULL, &gRectBrique4);
        SDL_RenderCopy(gRenderer, gTextureBrique5, NULL, &gRectBrique5);
        SDL_RenderCopy(gRenderer, gTextureBrique6, NULL, &gRectBrique6);
        SDL_RenderCopy(gRenderer, gTextureBrique7, NULL, &gRectBrique7);
        SDL_RenderCopy(gRenderer, gTextureBrique8, NULL, &gRectBrique8);
        SDL_RenderCopy(gRenderer, gTextureBrique9, NULL, &gRectBrique9);
        SDL_RenderCopy(gRenderer, gTextureBrique10, NULL, &gRectBrique10);
        SDL_RenderCopy(gRenderer, gTextureBrique11, NULL, &gRectBrique11);
        SDL_RenderCopy(gRenderer, gTextureBrique12, NULL, &gRectBrique12);
        SDL_RenderCopy(gRenderer, gTextureBrique13, NULL, &gRectBrique13);
        SDL_RenderCopy(gRenderer, gTextureBrique14, NULL, &gRectBrique14);
        SDL_RenderCopy(gRenderer, gTextureBrique15, NULL, &gRectBrique15);
        SDL_RenderCopy(gRenderer, gTextureBrique16, NULL, &gRectBrique16);
        SDL_RenderCopy(gRenderer, gTextureBrique17, NULL, &gRectBrique17);
        SDL_RenderCopy(gRenderer, gTextureBrique18, NULL, &gRectBrique18);

        // Mettre à jour l'affichage
        SDL_RenderPresent(gRenderer);

        // Effacer l'écran
        SDL_RenderClear(gRenderer);        

        // Ajouter une légère pause pour contrôler la vitesse du jeu
        SDL_Delay(16);
    }

    // Libérer les textures
    SDL_DestroyTexture(gTextureJoueur);
    SDL_DestroyTexture(gTextureBalle);
    SDL_DestroyTexture(gTextureMurHaut);
    SDL_DestroyTexture(gTextureMurBas);
    SDL_DestroyTexture(gTextureMurGauche);
    SDL_DestroyTexture(gTextureMurDroit);
    SDL_DestroyTexture(gTextureCollisionGauche1);
    SDL_DestroyTexture(gTextureCollisionGauche2);
    SDL_DestroyTexture(gTextureCollisionDroit1);
    SDL_DestroyTexture(gTextureCollisionDroit2);
    SDL_DestroyTexture(gTextureBrique1);
    SDL_DestroyTexture(gTextureBrique2);
    SDL_DestroyTexture(gTextureBrique3);
    SDL_DestroyTexture(gTextureBrique4);
    SDL_DestroyTexture(gTextureBrique5);
    SDL_DestroyTexture(gTextureBrique6);
    SDL_DestroyTexture(gTextureBrique7);
    SDL_DestroyTexture(gTextureBrique8);
    SDL_DestroyTexture(gTextureBrique9);
    SDL_DestroyTexture(gTextureBrique10);
    SDL_DestroyTexture(gTextureBrique11);
    SDL_DestroyTexture(gTextureBrique12);
    SDL_DestroyTexture(gTextureBrique13);
    SDL_DestroyTexture(gTextureBrique14);
    SDL_DestroyTexture(gTextureBrique15);
    SDL_DestroyTexture(gTextureBrique16);
    SDL_DestroyTexture(gTextureBrique17);
    SDL_DestroyTexture(gTextureBrique18);

}

void resultLoop() {
    SDL_Event a;
    int gVariableFin = 0;

    // Message de victoire
    TTF_Font* gTTFVictoire = chargerPolice("fonts/font.ttf", 64);
    SDL_Surface* gSurfaceVictoire = TTF_RenderText_Solid(gTTFVictoire, "! WIN !", (SDL_Color){0, 255, 0, 255});
    SDL_Texture* gTextureVictoire = SDL_CreateTextureFromSurface(gRenderer, gSurfaceVictoire);
    SDL_Rect gRectVictoire;
    gRectVictoire.x = 50;
    gRectVictoire.y = 100;
    gRectVictoire.w = 300;
    gRectVictoire.h = 80;
    SDL_FreeSurface(gSurfaceVictoire);

    // Message de défaite
    TTF_Font* gTTFDefaite = chargerPolice("fonts/font.ttf", 64);
    SDL_Surface* gSurfaceDefaite = TTF_RenderText_Solid(gTTFDefaite, "YOU LOSE", (SDL_Color){255, 0, 0, 255});
    SDL_Texture* gTextureDefaite = SDL_CreateTextureFromSurface(gRenderer, gSurfaceDefaite);
    SDL_Rect gRectDefaite;
    gRectDefaite.x = 50;
    gRectDefaite.y = 100;
    gRectDefaite.w = 300;
    gRectDefaite.h = 80;
    SDL_FreeSurface(gSurfaceDefaite);

    // Charger les informations
    TTF_Font* gTTFInfo = chargerPolice("fonts/font.ttf", 64);
    SDL_Surface* gSurfaceInfo = TTF_RenderText_Solid(gTTFInfo, "PRESS -P- FOR PLAY", (SDL_Color){0, 0, 0, 255});
    SDL_Texture* gTextureInfo = SDL_CreateTextureFromSurface(gRenderer, gSurfaceInfo);
    SDL_Rect gRectInfo;
    gRectInfo.x = 25;
    gRectInfo.y = 250;
    gRectInfo.w = 350;
    gRectInfo.h = 60;
    SDL_FreeSurface(gSurfaceInfo);

    while (!gVariableFin) {
        while (SDL_PollEvent(&a) != 0) {
            if (a.type == SDL_QUIT) {
                gVariableFin = 1;
            }

            const Uint8* gControleMenu = SDL_GetKeyboardState(NULL);
            if (gControleMenu[SDL_SCANCODE_P]) {
                gVariableFin = 0;
                appLoop();
            }

        }

        const Uint8* gControleMenu = SDL_GetKeyboardState(NULL);
        if (gControleMenu[SDL_SCANCODE_P]) {
            gVariableFin = 0;
            appLoop();
        }
        
        if (gVariableJeu == 1) {SDL_RenderCopy(gRenderer, gTextureVictoire, NULL, &gRectVictoire);}
        if (gVariableJeu == 2) {SDL_RenderCopy(gRenderer, gTextureDefaite, NULL, &gRectDefaite);}
        SDL_RenderCopy(gRenderer, gTextureInfo, NULL, &gRectInfo);

        // Mettre à jour l'affichage
        SDL_RenderPresent(gRenderer);

        // Effacer l'écran
        SDL_RenderClear(gRenderer);        

        // Ajouter une légère pause pour contrôler la vitesse du jeu
        SDL_Delay(16);
    }

    SDL_DestroyTexture(gTextureVictoire);
    SDL_DestroyTexture(gTextureDefaite);
    SDL_DestroyTexture(gTextureInfo);

}

int main(int argc, char* args[]) {
    // Initialiser SDL
    initSDL();

    // Lancer la boucle de démarrage
    startLoop();

    // Lancer la boucle de jeu
    appLoop();

    // Lancer la boucle des résultats
    resultLoop();

    // Fermer SDL
    closeSDL();

    return 0;
}