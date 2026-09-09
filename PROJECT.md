# Q-Learning tabulaire — Gridworld en C++

## Objectif
Implémenter de zéro, en C++, un environnement gridworld (un robot doit
atteindre une cible en évitant des obstacles) et un agent Q-learning tabulaire
(Q-table stockée dans un tableau), **sans aucune librairie RL ni Gym**.

Objectif pédagogique principal : rendre concrets les concepts de MDP, politique,
fonction de valeur état-action Q, équation de Bellman, mise à jour TD, et
dilemme exploration/exploitation.
Objectif pédagogique secondaire : pratiquer le C++ (structure de projet, build,
tests, séparation des responsabilités) pour le portfolio GitHub.

## Contexte de l'apprenant
- Maîtrisé : ROS2, simulation physique, contrôleurs classiques, EKF. Ingénieur
  en activité.
- À découvrir (traité comme débutant motivé) : RL, formalisme MDP appliqué,
  Q-learning.
- C++ : terrain d'entraînement volontaire, pas le langage du quotidien. Niveau
  précis à confirmer.
- Python : maîtrisé — utile pour l'analyse et la visualisation hors ligne des
  logs produits par le programme C++.

## Notions ciblées
- Formalisme MDP : états, actions, transitions, récompense, facteur
  d'actualisation gamma, épisode terminal.
- Fonction de valeur Q(s,a), politique gloutonne, politique epsilon-greedy.
- Équation de Bellman d'optimalité et sa version échantillonnée (mise à jour TD).
- Q-learning : algorithme off-policy ; différence avec SARSA.
- Exploration : epsilon-greedy, décroissance de epsilon, rôle du taux
  d'apprentissage alpha.
- Diagnostic d'apprentissage : récompense cumulée par épisode, convergence de la
  Q-table, visualisation de la politique et de la fonction de valeur.

## Prérequis à valider avant de coder
- [ ] Écrire à la main la règle de mise à jour de Q-learning et expliquer chaque
      terme (cible TD, erreur TD, rôle de alpha et gamma).
- [ ] Expliquer pourquoi Q-learning est « off-policy ».
- [ ] Énoncer les conditions qualitatives de convergence (couverture des paires
      état-action, décroissance de alpha).
- [ ] Arrêter les décisions de tooling C++ : build system, framework de test,
      organisation des fichiers.

Ressources proposées :
- Sutton & Barto, *Reinforcement Learning: An Introduction* (2e éd.),
  chap. 3 (MDP), 4 (programmation dynamique), 6 (TD ; section 6.5 = Q-learning).
- Cours David Silver (UCL/DeepMind), leçons 1 à 5.
- cppreference.com pour la STL et le C++ moderne.

## État d'avancement
- [x] Projet choisi et cadré : Q-learning tabulaire, gridworld custom, C++,
      aucune lib RL.
- [ ] Prérequis théoriques validés.
- [ ] Décisions d'architecture arrêtées (classes, responsabilités, build, tests).
- [ ] Structure de fichiers cible écrite dans ce document.
- [ ] Environnement gridworld implémenté et testé (reset/step, récompenses,
      obstacles, état terminal).
- [ ] Agent Q-learning implémenté (Q-table, sélection d'action, mise à jour TD).
- [ ] Boucle d'entraînement + logging des métriques.
- [ ] Analyse des résultats (courbes, politique apprise, sensibilité aux
      hyperparamètres).
- [ ] README et présentation portfolio.

## Décisions prises et pourquoi
- **C++ plutôt que Python** : entraînement délibéré au C++ pour le portfolio ;
  le surcoût (gestion mémoire, tooling) est assumé comme partie de l'exercice.
- **Aucune librairie RL ni Gym** : l'objectif est de comprendre les rouages, pas
  de produire l'agent le plus performant.
- (à compléter au fil du projet)

## Points de blocage résolus
- (aucun pour l'instant)

## Points de blocage en cours
- Prérequis théoriques pas encore explicitement validés.
- Décisions de tooling C++ non prises.

## Prochaine étape prévue
1. Valider les prérequis théoriques ci-dessus (courte session de vérification par
   questions).
2. Arrêter les décisions d'architecture : quelles classes, quelles
   responsabilités, quel build system, quel framework de test.
3. Écrire la structure de fichiers cible dans ce document avant d'écrire la
   moindre ligne de code.
