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

Le <b>firmware</b> du lapin est un logiciel de bas niveau.  Il doit être compilé en utilisant les outils de développement AVR-IAR et il ne peut être mis à jour sur le lapin qu'en utilisant la sont de programmation adéquate (TODO : Vérifier s'il s'agit de l'emplacement libre sur la carte du Nabaztag).

Le language utilisé pour le firmware est le C.  Les sources se trouve dans Hardware/compilateur/Projet-IAR.

Le firmware comprend :
<ul>
	<li>Tous les drivers de chaque élément interne du lapin (WIFI, USB, LED, RFID, ...).</li>
	<li>Un OS permettant la gestion du multitâche, l'interraction entre les différents driver.</li>
	<li>Une machine virtuelle pour exécuter le code Metal compilé (Metal = Méta Language créé par un des créateurs du lapin : Sylvain Huet).  TODO : + d'info sur le langage Metal?</li>
	<li>Le bc-boot (bytecode boot) compilé : fichier bc.c.</li>
</ul>

REM : Si on voulait mettre à jour le firware, il faudrait pouvoir le mettre à jour physiquement sur le lapin.  Est-ce possible/utile?

La <b>machine virtuelle</b> exécutant le code Metal compilé utilise 2 fichiers bc (bytecode) :
<ul>
	<li><b>bc-boot</b> : dans le répertoire Hardware/bytecode/bc-boot.<br/>
	Il est chargé à chaque démarrage.<br/>
	Il peut être modifié via l'interface de configuration mais il n'est pas conseillé de le faire car une erreur pourrait rendre le lapin inutilisable.<br/>
	Il n'est peut-être de toute facçon pas utile de vouloir le modifier car ce fichier permet de gérer la configuration (en démarrant le lapin tout en appuyant sur le bouton et ensuite en se connectant à celui-ci) et ensuite à charger le fichier bc-nominal et l'exécuter.
	</li>
	<li><b>bc-nominal</b> : dans le répertoire Hardware/bytecode/bc-nominal.<br/>
	Chargé à partir du serveur sur lequel se connecte le lapin et est ensuite exécuté.<br/>
	Il charge un nouveau logiciel sur le lapin à chaque fois qu'il se connecte sur un serveur.<br/>
	Il permet de gérer entièrement le lapin au niveau du réseau, des oreilles, des leds, du bouton, du rfid.<br/>
	Il permet aussi de lire des MP3 directement depuis le lapin (TODO voir comment on met des MP3 sur le lapin).<br/>
	C'est donc sur ce fichier qu'il est préférable de travailler.<br/>
	REM : les sources contiennent également un dossier nommé nominal_splitted qui permettra peut-être de mieux analysé ce fichier bc-nominal (TODO).
	</li>	
</ul>

Le <b>langage Metal</b> est donc un langage créé par Sylvain Huet.<br/>
On peut trouver la documentation de ce langage sur son site : <a href="http://www.sylvain-huet.com/rsc/metal/doc/Metal.html">http://www.sylvain-huet.com/rsc/metal/doc/Metal.html</a>.<br/>
Il existe également un document dans le répertoire Hardware/Outils/Docs qui décrit brièvement la grammaire et les principes de ce langage.

Pour créer le binaire à partir du fichier bc-nominal.mtl il faut utilisé un compilateur qui est heureusement fourni dans les sources.

Il y a une version Windows et une version Linux.

Je ne possède pas d'environnement Linux, donc je ne m'intéresserai qu'à la version Windows disponnible dans le répertoire Hardware/compilateur/Projet-VS.

# Ressources intéressantes 

<a href="http://www.sylvain-huet.com/chronology.php#nabv2">http://www.sylvain-huet.com/chronology.php#nabv2</a>


