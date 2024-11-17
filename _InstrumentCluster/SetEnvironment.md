## Overview
This document outlines the necessary dependencies and setup steps for both the host machine and the PiRacer. Proper installation of these dependencies is crucial for the successful operation and development on the PiRacer, which uses Debian bullseye and qt5.

## Host Machine Setup
### Dependencies
On the host machine, you need to install Qt dependencies and Docker.

Below are the commands to set up the required environment:

Update the package list and upgrade existing packages:

```　bash
sudo apt-get update
sudo apt-get upgrade
```

Install essential development tools and other necessary packages:

```　bash
sudo apt-get install gcc git bison python gperf pkg-config gdb-multiarch
sudo apt install build-essential
```

Additional Tools
Docker installation might be required for containerized development and deployment. Follow the official Docker installation guide for your specific OS.

## PiRacer Setup
### Dependencies
The PiRacer requires several Qt dependencies to be installed. The following commands will install the necessary packages on a Debian bullseye system:

Install build dependencies for various Qt components:

```　bash
sudo apt-get build-dep qt5-qmake
sudo apt-get build-dep libqt5gui5
sudo apt-get build-dep libqt5webengine-data
sudo apt-get build-dep libqt5webkit5
```

Install additional required libraries:

```　bash
sudo apt-get install libudev-dev libinput-dev libts-dev libxcb-xinerama0-dev libxcb-xinerama0 gdbserver
```

## Summary
Ensure that both the host machine and PiRacer have the necessary dependencies installed as outlined above.
Proper setup of these dependencies is essential for the smooth development and operation of the PiRacer environment.
