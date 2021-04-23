#sterg tot ce e de forma *_rata_*, *_putere_*, *_dup_*
while read line 
do
   ONE=`echo $line | cut -d'_' -f1`
   TWO=`echo $line | cut -d'_' -f2`

  rm ${ONE}_rata_${TWO}.txt
  rm ${ONE}_putere_${TWO}.txt
  rm ${ONE}_dup_${TWO}.txt

done < toate_testele.txt

#sterg si celelalte fisiere
rm aux.txt
rm rezultate_partiale.txt
rm rezultate_finale.txt
rm nr_deja_reluate.txt
rm se_testeaza_acum.txt
rm toate_testele.txt
rm nr_retestari.txt
rm plot_file.txt
rm rez_partiale.txt
rm data.txt
rm tshark.txt
rm client
rm server
rm listeaza
rm rateAndPower
rm putere_si_rata.txt
rm incaperi.txt
rm cumuleaza
rm listeaza
rm indice_final
rm top3
rm top3.txt
rm dup
rm c1.wmv
rm f
rm myapp-bin
rm sinx.png
rm data.png
rm sesiuni.txt
touch sesiuni.txt


#reinitializez numarul sesiunii
sudo echo 1 > nr_sesiunii.txt

