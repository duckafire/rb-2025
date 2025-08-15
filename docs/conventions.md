[refact]: https://en.wikipedia.org/wiki/Code_refactoring "What is code refactoring?"

# Conventions

This file has a collection edition conventions to this project.

# Git commits

To follow these conventions, it is necessary divide the commit content correctly.
So, do not to mix the contents (from different contexts) in commits. If the changes
were done in different context, commit them in separated commits. The use of `git stash`
can help with this, try to run `git stash --help` or `man git-stash`.

## Structure

### Overview

#### No description:

```
[CONTEXT: subcontext] Tag ...
```

#### With description:

##### No notes

```
[CONTEXT: subcontext] Tag ...:

1 - Tag ...
2 - Tag ...
  2.1 - Tag ...
  2.N - Tag ...
N - Tag ...
```

##### With notes

```
[CONTEXT: subcontext] Tag ...:

1 - Tag ...
2 - Tag ...
  2.1 - Tag ...
  2.N - Tag ...
N - Tag ...

Lorem lorem lorem ...
```

> [!IMPORTANT]
> The description have to be used to improve the *title* explanation, in addition to
> highlight small changes in the context/sub-context. It must be a list of changes.
> The notes, on the other hand, have to be used to explain (or to give more depth) some
> decision cited in the other commit parts. It must be a (group of) text(s).
> The description must be putted before the notes, unless that a description was not
> used/written.

### Context

> The main location where the changes occur.

| Type    | Description                                                |
| :--     | :--                                                        |
| BUILD   | changes in ./docker/build-files/\*                         |
| COMPOSE | changes in ./docker/compose-files/\*                       |
| SOURCE  | changes in ./src/\*                                        |
| DOCS    | changes in ./docs/\*                                       |
| MISC    | changes in files that it is not included in other Contexts |

> [!NOTE]
> A commit with the addition of the new (sub-)context must be done before of it to be
> commited. In other words, if a new (sub-)context will be created, this file of
> conventions must be updated with the new (sub-)context and then to be commited, before
> the new (sub-)context to be commited/created.

### Subcontext

> The main location, in the Context, where the changes occur.

| Type    | Description                                                    |
| :--     | :--                                                            |
| payment | files related to the Payment Processors.                       |
| checker | files related to the Health Checker.                           |
| shell   | files/scripts used to run Shell command, in or out containers. |
| igfiles | changes in gitignore and/or dockerignore.                      |
| merge   | indicate that a branch was merged with the current branch.     |
| misc    | files that it is not included in other Subcontexts.            |

### Tag

> Indicate the type of change that was done.

| Type        | Description                           |
| :--         | :--                                   |
| Add         | something (new) was implemented.      |
| Change      | a logic change occur.                 |
| Correct     | some no-programming problem was fixed.|
| Fix         | some programming problem was fixed.   |
| Refactoring | the content was [refactored][refact]. |
| Remove      | remove a something from somewhere.    |
| Separate    | indicate that a feature was divided.  |
| Improve     | something was improved.               |
| Update      | something was superficially changed.  |
| Upgrade     | something was depth changed.          |

### Other important things

> Conventions about the construction of the *commit phrase*.

* File names must be between double quotes.
* Identifier names (variables, ...) must be between grave accents.
* Imperative must be used to create the *commit phase* (`...`).
* The *commit phrase* have to be short.
* Prefix sub-lists with an incrementable layer of two spaces.
* Items, in horizontal lists, must be separated (and end) with semicolon.
* Do not create commits with long lines, break them.

> [!TIP]
> When in a terminal, write the *commit text* between simple quotes.

### Commit examples

```
git commit -m '[SOURCE: checker] Fix `sleep` time'
```

```
git commit -m '[COMPOSE: payment] Add new container image (foo):' -m '
"foo" was chosen to improve the network communication
between the "bar" and "BAR" container images, ...'
```

```
git commit -m '[BUILD: checker] Update Dockerfile optimization:' -m '
1 - Separate code that download APT packages: compile tools; libraries;
2 - Add new boot script (bash) "foobar.sh".
3 - Remove unnecessary commentaries.
4 - Improve the order of the commands.'
```

```
git commit -m '[MISC: misc] Update main README:' -m '
1 - Add index list.
2 - Remove unnecessary links.
3 - Add header of links.
4 - Remove HTML code.
5 - Correct grammar errors.

Links difficult the reading of the file content
in not interpreted context, then they was moved
to a header, in the top of the file, that it use
a special Markdown link declaration. TODO: it
have to be replicated in other Markdown files.

HTML will not be used again inside Markdown files,
because it is not widely support by Markdown
interpreters, what difficult the edition of this
type of file.'