sudo ~
# Check if wget is available
if command -v wget >/dev/null 2>&1; then
    echo "✅ wget is already installed at: $(command -v wget)"
else
    echo "❌ wget is NOT installed."
    echo "📦 Installing wget now..."

    # Update package list and install wget
    sudo apt update && sudo apt install -y wget

    # Check again after installation
    if command -v wget >/dev/null 2>&1; then
        echo "✅ wget has been successfully installed!"
    else
        echo "❌ Failed to install wget. Please check your network or package sources."
    fi
fi

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