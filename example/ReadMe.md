* Test [image](data/lena.jpg) was embeded into [resources.c](resources.c) with `minirc`

* File [resources.h](resources.h) contains declarations of image data (as array of hex values) and it's length

* At the beginning of [resources.h](resources.h) header there is a declaration of `rc_restore` function which saves the resource in the file system during runtime

* File [example.c](example.c) restores embeded image `data/lena.jpg` to `data/restored.jpg`  

* To build the example: `make && ./build/example`
