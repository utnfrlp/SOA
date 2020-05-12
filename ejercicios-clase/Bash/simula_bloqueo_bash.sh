PID=1
PTOTAL=10

contar() {
  # leo el contador,
  # si justo otro "proceso" está leyendo simulo que el contador está en 0
  LEE_CONTADOR=$(cat contador.txt)
  CONTADOR=${LEE_CONTADOR:-0}
  # echo "Proceso: $1, contador: $CONTADOR"

  let COND=PID%2
  if [ $COND -eq 0 ] || [ $CONTADOR -ge 2 ]
  then
    let CONTADOR++
    echo $CONTADOR > contador.txt
    echo "Proceso $1 incrementa contador a $CONTADOR"
  else
    sleep 1
    contar $PID
  fi
}

# inicializo "contador" en 0
touch contador.txt
echo 0 > contador.txt
echo "________________________inicio"

# simulo creación de 10 procesos
while [[ $PID -ne $PTOTAL ]]
do
  contar $PID &

  let "PID++"
done


wait
echo "________________________fin"
rm contador.txt
