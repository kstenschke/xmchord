xmchord
=======

xmchord is a productivity tool for Linux desktops, that allows binding custom functions to `chording*` events of mouse buttons
and key presses: this way, mouse buttons become additional modifier keys. 

**`*Chording:`** Chording generally means pushing several keys or buttons simultaneously to achieve a result.

xmchord comes with a comprehensive set of example shortcut actions.


## Table of contents

* [What does it do?](#what-does-it-do)
* [Usage and arguments](#usage-and-arguments)
  * [Argument: `debug`](#argument-debug)
  * [Argument: `actions`](#argument-actions)
  * [Argument: `version`](#argument-version)
* [Included shortcut actions](#included-shortcut-actions)
  * [Global actions](#global-actions-not-application-specific)
  * [Application specific actions](#application-specific-actions)
    * [Chromium and Firefox Web-Browser](#chromium-and-firefox-web-browser)
    * [Evolution Email-Client](#evolution-email-client)
    * [Gnome Terminal](#gnome-terminal)
* [Action shell scripting tricks](#action-shell-scripting-tricks)
  * [1. User-specific actions](#1-user-specific-actions)
  * [2. Launching applications and switching windows](#2-launching-applications-and-switching-windows)
  * [3. Triggering window actions](#3-triggering-window-actions)
  * [4. Application specific shortcut actions](4-application-specific-shortcut-actions)
* [Building from source](#building-from-source)
* [Code Convention](#code-convention)
* [Bug Reporting and Feature Requests](#bug-reporting-and-feature-requests)
* [Author and License](#author-and-license)


What does it do?
----------------

xmchord listens for events of mouse buttons pressed together with keyboard keys. When observing a chording event, 
xmchord generates an identifier code for the given combination of button/key presses. If there is a shell script file 
named by the current event code, within xmchord's `actions` directory, it is executed by xmchord than.


Usage and arguments
-------------------

Usage is: `sudo xmchord` 

To ensure read-access to Linux device events, xmchord must be run with root privileges (e.g. via`sudo`).
Action shell scripts that perform user specific tasks, therefor must take care of 
[running on that user's behalf](#1-user-specific-actions).


### Argument: `debug` 

Running `xmchord debug` or  `xmchord d` activates tracing of event codes. While in debug mode, action shell script 
files can be added without having to stop and restart xmchord.

In regular mode, xmchord reduces processing time by indexing which actions are available once during startup.


### Argument: `actions` 

Running `xmchord actions` or `xmchord a` lists all recognized action shell scripts, including their inlined 
description comment (which must be prefixed with `#:`).


### Argument: `version` 

Running `xmchord version` or  `xmchord v` tests if xmchord is available and displays it's version number.


## Included shortcut actions

See files under `bin/actions`

The included shortcut actions are scripted for use with a 
[**Kensiongton Expert Mouse**](https://www.kensington.com/p/products/control/trackballs/expert-mouse-wired-trackball) 
trackball, tested on Linux Mint Cinnamon, but should be compatible or easily adjustable for other devices and Linux 
distributions and desktop environments.

**Please note:** The following third party dependencies must be installed for all the included actions to work:

* [xdotool](https://www.semicomplete.com/projects/xdotool/) - Fake keyboard/mouse input, window management, and more 
* [wmctrl](http://tripie.sweb.cz/utils/wmctrl/) - Command line tool to interact with an EWMH/NetWM compatible X Window Manager
* [osd-cat](https://linux.die.net/man/1/osd_cat) - Display FILE, or standard input, on X screen


## Global actions (not application specific)

**Symbols are:**

◤ ◥ = Top buttons left / right  
◣ ◢ = Bottom buttons left / right

| **Shortcut**               | **Description**                                        |
|----------------------------|--------------------------------------------------------|
| ◤ + ←                      | Move active window to screen left of current           |
| ◤ + →                      | Move active window to screen right of current          |
| ◤ + ◢                      | Jump to next workspace                                 |
| Right Shift + ◤ + ◢        | Jump to previous workspace                             |
| ◣ + ◢                      | Touch bottom-right hot-corner (E.g. expose windows)    |
| &nbsp; &nbsp; ◢ + Esc      | Launch or bring System Monitor to front                |
| &nbsp; &nbsp; ◢ + C        | Launch or bring Chromium to front                      |
| &nbsp; &nbsp; ◢ + D        | Launch or bring DataGrip to front                      |
| &nbsp; &nbsp; ◢ + F        | Launch or bring Firefox to front                       |
| &nbsp; &nbsp; ◢ + K        | Launch or bring Kitematic to front                     |
| &nbsp; &nbsp; ◢ + M        | Launch or bring Evolution mail client to front         |
| &nbsp; &nbsp; ◢ + N        | Launch or bring Nemo file explorer to front            |
| &nbsp; &nbsp; ◢ + P        | Launch or bring Pidgin to front                        |
| &nbsp; &nbsp; ◢ + R        | Toggle active window roll-up state                     |
| &nbsp; &nbsp; ◢ + T        | Toggle active window always-on-top state               |
| &nbsp; &nbsp; ◢ + V        | Toggle active window always-on-visible-workspace state |
| &nbsp; &nbsp; ◢ + ←        | Focus previous tab                                     |
| &nbsp; &nbsp; ◢ + →        | Focus next tab                                         |
| &nbsp; &nbsp; ◢ + ↑        | Scroll to top (same as home key)                       |
| &nbsp; &nbsp; ◢ + ↓        | Scroll to bottom (same as end key)                     |
| &nbsp; &nbsp; ◢ + Numpad 7 | Tile active window to top-left 50% of screen           |
| &nbsp; &nbsp; ◢ + Numpad 8 | Tile active window to top 50% of screen                |
| &nbsp; &nbsp; ◢ + Numpad 9 | Tile active window to top-right 50% of screen          |
| &nbsp; &nbsp; ◢ + Numpad 6 | Tile active window to right 50% of screen              |
| &nbsp; &nbsp; ◢ + Numpad 3 | Tile active window to bottom-right 50% of screen       |
| &nbsp; &nbsp; ◢ + Numpad 2 | Tile active window to bottom 50% of screen             |
| &nbsp; &nbsp; ◢ + Numpad 1 | Tile active window to bottom-left 50% of screen        |
| &nbsp; &nbsp; ◢ + Numpad 4 | Tile active window to left 50% of screen               |
| &nbsp; &nbsp; ◢ + Numpad 5 | Maximize active window                                 |
| ◣ + ↑                      | Increase audio volume                                  |
| ◣ + ↓                      | Decrease audio volume                                  |


## Application specific actions

For these actions to be triggered, a window of the respective application must be focussed when the shortcut is fired.


### Chromium and Firefox Web-Browser

| **Shortcut**        | **Description**                           |
|---------------------|-------------------------------------------|
| ◤ + D               | Show downloads                            |
| ◤ + R               | Reload                                    |
| ◤ + U               | Focus URL field                           |
| &nbsp; &nbsp; ◢ + ← | Go URL backwards                          |
| &nbsp; &nbsp; ◢ + → | Go URL forward                            |
| ◣ + ←               | Focus previous tab (browser and DevTools) |
| ◣ + →               | Focus next tab (browser and DevTools)     |
| ◣ + F4              | Close active tab                          |


### Evolution Email-Client

| **Shortcut**               | **Description**                   |
|----------------------------|-----------------------------------|
| ◣ + A                      | Activate "all messages" filter    |
| ◣ + U                      | Activate "unread messages" filter |


### Gnome Terminal

| **Shortcut**               | **Description**    |
|----------------------------|--------------------|
| ◤                          | Close active tab   |
| ◣ + F                      | Search             |
| ◣ + ←                      | Focus previous tab |
| ◣ + →                      | Focus next tab     |


## Action shell scripting tricks


### 1. User-specific actions 

**Problem:** xmchord runs as root, but most actions need to be run for a specific logged-in user.

E.g. Cinnamon's D-Bus methods require being launched by a specific user. 
The following script switches from root to original user, before triggering the desired method:

```bash
#!/bin/bash
me=$SUDO_USER
sudo -u $me dbus-send --dest=org.Cinnamon --print-reply /org/Cinnamon org.Cinnamon.switchWorkspaceRight
```


### 2. Launching applications and switching windows

Shell scripts can detect whether an application is running already and using e.g. 
[wmctrl](http://tripie.sweb.cz/utils/wmctrl/), bring a respective window onto the active workspace, or launch the 
application.

```bash
#!/bin/bash
if pidof -s evolution > /dev/null; then
    wmctrl -a Evolution
else
    me=$SUDO_USER
    sudo -u $me nohup evolution > /dev/null &
fi
```


### 3. Triggering window actions

Using e.g. [wmctrl](http://tripie.sweb.cz/utils/wmctrl/), shell scripts can switch the active window's roll-up and 
always-on-top state:

```bash
#!/bin/bash
wmctrl -b toggle,shaded -r :ACTIVE:
```


```bash
#!/bin/bash
wmctrl -r :ACTIVE: -b toggle,above
```


### 4. Application specific shortcut actions

Using e.g. [xdotool](https://www.semicomplete.com/projects/xdotool/), shell scripts can detect the currently focused 
window's application, and vary the triggered ActionRunner accordingly.
Xdotool also allows to trigger key-combinations for various shortcuts:

```bash
#!/bin/bash
focusApplication=`cat /proc/$(xdotool getwindowpid $(xdotool getwindowfocus))/comm`
if [[ "$focusApplication" =~ "gnome-terminal-" ]]; then
    xdotool key Control_L+Page_Up
else
    xdotool key shift+ctrl+Tab
fi
```


## Building from source

```bash
cmake CMakeLists.txt; make
```


## Code Convention

The source code of xmchord follows the Google C++ Style Guide,
see: https://google.github.io/styleguide/cppguide.html


## Bug Reporting and Feature Requests

If you find a bug or have an enhancement request, please file an issue on the github repository.


## Author and License

Written by Kay Stenschke.
xmchord is licensed under the [New BSD License](http://opensource.org/licenses/BSD-3-Clause)

> Copyright (c), Kay Stenschke
> All rights reserved.
>
> Redistribution and use in source and binary forms, with or without modification,
> are permitted provided that the following conditions are met:
>
> 1. Redistributions of source code must retain the above copyright notice, this
>    list of conditions and the following disclaimer.
>
> 2. Redistributions in binary form must reproduce the above copyright notice,
>    this list of conditions and the following disclaimer in the documentation
>    and/or other materials provided with the distribution.
>
> 3. Neither the name of the copyright holder nor the names of its contributors
>    may be used to endorse or promote products derived from this software without
>    specific prior written permission.
>
> THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
> ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
> WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
> DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
> ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
> (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
>  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
> ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
> (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
> SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
