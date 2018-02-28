# Djinni
Terminal text editor for Linux

# Usage
``` djinni <filename | --version | --help> ```
# Installation
## Prerequisites
* ``` git ```
* ``` clang++ 5.0.1 ```
* ``` ncurses ```, a C library 
* ``` GNU make ```
## Process
1. Download the git repository and cd into it. 

``` git clone https://github.com/YRMYJASKA/Djinni ```

  and

```  cd Djinni```



2. To build Djinni. The executable will be in 'bin/'

``` make install && make ```

3. To launch djinni.

``` bin/djinni ```

# Contributing
## Code
When contributing code please make your commit messages clear and articulate yourself.

**ALL** Source code in C++ should be formatted according to the WebKit format.
See other .cpp files to see how they are structured. Please try and include as much comments as needed but not too much.

## Wiki
See the wiki guidelines [here!](../../wiki)
## Trello
[The Trello board](https://trello.com/b/6fvZ7hgc/djinni-editor)

# License
The Djinni text editor is under MIT license. See it [here](LICENSE)
