#EasyGettext
[![Build Status](https://travis-ci.org/DIG-/easygettext.svg?branch=master)](https://travis-ci.org/DIG-/easygettext)
[![license](https://img.shields.io/badge/license-Apache_2.0-blue.svg)](https://github.com/DIG-/easygettext)

Simple and small library, and without dependencies, who provides gettext functions and support gettext file format.

### Why "Easy" Gettext?

Gettext is an excelent library for translations, available in most of common program languages (C/C++, Java, Python, PHP, etc.), but some problems was found while trying to use C/C++ library, like:

* **Lack of support for _Windows_**

Don't try to compile GNU Gettext library, time for nothing. But to use DLLs you will need 2 or more DLLs only to use gettext. Even for a big project, it increase the total of your project files, increase size, chance of corruption, vulnerability, etc.

Also MinGW does not come up with gettext build. Up to now.

* **Ugly path to search for translations**

For GNU Gettext, all translations need to be in a path like `<folder>/[ll_CC]/LC_MESSAGES/<domain>.mo`.

It isn't possible to change this format, and force 2 directories extras for each translations, while, for a project with all translations in a exclusive location, it is unnecessary.

### What EasyGettext does different?

EasyGettext have the concept to be compilable in _Windows_ and most _Linux_, and does not require any other library to be compiled or executed.

MinGW (GCC) was used to compile for Windows and all releases are from it, but only shared librarys are included, due to support MSVC.

While seaching for translations, EasyGettext will try to find translations in:

* `<path>/[ll_CC].mo`
* `<path>/[ll].mo`

It forces to all translations to be inside only one folder.
If you are familiar with concept of textdomain, since you set the `path`for search, you can bind the textdomain to the `path`.

### How to compile EasyGettext

Nothing more than:
```shell
make
```

If you need to compile manualy, compile these files:
```
src/easy-gettext.c
src/easy-plural.c
```
And enable these macros:
```C
#define _EASY_GETTEXT_COMPILE_TIME_ 1  	// Mandatory
#define EASY_GETTEXT_STATIC 1 			// To create static version
```

### How to import and use EasyGettext

Copy all files inside `include` or set this folder as include path in your project.
Include file `easy-gettext.h` in every file where you will use gettext functions.
If you want to use static EasyGettext, add macro `EASY_GETTEXT_STATIC` before including the header.

If you want to use the global domain for translation, wich is common, you can use `src/example.c` as example.
```C
EG_init("locale","path");
EasyGettext_init(&EasyGettext_default,"locale","path");
```
One of functions above need to be called before any other gettext function. And one of functions below need to be called after all gettext functions and before terminate program.
```C
EG_clean();
EasyGettext_clean(&EasyGettext_default);
```

### How to generate MO and PO files

There is some guides on Internet, but here you will find the basics.

**Note:** *Poedit* and `xgettext` does not expand macro

* **Easy mode**
1. Download and install [*Poedit*](//poedit.net/)(free version under MIT license), available for _Windows_, _Linux_ and _MAC_
2. Create a new translation file.
3. Open the catalog properties.
4. Set the source path as your project source path
5. Add `_`, `EG_`, `EG_N`, `EasyGettext_gettext` and `EasyGettext_ngettext` to `keywords` if you are using these functions in your project.

If you are using only `gettext` and `ngettext`, that last step is unecessary.
Poedit also generates (automaticaly) the binary (MO) file.


* **Hard mode**
You need 3 programs: `xgettext`, `msgfmt` and text editor
1. Call `xgettext -o <output>.po <source_1> <source_2>...`
2. Edit the `<output>.po` file
3. Call `msgfmt -o <output>.mo <input>.po`

Like the 5th step on easy mode, for each function used, add `-k <function>` on `xgettext` command.