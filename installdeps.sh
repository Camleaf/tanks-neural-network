sudo apt update


echo "Installing deps"
sudo apt-get install libx11-dev libxi-dev libxrandr-dev libxcursor-dev libxi-dev libudev-dev libgl1-mesa-dev


echo "Setting up VCPKG"

# add setup conditional on if vcpkg is already insatlled

if [ ! -d "$HOME/vcpkg" ]; then
    cd "$HOME" || exit 1
    git clone https://github.com/microsoft/vcpkg.git
    cd vcpkg || exit 1
    ./bootstrap-vcpkg.sh
    echo -e 'Add to .bashrc:\nexport VCPKG_ROOT="$HOME/vcpkg"\nexport PATH="$VCPKG_ROOT:$PATH"'
else
    echo "VCPKG already exists"
fi
