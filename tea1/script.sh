#! /bin/bash

getL () {
	FIC=$1
	NUMLIGNE=$2
	cat $FIC | head -n $NUMLIGNE | tail -n 1
}

hasOp() {
	EXP=$1
	echo "$EXP" | grep -c "+\|-\|x\|/"
}

hasEq(){
	EXP=$1
	echo "$EXP" | grep -c "="
}

getCalc() {
	EXP=$1
	echo "$EXP" | cut -d'=' -f1
}

getRes() {
	EXP=$1
	echo "$EXP" | cut -d'=' -f2 | tr -d ' '
}

isEmpty() {
	EXP=$1
	TAILLE=$(echo $EXP | wc -w)
	if [ $TAILLE -ge 1 ]
	then 
		echo 0
	else 
		echo 1
	fi
}

addQuotes() {
	for i in $@
	do
		if [ $i = "x" ]
		then 
			echo -n ' "*" '
		else 
			echo -n " $i"
		fi
	done
}

evalCalc() {
	EXP="expr $(addQuotes $1)"
	eval $EXP
}

verif() {
	ARGS=$1
	./compteestbon.exe $ARGS 2>/dev/null >aux
	NBL=$(cat aux | wc -l)

	echo "$NBL lignes trouvées"

	NUML=1
	while [ $NUML -le $NBL ]
	do 
		L=$(getL aux $NUML)
		echo -n "Verification de la ligne $NUML ($L) "
		
		if [ $(hasOp "$L") -ne 1 ]
		then 
			echo ""
			echo "pas d'opérateur ! Fichier incorrect !"
			exit 1
		fi
		
		if [ $(hasEq "$L") -ne 1 ]
		then 
			echo ""
			echo "pas de symbole = ! Fichier incorrect !"
			exit 1
		fi
		
		CALC=$(getCalc "$L")	
		ECALC=$(evalCalc "$CALC")
		RES=$(getRes "$L")
		
		if [ $ECALC -ne $RES ]
		then 
			echo ""
			echo "résultat incorrect !"
			exit 1
		fi
		
		echo "OK"
		
		NUML=$(expr $NUML + 1)
	done
	
	echo ""
}

echo "exécution du programme avec un jeu d'essai exact"
verif "3 5 7 9 25 50 859"


echo "exécution du programme avec un jeu d'essai approché"
verif "2 2 3 4 6 10 631"

