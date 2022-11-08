Ex : 
echo "ls | test" >> file | wc -l | cat -e "$USER"
echo "ls | test" >> file"lol" | wc -l | cat -e "$USER"
echo "hi$test lol" >> file | wc -l | cat -e "$USER"
echo "hi$USER lol" >> file | hihi$LANG wc -l | cat -e "$USER" '$USER' $USER
echo "coucou '$U"S"ER'" salut $USER
echo "coucou U"S"ER" salut $USER ""
echo coucouU"S"ER salut $USER ""


echo $-USER // - ! 
himBHsUSER

echo $=USER // = % ^ + / . ~
$=USER

echo $@USER // @ * 12 123 ignore 1er, affiche les suivants
USER

echo $#USER
0USER

echo $_USER

echo $\USER
$USER

echo $&USER // & ; | 
USER: command not found



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
- pipe // OK
- simple quotes : doit empêcher le shell d interpréter les méta-caractères présents dans la str entre les ' ' // OK
- double quotes : doit empêcher le shell d interpréter les méta-caractères présents dans la str entre les " " sauf le $ // faire fonction carac speciaux
- commande / builtins
- variable d environnement precedee d un "$" // OK
- $? : doit être substitué par le statut de sortie de la dernière pipeline exécutée au premier plan // NO

b) mettre chaque element avec leurs infos (type) dans un maillon //OK
c) modifier les maillons selon type :
	- si option d une commande, join les maillons de la commande et de l option //OK
	- si guillemets : regarder si $ et changer le type du maillon // OK
	
d) construire tableau de struc de commandes
mettre chaque morceau avant le pipe dans une structure qui contient 
- char ** avec chaque maillon 
- int fd_in
- int fd_out
- char *file_in


II.EXEC
/*quel comportement suivant le type d element, en prenant compte des pipes*/
au debut = recuperer shell level avec getenv puis ajouter +1 a chaque execution de nouveau minishell / bash


III.CODER BUILTINS
	◦ cd uniquement avec un chemin relatif ou absolu // OK
	◦ exit sans aucune option // OK
	◦ pwd sans aucune option
	◦ echo et option -n // OK
	◦ export var de lenvironnement sans aucune option 
	◦ unset sans aucune option
	◦ env sans aucune option ni argument