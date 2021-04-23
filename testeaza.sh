
sudo rm putere_si_rata.txt;
sudo touch putere_si_rata.txt;

sudo rm tshark.txt;
sudo touch tshark.txt;

#pornesc tshark si redirectionez in fisierul ok.txt
setsid sudo tshark -i wlan0 -Y tcp.port==80 > tshark.txt  &
#sudo gcc server.c -o server; setsid sudo ./server 80 &	#pornesc serverul
#sudo gcc client.c -o client; sleep 2; setsid sudo ./client 192.168.100.197 80 video2.mp4 & #pornesc clientul si cu && celelalte se vor executa doar cand transferul este gata si daca el s-a efectuat cu succes

sudo gcc client.c -o client; sleep 2; setsid sudo ./client localhost 80 video2.mp4 & #pornesc clientul si cu && celelalte se vor executa doar cand transferul este gata si daca el s-a efectuat cu succes

#cat timp clientul ruleaza, preiau informatii despre rata si putere pentru a face o rata a lor

while (pgrep -f "./client localhost 80 video2.mp4")
#while (pgrep -f "./client 192.168.100.197 80 video2.mp4")
do
  sudo setsid iwconfig wlan0 >> putere_si_rata.txt; #pentru a vedea rata si puterea folosesc iwconfig si pun in fisier rezultatul
done



sudo gcc extrage_puterea_si_rata.c -o rateAndPower; setsid sudo ./rateAndPower putere_si_rata.txt; #extrage exact puterea si rata pe care le scrie in fisierul cu rezultate partiale

sudo gcc no_of_duplicates.c -o dup; sudo ./dup tshark.txt; #calculez rata de duplicate si o scriu in fisierul cu rezultate partiale


