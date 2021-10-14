# Projet Malloc (version 1.0 de Yann)
## Objectif
Reproduire les fonctions suivantes : Malloc, Calloc, Realloc, Free, Split et Merge
## Malloc
Alloue size octets, et renvoie un pointeur sur la mémoire allouée. Le contenu de la zone de mémoire n'est pas initialisé. Si size vaut 0, malloc() renvoie soit NULL, soit un pointeur unique qui pourra être passé ultérieurement à free() avec succès.
## Calloc
Alloue la mémoire nécessaire pour un tableau de nmemb éléments de taille size octets, et renvoie un pointeur vers la mémoire allouée. Cette zone est remplie avec des zéros. Si nmemb ou size vaut 0, calloc() renvoie soit NULL, soit un pointeur unique qui pourra être passé ultérieurement à free() avec succès.
## Realloc
Modifie la taille du bloc de mémoire pointé par ptr pour l'amener à une taille de size octets. realloc() conserve le contenu de la zone mémoire minimum entre la nouvelle et l'ancienne taille. Le contenu de la zone de mémoire nouvellement allouée n'est pas initialisé. Si ptr est NULL, l'appel est équivalent à malloc(size), pour toute valeur de size. Si size vaut zéro, et ptr n'est pas NULL, l'appel est équivalent à free(ptr). Si ptr n'est pas NULL, il doit avoir été obtenu par un appel antérieur à malloc(), calloc() ou realloc(). Si la zone pointée était déplacée, un free(ptr) est effectué. 
## Free
Libère l'espace mémoire pointé par ptr, qui a été obtenu lors d'un appel antérieur à malloc(), calloc() ou realloc(). Si le pointeur ptr n'a pas été obtenu par l'un de ces appels, ou s'il a déjà été libéré avec free(ptr), le comportement est indéterminé. Si ptr est NULL, aucune tentative de libération n'a lieu.
## Split
Découpe la mémoire nécessaire lors de l'apellation des fonctions d'une mémoire deja alloué et suffisamment grande.
## Merge
Fusionne deux emplacement memoire déjà alloué si les deux sont successive et ont été free.
