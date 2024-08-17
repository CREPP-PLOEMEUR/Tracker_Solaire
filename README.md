<!--# Tracker solaire -->
<!--+ 2023-2024 -->
<!--$ C++-->
<!--$ Freecad -->
<!--$ GPS -->
<!--% Ce projet vise à concevoir et construire un système de suivi solaire spécialement conçu pour maximiser l'efficacité de la capture d'énergie solaire à partir d'un panneau solaire. -->
 -->
# Projet de Tracker Solaire pour Panneau 1m x 1m60

Ce projet vise à concevoir et construire un système de suivi solaire spécialement conçu pour maximiser l'efficacité de la capture d'énergie solaire à partir d'un panneau solaire de dimensions spécifiques.

## Table des matières

- [Aperçu](#aperçu)
- [Fonctionnalités](#fonctionnalités)
- [Matériaux](#matériaux)
- [Schémas et Conception](#schémas-et-conception)

## Aperçu

Ce projet a pour objectif de créer un tracker solaire qui ajuste automatiquement la position d'un panneau solaire de 1 mètre sur 1 mètre 60 pour suivre le mouvement du soleil tout au long de la journée. Cette optimisation permettra une captation maximale de l'énergie solaire disponible.

## Fonctionnalités

Le tracker solaire comprend différentes fonctionnalités :

- Suivi précis et automatique de la trajectoire du soleil pour maximiser la production d'énergie solaire.
- Utilisation d'un module GPS pour déterminer la position du panneau solaire.  Une fois la position captée, l'heure permet de calculer 
la position du Soleil à n'importe quel moment de la journée.
- Un module RTC (Real Time Clock) enregistre l'heure pour éviter de solliciter le module GPS
- Contrôle fluide des moteurs pour ajuster la position du panneau solaire 
- Interface de communication pour surveiller et configurer les performances du tracker.
- Tous les évènements sont enregistrés dans une carte microSD.
- Le tracker se met en veille profonde dès que la luminosité devient trop faible.
- Une rafale de vent, dont la consigne peut être ajustée par l'utilisateur, réveille en cas de besoin le tracker pour le mettre en position horizontale.

## Matériaux

- Composants électroniques standard tels que microcontrôleurs, GPS, moteurs pas à pas, etc.
- Carte de circuit imprimé spécialement conçue pour le tracker solaire.

![Image de PCB](/Images/PCB.png "Une version du PCB)

- Moteurs pas à pas robustes adaptés aux dimensions du panneau solaire.
- Structure mécanique pour soutenir et orienter le panneau solaire.
- Source d'alimentation adaptée aux moteurs et à l'électronique.

## Schémas et Conception

Les schémas électriques détaillés et les plans de conception du circuit imprimé spécifique au tracker solaire sont disponibles dans le dossier `Hardware`. 

