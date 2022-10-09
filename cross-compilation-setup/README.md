## Description

Cross compilation setup using a Debian 10.4 VM on a Mac M1.

Workflow:

* start the VM, point VSCode-Remote to it;

* develop changes, cross-compile the final executable;

* sftp the executable into the BBB;

* run the executable from the BBB.

## The test program

Here's the test program used throughout this readme:

*testprogram.cpp*
```cpp
#include <iostream>

int main()
{
    int x{5};
    x++;
    std::cout << "The value of x is: " << x << '\n';
    return 0;
}
```

## UTM

You can use UTM to add a Debian VM to MacOS:

```sh
brew install --cask utm
```

The "Debian 10.4 (Xfce)" image will do: https://mac.getutm.app/gallery/debian-10-4-xfce

You can also use the "Debian 10.4 (Minimal)" image, but it won't allow shared directories (for some reasons unknown to me).

## SSH

First, set up your router to give the BBB a static IP address each time it connects, e.g. `192.168.178.10`.

Then, to `ssh` and `sftp` into the BBB:

```sh
ssh -X debian@192.168.178.10
sftp debian@192.168.178.10
```

To `ssh` into the Debian VM, first forward guest's port `22` to host's port `22022` (or any of your choice).
See: https://getutm.app/guide/#port-forwarding

Then, as before:

```sh
ssh -p 22022 debian@localhost
```

To avoid entering a password each time you ssh into the VM, create an identity key and copy the public one into the VM:

```sh
ssh-keygen

ssh-copy-id -p 22022 debian@localhost
```

All becomes easier when adding aliases to `~/.bashrc`:

```sh
alias ssh-bbb='ssh -X debian@192.168.178.10'
alias sftp-bbb='sftp debian@192.168.178.10'
alias ssh-debianvm='ssh -p 22022 debian@localhost'
alias sftp-debianvm='ssh -P 22022 debian@localhost'
```

If you want to open VSCode into these remote directories, add those lines to your `ssh/config`:

*~/.ssh/config*
```sh
# UTM Debian VM for cross-compiling
Host debianvm
    HostName localhost
    Port 22022
    User debian

# BeagleBone Black
Host beaglebone
    HostName 192.168.178.10
    ForwardX11 yes
    User debian
```

## Shared Directories

It might be useful to have a shared directory between the host-os and the guest-os.

UTM's documentation is quite scarce on the topic: https://mac.getutm.app/guide/#sharing

This comment fills the missing steps: https://github.com/utmapp/UTM/discussions/3755#discussioncomment-2487252

## Shared Directories - Do you really need them?

Working on a project on the VM using shared directories is quite painful.
Much easier, instead, to clone the repo directly in the VM and work from there instead.

You may want to create a separate GitHub token for the VM:

* https://docs.github.com/en/get-started/getting-started-with-git/about-remote-repositories#cloning-with-https-urls
* https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/creating-a-personal-access-token

You may need to import your GPG keys into your VM: https://linuxhint.com/export-import-keys-with-gpg

## Compilation

On the VM, install what's necessary to compile C/C++ programs:

```sh
sudo apt update
sudo apt install build-essential
```

Finally, compile and run your program:

```sh
g++ testprogram.cpp -o testprogram
```

PS. If you want to install a recent enough version of `CMake`, the best option is to build it from source.
See: https://github.com/Kitware/CMake

## Cross-compilation

First, install the toolchain to compile for ARM:

```sh
sudo apt install crossbuild-essential-armhf

# check if it's all good
arm-linux-gnueabihf-g++ -v
```

Then compile using the new toolchain, and put it in the BeagleBoard:

```sh
arm-linux-gnueabihf-g++ testprogram.cpp -o testcross

sftp debian@192.168.178.10
sftp> put testcross
```

You can now execute it from there.

## QEMU on the VM

Install the required tools and update the apt packages:

```sh
sudo apt install qemu-user-static

sudo dpkg --add-architecture armhf
# check if it's all good
dpkg --print-foreign-architectures

sudo apt update
```

Finally compile the program using the `-static` flag (to place the dynamic libraries into the final executable) and run it:

```sh
arm-linux-gnueabihf-g++ -static testprogram.cpp -o statictestcross

qemu-arm-static ./statictestcross
```

Alternatively, without using `-static`, specify the libraries directory:

```sh
arm-linux-gnueabihf-g++ testprogram.cpp -o testcross

qemu-arm-static -L /usr/arm-linux-gnueabihf/ ./testcross
```

## GDB - Setup

On the BeagleBone, install the GDB Server:

```sh
sudo apt install gdbserver
```

On the VM, install the multi-architecture debugger:

```sh
sudo apt install gdb-multiarch
```

## GDB - Debugging Session

On the BeagleBone, run the GDB Server (e.g. on port 12345):

```sh
gdbserver --multi localhost:12345
```

On the VM, compile the program with debug symbols, then put it on the BBB:

```sh
arm-linux-gnueabihf-g++ -g testprogram.cpp -o testcross

sftp debian@192.168.178.10
sftp> put testcross
```

Finally, on the VM, start debugging:

```sh
gdb-multiarch -q testcross

(gdb) set architecture arm
(gdb) target extended 192.168.178.10:12345
(gdb) set remote exec-file testcross
(gdb) break main
(gdb) run
```

On the VM, to avoid repeating the first three GDB commands over and over,
place them in a `.gdbinit` file at `$HOME`:

```
set architecture arm
target extended 192.168.178.10:12345
set remote exec-file testcross
```

## GDB - Debugging Session with VSCode

I didn't manage to properly set it up yet :(
