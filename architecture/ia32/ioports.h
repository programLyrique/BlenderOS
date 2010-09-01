/** \file ports.h
 * Gère les ports du processeur : la série outx en fournissant une couche d'abstraction
 */
 
#ifndef IOPORTS_H_INCLUDED
#define IOPORTS_H_INCLUDED

#include "ia32_types.h" 

/** \brief Envoie un octet sur un port
 * \param byte octet à envoyer
 * \param port port destination
 */
extern inline void outb(const uint_16 port, const uint_8 byte);

/** \brief Reçoit un octet d'un port
 * \param port port expéditeur
 * \return char l'octet reçu
 */
extern inline uint_8 inb(const  uint_16 port);

/** \brief Envoie un mot -16 bits) sur un port)*/
extern inline void outw(const uint_16 port, const uint_16 word);

/**\brief Lit un mot sur un port*/
extern inline uint_16 inw(const uint_16 port);

/** \brief Crée une petite temporisation.
 *
 * Envoie une valeur sur le port 80 si bien que la temporisation est indépendante 
 * de la vitesse du cpu
 * Cela peut servir à attendre la fin d'un opération d'entrée/sortie par les ports.
 */
extern inline void io_wait(void);

#endif