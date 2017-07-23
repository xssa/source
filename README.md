Custom LEDE Patch For TL-WR1043ND (With Working Fast Path)
==========================================================

Dependencies
------------

* LEDE BuildRoot
* LEDE BuildRoot Dependencies
* Java Runtime

How to use
----------

* Install all the development packages required for LEDE BuildRoot
* Install Java Runtime
* Clone the LEDE Repository

    git clone -b lede-17.01 https://github.com/lede-project/source.git lede

Clone this Repository and copy into the LEDE repository

    git clone -b lede-17.01 https://github.com/gwlim/mips24k-lede-patch.git temp; mv temp/* lede/; rm -rf temp

Change directory into the LEDE Repository

    cd lede

Run the script

./patch_LEDE.sh

Make Menuconfig Default Target Profile is TP-LINK TL-WR1043ND (all the packages and config is inside)
Make Menuconfig Default Target is TL-WDR4300 (all the packages and config is inside)
If you want to enable Fast Path select all the fast path modules in

Kernel Modules > Network Support > 

Select all the 3 modules

* kmod-fast-classifier
* kmod-shortcut-fe
* kmod-shortcut-fe-cm

    make menuconfig

Save and make

    make V=s
    
FAQ
---

I can't connect to certain websites, what is wrong?

* Go to Network > Firewall > General Settings

* Check on MSS Clamping


Where can I download the firmware for my Router?

https://github.com/gwlim/Fast-Path-LEDE-OpenWRT

The binaries in the link above will contain firmware build with this patchset
