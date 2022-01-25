# Nabaztag-Source-Code

Original source code for Nabaztag V2 (Nabaztag:tag)

# Vous rappelez-vous de Nabaztag:Tag?

Nabaztag:Tag c'est (c'était) le lapin connecté de la société Violet.  

Ceci ne concerne que la V2.

Violet à malheureusement connu de gros problèmes financiers, a été reprise par la société Mindscape, qui elle aussi a eu de gros problème financiers.  

Résultats...  Les serveurs permettant aux Nabaztag:Tag de vivre on été arrêtés, laissant tous les lapins sans terrier.

Beaucoup de serveurs alternatifs, de solutions alternatives ont depuis vu le jour.

Mais surtout, Mindscape a mis les codes sources à disposition pour que les pationnés puissent faire revivre leur lapin.

Ce sont donc ici les codes sources originaux de la société Mindscape.

# Mon projet

Les analyser, les comprendre, faire revivre mon lapin ou utiliser ses composants pour un autre projet.

# Informations utiles

Le firmware du lapin est un logiciel de bas niveau.  Il doit être compilé en utilisant les outils de développement AVR-IAR et il ne peut être mis à jour sur le lapin qu'en utilisant la sont de programmation adéquate.

Le language utilisé pour le firmware est le C.  Les sources se trouve dans Hardware/compilateur/Projet-IAR.

Le firmware comprend :
<li>
Tous les drivers de chaque élément interne du lapin (WIFI, USB, LED, RFID, ...).
Un OS permettant la gestion du multitâche, l'interraction entre les différents driver.
Une machine virtuelle pour exécuter le code Metal compilé (Metal = Méta Language créé par un des créateurs du lapin : Sylvain Huet).  TODO : + d'info sur le langage Metal?
Le bc-boot (bytecode boot) compilé : fichier bc.c
</li>
