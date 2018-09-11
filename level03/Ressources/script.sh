#!/bin/sh

numero=322424824
limite=322424845

while test $numero != $limite;
    do
	echo "$(($numero))\n" | ~/level03;
	echo "$(($numero))"
	numero=$(($numero + 1));
done;