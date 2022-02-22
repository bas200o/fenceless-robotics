# Ubuntu
## install packages

Run the following commands
`sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE || sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-key F6E65AC044F831AC80A06380C8B3A55A6F3EFCDE`  
`sudo add-apt-repository "deb https://librealsense.intel.com/Debian/apt-repo $(lsb_release -cs) main" -u`  
`sudo apt-get update`  
`sudo apt-get upgrade`  

`sudo apt-get install librealsense2-dkms librealsense2-utils libpcl-dev libopencv-dev python3-opencv build-essential qt5-default`  

Continue to the next chapter

# Updating the Manjaro system
Even though we just installed Manjaro we need to update the OS and packages.  
Manjaro uses pamac to update the system (Arch users can use pacman).  
To update the system open a terminal `f12` 

***

Execute the following command `sudo pamac update`
* `sudo` makes a command execute as root/administrator level allowing changes to the OS
* `pamac` the Manjaro package manager will later be replaced
* `update` the first argument for the pamac command telling the package manager to update the packages

You will be asked for your root password.
After a couple of seconds you will be asked `Apply transaction ? [y/N]` press y and enter.  
The terminal will now list a lot of information in the terminal just sit back and watch.  
If you have issues updating or get extra questions go to the troubleshooting section of the wiki [here](www.example.com).

# Installing packages
The following packages are needed to compile the programs: `base-devel yay`
* `base-devel` Basic development tools like GCC make etc
* `yay` the new package manager with acces to the [AUR](https://wiki.archlinux.org/title/Arch_User_Repository)

Run the following command to install the packages `sudo pamac install base-devel yay`

![pamac install](https://i.imgur.com/cKYXfpP.png)

When the installer asks to enter a selection just hit enter this will install all packages.  
After a couple of seconds you will be asked `Apply transaction ? [y/N]` press y and enter.

# Pre install configuration
Because the SDK's have to be compiled you need at least 32GB of ram.  
If you do not have that much installed you need to make a swap file.

## extra dependencies needed before installation
Run the command  
`sudo pacman -S gnuplot graphviz python python-mpi4py python-matplotlib openmpi qt5-x11extras qt5-webkit tk adios2 cgns ffmpeg gdal gl2ps glew hdf5 jsoncpp libarchive libharu liblas lz4 netcdf openimagedenoise openvdb openvr ospray pdal postgresql pugixml proj sqlite unixodbc openvdb utf8cpp vtk jdk-openjdk`

`:: Proceed with installation? [Y/n]` press `y` and `enter`


## Making a swap file
Run the following commands  
``` bash
sudo fallocate -l 16G /swapfile
sudo chmod 600 /swapfile
sudo mkswap /swapfile 
sudo swapon /swapfile
echo '/swapfile swap swap defaults 0 0' | sudo tee -a /etc/fstab
```

You now have a 16GB swapfile

# Installing realsense
To install the realsense SDK run the following command `yay librealsense`.  
You will get the following results.

![realsense install](https://i.imgur.com/QsEc6Is.png)

Select the 
```
aur/librealsense 'version number'
    Intel® RealSense™ SDK 2.0 is a cross-platform library for Intel® RealSense™ depth cameras (D400 series and the SR300) and the T265 tracking camera.

```
 In this case option 1.  
Just enter the number followed by the enter key.
You will be asked the following :
* `==> Remove make dependencies after install? [y/N]` press `n` and `enter`.
* `==> Diffs to show?` press `n` and enter.
* `:: Proceed with installation? [Y/n]` press `y` and `enter`

If you run into problem go to the troubleshooting section of the wiki [here](example.com)

# Installing ZED
To use the ZED SDK you need a CUDA capable GPU installed.  
Go to troubleshooting if you work in a VM [here](example.com)  
Go to troubleshooting if you have not selected the nvidia drivers at setup [here](example.com)  
Have an AMD or only intel GPU? Get a thunderbold dock with nvidia GPU or a nvidia gpu for a tower pc recommanded dock is a Razor Core X [link to tweakers.net](https://tweakers.net/pricewatch/1365868/razer-core-x.html)  

***
First install cuda from the pamac  
`sudo pamac install cuda`  
Follow the following guide [https://www.stereolabs.com/docs/installation/linux/](https://www.stereolabs.com/docs/installation/linux/)
![](https://i.imgur.com/XCPN9Eh.png)


# Installing PCL
Run the following command `yay pcl` the following results will show

![pcl yay](https://i.imgur.com/kmA7DIK.png)

select the package  
```
aur/pcl 'version number' 
    A comprehensive open source library for n-D Point Clouds and 3D geometry processing
```  

In this case number 11
* `==> Remove make dependencies after install? [y/N]` press `n` and `enter`.
* `==> Diffs to show?` press `n` and enter.
* `:: Proceed with installation? [Y/n]` press `y` and `enter`





