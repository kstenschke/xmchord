xmchord Changelog
=================

V0.4.2 - Not released yet
-------------------------
* Improve actions that make use of Ctrl+C: Retain previous clipboard content
* Add browser action: Right-CTRL + ◢ + Left - Chromium/Firefox: Focus previous tab, than reload it 
* Add browser action: Right-CTRL + ◢ + Right - Chromium/Firefox: Focus next tab, than reload it 

V0.4.1 - 2021/01/20
-------------------
* Fix action shell scripts style issues (google convention)
* Add shellcheck continuous inspection of action shell scripts to travis config   
* Add "Build tools and Continuous Integration" section into README.md
* Add action: ◢ + ENTER = Click left mouse button three times (select line)
* Actions listing: improve padding between filename, chording identifier and descriptions
* Change Claws Mail action: ◢ + H = Toggle "Hide read messages" (was: "hide read threads")
* Add recognition of held modifier keys (left/right alt, ctrl, shift) 

V0.4.0 - 2021/01/12
-------------------
* Add Claws Mail action: ◢ + F = Open "Search Folder" popup
* Add action: ◢ + W = Hit CTRL + W (close window)
* Add action: ◢ + ' = Output name of application of focused window
* Add Gnome Terminal action: ◢ + Numpad / = Insert 40 empty lines (helpful to separate sections of output)
* Add browser action: ◢ + H = Toggle HTML "view-source" of current URL
* Improve `action` command: Output also amount of actions found  
* Improve `action` command: Extract multiple consecutive comment-lines
* Improve `action` command: Format output more readable  
* Add `help` and `h` command: List and explain available commands
* Improve copy action (◣ + C): Auto-close popup, notify copied string
* Improve ◢ + Up action: add jump to top in gnome-terminal
* Add action: ◢ + $ = Convert selected text to all upper/lower case
* Improve ◢ + Up/Down actions: Fire Ctrl+Home/End in Java-based Applications
* Use special (triangle) characters to symbolize specific buttons within actions' inline comments

V0.3.0 - 2020/12/20
-------------------
* Add options for using specific non-default keyboard device
* Add browser action: ◢ + Backspace = Remove trailing segment from current URL
* Add browser action: ◢ + C = Copy trailing segment of URL
* Change: Use aosd-cat instead of notify-send for notifications
* Improve Gnome Screenshot action ◣ + V: Set feh window always on top
* Remove Evolution Mail actions
* Add Claws Mail action: ◢ + H = Toggle "Hide read threads"
* Change action: ◢ + M = Launch/bring to front Claws Mail

V0.2.1 - 2020/12/13
-------------------
* Autodetect and suggest keyboard device for observation at 1st run of xmchord

V0.2.0 - 2020/12/12
-------------------
* Add keyboard device selection to startup
* Add Chromium/Firefox action: ◢ + D = Duplicate tab
* Add Gnome Screenshot action: ◢ + G = Paste clipboard image into Gimp
* Add Gnome Screenshot action: ◣ + V = Export clipboard image to temporary file and view in feh Image Viewer
* Improve event-code cache: Click w/o chording wasn't mapped correctly / invoked possibly unnecessary file read attempt

V0.1.8 - 2020/12/07
-------------------
* Add Gnome Screenshot action: ◣ + AltGr = Click than hit Esc key

V0.1.7 - 2020/12/04
-------------------
* Add action to type current UNIX timestamp

V0.1.6 - 2020/09/13
-------------------
* Add action to roll-up window sideways

V0.1.5 - 2020/09/06
-------------------
* Add action to toggle keyboard backlight

V0.1.4 - 2020/04/17
-------------------
* Cleanup to more conform w/ code conventions

V0.1.3 - 2020/03/20
-------------------
* Add auto-detection of available keyboard device

V0.1.2 - 2020/03/19
-------------------
* Improve device compatibility: Add fallback to internal keyboard when no external keyboard present

V0.1.1 - 2019/12/06
-------------------
* Change dependency: Default actions now use "notify-send" instead of osd-cat for notifications
* Add Travis CI build config: Compile using clang and gcc, run cppcheck
* Improve: Performance (use initialization lists, narrow-down variable scopes)
* Add zlib/zconf.h header to source

V0.1.0 - 2019/07/16
-------------------
* Add actions to increment/decrement audio volume
* Add actions to type uppercase umlauts (helpful on swiss keyboards)  
* Add browser actions to increment/decrement numeric ending of current url  
* Add emulations of most system-wide ctrl-key combinations  
* Add OSD info to example actions: toggle active window above / sticky, audio volume up / down  
* Improve window arrangement action to work w/ up to three monitors 

V0.0.1 - 2019/04/24
-------------------
* Initial release
