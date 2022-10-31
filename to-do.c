Ex : echo "ls | test" >> file | wc -l | cat -e "$USER"

I.LEXING
/*ou Tokenization : Conversion d’une chaîne de caractères en une liste de symboles.
Elle fait partie de la première phase de la chaîne de compilation
*/
1) PARCOURIR LA STRING 
a) identifier chaque element : //OK
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
- variable d environnement precedee d un "$" // NO
- $? : doit être substitué par le statut de sortie de la dernière pipeline exécutée au premier plan // NO

b) mettre chaque element avec leurs infos (type) dans un maillon //OK
c) modifier les maillons selon type :
	- si option d une commande, join les maillons de la commande et de l option //OK
	- si guillemets : regarder si $ et changer le type du maillon
	
d) construire tableau de commandes

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