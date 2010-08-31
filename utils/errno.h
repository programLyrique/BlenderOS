/** \file  errno.h
   * Contient les codes d'erreurs ainsi que des messages descriptifs.
   * Valeur positive ou nulle : pas d'erreur.
   * Valeur négative : erreur ; cause de l'erreur = opposé du retour
   */
   
#ifndef ERRNO_H_INCLUDED
#define ERRNO_H_INCLUDED

/** \brief décrit les erreurs courantes
 * \todo rajouter des codes d'erreurs
 */
enum
{
	BOS_OK,
	BOS_NOT_IMPLEMENTED,//fonction non implémentée
	BOS_EINVAL,//paramètres invalides
};

#endif