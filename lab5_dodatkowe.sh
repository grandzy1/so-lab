#!/bin/bash

echo "Wprowadz partycje dla ktorej powinno sie sprawdzic dostepne miejsce"
echo "FORMAT: nazwa partycji np. sda1, sdb2"

read PARTITION

DATE=$(date +"%Y%m%d-%H%M%S")
FILENAME="Report_$DATE.txt"
DF=$(df -h /dev/$PARTITION)

lsblk > drives.txt

echo "Dostepne dyski: " > "$FILENAME"
cat drives.txt >> "$FILENAME"

echo "Miejsce dostepne na wybranej partycji: " >> "$FILENAME"
echo $DF >> "$FILENAME"

rm drives.txt

echo "Plik $FILENAME zostal zapisany w $(pwd)"