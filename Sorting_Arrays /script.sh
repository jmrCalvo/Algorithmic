#!/bin/bash
#si existe la carpeta y tiene los archivos
rm datos/*
rmdir datos
mkdir datos
#echo "" >> salida.dat
echo "Empezando fibonacci "

cont=0
while [ $cont -lt 60 ];
do
	echo "iter no $cont"
	./fibonacci $cont >> datos/fibonacci.dat
     let cont=cont+2
done

echo "Empezando floyd "

cont=50
while [ $cont -lt 1500 ];
do
	./floyd $cont >> datos/floyd.dat
     let cont=cont+50
done



echo "Empezando burbuja "

cont=1000
while [ $cont -lt 30000 ];
do
	echo " BURBUJA iter no $cont "
	./burbuja $cont >> datos/burbuja.dat
     let cont=cont+1000
done

echo "Empezando insercion "


cont=1000
while [ $cont -lt 30000 ];
do
	./insercion $cont >> datos/insercion.dat
     let cont=cont+1000
done

echo "Empezando seleccion "

cont=1000
while [ $cont -lt 30000 ];
do
	./seleccion $cont >> datos/seleccion.dat
     let cont=cont+1000
done

echo "Empezando mergesort "


cont=1000
while [ $cont -lt 30000 ];
do
	./mergesort $cont >> datos/mergesort.dat
     let cont=cont+1000
done

echo "Empezando quicksort "

cont=1000
while [ $cont -lt 30000 ];
do
	./quicksort $cont >> datos/quicksort.dat
     let cont=cont+1000
done

echo "Empezando heapsort "

cont=1000
while [ $cont -lt 30000 ];
do
	./heapsort $cont >> datos/heapsort.dat
     let cont=cont+1000
done


