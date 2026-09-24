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
- Mode d'accompagnement souhaité : orienté objectif, pas de redécouverte
  socratique. Le tuteur demande un avis (une seule question ciblée, seulement
  sur un vrai choix de conception), corrige franchement en donnant la réponse
  complète, puis fournit un guide d'implémentation détaillé sans code (fichiers,
  classes/fonctions, entrées/sorties, étapes ordonnées, pièges, vérification).
  Le but est de comprendre et appliquer la technologie, pas de la redécouvrir.

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
- [x] Écrire à la main la règle de mise à jour de Q-learning et expliquer chaque
      terme (cible TD, erreur TD, rôle de alpha et gamma). Validé après
      dérivation guidée.
- [x] Expliquer pourquoi Q-learning est « off-policy » (politique cible =
      gloutonne via le max, politique de comportement = epsilon-greedy ;
      différence avec SARSA identifiée).
- [x] Énoncer les conditions qualitatives de convergence (couverture des paires
      état-action, décroissance de alpha). Validé : conditions de Robbins-Monro
      énoncées correctement sans indice (couverture infinie des paires (s,a),
      somme alpha_t = infini, somme alpha_t² < infini ; alpha=1/t les vérifie,
      alpha constant non — d'où le bruit résiduel avec alpha constant).
- [x] Arrêter les décisions de tooling C++ : build system, framework de test,
      organisation des fichiers. Build system et framework de test tranchés
      (CMake, GoogleTest) ; organisation des fichiers restant à détailler
      (prochaine étape).

Ressources proposées :
- Sutton & Barto, *Reinforcement Learning: An Introduction* (2e éd.),
  chap. 3 (MDP), 4 (programmation dynamique), 6 (TD ; section 6.5 = Q-learning).
- Cours David Silver (UCL/DeepMind), leçons 1 à 5.
- cppreference.com pour la STL et le C++ moderne.

## État d'avancement
Chaque jalon est accompagné de son critère de validation (« Fait quand »).

- [x] Projet choisi et cadré : Q-learning tabulaire, gridworld custom, C++,
      aucune lib RL.
- [x] Prérequis théoriques validés (règle de mise à jour, off-policy,
      conditions de convergence).
- [x] Décisions d'architecture arrêtées (classes, responsabilités, build, tests).
      Voir « Architecture v1 » dans « Décisions prises ».
- [ ] Structure de fichiers cible écrite dans ce document.
      Fait quand : l'arborescence (include/, src/, tests/, scripts/,
      CMakeLists.txt) figure dans ce fichier et un projet CMake vide compile
      avec un test GoogleTest trivial qui passe.
- [ ] Environnement gridworld implémenté et testé (reset/step, récompenses,
      obstacles, état terminal).
      Fait quand : tests unitaires verts sur reset (retour à l'état initial),
      déplacement contre un mur/obstacle, récompense et drapeau terminal à
      l'arrivée sur la cible, conversion position <-> indice d'état.
- [ ] Agent Q-learning implémenté (Q-table, sélection d'action, mise à jour TD).
      Fait quand : tests unitaires verts sur une mise à jour TD calculée à la
      main, sur epsilon = 0 (toujours l'action gloutonne) et sur le compteur
      de visites par paire (s,a).
- [ ] Boucle d'entraînement + logging des métriques.
      Fait quand : un entraînement complet produit un CSV (épisode, récompense
      cumulée, nombre de pas, epsilon) et la politique gloutonne finale atteint
      la cible en un nombre de pas minimal.
- [ ] Analyse des résultats (courbes, politique apprise, sensibilité aux
      hyperparamètres).
      Fait quand : script Python produisant la courbe de récompense, la carte
      de la politique (flèches) et de V(s) = max_a Q(s,a), plus une comparaison
      d'au moins deux réglages de alpha/epsilon.
- [ ] README et présentation portfolio.

## Décisions prises et pourquoi
- **C++ plutôt que Python** : entraînement délibéré au C++ pour le portfolio ;
  le surcoût (gestion mémoire, tooling) est assumé comme partie de l'exercice.
- **Aucune librairie RL ni Gym** : l'objectif est de comprendre les rouages, pas
  de produire l'agent le plus performant.
- **Pas de lib de plotting en C++ (pas de matplotlib-cpp)** : le C++ se limite
  à écrire les métriques d'entraînement (récompense par épisode, etc.) dans un
  CSV ; l'analyse et la visualisation se font a posteriori en Python. Pattern
  standard en RL/robotique industrielle (découplage exécution/diagnostic,
  évite une dépendance de build fragile à Python/numpy pour un gain nul en
  performance).
- **CMake comme build system** : standard de facto en C++ moderne.
- **GoogleTest (gtest/gmock) comme framework de test**, plutôt que Catch2 :
  c'est le framework utilisé par défaut dans ROS2 (`ament_cmake_gtest`), donc
  cohérent avec l'écosystème déjà pratiqué par l'apprenant.
- **Architecture v1** (arrêtée après correction de la première ébauche de
  l'apprenant, qui proposait GameState/Action en dataclasses, un GameHandler,
  une classe abstraite Player (Agent, KeyboardInput) et une classe abstraite
  UIHandler (temps réel, replay depuis logs)). Namespace C++ `qlearning`.
  - `types.hpp` : `enum class Action {Up, Right, Down, Left}` + constante
    `kNumActions = 4` (un enum, pas une struct : une action discrète est un
    indice de colonne de la Q-table) ; `struct Position {int row, col;}` ;
    `struct StepResult {int next_state; double reward; bool terminated;
    bool truncated;}` ; `struct Transition {int state; Action action;
    double reward; int next_state; bool terminated;}`.
  - `GridWorld` (environnement, passif, style Gym) : construit depuis un
    `GridConfig` immuable (largeur, hauteur, départ, cible, obstacles,
    récompenses, `max_steps`). Méthodes : `int reset()`,
    `StepResult step(Action)`, `int numStates()`, `int stateIndex(Position)`,
    `Position positionOf(int)`, `bool isBlocked(Position)`,
    `Position agentPosition()`, `const GridConfig& config()`. Ne connaît ni
    l'agent, ni la Q-table, ni epsilon, ni le rendu. L'agent ne voit que
    l'indice d'état entier s = row * width + col, jamais l'état complet.
    Choix v1 : un déplacement vers un mur/obstacle laisse l'agent sur place
    (pas terminal). Récompenses de départ : -1 par pas, +10 à la cible
    (terminal), `max_steps` = 4 * width * height (troncature).
  - `QLearningAgent` : Q-table en `std::vector<double>` contigu de taille
    S*A (indice s*A + a), compteurs de visites N(s,a) de même taille,
    `std::mt19937` seedé injecté par le constructeur. Méthodes :
    `Action selectAction(int s)` (epsilon-greedy, départage aléatoire des
    ex æquo), `Action greedyAction(int s) const`, `void update(const
    Transition&)`, `void decayEpsilon()`, accesseurs `epsilon()`, `q(s,a)`,
    `visitCount(s,a)`. Configuré par `QLearningConfig` (gamma, alpha constant
    ou 1/N(s,a), epsilon_start/min/decay). Ne connaît ni la grille ni les
    positions.
  - `train(...)` (module trainer) : **possède la boucle épisode/pas** ;
    appelle env.reset/step, agent.selectAction/update, decayEpsilon en fin
    d'épisode, produit un `EpisodeStats {episode, return, steps, epsilon,
    reached_goal}` par épisode transmis au logger.
  - `CsvLogger` : écrit `metrics.csv` ; une fonction d'export écrit
    `qtable.csv` (state, row, col, Q pour chaque action) — seul endroit
    autorisé à connaître à la fois l'env et l'agent (pour row/col).
  - `render` : fonctions libres d'affichage ASCII (grille, politique en
    flèches) vers un `std::ostream`, pour le debug.
  - `apps/train_main.cpp` : assemble le tout, écrit les CSV, affiche le
    chemin glouton final.
  Justifications des corrections apportées à l'ébauche :
  - La récompense était absente de l'ébauche : `step` doit renvoyer
    (s', r, terminated, truncated), sinon l'agent ne peut pas apprendre.
  - terminated vs truncated : sur terminated la cible TD est r ; sur
    truncated (limite de pas) on bootstrappe quand même r + gamma max Q(s')
    car l'état n'est pas réellement terminal.
  - La boucle appartient au trainer, pas au GameHandler : un environnement
    qui tire lui-même les actions d'un Player est intestable isolément et
    couple env et agent.
  - « Métaclasse » était le mauvais terme : en C++ on parle de classe de base
    abstraite (méthodes virtuelles pures). Aucune n'est nécessaire en v1.
  - Player/KeyboardInput et les UI temps réel / replay sont reportés au
    backlog (hors objectif pédagogique RL) ; une interface `Policy` avec
    `selectAction(int)` pourra être extraite plus tard si un joueur clavier
    est ajouté. Les « logs » de l'ébauche (trajectoires) sont distincts des
    métriques CSV.
- **Graphe de dépendances** : types <- GridWorld, QLearningAgent ;
  trainer -> GridWorld, QLearningAgent, CsvLogger ; main -> tout. GridWorld et
  QLearningAgent ne dépendent jamais l'un de l'autre (testables isolément).
- **GoogleTest récupéré via CMake FetchContent** (version épinglée) plutôt
  que le paquet système : build reproductible pour quiconque clone le repo.
- **C++17**, warnings stricts (-Wall -Wextra -Wpedantic -Wshadow
  -Wconversion), build hors source dans `build/`, pas de colcon/ament (projet
  CMake pur).

Backlog (hors v1) : joueur clavier, UI temps réel, replay de trajectoires,
comparaison avec SARSA, obstacles terminaux (variante « cliff »).

## Points de blocage résolus
- Confusion initiale possible sur alpha décroissant : alpha_t(s,a) doit être
  indexé sur le nombre de visites de la paire (s,a), pas sur le pas de temps
  global de l'entraînement (sinon les paires rarement visitées cessent
  quasiment d'apprendre). Conséquence pour l'architecture : l'agent doit
  maintenir un compteur de visites par paire (s,a).

## Points de blocage en cours
- (aucun pour l'instant)

## Prochaine étape prévue
1. Squelette du projet (guide fourni) : arborescence include/qlearning,
   src, apps, tests, scripts ; CMakeLists.txt avec bibliothèque
   `qlearning_core`, exécutable `train`, `unit_tests` via FetchContent
   GoogleTest + gtest_discover_tests ; un test trivial sur `types.hpp`.
   Fait quand : `cmake -S . -B build && cmake --build build && ctest
   --test-dir build` passe (1/1). Reporter l'arborescence ici ensuite.
2. Guide d'implémentation de `GridWorld`, implémentation par l'apprenant,
   revue de code par le tuteur.
