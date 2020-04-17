xmchord Changelog
=================

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
