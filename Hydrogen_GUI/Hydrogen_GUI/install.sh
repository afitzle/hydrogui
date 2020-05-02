
echo "Installing xdot to display MVICFGs"
sudo apt-get install xdot
echo "Downloading docker... this may take awhile."
sudo apt-get install docker.io
echo "Downloading hydrogen image... this will take longer"
sudo docker pull ashwinkj/hydrogen_env
#persistent container
echo "Creating persistent container"
sudo docker run -t -d --name Hydrogen_Env ashwinkj/hydrogen_env
echo "Cloning hydrogen into container"
sudo docker exec Hydrogen_Env git clone https://github.com/iowastateuniversity-programanalysis/hydrogen.git /home/Hydrogen/MVICFG
sudo docker exec Hydrogen_Env mkdir /home/Hydrogen/MVICFG/BuildNinja
echo "Putting helper script in container and executing cmake + ninja"
sudo docker cp ninjahelp.sh Hydrogen_Env:/home/Hydrogen/MVICFG/
sleep 1
#cmake builds directories locally and it is a pain to configure so ninjahelp.sh takes care of that
sudo docker exec Hydrogen_Env chmod 777 /home/Hydrogen/MVICFG/ninjahelp.sh
sudo docker exec Hydrogen_Env bash /home/Hydrogen/MVICFG/ninjahelp.sh
echo "Done!"
