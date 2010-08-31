/** \file  errno.h
   * Contient les codes d'erreurs ainsi que des messages descriptifs.
   * Valeur positive ou nulle : pas d'erreur.
   * Valeur n�gative : erreur ; cause de l'erreur = oppos� du retour
   */
   
#ifndef ERRNO_H_INCLUDED
#define ERRNO_H_INCLUDED

/** \brief d�crit les erreurs courantes
 * \todo rajouter des codes d'erreurs
 */
enum
{
	BOS_OK,
	BOS_NOT_IMPLEMENTED,//fonction non impl�ment�e
	BOS_EINVAL,//param�tres invalides
};

#endif