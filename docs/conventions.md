[refact]: https://en.wikipedia.org/wiki/Code_refactoring "What is code refactoring?"

# Conventions

This file has a collection of edition conventions to this project.

# Git commits

## Structure

```
\[<context-0>[+<context-N>][: <sub-context-0>[+<sub-context-N>]]\][ <description>][:
1 - <list-item>
2 - <list-item>
  2.1 - <sub-list-item>
  2.2 - <sub-list-item>
3 - <list-item>: <item-0>; [item-1; [item-N;]]
N - <list-item>][

notes-about-x][

notes-about-y]
```

> [!NOTE]
> There is an empty line between the *description list* and the *notes*, and between
> both the *notes*.

## Context

| Type    | Description                                                        |
| :--     | :--                                                                |
| BUILD   | changes in (auxiliary) files used to build of a Docker image.      |
| DOCS    | changes in the documentation files, what it include the *READMEs*. |
| IGFILES | changes in `.gitignore` and/or `.dockerignore`.                    |
| IMAGE   | changes in dependence of the images, except the *SOURCE* content.  |
| SOURCE  | changes in files used to build the project programs.               |
| MISC    | changes in files that it is not included in other Contexts.        |

[//]: # "MISC is the last because its purpose."

> [!NOTE]
> *IGFILES* can be suffixed by a pair of parentesis, that it must contain the
> word(s) added/removed of the ignore-files. Use `+`/`-`, as prefix, to indicate
> that a word was added/removed. Separate different words with commas. Avoid
> to use this "resource" to list a lot of words.

## Sub-context

Any words that can be used to refer one or more specific files, sub-directories, group
of related files or similar. Like *payment*, that it can be used to refer to the compose
files of the payment processors, the volumes of the payment processors, and other.

## Grammar

* Start phrases with the imperative tense.
* Do not write long lines (break them).
* Commit phrases must be direct.
* Names/identifiers highlight:
	* Double quotes to name of files, (sub)directories, and similar.
	* Grave accent to variable, functions, and similar.

> [!TIP]
> When in a terminal, write the *commit input* between **single quotes**, this avoid that
> the shell interpret special characters inside the *commit input*.

## Examples

```
git commit -m '[IMAGE+IGFILE] Create new Docker volume ("foo") for backups'
```

```
git commit -m '[BUILD: payment+checker] Improve compose file:' -m '
1 - Change compose version: x.x -> x.y.
2 - Add new template: foo-template.
3 - Remove unnecessary commentaries.'
```

```
git commit -m '[SOURCE: checker] Upgrade libfoo3.x to libfoo3.y:' -m '
This new version has a lot of bug fixes and improvement
about optimization, what fix the bug cited in the last
commit.'
```
