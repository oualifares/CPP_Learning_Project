# Se familiariser avec l'existant

## A- Exécution

Compilez et lancez le programme.

Allez dans le fichier `tower_sim.cpp` et recherchez la fonction responsable de gérer les inputs du programme.
Sur quelle touche faut-il appuyer pour ajouter un avion ?
Comment faire pour quitter le programme ?
A quoi sert la touche 'F' ?

Ajoutez un avion à la simulation et attendez.
Que est le comportement de l'avion ?
Quelles informations s'affichent dans la console ?

Ajoutez maintenant quatre avions d'un coup dans la simulation.
Que fait chacun des avions ?

```c++
La fonction responsable de gérer les inputs du programme est create_keystrokes() dans la
classe tower_sim.cpp.
Pour ajouter un avion aléatoire il faut appuyer sur la touche ‘c’, la touche ‘q’ permet de quitter
le programme et la touche ‘f’ place le simulateur en mode plein ecran et ‘+’/’-’ pour
manipuler le zoom.
Ajoutez un avion à la simulation et attendez. Que est le comportement de l'avion ? Voler,
atterrir, aller au terminal et s'envoler.
Quelles informations s'affichent dans la console ? Lorsque l'aéronef atterrit, décolle et lorsque
le terminal démarre / arrête l'entretien d'un aéronef
Quand on ajoute 3 avions puis 4, Les trois premier se pose et rejoigne un terminal tandis que
le 4ème attend qu’un terminal se libère en tournant autour de l’aéroport.

```
## B- Analyse du code

Listez les classes du programme à la racine du dossier src/.
Pour chacune d'entre elle, expliquez ce qu'elle représente et son rôle dans le programme.

Pour les classes `Tower`, `Aircaft`, `Airport` et `Terminal`, listez leurs fonctions-membre publiques et expliquez précisément à quoi elles servent.
Réalisez ensuite un schéma présentant comment ces différentes classes intéragissent ensemble.

Quelles classes et fonctions sont impliquées dans la génération du chemin d'un avion ?
Quel conteneur de la librairie standard a été choisi pour représenter le chemin ?
Expliquez les intérêts de ce choix.
```c++
Waypoint: un point sur un chemin d'un avion, c'est juste un Point3D avec l'information si ce
point se trouve au sol, chez un terminal ou dans l'air; ici, on voit aussi qu'un "chemin" est un
dequeue de Waypoints.
Tower_Sim: une classe pour la gestion de la simulation: creation de l'aeroport, affichage de
l'usage sur la ligne de commande, creation des avions … .
Runway: stocke le début et le fin d'un piste de décollage
Displayable: c’est une classe abstraite qui représente les objets qu’on peut dessiner dans le
projet. La classe contient une coordonné qui permet de trier les objets de cette classe.
DynamicObject: une classe abstraite qui forme la base pour tous les objets qui ont la
spécificité de bouger (de faire bouger un autre objet pour le cas du terminal).
Image: une classe qui gère les octets d'une image. Utilisé dans la classeTexture2D
MediaPath: une classe qui gère l'acces aux PNGs qui vont avec le code
Point2D: classes qui gèrent des maths entre points dans l'espace 2D
Point3D : classes qui gèrent des maths entre points dans l'espace 3D
AircraftType: le type d'un avion stocke des limites de vitesse et accélération ainsi que la
texture; il y a 3 types pré-definit.

AirportType: contiennent les coordonnés importantess (relatives à l’aéroport) comme le
début/fin des runways (il peut en avoir plusieurs); chaque AirportType peut générer des
chemins pour atterrir et pour décoller.
Aircraft : represente les avions du projet. Cette classe herite de DynamicObject et
Displayable
distance_to(): renvoir la distance entre cet avion et un point
display() : afficher l'avion
move() : mise à jour de la position de l'avion
Airport: gère l'aéroport, contient les terminaux et le Tower. La classe Tower est friend class
de Airport et elle seule peut réserver des terminaux et demander un chemin de décollage
get_tower() : renvoie la tour de contrôle
display() : affiche l'aéroport
move() : fait bouger tous les terminaux
Tower: classe qui gère la fonctionnalité de la tour de contrôle; des avions peuvent demander
des nouvelles instructions ainsi qu'indiquer qu'ils sont arrivés à leur terminal; Chaque Tower
contient une affectation des avions aux terminals. Si un avion demande d'atterrir à un moment
quand tous les terminals de l'aéroport sont affectés, alors le tower retourne un "cercle" autour
de l'aéroport pour que l’avion redemande quand il a fini son cercle
get_instructions (Aircraft&) : génère des instructions pour l'avion
arrived_at_terminal (Aircraft&) : récupère le terminal sur lequel doit se poser l'avions
et ensuite lui donne l'avion
Terminal: classe qui gère le débarquement d'un avion. Chaque Terminal ne peut pas
débarquer qu'un seul avion à la fois
in_use() : renvoie true s'il est en cours d'utilisation
is_servicing() : renvoie true de moment qu'il n'a pas fini de s'occuper de l'avion
assign_craft() : assigne un nouvel avion.
start_service() : affiche un message et commence à s'occuper de l'avion
finish_service() : affiche un message et supprime la reférence sur l'avion
move() : incremente le conteur le temps du service.
Les classes Waypoint, Airport et Tower sont impliquées dans la génération du chemin d’un
avion par le biais des fonctions get_instructions, reserve_terminal, get_circle,
reserve_terminal, et start_path. Pour représenter le chemin d’un avion on utilise un queue.
Une queue parce qu'on veut ajouter des points à la fin et pouvoir les récupérer à partir du
début.

```




## C- Bidouillons !

1) Déterminez à quel endroit du code sont définies les vitesses maximales et accélération de chaque avion.
Le Concorde est censé pouvoir voler plus vite que les autres avions.
Modifiez le programme pour tenir compte de cela.

```c++
    elles sont définies dans AircraftTypes
    dans la classe Aircraft_factory. La Concorde est plus rapide en changeant les valeurs lors de
    sa construction.

```

2) Identifiez quelle variable contrôle le framerate de la simulation.
Ajoutez deux nouveaux inputs au programme permettant d'augmenter ou de diminuer cette valeur.
Essayez maintenant de mettre en pause le programme en manipulant ce framerate. Que se passe-t-il ?\
Ajoutez une nouvelle fonctionnalité au programme pour mettre le programme en pause, et qui ne passe pas par le framerate.
```c++
la variable qui s’occupe est GL::tick_per_frame. 
pour contrôler la frame j’ai ajouté deux
inputs ‘z’ et ‘a’, j’ai été contraint de gérer le cas ou le frame descend en dessous de 0 pour ne
pas avoir un bug donc il a fallu l’empecher de descendre de 1. Pour pause il a fallu ajouter un


```

3) Identifiez quelle variable contrôle le temps de débarquement des avions et doublez-le.
```c++
champ boolean dans opengl-interface pour ma variable qui contrôle le temps de débarquement
des avions est SERVICE_CYCLES.
constexpr unsigned int SERVICE_CYCLES = 40u;


```

4) Lorsqu'un avion a décollé, il réattérit peu de temps après.
Faites en sorte qu'à la place, il soit retiré du programme.\
Indices :\
A quel endroit pouvez-vous savoir que l'avion doit être supprimé ?\
Pourquoi n'est-il pas sûr de procéder au retrait de l'avion dans cette fonction ?
A quel endroit de la callstack pourriez-vous le faire à la place ?\
Que devez-vous modifier pour transmettre l'information de la première à la seconde fonction ?

```c++
On peut savoir que l’avion a été supprimé dans Aircraft::move, il n'est pas sûr de procéder
au retrait de l'avion dans cette fonction ,l’implémentation actuelle fait qu’il est préférable de
le faire dans GL::move_queue .On peut faire la callstack dans GL::timer. j’ai changé la
signature de la fonction. Elle retourne désormais un un booléen pour transmettre l'information
de la première à la seconde fonction.


```

5) Lorsqu'un objet de type `Displayable` est créé, il faut ajouter celui-ci manuellement dans la liste des objets à afficher.
Il faut également penser à le supprimer de cette liste avant de le détruire.
Faites en sorte que l'ajout et la suppression de `display_queue` soit "automatiquement gérée" lorsqu'un `Displayable` est créé ou détruit.
Pourquoi n'est-il pas spécialement pertinent d'en faire de même pour `DynamicObject` ?

```c++
On met l'ajout et la suppression des elements de la display queue dans le constructeur et le
destructeur de Displayable. On peut donc retirer les ajouts et les suppressions .Il n’est pas
pertinent de faire de même pour un DynamicObject car ces derniers ont un comportement
moins prévisible. Les avions peuvent crasher par exemple ou simplement finir leur service et
quitter la scène etc.


```

6) La tour de contrôle a besoin de stocker pour tout `Aircraft` le `Terminal` qui lui est actuellement attribué, afin de pouvoir le libérer une fois que l'avion décolle.
Cette information est actuellement enregistrée dans un `std::vector<std::pair<const Aircraft*, size_t>>` (size_t représentant l'indice du terminal).
Cela fait que la recherche du terminal associé à un avion est réalisée en temps linéaire, par rapport au nombre total de terminaux.
Cela n'est pas grave tant que ce nombre est petit, mais pour préparer l'avenir, on aimerait bien remplacer le vector par un conteneur qui garantira des opérations efficaces, même s'il y a beaucoup de terminaux.\
Modifiez le code afin d'utiliser un conteneur STL plus adapté. Normalement, à la fin, la fonction `find_craft_and_terminal(const Aicraft&)` ne devrait plus être nécessaire.

```c++
J’ai utilisé une std::map pour pouvoir faire les opérations de suppression et de recherche en
O(1).
```

## D- Théorie

1) Comment a-t-on fait pour que seule la classe `Tower` puisse réserver un terminal de l'aéroport ?
```c++
-Pour que la classe Tower puisse être la seule à pouvoir réserver un terminal de l'aéroport on
fait en sorte que seul Airport appel la methode assign_craft.
```

2) En regardant le contenu de la fonction `void Aircraft::turn(Point3D direction)`, pourquoi selon-vous ne sommes-nous pas passer par une réference ?
Pensez-vous qu'il soit possible d'éviter la copie du `Point3D` passé en paramètre ?
```c++
L’objet direction est modifié dans la méthode turn, si on le prenait par référence cela aurait
été contraire aux principes des bonnes pratiques la programmation orientée objet.
On aurait pu prendre direction par référence mais il aurait fallu faire les traitements autrement.

```

## E- Bonus

Le temps qui s'écoule dans la simulation dépend du framerate du programme.
La fonction move() n'utilise pas le vrai temps. Faites en sorte que si.
Par conséquent, lorsque vous augmentez le framerate, la simulation s'exécute plus rapidement, et si vous le diminuez, celle-ci s'exécute plus lentement.

Dans la plupart des jeux ou logiciels que vous utilisez, lorsque le framerate diminue, vous ne le ressentez quasiment pas (en tout cas, tant que celui-ci ne diminue pas trop).
Pour avoir ce type de résultat, les fonctions d'update prennent généralement en paramètre le temps qui s'est écoulé depuis la dernière frame, et l'utilise pour calculer le mouvement des entités.

Recherchez sur Internet comment obtenir le temps courant en C++ et arrangez-vous pour calculer le dt (delta time) qui s'écoule entre deux frames.
Lorsque le programme tourne bien, celui-ci devrait être quasiment égale à 1/framerate.
Cependant, si le programme se met à ramer et que la callback de glutTimerFunc est appelée en retard (oui oui, c'est possible), alors votre dt devrait être supérieur à 1/framerate.

Passez ensuite cette valeur à la fonction `move` des `DynamicObject`, et utilisez-la pour calculer les nouvelles positions de chaque avion.
Vérifiez maintenant en exécutant le programme que, lorsque augmentez le framerate du programme, vous n'augmentez pas la vitesse de la simulation.

Ajoutez ensuite deux nouveaux inputs permettant d'accélérer ou de ralentir la simulation.
