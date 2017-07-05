# Mini RC

[![License: MIT](https://img.shields.io/badge/license-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

### Cross-Platform resource compiler for C/C++ projects

`MiniRC` helps you to embed your resources (images, binaries, arhives, etc.) into your C/C++ program's binary output. 

`MiniRC` generates two files (*resources.h* and *resources.c*) with embeded resources and functions to deal with them at runtime.

`MiniRC` is developed under macOS, but is set-up to be highly portable.

# Table of Contents

- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Maintainers](#maintainers)
- [License](#license)

# Prerequisites

To build `minirc` from source you will need `make`, `git` and `gcc`.

# Installation

```
git clone https://github.com/galarius/minirc.git
cd minirc
make && make install
```

# Usage

* `minirc -n resources.rc`  to generate new resources file

* `minirc resources.rc`  to generate `resources.h` and `resources.c` with embeded resources listed in resources.rc

* `minirc -h` to get help  

See [example](example/ReadMe.md) folder for the example of how to use resources.h and resources.c from client code.

# Maintainers
|![](https://avatars1.githubusercontent.com/u/7501085?v=3&u=c884e4a910a24a703eadf9877a2437ae126665c2&s=144)|
|-|
|[@Ilya Shoshin (Galarius)](https://github.com/Galarius)|

# License

MIT License

Copyright (c) 2017 Shoshin Ilya

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

 See the [MIT License](https://choosealicense.com/licenses/mit/) for more details.