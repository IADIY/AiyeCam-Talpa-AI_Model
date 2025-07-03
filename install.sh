sudo ~
sudo apt install build-essential
sudo apt install make libmpc-dev
sudo apt install libftdi1-dev
sudo apt install python3 python3-pip
sudo pip3 install pyelftools
pip install gdown
sudo ln -s ~/.local/bin/gdown /usr/bin/gdown
gdown https://drive.google.com/uc?id=1A9zqGXgxTyUZky_cSemNg_FN1VOsNNYs

chmod -R 777 nbsdk.tar.gz
tar -zvxf nbsdk.tar.gz
chmod -R 777 nbsdk/