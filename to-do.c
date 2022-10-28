DANS STRUCTURE
ajouter liste chainee 

I.LEXING
/*ou Tokenization : Conversion d’une chaîne de caractères en une liste de symboles.
Elle fait partie de la première phase de la chaîne de compilation
*/
1) PARCOURIR LA STRING 
a) identifier chaque element : 
- chevron (suivi forcement d un file)
	◦ < doit rediriger l entrée - ca remplace
	◦ > doit rediriger la sortie - ca remplace
	◦ << doit recevoir un délimiteur et lire l input donné jusqu à rencontrer une ligne	contenant le délimiteur. - ca met a la suite
		Cependant, l historique n a pas à être mis à jour !
	◦ >> doit rediriger la sortie en mode append. - ca met a la suite
- pipe
- simple quotes : doit empêcher le shell d interpréter les méta-caractères présents dans la str entre les ' '
- double quotes : doit empêcher le shell d interpréter les méta-caractères présents dans la str entre les " " sauf le $
- commande / builtins
- variable d'environnement precedee d'un "$"
- $? : doit être substitué par le statut de sortie de la dernière pipeline exécutée au premier plan

b) mettre chaque element avec leurs infos (type) dans un maillon
c) construire tableau de commandes en ayant modifier les maillons de la liste, selon leur type

II.EXEC
/*quel comportement suivant le type d element, en prenant compte des pipes*/


III.CODER BUILTINS
	◦ echo et l option -n
	◦ cd uniquement avec un chemin relatif ou absolu
	◦ pwd sans aucune option
	◦ export sans aucune option
	◦ unset sans aucune option
	◦ env sans aucune option ni argument
	◦ exit sans aucune option