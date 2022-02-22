# Ubuntu installation guide
This guide will be newbie friendly for linux beginners.  
Requirements:
* x64 compatible cpu
* internet access
* 64 GB free space
* 8 GB minimum RAM (32+ GB when not using swap)
* 8 GB usb drive (not required for VM)

ZED SDK requirements
* Nvidia GPU with CUDA support
* Nvidia proprietary drivers

## Download Ubuntu
get ubuntu here: 
[https://ubuntu.com/download/desktop/thank-you?version=20.04.3&architecture=amd64](https://ubuntu.com/download/desktop/thank-you?version=20.04.3&architecture=amd64)
installation is the same as the manjaro install

# manjaro installation guide
This guide will be newbie friendly for linux beginners.  
Requirements:
* x64 compatible cpu
* internet access
* 64 GB free space
* 8 GB minimum RAM (32+ GB when not using swap)
* 8 GB usb drive (not required for VM)

ZED SDK requirements
* Nvidia GPU with CUDA support
* Nvidia proprietary drivers

## Download Manjaro
In this guide the manjaro-kde distro will be used: to download Manjaro go to [https://manjaro.org/downloads/official/kde/](https://manjaro.org/downloads/official/kde/)


## Flashing installation
VM users can skip to `INSERT INSTALL LINK`

Download [etcher](https://www.balena.io/etcher/) or another usb flasher
1. Select the downloaded ISO
2. Select the USB stick you want to flash to
3. Select Flash

![etcher install](https://i.imgur.com/FULNGzu.png)

## Booting to the usb
Shut down your computer and go to the BIOS
Windows users can shift click the restart button from the start menu and go to `repair` -> `advanced` -> `UEFI setings`
In the UEFI go to boot and select the USB disk as first to boot.

## Booting the OS
When the pc has booted you should be greeted with the following screen:
![manjaro grub](https://i.imgur.com/2Lwh08k.png)
If you have a `Nvidia` GPU in your pc select the `Boot with proprietary drivers`
If you only have an AMD or intel GPU the option doesn't matter.

## Installing Manjaro
After the os has loaded you should be greeded with an welcome screen 

![welcome screen](https://i.imgur.com/LgA6n9B.png)

Select the `Launch installer`
You are now greeded with the installer
Select `American English` as language even if you are not a native speaker this will help with debugging and support as not all programs are availible in other languages.
select `Next`
Select your correct region `next` Select your keyboard layout.

### Installing on disk
You should now see the following screen:

![](https://i.imgur.com/nSAHCm5.png)

This is where we install the os on the harddisk.
You should select the correct disk on the top of the window.
When your correct disk is selected you can choose to erase the disk or install alongside.
Assuming you want to keep your Windows OS select the install alongside.
Make the Manjaro partition 64 GB in size.

`Next`

Setup a name and password.

`Next`

Read the summary and doublecheck that you make the changes to the right disk.

`Install`

You should now see the following page just wait.
Grab a cup of tea or a beer if that is more your thing sit back and relax.
![install page manjaro](https://i.imgur.com/MwvAk1K.png)

![done](https://i.imgur.com/0Rgww4r.png)

When the install is done reboot the computer.


